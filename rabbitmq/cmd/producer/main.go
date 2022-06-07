package main

import (
	"context"
	"log"
	"math/rand"
	"os"
	"os/signal"
	"strconv"
	"sync"
	"syscall"
	"time"

	amqp "github.com/rabbitmq/amqp091-go"
)

func init() {
	rand.Seed(time.Now().UnixNano())
}

func main() {
	amqpAddr := os.Getenv("PRODUCER_AMQP_ADDRESS")
	queueName := os.Getenv("PRODUCER_QUEUE_NAME")

	conn, err := amqp.Dial(amqpAddr)
	if err != nil {
		log.Fatalf("failed to connect to AMQP server '%s': %s", amqpAddr, err)
		return
	}
	defer conn.Close()

	ch, err := conn.Channel()
	if err != nil {
		log.Printf("failed to open a channel: %s", err)
		return
	}

	queue, err := ch.QueueDeclare(queueName, true, false, false, false, nil)
	if err != nil {
		log.Printf("failed to declare a queue: %s", err)
		return
	}

	if err := ch.Qos(1, 0, false); err != nil {
		log.Printf("failed to change prefetch count: %s", err)
		return
	}

	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

	var wg sync.WaitGroup
	wg.Add(2)

	go runFanoutExchange(ctx, &wg, conn)

	go func() {
		defer wg.Done()

		ticker := time.NewTicker(5 * time.Second)
		defer ticker.Stop()

		for {
			select {
			case <-ctx.Done():
				return
			case <-ticker.C:
				body := strconv.FormatInt(rand.Int63(), 10)

				m := amqp.Publishing{
					DeliveryMode: amqp.Persistent,
					Timestamp:    time.Now().UTC(),
					ContentType:  "text/plain",
					Body:         []byte(body),
				}

				if err := ch.Publish("", queue.Name, false, false, m); err != nil {
					log.Printf("failed to publish message to queue: %s", err)
					return
				}

				log.Printf("produced: %s", body)
			}
		}
	}()

	sigCh := make(chan os.Signal, 1)
	signal.Notify(sigCh, syscall.SIGINT, syscall.SIGTERM)
	<-sigCh

	cancel()
	wg.Wait()
}

func runFanoutExchange(ctx context.Context, wg *sync.WaitGroup, conn *amqp.Connection) {
	defer wg.Done()

	ch, err := conn.Channel()
	if err != nil {
		log.Printf("failed to create channel for a fanout exchange")
		return
	}

	exchangeName := "current_timestamp"

	err = ch.ExchangeDeclare(exchangeName, "fanout", true, false, false, false, nil)
	if err != nil {
		log.Printf("failed to declare timestamp exchange")
		return
	}

	ticker := time.NewTicker(1 * time.Second)
	defer ticker.Stop()

	for {
		select {
		case <-ctx.Done():
			return
		case t := <-ticker.C:
			body := strconv.FormatInt(t.Unix(), 10)

			p := amqp.Publishing{
				ContentType: "plain/text",
				Body:        []byte(body),
			}

			if err := ch.Publish(exchangeName, "", false, false, p); err != nil {
				log.Printf("failed to publish to exchange '%s': %s", exchangeName, err)
				return
			}

			log.Printf("published timestamp: %s", body)
		}
	}
}
