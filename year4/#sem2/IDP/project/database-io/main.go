package main

import (
	"io-service/logger"
	db "io-service/orm"
	"io-service/server"
)

func main() {
	logger.InitLogger()
	log := logger.Log

	log.Info("Initializing database connection...")
	client := db.ConnectDB()
	client.AutoMigrate(&db.Artist{}, &db.Album{}, &db.Song{}, &db.UserFeedback{})

	log.Info("Starting server...")
	server.CreateServer()
}
