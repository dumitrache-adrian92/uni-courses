package server

import (
	"context"
	"encoding/json"
	"errors"
	"io-service/logger"
	db "io-service/orm"
	"io-service/proto"
	"net"
	"sort"

	"google.golang.org/grpc"
	"gorm.io/gorm"
)

var log = logger.Log
var client = db.ConnectDB()

func CreateServer() {

	lis, err := net.Listen("tcp", ":50051")
	if err != nil {
		log.Fatalf("Failed to listen: %v", err)
		panic("Failed to start server")
	}
	s := grpc.NewServer()
	proto.RegisterBusinessLogicServer(s, &server{})
	log.Info("Server is running on port 50051")
	if err := s.Serve(lis); err != nil {
		log.Fatalf("failed to serve: %v", err)
		panic("Failed to start server")
	}
}

func (s *server) GetData(ctx context.Context, req *proto.GetDataRequest) (*proto.Reply, error) {
	if req.GetType() == "artist" {
		artist := &db.Artist{}
		if err := client.Preload("Albums").Where("name = ?", req.GetName()).First(artist).Error; err != nil {
			return nil, err
		}
		score, err := CalculateArtistScore(artist.ID)
		if err != nil {
			log.Error("Failed to calculate artist score: ", err)
			return nil, err
		}

		// Create simplified album responses
		var albumResponses []AlbumResponse
		for _, album := range artist.Albums {
			albumResponses = append(albumResponses, AlbumResponse{
				ID:       album.ID,
				Name:     album.Name,
				ArtistID: album.ArtistID,
			})
		}

		// Create artist response
		artistResponse := ArtistResponse{
			ID:     artist.ID,
			Name:   artist.Name,
			Albums: albumResponses,
		}

		response := ScoredArtist{
			Artist: artistResponse,
			Score:  score,
		}

		jsonData, err := json.Marshal(response)
		if err != nil {
			log.Error("Failed to marshal artist data: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   string(jsonData),
		}, nil
	}
	if req.GetType() == "album" {
		album := &db.Album{}
		if err := client.Preload("Songs").Where("name = ?", req.GetName()).First(album).Error; err != nil {
			return nil, err
		}
		score, err := CalculateAlbumScore(album.ID)
		if err != nil {
			log.Error("Failed to calculate album score: ", err)
			return nil, err
		}

		// Create track responses
		var trackResponses []TrackResponse
		for _, song := range album.Songs {
			trackResponses = append(trackResponses, TrackResponse{
				ID:       song.ID,
				Name:     song.Name,
				ArtistID: song.ArtistID,
				AlbumID:  song.AlbumID,
			})
		}

		// Create album response
		albumResponse := AlbumResponse{
			ID:       album.ID,
			Name:     album.Name,
			ArtistID: album.ArtistID,
			Songs:    trackResponses,
		}

		response := ScoredAlbum{
			Album: albumResponse,
			Score: score,
		}

		jsonData, err := json.Marshal(response)
		if err != nil {
			log.Error("Failed to marshal album data: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   string(jsonData),
		}, nil
	}
	if req.GetType() == "track" {
		track := &db.Song{}
		if err := client.Where("name = ?", req.GetName()).First(track).Error; err != nil {
			return nil, err
		}
		score, err := CalculateTrackScore(track.ID)
		if err != nil {
			log.Error("Failed to calculate track score: ", err)
			return nil, err
		}

		trackResponse := TrackResponse{
			ID:       track.ID,
			Name:     track.Name,
			ArtistID: track.ArtistID,
			AlbumID:  track.AlbumID,
		}

		response := ScoredTrack{
			Track: trackResponse,
			Score: score,
		}

		jsonData, err := json.Marshal(response)
		if err != nil {
			log.Error("Failed to marshal track data: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   string(jsonData),
		}, nil
	}
	return &proto.Reply{
		Status: 400,
		Json:   "{ \"message\" : \"Invalid type\" }",
	}, nil
}

func (s *server) PostData(ctx context.Context, req *proto.PostDataRequest) (*proto.Reply, error) {
	if req.GetType() == "artist" {
		artist := &db.Artist{}
		if err := json.Unmarshal([]byte(req.GetJson()), artist); err != nil {
			log.Error("Failed to unmarshal artist data: ", err)
			return nil, err
		}
		if err := client.Create(artist).Error; err != nil {
			log.Error("Failed to create artist: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   "{ \"message\" : \"Artist created successfully\" }",
		}, nil
	}
	if req.GetType() == "album" {
		album := &db.Album{}
		if err := json.Unmarshal([]byte(req.GetJson()), album); err != nil {
			log.Error("Failed to unmarshal album data: ", err)
			return nil, err
		}
		if err := client.Create(album).Error; err != nil {
			log.Error("Failed to create album: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   "{ \"message\" : \"Album created successfully\" }",
		}, nil
	}
	if req.GetType() == "track" {
		song := &db.Song{}
		if err := json.Unmarshal([]byte(req.GetJson()), song); err != nil {
			log.Error("Failed to unmarshal track data: ", err)
			return nil, err
		}
		if err := client.Create(song).Error; err != nil {
			log.Error("Failed to create track: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   "{ \"message\" : \"Track created successfully\" }",
		}, nil
	}

	if req.GetType() == "score" {
		score := &db.UserFeedback{}
		if err := json.Unmarshal([]byte(req.GetJson()), score); err != nil {
			log.Error("Failed to unmarshal score data: ", err)
			return nil, err
		}

		var existing db.UserFeedback
		if err := client.Where("user = ? AND song_id = ?", score.User, score.SongID).First(&existing).Error; err == nil {
			log.Warnf("User %s already scored song %d", score.User, score.SongID)
			return &proto.Reply{
				Status: 409,
				Json:   "{ \"error\" : \"You have already scored this song\" }",
			}, nil
		} else if !errors.Is(err, gorm.ErrRecordNotFound) {
			log.Error("Error checking for existing score: ", err)
			return nil, err
		}
		if err := client.Create(score).Error; err != nil {
			log.Error("Failed to create score: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   "{ \"message\" : \"Score created successfully\" }",
		}, nil
	}

	return &proto.Reply{
		Status: 400,
		Json:   "{ \"message\" : \"Invalid type\" }",
	}, nil
}

func (s *server) DeleteData(ctx context.Context, req *proto.DeleteDataRequest) (*proto.Reply, error) {
	if req.GetType() == "artist" {
		artist := &db.Artist{}
		if err := client.Where("name = ?", req.GetName()).Delete(artist).Error; err != nil {
			log.Error("Failed to delete artist: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   "{ \"message\" : \"Artist deleted successfully\" }",
		}, nil
	}
	if req.GetType() == "album" {
		album := &db.Album{}
		if err := client.Where("name = ?", req.GetName()).Delete(album).Error; err != nil {
			log.Error("Failed to delete album: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   "{ \"message\" : \"Album deleted successfully\" }",
		}, nil
	}
	if req.GetType() == "track" {
		song := &db.Song{}
		if err := client.Where("name = ?", req.GetName()).Delete(song).Error; err != nil {
			log.Error("Failed to delete track: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   "{ \"message\" : \"Track deleted successfully\" }",
		}, nil
	}
	if req.GetType() == "score" {
		var song db.Song
		if err := client.Where("name = ?", req.GetName()).First(&song).Error; err != nil {
			log.Errorf("Song not found: %s", req.GetName())
			return &proto.Reply{
				Status: 404,
				Json:   "{\"error\": \"Song not found\"}",
			}, nil
		}
		score := &db.UserFeedback{}
		if err := client.Where("user = ? AND song_id = ?", req.GetName(), song.ID).Delete(score).Error; err != nil {
			log.Error("Failed to delete score: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   "{ \"message\" : \"Score deleted successfully\" }",
		}, nil
	}
	return &proto.Reply{
		Status: 400,
		Json:   "{ \"message\" : \"Invalid type\" }",
	}, nil
}

func (s *server) PutData(ctx context.Context, req *proto.UpdateDataRequest) (*proto.Reply, error) {
	if req.GetType() == "artist" {
		artist := &db.Artist{}
		if err := json.Unmarshal([]byte(req.GetJson()), artist); err != nil {
			log.Error("Failed to unmarshal artist data: ", err)
			return nil, err
		}
		if err := client.Where("name = ?", req.GetName()).Updates(artist).Error; err != nil {
			log.Error("Failed to update artist: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   "{ \"message\" : \"Artist updated successfully\" }",
		}, nil
	}
	if req.GetType() == "album" {
		album := &db.Album{}
		if err := json.Unmarshal([]byte(req.GetJson()), album); err != nil {
			log.Error("Failed to unmarshal album data: ", err)
			return nil, err
		}
		if err := client.Where("name = ?", req.GetName()).Updates(album).Error; err != nil {
			log.Error("Failed to update album: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   "{ \"message\" : \"Album updated successfully\" }",
		}, nil
	}
	if req.GetType() == "track" {
		song := &db.Song{}
		if err := json.Unmarshal([]byte(req.GetJson()), song); err != nil {
			log.Error("Failed to unmarshal track data: ", err)
			return nil, err
		}
		if err := client.Where("name = ?", req.GetName()).Updates(song).Error; err != nil {
			log.Error("Failed to update track: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   "{ \"message\" : \"Track updated successfully\" }",
		}, nil
	}

	if req.GetType() == "score" {
		var song db.Song
		if err := client.Where("name = ?", req.GetName()).First(&song).Error; err != nil {
			log.Errorf("Song not found: %s", req.GetName())
			return &proto.Reply{
				Status: 404,
				Json:   "{\"error\": \"Song not found\"}",
			}, nil
		}
		score := &db.UserFeedback{}
		if err := json.Unmarshal([]byte(req.GetJson()), score); err != nil {
			log.Error("Failed to unmarshal score data: ", err)
			return nil, err
		}
		if err := client.Where("user = ? AND song_id = ?", score.User, song.ID).Updates(score).Error; err != nil {
			log.Error("Failed to update score: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   "{ \"message\" : \"Score updated successfully\" }",
		}, nil
	}

	return &proto.Reply{
		Status: 400,
		Json:   "{ \"message\" : \"Invalid type\" }",
	}, nil
}

func (s *server) GetStatistics(ctx context.Context, req *proto.GetStatisticsRequest) (*proto.Reply, error) {
	if req.GetType() == "artist" {
		var artists []db.Artist
		if err := client.Preload("Albums").Find(&artists).Error; err != nil {
			log.Error("Failed to get artists: ", err)
			return nil, err
		}
		var rankedArtists []ScoredArtist
		for _, artist := range artists {
			score, err := CalculateArtistScore(artist.ID)
			if err != nil {
				log.Error("Failed to calculate artist score: ", err)
				return nil, err
			}

			// Create simplified album responses
			var albumResponses []AlbumResponse
			for _, album := range artist.Albums {
				albumResponses = append(albumResponses, AlbumResponse{
					ID:       album.ID,
					Name:     album.Name,
					ArtistID: album.ArtistID,
				})
			}

			// Create artist response
			artistResponse := ArtistResponse{
				ID:     artist.ID,
				Name:   artist.Name,
				Albums: albumResponses,
			}

			rankedArtists = append(rankedArtists, ScoredArtist{
				Artist: artistResponse,
				Score:  score,
			})
		}
		sort.Slice(rankedArtists, func(i, j int) bool {
			return rankedArtists[i].Score > rankedArtists[j].Score
		})
		jsonData, err := json.Marshal(rankedArtists)
		if err != nil {
			log.Error("Failed to marshal ranked artists: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   string(jsonData),
		}, nil

	}
	if req.GetType() == "album" {
		var albums []db.Album
		if err := client.Preload("Songs").Find(&albums).Error; err != nil {
			log.Error("Failed to get albums: ", err)
			return nil, err
		}
		var rankedAlbums []ScoredAlbum
		for _, album := range albums {
			score, err := CalculateAlbumScore(album.ID)
			if err != nil {
				log.Error("Failed to calculate album score: ", err)
				return nil, err
			}

			// Create track responses
			var trackResponses []TrackResponse
			for _, song := range album.Songs {
				trackResponses = append(trackResponses, TrackResponse{
					ID:       song.ID,
					Name:     song.Name,
					ArtistID: song.ArtistID,
					AlbumID:  song.AlbumID,
				})
			}

			// Create album response
			albumResponse := AlbumResponse{
				ID:       album.ID,
				Name:     album.Name,
				ArtistID: album.ArtistID,
				Songs:    trackResponses,
			}

			rankedAlbums = append(rankedAlbums, ScoredAlbum{
				Album: albumResponse,
				Score: score,
			})
		}
		sort.Slice(rankedAlbums, func(i, j int) bool {
			return rankedAlbums[i].Score > rankedAlbums[j].Score
		})
		jsonData, err := json.Marshal(rankedAlbums)
		if err != nil {
			log.Error("Failed to marshal ranked albums: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   string(jsonData),
		}, nil
	}
	if req.GetType() == "track" {
		var tracks []db.Song
		if err := client.Find(&tracks).Error; err != nil {
			log.Error("Failed to get tracks: ", err)
			return nil, err
		}
		var rankedTracks []ScoredTrack
		for _, track := range tracks {
			score, err := CalculateTrackScore(track.ID)
			if err != nil {
				log.Error("Failed to calculate track score: ", err)
				return nil, err
			}

			trackResponse := TrackResponse{
				ID:       track.ID,
				Name:     track.Name,
				ArtistID: track.ArtistID,
				AlbumID:  track.AlbumID,
			}

			rankedTracks = append(rankedTracks, ScoredTrack{
				Track: trackResponse,
				Score: score,
			})
		}
		sort.Slice(rankedTracks, func(i, j int) bool {
			return rankedTracks[i].Score > rankedTracks[j].Score
		})
		jsonData, err := json.Marshal(rankedTracks)
		if err != nil {
			log.Error("Failed to marshal ranked tracks: ", err)
			return nil, err
		}
		return &proto.Reply{
			Status: 200,
			Json:   string(jsonData),
		}, nil
	}
	return &proto.Reply{
		Status: 400,
		Json:   "{ \"message\" : \"Invalid type\" }",
	}, nil
}
