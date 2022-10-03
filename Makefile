# Executable names:
EXE = main
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o

CPP_FILES += $(wildcard src/graph/*.cpp)
CPP_FILES += $(wildcard src/algorithms/dfs/*.cpp)
CPP_FILES += $(wildcard src/algorithms/dijkstra/*.cpp)
CPP_FILES += $(wildcard src/algorithms/stronglyConnected/*.cpp)
CPP_FILES += $(wildcard src/AnalyzeGraphs.cpp)
OBJS += $(CPP_FILES:.cpp=.o)

include cs225/make/cs225.mk
