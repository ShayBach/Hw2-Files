#!/bin/bash

# Find all C files in the current working directory
c_files=$(find . -maxdepth 1 -type f -name "*.c")

# Check if any C files were found
if [ -z "$c_files" ]; then
    echo "No C files found in the current working directory."
    exit 1
fi

# Compile each C file
for file in $c_files; do
    # Extract the filename without extension
    filename=$(basename "$file" .c)
    # Compile the C file
    gcc -g -Wall "$file" -o "$filename".exe 
    
    # Check if compilation was successful
    if [ $? -eq 0 ]; then
        echo "Compilation successful for $file"
    else
        echo "Compilation failed for $file"
    fi
done