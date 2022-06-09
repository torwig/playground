**How to run RabbitMQ Streams example**

For RabbitMQ server:

`docker run -it --rm --name rabbitmq -p 5552:5552 -p 15672:15672 -e RABBITMQ_SERVER_ADDITIONAL_ERL_ARGS='-rabbitmq_stream advertised_host localhost -rabbit loopback_users "none"' rabbitmq:3.9-management`

`docker exec rabbitmq rabbitmq-plugins enable rabbitmq_stream_management`

For producer:

`cd cmd/streams/producer`

`go build .`

`export PRODUCER_STREAM_HOST=localhost`
`export PRODUCER_STREAM_PORT=5552`
`export PRODUCER_STREAM_USER=guest`
`export PRODUCER_STREAM_PASSWORD=guest`
`export PRODUCER_STREAM_NAME=example_stream`
`./producer`

For consumer:

`cd cmd/streams/consumer`

`go build .`

`export CONSUMER_STREAM_HOST=localhost`

`export CONSUMER_STREAM_PORT=5552`

`export CONSUMER_STREAM_USER=guest`

`export CONSUMER_STREAM_PASSWORD=guest`

`export CONSUMER_STREAM_NAME=example_stream`

`export CONSUMER_NAME=consumer1`

`./consumer`
