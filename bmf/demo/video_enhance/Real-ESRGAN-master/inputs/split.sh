#!/bin/bash

# Create the directories
mkdir -p dir1 dir2 dir3

# Get the list of PPM files
files=(output_*.ppm)

# Calculate the total number of files and the number of files per directory
total_files=${#files[@]}
files_per_dir=$(( (total_files + 2) / 3 )) # Add 2 for rounding up

# Move the files to the directories
for ((i=0; i<total_files; i++)); do
    if (( i < files_per_dir )); then
        mv "${files[i]}" dir1/
    elif (( i < 2 * files_per_dir )); then
        mv "${files[i]}" dir2/
    else
        mv "${files[i]}" dir3/
    fi
done

