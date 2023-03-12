#!/bin/sh

cd ../../..
x11docker -i --sudouser -- --rm -v "$(pwd):/root/models" -u "$(id -u):$(id -g)" -- brunopec/veins:v4.7.1-o5.6.2-s1.8.0
