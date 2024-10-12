CXX = g++

BIN := main.exe
SRC := src/main.cpp

CPPFLAGS := -O3 -Wall -Wextra -pthread -std=c++17

.PHONY: build run clean

$(BIN): build

build:
	$(CXX) $(CPPFLAGS) -o $(BIN) $(SRC)

run: $(BIN)
	$<

clean:
	$(RMDIR) $(OBJ)