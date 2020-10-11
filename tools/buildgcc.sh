#!/bin/bash
# todo: complete this script
# This script will also handle patching gcc/binutils when we start needing to do that

fetch_and_decompress() {
	wget $1
	tar xvf $2
}


