#!/bin/sh
whom="$USER"
printf "Hello, %s %s \n" "$whom" "$1"
echo "How to address you? Mr./Ms." 
read pre
echo "Thanks, $pre $1! \n"
