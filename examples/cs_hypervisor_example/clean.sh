#!/bin/bash

rm -fr bao-baremetal-guest/build
rm -fr bao-baremetal-guest2/build
rm -fr opensbi/build

cd CROSSCON-Hypervisor
make clean
cd ..
