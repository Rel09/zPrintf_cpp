CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic

# Windows
# If you run this on windows, make sure you use another terminal (git bash for example)
ifeq ($(OS),Windows_NT)
	LIB := zPrintf_cpp.lib
	OS_SRC := os/zwindows.cpp
# MacOS
else ifeq ($(shell uname -s), Darwin)
	LIB := zPrintf_cpp.a
	OS_SRC := os/zmacos.cpp
endif

SRC := zprintf.cpp
OBJ := $(SRC:.cpp=.o) $(OS_SRC:.cpp=.o)
$(LIB): $(OBJ)
	@ar rcs $@ $^
	@echo [+] zPrintf Successfully Compiled!

%.o: %.cpp
	@echo [+] Compiling: $<
	@$(CC) $(CFLAGS) -c -o $@ $<

fclean: clean
	@rm -rf $(LIB)

clean:
	@rm -rf $(OBJ)
	@echo [+] zPrintf has been Cleaned !

.PHONY: clean
