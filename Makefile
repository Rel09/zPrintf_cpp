CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic
SRC := zprintf.cpp

# ------ Windows ------
ifeq ($(OS),Windows_NT)
	LIB := zPrintf_cpp.lib
	OS_SRC := os/zwindows.cpp

# ------- MacOS -------
else ifeq ($(shell uname -s), Darwin)
	LIB := zPrintf_cpp.a
	OS_SRC := os/zmacos.cpp
endif

# ------- Colors -------
PINK="\033[1;35m"
DARKPINK="\033[0;35m"
ENDCOLOR="\033[0m"

# ---- Compilation -----

OBJ := $(SRC:.cpp=.o) $(OS_SRC:.cpp=.o)
$(LIB): $(OBJ)
	@ar rcs $@ $^
	@echo $(DARKPINK)[+] zPrintf Successfully Compiled!$(ENDCOLOR)

%.o: %.cpp
	@echo $(PINK)[+] Compiling: $<$(ENDCOLOR)
	@$(CC) $(CFLAGS) -c -o $@ $<

fclean: clean
	@rm -rf $(LIB)

clean:
	@rm -rf $(OBJ)
	@echo $(DARKPINK)[+] zPrintf has been Cleaned !$(ENDCOLOR)

.PHONY: clean
