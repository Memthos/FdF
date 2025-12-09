SRCS_DIR=sources/
OBJS_DIR=objects/
HEADERS=headers/
SRCS=fdf.c
OBJS=$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
LIBFT_DIR=libs/libft_rework/
LIBFT=$(addprefix $(LIBFT_DIR), libft.a)
MACROLIBX_DIR=libs/MacroLibX/
MACROLIBX=$(addprefix $(MACROLIBX_DIR), libmlx.so)
CFLAGS=-Wall -Wextra -Werror -I$(HEADERS) -lSDL2
CC=cc
NAME=fdf

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MACROLIBX)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "Finished compiling FdF"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@echo "Compiling sources..."
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(LIBFT):
	@make -sC $(LIBFT_DIR) all
	@echo "Compiled library Libft"

$(MACROLIBX):
	@make -sC $(MACROLIBX_DIR) all
	@echo "Compiled library MinilibX"

clean:
	@rm -drf $(OBJS_DIR)
	@make -sC $(LIBFT_DIR) clean
	@make -sC $(MACROLIBX_DIR) clean
	@echo "Cleaned FdF object files"


fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFT_DIR) fclean
	@make -sC $(MACROLIBX_DIR) fclean
	@echo "Cleaned FdF"


re: fclean all
	@echo "Recompiled FdF"

.PHONY: all clean fclean re