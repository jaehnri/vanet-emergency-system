#!/bin/sh

docker exec -it $(docker ps --format '{{.Names}}' | grep x11docker) /root/models/projects/vanet-emergency-system/bin/veins_launchd -vv -c sumo
