CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic

############################# Windows #################################
ifeq ($(OS),Windows_NT)
	LIB := zprintf.lib
	OS_SRC := os/zwindows.cpp
############################# MacOS ###################################
else ifeq ($(shell uname -s), Darwin)
	LIB := zprintf.a
	OS_SRC := os/zmacos.cpp
endif
########################################################################
SRC := zprintf.cpp
OBJ := $(SRC:.cpp=.o) $(OS_SRC:.cpp=.o)
$(LIB): $(OBJ)
	@ar rcs $@ $^
	@echo [+] zPrintf Successfully Compiled!

%.o: %.cpp
	@echo [-] Compiling: $<
	@$(CC) $(CFLAGS) -c -o $@ $<

fclean: clean
ifeq ($(OS),Windows_NT)
	@powershell -Command "If (Test-Path '$(LIB)') { Remove-Item '$(LIB)' -Force }"
else ifeq ($(shell uname -s), Darwin)
	@rm -rf $(LIB)
endif

clean:
ifeq ($(OS),Windows_NT)
	@for %%F in ($(OBJ)) do powershell -Command "If (Test-Path '%%F') { Remove-Item '%%F' -Force }"
else ifeq ($(shell uname -s), Darwin)
	@rm -rf $(OBJ)
endif
	@echo [+] zPrintf has been Cleaned !


.PHONY: clean
