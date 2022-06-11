package main

import (
	"log"
	"os"
	"os/signal"
	"strconv"
	"syscall"

	"github.com/nats-io/nats.go"
)

func main() {
	serverAddr := os.Getenv("RECEIVER_NATS_ADDRESS")
	subject := os.Getenv("RECEIVER_SUBJECT")

	client, err := nats.Connect(serverAddr)
	if err != nil {
		log.Fatalf("failed to connect to nats server: %s", err)
	}
	defer client.Close()

	sub, err := client.Subscribe(subject, processReceivedMessage)
	if err != nil {
		log.Printf("failed to subscribe for subject '%s': %s", subject, err)
		return
	}

	log.Printf("subscribed to: %s", subject)

	sigCh := make(chan os.Signal, 1)
	signal.Notify(sigCh, syscall.SIGINT, syscall.SIGTERM)
	<-sigCh

	if err := sub.Unsubscribe(); err != nil {
		log.Printf("failed to unsubscribe from subject '%s': %s", subject, err)
		return
	}

	if err := sub.Drain(); err != nil {
		log.Printf("failed to drain: %s", err)
	}
}

func processReceivedMessage(msg *nats.Msg) {
	log.Printf("got from '%s': %s", msg.Subject, string(msg.Data))
	n, err := strconv.ParseInt(string(msg.Data), 10, 64)
	if err != nil {
		log.Printf("failed to parse integer value: %s", err)
		return
	}

	if err := msg.Respond([]byte(strconv.FormatInt(n+1, 10))); err != nil {
		log.Printf("failed to respond: %s", err)
	}
}
