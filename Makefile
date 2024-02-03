CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic

ifeq ($(OS),Windows_NT)
############################# Windows #################################
	LIB := zprintf.lib
	OS_SRC := os/zwindows.cpp
	DO_FCLEAN := @powershell -Command "If (Test-Path '$(LIB)') { Remove-Item '$(LIB)' -Force }"
define DO_CLEAN 
	@for %%F in ($(OBJ)) do powershell -Command "If (Test-Path '%%F') { Remove-Item '%%F' -Force }"
endef
############################# MacOS ###################################
else
	LIB := zprintf.a
	DO_CLEAN := rm -rf $(OBJ)
	DO_FCLEAN := rm -rf $(LIB)
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		OS_SRC := os/zmacos.cpp
	endif
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

fclean:
	$(DO_CLEAN)
	$(DO_FCLEAN)
	@echo [+] zPrintf has been fcleaned !

clean:
	$(DO_CLEAN)
	@echo [+] zPrintf has been cleaned !



.PHONY: clean
