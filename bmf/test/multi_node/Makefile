# Define compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -g
INCLUDES = -I/root/workspace/bmf_OSPP/output/bmf/include \
		   -I/root/workspace/bmf_OSPP/bmf/engine/c_engine/include \
		   -I/root/workspace/bmf_OSPP/output/bmf/include/nlohmann
LDFLAGS = -L/root/workspace/bmf_OSPP/output/bmf/lib 
LIBS = -lengine -lbmf_module_sdk -lhmp -lpthread 

# Find all cpp files except call_back_for_test.cpp
#SRCS = $(wildcard *.cpp)

# Create list of executables
#TARGETS = $(SRCS:.cpp=)

# Default target
#all: $(TARGETS)

# Rule to create each executable
cpp_demo: cpp_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(INCLUDES) $(LDFLAGS) $(LIBS)


# Clean up build files
clean:
	rm -f $(TARGETS) 

.PHONY: all clean