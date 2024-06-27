#!/bin/bash

# Check if the number of directories is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <number_of_directories>"
  exit 1
fi

# Number of directories to split into
num_dirs=$1

# Create the directories
for ((i=1; i<=num_dirs; i++)); do
  mkdir -p "dir$i"
done

# Get the list of PPM files
files=(output_*.ppm)

# Calculate the total number of files and the number of files per directory
total_files=${#files[@]}
files_per_dir=$(( (total_files + num_dirs - 1) / num_dirs )) # Round up

# Move the files to the directories
for ((i=0; i<total_files; i++)); do
  dir_index=$((i / files_per_dir + 1))
  mv "${files[i]}" "dir$dir_index/"
done

