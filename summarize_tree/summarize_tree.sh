#!/bin/bash -x

targetDir="$1"

numDir="$(find "$targetDir" -type d | wc -l | tr -d ' ')"
numFiles="$(find "$targetDir" -not -type d | wc -l | tr -d ' ')"
echo "There were $numDir directories."
echo "There were $numFiles regular files."