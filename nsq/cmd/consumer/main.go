package main

import (
	"encoding/json"
	"log"
	"os"
	"os/signal"
	"syscall"

	"github.com/nsqio/go-nsq"
	"github.com/pkg/errors"
	"github.com/torwig/playground/nsq/messages"
)

func main() {
	nsqAddr := os.Getenv("CONSUMER_NSQLOOKUPD_ADDRESS")
	channel := os.Getenv("CONSUMER_CHANNEL")
	topic := os.Getenv("CONSUMER_TOPIC")

	cfg := nsq.NewConfig()
	consumer, err := nsq.NewConsumer(topic, channel, cfg)
	if err != nil {
		log.Fatalf("failed to create consumer; %s", err)
	}
	defer consumer.Stop()

	handler := &messageHandler{}

	consumer.AddHandler(handler)

	if err := consumer.ConnectToNSQLookupd(nsqAddr); err != nil {
		log.Printf("failed to connect to nsqlookupd: %s", err)
		return
	}

	sigCh := make(chan os.Signal, 1)
	signal.Notify(sigCh, syscall.SIGINT, syscall.SIGTERM)
	<-sigCh
}

type messageHandler struct{}

func (h *messageHandler) HandleMessage(msg *nsq.Message) error {
	if len(msg.Body) == 0 {
		return nil
	}

	var m messages.AnimalAction
	if err := json.Unmarshal(msg.Body, &m); err != nil {
		return errors.Wrap(err, "failed to decode message body")
	}

	log.Printf("received: animal=%s action=%s", m.Animal, m.Action)

	return nil
}
