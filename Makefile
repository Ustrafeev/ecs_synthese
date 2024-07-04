##
## EPITECH PROJECT, 2024
## synthese
## File description:
## Makefile
##

CC = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++20 -g3 -I ./include
LDFLAGS =

SRC_DIR = ./src
SRC := $(wildcard $(SRC_DIR)/*.cpp)  $(wildcard $(SRC_DIR)/**/*.cpp)

BUILDDIR = ./obj
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC))

EXEC = ecs

ECHO = echo -e
RED = \033[0;31m\033[1m
GREEN = \033[0;32m\033[1m
WHITE = \033[1;37m\033[1m
NC = \033[0m

$(BUILDDIR)/%.o: $(SRC_DIR)/%.cpp
	@$(ECHO) "$(WHITE)[BUILD CORE]$(NC)"
	@mkdir -p $(dir $@)
	$(CC) -o $@ -MD -c $< $(CXXFLAGS)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)


clean :
	@$(ECHO) "$(WHITE)[CLEAN]$(NC)"
	rm -rf $(BUILDDIR)
fclean : clean
	@$(ECHO) "$(WHITE)[FCLEAN]$(NC)"
	rm -rf $(EXEC)

re: fclean all

-include $(OBJ:%.o=%.d)

.PHONY: clean fclean re
