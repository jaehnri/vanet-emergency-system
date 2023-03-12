#!/bin/sh

docker exec -it $(docker ps --format '{{.Names}}' | grep x11docker) sh
