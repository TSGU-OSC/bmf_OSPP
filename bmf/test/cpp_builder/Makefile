# Define compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -g
INCLUDES = -I/root/workspace/bmf_OSPP/output/bmf/include \
           -I/root/workspace/bmf_OSPP/bmf/hml/third_party/gtest/googletest/include \
		   -I/root/workspace/bmf_OSPP/bmf/engine/c_engine/include \
		   -I/root/workspace/bmf_OSPP/output/bmf/include/nlohmann
LDFLAGS = -L/root/workspace/bmf_OSPP/output/bmf/lib \
          -L/root/workspace/bmf_OSPP/bmf/hml/third_party/gtest/build/lib
LIBS = -lengine -lbmf_module_sdk -lhmp -lgtest -lgtest_main -lpthread 

# Find all cpp files except call_back_for_test.cpp
SRCS = $(filter-out cpp_test_helper.cpp, $(wildcard *.cpp))

# Create list of executables
TARGETS = $(SRCS:.cpp=)

# Default target
all: $(TARGETS)

# Rule to create each executable
%: %.cpp cpp_test_helper.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(INCLUDES) $(LDFLAGS) $(LIBS)

# Compile call_back_for_test.cpp into object file
cpp_test_helper.o: cpp_test_helper.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGETS) cpp_test_helper.o

.PHONY: all clean