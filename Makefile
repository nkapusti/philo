NAME = philo 
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC_PATH = src/
OBJ_PATH = objs/

SRC = 	philo.c \
		utils.c \
		init.c \
		exit.c \
		philosopher.c \
		output.c \
		time.c \
		monitor.c \
		
		
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INC = -I ./includes/

all: $(NAME)
				
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "Done!🥳"

clean:
	@rm -rf $(OBJ_PATH)
	@echo "Objects removed!👍"

fclean: clean
	@rm -f $(NAME)
	@echo "Philo deleted!😱"

re: fclean all

run: re
	./philo 5 200 120 100 

.PHONY: all re clean fclean
