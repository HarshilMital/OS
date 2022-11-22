#!/bin/bash
cd /root/new_kernel3/new_kernel/linux-5.19.9 && make mrproper
cp /root/new_kernel/linux-5.19.9/.config /root/new_kernel3/new_kernel/linux-5.19.9
cd /root/new_kernel3/new_kernel/linux-5.19.9 && make