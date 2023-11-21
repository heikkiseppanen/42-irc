# Meta

NAME := ircserv

SRCDIR := ./src
OBJDIR := ./obj

SRC :=\
	main.cpp\
	ClientDatabase.cpp\
	ChannelDatabase.cpp\
	Channel.cpp

OBJ := $(addprefix $(OBJDIR)/,$(SRC:.cpp=.o))
DEP := $(OBJ:%.o=%.d)

# Compilation 

CPP := c++
CPPFLAGS := -O2 -Wall -Werror -Wextra -std=c++98
LDFLAGS := -std=c++98

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
	/bin/rm $(NAME)

re: fclean all

.PHONY: all clean fclean re debug
