#!/bin/bash
# Builds host tools (lazy since they're all single file)


# $1 cpp filename
# $2 outname
buildcpptool() {
	echo "Building \"$2\"...";
	g++ -std=c++17 -O3 -ffast-math -march=native -mtune=native $1 -o bin/$2 || echo "Build failed."
	echo "Build succedded."
}

buildcpptool place.cpp place