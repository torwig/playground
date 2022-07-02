package main

import (
	"log"
	"os"
	"strings"

	"github.com/gocql/gocql"
	"github.com/scylladb/gocqlx/v2"
	"github.com/scylladb/gocqlx/v2/table"
)

func main() {
	clusterAddresses := os.Getenv("CLIENT_DATABASE_CLUSTER")
	clusterAddrList := strings.Split(clusterAddresses, ",")
	keyspace := os.Getenv("CLIENT_DATABASE_KEYSPACE")
	dbUser := os.Getenv("CLIENT_DATABASE_USER")
	dbPassword := os.Getenv("CLIENT_DATABASE_PASSWORD")

	cluster := gocql.NewCluster(clusterAddrList...)
	cluster.Keyspace = keyspace
	cluster.Authenticator = gocql.PasswordAuthenticator{
		Username: dbUser,
		Password: dbPassword,
	}

	session, err := gocqlx.WrapSession(cluster.CreateSession())
	if err != nil {
		log.Fatalf("failed to wrap database session: %s", err)
	}
	defer session.Close()

	messages := table.New(channelMessages)

	var chMsgs []ChannelMessage
	q := session.Query(messages.Select())
	if err := q.SelectRelease(&chMsgs); err != nil {
		log.Printf("failed to make a query: %s", err)
		return
	}

	for _, u := range chMsgs {
		log.Printf("found message in the database: %v", u)
	}
}

var channelMessages = table.Metadata{
	Name:    "channel_messages",
	Columns: []string{"message_id", "sender_id", "channel_name", "body", "created_at"},
}

type ChannelMessage struct {
	MessageID   string `db:"message_id"`
	SenderID    int64  `db:"sender_id"`
	ChannelName string `db:"channel_name"`
	Body        string `db:"body"`
	CreatedAt   int64  `db:"created_at"`
	Date        string `db:"date"`
}
