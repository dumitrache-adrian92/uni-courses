package server

import (
	"io-service/proto"
)

type server struct {
	proto.UnimplementedBusinessLogicServer
}

// TrackResponse is a simplified track representation
type TrackResponse struct {
	ID       uint   `json:"id"`
	Name     string `json:"name"`
	ArtistID uint   `json:"artistId"`
	AlbumID  *uint  `json:"albumId,omitempty"`
}

// AlbumResponse is a simplified album representation without the Artist field
type AlbumResponse struct {
	ID       uint            `json:"id"`
	Name     string         `json:"name"`
	ArtistID uint           `json:"artistId"`
	Songs    []TrackResponse `json:"songs,omitempty"`
}

// ArtistResponse is the artist representation with simplified albums
type ArtistResponse struct {
	ID     uint            `json:"id"`
	Name   string         `json:"name"`
	Albums []AlbumResponse `json:"albums,omitempty"`
}

type ScoredArtist struct {
	Artist ArtistResponse `json:"artist"`
	Score  float64       `json:"score"`
}

type ScoredAlbum struct {
	Album AlbumResponse `json:"album"`
	Score float64      `json:"score"`
}

type ScoredTrack struct {
	Track TrackResponse `json:"track"`
	Score float64      `json:"score"`
}
