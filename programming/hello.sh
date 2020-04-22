#!/usr/bin/env bash
# Note that spaces cannot be used around the `=` assignment operator
whom_variable="$USER"
# Use printf to safely output the data
printf "Hello, user: %s\n" "$whom_variable"
#empty line not allowed
#print out the first command line argument
printf "the first command line argument is: %s\n" "$1"
read -p $'Enter your name: \n' 
echo "Welcome, $REPLY !"