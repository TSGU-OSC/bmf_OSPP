# Define compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -g
INCLUDES = -I/root/workspace/bmf_OSPP/output/bmf/include \
           -I/root/workspace/bmf_OSPP/bmf/hml/third_party/gtest/googletest/include
LDFLAGS  = -L/root/workspace/bmf_OSPP/output/bmf/lib \
           -L/root/workspace/bmf_OSPP/bmf/hml/third_party/gtest/build/lib
LIBS 	 = -lbmf_module_sdk -lhmp -lgtest -lgtest_main -lpthread

# Find all cpp files except 
SRCS =  $(filter-out test_convert_backend.cpp test_video_frame.cpp test_audio_frame.cpp test_log_buffer.cpp,  $(wildcard *.cpp))

# Create list of executables
TARGETS = $(SRCS:.cpp=)

# Default target
all: $(TARGETS)

# Rule to create each executable
%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(INCLUDES) $(LDFLAGS) $(LIBS)

# Clean up build files
clean:
	rm -f $(TARGETS)

.PHONY: all clean

