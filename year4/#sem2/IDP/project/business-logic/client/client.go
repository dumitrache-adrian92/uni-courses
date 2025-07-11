package client

import (
	"business-logic/logger"
	"business-logic/proto"
	"fmt"
	"os"

	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

var client proto.BusinessLogicClient
var log = logger.Log
var serverAddress = os.Getenv("SERVER_ADDRESS")

func GetClient() proto.BusinessLogicClient {
	if client == nil {
		conn, err := grpc.NewClient(
			fmt.Sprintf("%s:50051", serverAddress),
			grpc.WithTransportCredentials(insecure.NewCredentials()),
		)
		if err != nil {
			log.Fatalf("failed to connect: %v", err)
		}
		log.Info("Connected to server")
		client = proto.NewBusinessLogicClient(conn)
	}
	return client
}
