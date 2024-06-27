# !/bin/bash

# Start time measurement
start_time=$(date +%s)

python3.8 inference_realesrgan.py -n realesr-animevideov3 -i dir1 --fp32 &
python3.8 inference_realesrgan.py -n realesr-animevideov3 -i dir2 --fp32 &
python3.8 inference_realesrgan.py -n realesr-animevideov3 -i dir3 --fp32 &

# Wait for both background processes to finish
wait

# End time measurement
end_time=$(date +%s)

# Calculate the elapsed time
elapsed_time=$((end_time - start_time))

# Print the elapsed time
echo "Total elapsed time: $elapsed_time seconds"
