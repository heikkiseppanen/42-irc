# Meta

NAME := ircserv

SRCDIR := ./src
OBJDIR := ./obj

SRC :=\
	main.cpp\
	ClientDatabase.cpp\
	Server.cpp\
	EventSystem.cpp\
	EventHandler.cpp\
	Socket.cpp\
	ChannelDatabase.cpp\
	Channel.cpp\
	Client.cpp\
	Reply.cpp\
	CommandParser.cpp

OBJ := $(addprefix $(OBJDIR)/,$(SRC:.cpp=.o))
DEP := $(OBJ:%.o=%.d)

# Compilation 

CPP := c++
CPPFLAGS := -O2 -Wall -Werror -Wextra -std=c++17
LDFLAGS := -std=c++17

# Rules

all: $(NAME) 

debug: CPPFLAGS+= -g -fsanitize=address,undefined
debug: LDFLAGS+= -g -fsanitize=address,undefined
debug: $(NAME) 

$(NAME): $(OBJ)
	$(CPP) -o $(NAME) $(OBJ) $(LDFLAGS)

# Include dependency info
-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@$(shell [ ! -d $(@D) ] && mkdir -p $(@D))
	$(CPP) $(CPPFLAGS) -MMD -c $< -o $@ 

clean:
	/bin/rm -rf $(OBJDIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug

test:
	@make -C testsrc
	@echo "------------RUNNING TESTS------------"
	@./testsrc/test
	@make fclean -C testsrc
