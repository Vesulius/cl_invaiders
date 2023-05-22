CC = g++
CPPFLAGS = -std=c++17 -Wall -Wextra -pedantic -march=native
LDFLAGS = -lncurses
SRC_DIR = src
INC_DIR = src/include

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

main: $(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) -I$(INC_DIR) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(OBJS) main
