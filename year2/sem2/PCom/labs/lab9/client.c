#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

int main(int argc, char *argv[])
{
    char *message;
    char *response;
    int sockfd;

    // Ex 1.1: GET dummy from main server
    message = compute_get_request("34.254.242.81", "/api/v1/dummy", NULL, NULL, 0);
    sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);

    printf("%s\n\n", response);

    free(message);
    free(response);
    // Ex 1.2: POST dummy and print response from main server
    char **body_data = malloc(sizeof(char *) * 100);
    for (int i = 0; i < 100; i++)
        body_data[i] = malloc(LINELEN);

    strcpy(body_data[0], "test");
    message = compute_post_request("34.254.242.81", "/api/v1/dummy", "application/x-www-form-urlencoded", body_data, 1, NULL, 0);
    send_to_server(sockfd, message);

    response = receive_from_server(sockfd);

    printf("%s\n\n", response);

    free(message);
    free(response);

    // Ex 2: Login into main server
    strcpy(body_data[0], "username=student&password=student");
    message = compute_post_request("34.254.242.81", "/api/v1/auth/login", "application/x-www-form-urlencoded", body_data, 1, NULL, 0);
    send_to_server(sockfd, message);

    response = receive_from_server(sockfd);

    printf("%s\n\n", response);

    free(message);
    free(response);

    // Ex 3: GET weather key from main server
    strcpy(body_data[0], "connect.sid=s%3AsiVYiRwEMALWS_E9CabVu00hTFjmjqIk.9IgxZQ4bfKVoxx7TD5JHRYBQbtYm71KAEqPv9OmxRjI; Path=/; HttpOnly");
    message = compute_get_request("34.254.242.81", "/api/v1/weather/key", NULL, body_data, 1);
    send_to_server(sockfd, message);

    response = receive_from_server(sockfd);

    printf("%s\n\n", response);

    free(message);
    free(response);

    // Ex 4: GET weather data from OpenWeather API
    int openweathermap = open_connection("82.196.7.246", 80, AF_INET, SOCK_STREAM, 0);
    if (openweathermap < 0)
        error("ERROR opening socket");

    message = compute_get_request("api.openweathermap.org", "/data/2.5/forecast", "q=Bucharest&APPID=b912dd495585fbf756dc6d8f415a7649", NULL, 0);
    send_to_server(sockfd, message);

    response = receive_from_server(sockfd);

    printf("%s\n\n", response);

    free(message);
    free(response);

    // Ex 5: POST weather data for verification to main server
    // Ex 6: Logout from main server

    // BONUS: make the main server return "Already logged in!"

    // free the allocated data at the end!
    for (int i = 0; i < 100; i++)
        free(body_data[i]);
    free(body_data);
    return 0;
}
