# Define compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -g -O0 -fPIC
INCLUDES = -I/root/workspace/bmf_OSPP/output/bmf/include \
           -I.
LDFLAGS = -L/root/workspace/bmf_OSPP/output/bmf/lib 
LIBS = -lengine -lbmf_module_sdk -lhmp -lpthread 

# Source files
LIB_SRCS = copy_module.cpp
MAIN_SRCS = cpp_demo.cpp

# Object files
LIB_OBJS = $(LIB_SRCS:.cpp=.o)
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)

# Dynamic library
DYNAMIC_LIB = libcopy_module.so

# Default target
all: cpp_demo

# Rule to create each object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDES)

# Rule to create the dynamic library
$(DYNAMIC_LIB): $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -shared -o $@ $^

# Rule to create the executable with dynamic library
cpp_demo: $(MAIN_OBJS) $(DYNAMIC_LIB)
	$(CXX) $(CXXFLAGS) -o $@ $(MAIN_OBJS) -L. -lcopy_module $(LDFLAGS) $(LIBS)

# Clean up build files
clean:
	rm -f $(LIB_OBJS) $(MAIN_OBJS) cpp_demo $(DYNAMIC_LIB)

.PHONY: all clean


# # Rule to create each executable
# cpp_demo: cpp_demo.cpp
# 	$(CXX) $(CXXFLAGS) -o $@ $^ $(INCLUDES) $(LDFLAGS) $(LIBS)


# # Clean up build files
# clean:
# 	rm -f $(TARGETS) 

# .PHONY: all clean