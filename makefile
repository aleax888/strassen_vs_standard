CXX = g++
CXXFLAGS = -O3 -flto -std=c++17 -Wall -Wextra
TARGET = build/exe

SRCS = \
    src/benchmark/main.cpp \
    src/benchmark/insertion_sort.cpp \
    src/benchmark/merge_sort.cpp \
    src/benchmark/data_generation.cpp \
    src/benchmark/benchmark_sorts.cpp

OBJS = $(SRCS:src/benchmark/%.cpp=build/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

build/%.o: src/benchmark/%.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build
