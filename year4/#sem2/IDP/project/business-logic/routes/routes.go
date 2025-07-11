package routes

import (
	"business-logic/client"
	"business-logic/logger"
	"business-logic/proto"
	"context"
	"encoding/json"
	"net/http"
	"time"

	"github.com/gin-gonic/gin"
)

var rpc_client = client.GetClient()
var log = logger.Log

func GetArtistByName(c *gin.Context) {
	artistName := c.Param("name")
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	out, err := rpc_client.GetData(ctx, &proto.GetDataRequest{
		Type: "artist",
		Name: artistName,
	})
	if err != nil {
		log.Errorf("Error while getting artists: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}

	c.JSON(int(out.Status), result)
}
func GetAlbumByName(c *gin.Context) {
	albumName := c.Param("name")
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	out, err := rpc_client.GetData(ctx, &proto.GetDataRequest{
		Type: "album",
		Name: albumName,
	})
	if err != nil {
		log.Errorf("Error while getting albums: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}

	c.JSON(int(out.Status), result)
}
func GetTrackByName(c *gin.Context) {
	trackName := c.Param("name")
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	out, err := rpc_client.GetData(ctx, &proto.GetDataRequest{
		Type: "track",
		Name: trackName,
	})
	if err != nil {
		log.Errorf("Error while getting tracks: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}

	c.JSON(int(out.Status), result)
}

func PostArtist(c *gin.Context) {
	jsonData, err := c.GetRawData()
	if err != nil {
		log.Errorf("Error while reading request body: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	out, err := rpc_client.PostData(ctx, &proto.PostDataRequest{
		Type: "artist",
		Json: string(jsonData),
	})
	if err != nil {
		log.Errorf("Error while posting artists: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}
	c.JSON(int(out.Status), result)
}

func PostAlbum(c *gin.Context) {
	jsonData, err := c.GetRawData()
	if err != nil {
		log.Errorf("Error while reading request body: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	out, err := rpc_client.PostData(ctx, &proto.PostDataRequest{
		Type: "album",
		Json: string(jsonData),
	})
	if err != nil {
		log.Errorf("Error while posting albums: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}
	c.JSON(int(out.Status), result)
}
func PostTrack(c *gin.Context) {
	jsonData, err := c.GetRawData()
	if err != nil {
		log.Errorf("Error while reading request body: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	out, err := rpc_client.PostData(ctx, &proto.PostDataRequest{
		Type: "track",
		Json: string(jsonData),
	})
	if err != nil {
		log.Errorf("Error while posting tracks: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}
	c.JSON(int(out.Status), result)
}

func PostScore(c *gin.Context) {
	username := c.GetString("username")
	jsonData, err := c.GetRawData()
	if err != nil {
		log.Errorf("Error while reading request body: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	var body map[string]interface{}
	if err := json.Unmarshal(jsonData, &body); err != nil {
		log.Errorf("Invalid JSON body: %v", err)
		c.JSON(400, gin.H{"error": "Invalid JSON"})
		return
	}
	body["username"] = username
	jsonData, _ = json.Marshal(body)
	out, err := rpc_client.PostData(ctx, &proto.PostDataRequest{
		Type: "score",
		Json: string(jsonData),
	})
	if err != nil {
		log.Errorf("Error while posting score: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}
	c.JSON(int(out.Status), result)
}

func DeleteArtistByName(c *gin.Context) {
	artistName := c.Param("name")
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	out, err := rpc_client.DeleteData(ctx, &proto.DeleteDataRequest{
		Type: "artist",
		Name: artistName,
	})
	if err != nil {
		log.Errorf("Error while deleting artists: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}

	c.JSON(int(out.Status), result)
}
func DeleteAlbumByName(c *gin.Context) {
	albumName := c.Param("name")
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	out, err := rpc_client.DeleteData(ctx, &proto.DeleteDataRequest{
		Type: "album",
		Name: albumName,
	})
	if err != nil {
		log.Errorf("Error while deleting albums: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}

	c.JSON(int(out.Status), result)
}
func DeleteTrackByName(c *gin.Context) {
	trackName := c.Param("name")
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	out, err := rpc_client.DeleteData(ctx, &proto.DeleteDataRequest{
		Type: "track",
		Name: trackName,
	})
	if err != nil {
		log.Errorf("Error while deleting tracks: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}

	c.JSON(int(out.Status), result)
}

func DeleteScoreByName(c *gin.Context) {
	scoreName := c.Param("name")
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	out, err := rpc_client.DeleteData(ctx, &proto.DeleteDataRequest{
		Type: "score",
		Name: scoreName,
	})
	if err != nil {
		log.Errorf("Error while deleting score: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}

	c.JSON(int(out.Status), result)
}

func PutArtistByName(c *gin.Context) {
	artistName := c.Param("name")
	jsonData, err := c.GetRawData()
	if err != nil {
		log.Errorf("Error while reading request body: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	out, err := rpc_client.UpdateData(ctx, &proto.UpdateDataRequest{
		Type: "artist",
		Name: artistName,
		Json: string(jsonData),
	})
	if err != nil {
		log.Errorf("Error while putting artists: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}
	c.JSON(int(out.Status), result)
}

func PutAlbumByName(c *gin.Context) {
	albumName := c.Param("name")
	jsonData, err := c.GetRawData()
	if err != nil {
		log.Errorf("Error while reading request body: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	out, err := rpc_client.UpdateData(ctx, &proto.UpdateDataRequest{
		Type: "album",
		Name: albumName,
		Json: string(jsonData),
	})
	if err != nil {
		log.Errorf("Error while putting albums: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}
	c.JSON(int(out.Status), result)
}
func PutTrackByName(c *gin.Context) {
	trackName := c.Param("name")
	jsonData, err := c.GetRawData()
	if err != nil {
		log.Errorf("Error while reading request body: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	out, err := rpc_client.UpdateData(ctx, &proto.UpdateDataRequest{
		Type: "track",
		Name: trackName,
		Json: string(jsonData),
	})
	if err != nil {
		log.Errorf("Error while putting tracks: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}
	c.JSON(int(out.Status), result)
}

func PutScoreByName(c *gin.Context) {
	username := c.GetString("username")
	scoreName := c.Param("name")
	jsonData, err := c.GetRawData()
	if err != nil {
		log.Errorf("Error while reading request body: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	var body map[string]interface{}
	if err := json.Unmarshal(jsonData, &body); err != nil {
		log.Errorf("Invalid JSON body: %v", err)
		c.JSON(400, gin.H{"error": "Invalid JSON"})
		return
	}
	body["username"] = username
	jsonData, _ = json.Marshal(body)
	out, err := rpc_client.UpdateData(ctx, &proto.UpdateDataRequest{
		Type: "score",
		Name: scoreName,
		Json: string(jsonData),
	})
	if err != nil {
		log.Errorf("Error while putting score: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}
	c.JSON(int(out.Status), result)
}

func GetAllArtistsRanked(c *gin.Context) {
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	out, err := rpc_client.GetStatistics(ctx, &proto.GetStatisticsRequest{
		Type: "artist",
	})
	if err != nil {
		log.Errorf("Error while getting all artists: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}

	c.JSON(int(out.Status), result)
}

func GetAllAlbumsRanked(c *gin.Context) {
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	out, err := rpc_client.GetStatistics(ctx, &proto.GetStatisticsRequest{
		Type: "album",
	})
	if err != nil {
		log.Errorf("Error while getting all albums: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}

	c.JSON(int(out.Status), result)
}

func GetAllTracksRanked(c *gin.Context) {
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()
	out, err := rpc_client.GetStatistics(ctx, &proto.GetStatisticsRequest{
		Type: "track",
	})
	if err != nil {
		log.Errorf("Error while getting all tracks: %v", err)
		c.JSON(500, gin.H{"error": "Internal Server Error"})
		return
	}
	var result any
	err = json.Unmarshal([]byte(out.Json), &result)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Invalid JSON from gRPC"})
		return
	}

	c.JSON(int(out.Status), result)
}
