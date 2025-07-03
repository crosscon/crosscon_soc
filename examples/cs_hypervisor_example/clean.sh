#!/bin/bash

rm -fr baremetal-guest/build
rm -fr baremetal-guest2/build
rm -fr opensbi/build

(cd CROSSCON-Hypervisor && make clean)
