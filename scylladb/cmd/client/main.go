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

	usersTable := table.New(usersTableMetadata)

	var users []User
	q := session.Query(usersTable.Select())
	if err := q.SelectRelease(&users); err != nil {
		log.Printf("failed to make a query: %s", err)
		return
	}

	for _, u := range users {
		log.Printf("found user in database: %v", u)
	}
}

var usersTableMetadata = table.Metadata{
	Name:    "users",
	Columns: []string{"user_id", "fname", "lname"},
}

type User struct {
	ID        int64  `db:"user_id"`
	FirstName string `db:"fname"`
	LastName  string `db:"lname"`
}
