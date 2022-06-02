Redis Pub/Sub example with Go.

Every second publisher generates a random number and publishes it to `even_numbers` or `odd_numbers` channel.

Each of two subscribers subscribes to a single Redis channel (`even_numbers` or `odd_numbers`), gets numbers and logs them out.

**Build**

`docker-compose build`

**Run**

`docker-compose up`
