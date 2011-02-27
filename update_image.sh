#!/bin/bash

sudo /sbin/losetup /dev/loop0 floppy.img
sudo mount /dev/loop0 /media/loop0
sudo cp src/kernel /media/loop0/kernel
sleep 1
sudo umount /dev/loop0
sudo /sbin/losetup -d /dev/loop0
