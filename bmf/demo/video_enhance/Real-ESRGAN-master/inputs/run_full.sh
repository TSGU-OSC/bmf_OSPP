#!/bin/bash

# Check if the number of Python processes is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <number_of_processes>"
  exit 1
fi

# Number of Python processes to run
num_processes=$1

# Start time measurement
start_time=$(date +%s)

# Run the specified number of Python processes
for ((i=1; i<=num_processes; i++)); do
  python3.8 inference_realesrgan.py -n realesr-animevideov3 -i "dir$i" --fp32 &
done

# Wait for all background processes to finish
wait

# End time measurement
end_time=$(date +%s)

# Calculate the elapsed time
elapsed_time=$((end_time - start_time))

# Print the elapsed time
echo "Total elapsed time: $elapsed_time seconds"

