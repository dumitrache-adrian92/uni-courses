package main

import (
	"os"

	"github.com/gin-gonic/gin"
	"github.com/supabase-community/gotrue-go/types"
	"github.com/supabase-community/supabase-go"
)

var (
	API_KEY = os.Getenv("SUPABASE_API_KEY")
	API_URL = os.Getenv("SUPABASE_API_URL")
)

type RegisterUser struct {
	Email    string `json:"email" binding:"required,email"`
	Username string `json:"username" binding:"required"`
	Password string `json:"password" binding:"required"`
}

type LoginUser struct {
	Email    string `json:"email" binding:"required,email"`
	Password string `json:"password" binding:"required"`
}

func SetupRouter() *gin.Engine {
	r := gin.Default()
	client, err := supabase.NewClient(API_URL, API_KEY, &supabase.ClientOptions{
		Headers: map[string]string{},
	})
	if err != nil {
		panic("Failed to create Supabase client: " + err.Error())
	}
	var auther = client.Auth

	r.POST("/auth/signup", func(c *gin.Context) {
		var user RegisterUser
		if err := c.ShouldBindJSON(&user); err != nil {
			c.JSON(400, gin.H{"error": "Missing or invalid fields", "details": err.Error()})
			return
		}

		_, err := auther.Signup(types.SignupRequest{
			Email:    user.Email,
			Password: user.Password,
			Data: map[string]any{
				"username": user.Username,
			},
		})
		if err != nil {
			c.JSON(500, gin.H{"error": "Signup failed", "details": err.Error()})
			return
		}

		c.JSON(200, gin.H{"message": "User signed up successfully"})
	})

	r.POST("/auth/login", func(c *gin.Context) {
		var user LoginUser
		if err := c.ShouldBindJSON(&user); err != nil {
			c.JSON(400, gin.H{"error": "Missing or invalid fields", "details": err.Error()})
			return
		}

		session, err := auther.SignInWithEmailPassword(user.Email, user.Password)
		if err != nil {
			c.JSON(500, gin.H{"error": "Login failed", "details": err.Error()})
			return
		}
		c.JSON(200, gin.H{"message": "User logged in successfully", "access_token": session.Session.AccessToken})
	})

	return r
}

func main() {
	r := SetupRouter()
	if err := r.Run(":8080"); err != nil {
		panic("Failed to start server: " + err.Error())
	}
}
