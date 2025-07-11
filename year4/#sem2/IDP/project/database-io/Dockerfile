FROM golang:1.24.1-alpine

WORKDIR /app

COPY . .
RUN go get . && \
    go build -o io-service
EXPOSE 50051

CMD ["./io-service"]