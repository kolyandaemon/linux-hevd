#!/bin/sh

sudo yum -y  update

sudo yum makecache

sudo sh /home/vagrant/scripts/cmake.sh --prefix=/usr/local  --exclude-subdir --skip-license

sudo yum install -y kernel-devel ncurses-devel make gcc bc bison flex elfutils-libelf-devel openssl-devel grub2 wget rpm-build vim

sudo yum install -y epel-release python36

 pip3.6 install --upgrade pip

sudo reboot
