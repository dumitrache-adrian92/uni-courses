package server

import (
	orm "io-service/orm"
)

func CalculateArtistScore(artistID uint) (float64, error) {
	var songs = []orm.Song{}

	if err := client.Preload("Feedback").Where("artist_id = ?", artistID).Find(&songs).Error; err != nil {
		return 0, err
	}

	var totalScore int
	var count int

	for _, song := range songs {
		for _, fb := range song.Feedback {
			totalScore += fb.Score
			count++
		}
	}

	if count == 0 {
		return 0, nil
	}

	return float64(totalScore) / float64(count), nil
}

func CalculateAlbumScore(albumID uint) (float64, error) {
	var songs = []orm.Song{}

	if err := client.Preload("Feedback").Where("album_id = ?", albumID).Find(&songs).Error; err != nil {
		return 0, err
	}

	var totalScore int
	var count int

	for _, song := range songs {
		for _, fb := range song.Feedback {
			totalScore += fb.Score
			count++
		}
	}

	if count == 0 {
		return 0, nil
	}

	return float64(totalScore) / float64(count), nil
}

func CalculateTrackScore(trackID uint) (float64, error) {
	var track orm.Song
	if err := client.Preload("Feedback").Where("id = ?", trackID).First(&track).Error; err != nil {
		return 0, err
	}

	var totalScore int
	var count int

	for _, fb := range track.Feedback {
		totalScore += fb.Score
		count++
	}

	if count == 0 {
		return 0, nil
	}

	return float64(totalScore) / float64(count), nil
}
