CXX = g++
TARGET = run
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))
CFLAGS =
LDFLAGS = -lm

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	-rm -rf $(TARGET)
	-rm -rf $(OBJ)

