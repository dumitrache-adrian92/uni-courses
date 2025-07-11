package main

import (
	"business-logic/logger"
	"business-logic/routes"

	"github.com/gin-gonic/gin"
	log "github.com/sirupsen/logrus"
)

func setupRouter() *gin.Engine {
	r := gin.New()
	r.SetTrustedProxies([]string{})
	r.Use(gin.Recovery())
	r.Use(gin.Logger())
	r.Use(gin.ErrorLogger())
	r.GET("/api/artist/:name", routes.GetArtistByName)
	r.GET("/api/album/:name", routes.GetAlbumByName)
	r.GET("/api/track/:name", routes.GetTrackByName)
	r.GET("/api/top/artists", routes.GetAllArtistsRanked)
	r.GET("/api/top/albums", routes.GetAllAlbumsRanked)
	r.GET("/api/top/tracks", routes.GetAllTracksRanked)
	protected := r.Group("/api", routes.JWTMiddleware())
	{
		protected.POST("/artist", routes.PostArtist)
		protected.POST("/album", routes.PostAlbum)
		protected.POST("/track", routes.PostTrack)

		protected.DELETE("/artist/:name", routes.DeleteArtistByName)
		protected.DELETE("/album/:name", routes.DeleteAlbumByName)
		protected.DELETE("/track/:name", routes.DeleteTrackByName)

		protected.PUT("/artist/:name", routes.PutArtistByName)
		protected.PUT("/album/:name", routes.PutAlbumByName)
		protected.PUT("/track/:name", routes.PutTrackByName)

		protected.POST("/score", routes.PostScore)
		protected.DELETE("/score/:name", routes.DeleteScoreByName)
		protected.PUT("/score/:name", routes.PutScoreByName)
	}

	return r
}

func main() {
	logger.InitLogger()
	log.Info("Starting business logic server...")
	r := setupRouter()
	if err := r.Run(":8080"); err != nil {
		panic("Failed to start server: " + err.Error())
	}
}
