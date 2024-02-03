CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic

SRC := zprintf.cpp
LIB := zprintf.a

# --- Select the right OS ---
OS_SRC := 
ifeq ($(OS),Windows_NT)
    OS_SRC := os/zwindows.cpp
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        OS_SRC := os/zmacos.cpp
    endif
endif
# ----------------------------
CYAN="\033[1;36m"
GREEN="\033[1;32m"
ENDCOLOR="\033[0m"
CLEANING := $(GREEN)[+] Cleaning Completed$(ENDCOLOR)
SUCCESS := $(GREEN)[+] ZPRINTF Successfully Compiled!$(ENDCOLOR)
# ----------------------------

OBJ := $(SRC:.cpp=.o) $(OS_SRC:.cpp=.o)

$(LIB): $(OBJ)
	@ar rcs $@ $^
	@echo $(SUCCESS)

%.o: %.cpp
	@echo $(CYAN)[-] Compiling: $<$(ENDCOLOR)
	@$(CC) $(CFLAGS) -c -o $@ $<

fclean: clean
	@rm -rf $(LIB)

clean:
	@rm -f $(OBJ)
	@echo $(CLEANING)

.PHONY: clean
