#!/bin/sh

build() {
    make clean && make && cp quadcopter /usr/sbin/
    cp quadcopter.service /etc/systemd/system/
    systemctl enable quadcopter.service
}

build
