#!/usr/bin/env bash

if [ -z "$1" ]; then 
	echo "Directory Is Not Given" 
	exit 1 
fi 

directory="$1" 
if [ ! -d "$directory" ]; then 
	echo "Directory '$directory' not found." 
	exit 1 
fi 

files=$(find "$directory" -type f -name "*.c" -o -name "*.cpp") 
printf "%-40s%-10s \t\t%10s\n\n" "Filename:" "FileSize:" "Lines of Code:" 
for file in $files; do 
	filename=$(basename "$file") 
	size=$(wc --bytes < "$file") 
	loc=$(wc -l < "$file") 
printf "%-40s%-10s\t\t%10s\n\n" "${filename%.*}" "$size" "$loc" 
done
