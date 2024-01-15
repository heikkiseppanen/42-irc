# Tests

NAME := test

SRCDIR := ./
OBJDIR := ./testobj

SRC :=\
	tests.cpp\
	t_client.cpp\
	t_clientDB.cpp\
	t_channelDB.cpp\
	t_channel.cpp\
	t_eventhandler.cpp

OBJ := $(addprefix $(OBJDIR)/,$(SRC:.cpp=.o))
DEP := $(OBJ:%.o=%.d)

MAINSRC :=\
	ClientDatabase.cpp\
	Server.cpp\
	EventSystem.cpp\
	EventHandler.cpp\
	Socket.cpp\
	ChannelDatabase.cpp\
	Channel.cpp\
	Client.cpp

MAINSRCDIR := ../src

MAINOBJ := $(addprefix $(OBJDIR)/,$(MAINSRC:.cpp=.o))

CPP := c++
CPPFLAGS := -O2 -Wall -Werror -Wextra -std=c++11
LDFLAGS := -std=c++11

all: $(NAME)

$(NAME): $(MAINOBJ) $(OBJ)
	@$(CPP) -o $(NAME) $(OBJ) $(MAINOBJ) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@$(shell [ ! -d $(@D) ] && mkdir -p $(@D))
	@$(CPP) $(CPPFLAGS) -I ../src -c $< -o $@

$(OBJDIR)/%.o: $(MAINSRCDIR)/%.cpp
	@$(shell [ ! -d $(@D) ] && mkdir -p $(@D))
	@$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug