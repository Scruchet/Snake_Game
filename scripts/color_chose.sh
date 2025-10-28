#!/bin/bash

# Vérifie qu'un argument a été fourni
if [ -z "$1" ]; then
    echo "Error : Invalid format"
    echo "Usage : $0 <valor>"
    exit 1
fi

FILE="../include/constante.hpp"

# Vérifie que le fichier existe
if [ ! -f "$FILE" ]; then
    echo "Error : $FILE file does not exist"
    exit 1
fi

# Remplace la ligne contenant la définition
sed -i "s/^#define COLORFUL_SNAKE .*/#define COLORFUL_SNAKE $1/" "$FILE"

