#!/bin/bash
PNAME="./bin/galerkin"

if [ "$#" -ne 4 ]; then
	echo "[ERROR] Illegal number of parameters"
	exit 1
fi

if [ ! -f $PNAME ]; then
	./rebuild_project.sh
fi

valgrind --leak-check=full $PNAME $1 $2 $3 $4
