CC := g++
CXXFLAGS = -std=c++17 -Wall
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %cpp,%o,$(SRCS))
TARGET := Dijstra
all:$(TARGET)
%.o:%.cpp
	$(CC) $(CFLAGS) -c $<
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -rf $(TARGET) *.o