#!/bin/bash

cd /home/vagrant/linux-hevd-tutorial/builder

sh ./Build_HEVD_Vulnerable_x64.sh

sudo insmod /home/vagrant/linux-hevd-tutorial/output/vulnerable/x64/hevd.ko

sudo chmod 777 /dev/hevd

sudo chown vagrant:vagrant /dev/hevd

cd ..
