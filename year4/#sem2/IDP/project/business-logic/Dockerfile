FROM golang:1.24.1-alpine

WORKDIR /app

COPY . .
RUN go get . && \
    go build -o business-logic
EXPOSE 8080

CMD ["./business-logic"]