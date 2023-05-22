CC = g++
CPPFLAGS = -std=c++17 -Wall -Wextra
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


# CPPFLAGS = -std=c++17 -Wall -Wextra -pedantic -march=native

# # Environment variable containing the names of headers that will be used
# # with most executables. Without this, make will not know to recompile
# # binaries when headers change.
# HEADERS = src/include/*

# SOURCE = ./src/main.cpp

# # A fake rule that tells make to not expect to actually create files 
# # called "clean" or "debug".
# .PHONY: clean debug

# main: $(SOURCE) $(HEADERS)
# 	g++ $(CPPFLAGS) -Ofast -o main main.cpp -lncurses

# clean:
# 	rm -f main

# debug: $(SOURCE) $(HEADERS)
# 	g++ $(CPPFLAGS) -g -D DEBUG -o main main.cpp -lncurses

# %.hpp:
