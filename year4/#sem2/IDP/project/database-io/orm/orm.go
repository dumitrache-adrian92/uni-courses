package db

import (
	"fmt"
	"io-service/logger"
	"os"

	"gorm.io/driver/postgres"
	"gorm.io/gorm"
)

var (
	host     = os.Getenv("DB_HOST")
	user     = os.Getenv("DB_USER")
	password = os.Getenv("DB_PASSWORD")
	log      = logger.Log
)

var db *gorm.DB = nil

func ConnectDB() *gorm.DB {
	if db != nil {
		return db
	}
	dsn := fmt.Sprintf("host=%s user=%s password=%s dbname=postgres port=5432 sslmode=disable TimeZone=Europe/Bucharest",
		host, user, password)
	client, err := gorm.Open(postgres.Open(dsn), &gorm.Config{})
	if err != nil {
		panic("Failed to connect to database")
	}
	log.Info("Connected to database")
	db = client
	return db
}
