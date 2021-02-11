#!/bin/bash

if [ "$DAZZLE_INIT" == "y" ]; then
	echo "Dazzle was already initalized in this shell.."
	exit 0;
fi

export DAZZLE_INIT="y";
export ToolsDir="$PWD/tools"
export PATH="${ToolsDir}/bin:${PATH}";

# Set the OS arch.
export OS_ARCH="x86"

export DAZZLE_SYSROOT="$PWD/sysroot";

if [ ! -d "$DAZZLE_SYSROOT" ]; then
	echo "Dazzle: Creating system root."
	mkdir -p $DAZZLE_SYSROOT
fi

# Indicate we're in a Dazzle shell.
export PS1="Dazzle ${PS1}"
