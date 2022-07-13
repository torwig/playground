package main

import (
	"context"
	"log"
	"os"
	"os/signal"
	"sync"
	"syscall"

	"github.com/go-redis/redis/v8"
)

func main() {
	addr := os.Getenv("REDIS_ADDR")

	if addr == "" {
		log.Printf("set environmental variable REDIS_ADDR")
		return
	}

	rdb := redis.NewClient(&redis.Options{
		Addr: addr,
	})

	if err := rdb.Ping(context.Background()).Err(); err != nil {
		log.Printf("failed to ping redis: %s", err)
		return
	}
	defer rdb.Close()

	sigint := make(chan os.Signal, 10)
	signal.Notify(sigint, syscall.SIGINT, syscall.SIGTERM)

	var wg sync.WaitGroup
	wg.Add(1)

	lastReadID := "0"

	go func() {
		defer wg.Done()

		for {
			select {
			case <-sigint:
				return
			default:
				res, err := rdb.XRead(context.Background(), &redis.XReadArgs{
					Streams: []string{"test-stream", lastReadID},
					Count:   100,
					Block:   1000,
				}).Result()
				if err != nil {
					log.Printf("failed to read from the stream: %s", err)
					continue
				}

				for _, s := range res {
					for _, m := range s.Messages {
						log.Printf("received %s entry", m.ID)
						lastReadID = m.ID
					}
				}
			}
		}
	}()

	wg.Wait()
}
