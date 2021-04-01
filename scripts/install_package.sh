#!/bin/sh

sudo yum update

sudo yum makecache

sudo sh /home/vagrant/scripts/cmake.sh --prefix=/usr/local  --exclude-subdir --skip-license
