CC=gcc
CFLAGS=-Wall -Wextra -Werror -I$(HEADERS) -g
VPATH=sources
OBJS_DIR=objs/
HEADERS=includes/
SRCS=fdf.c map_01.c map_02.c close.c utils.c line_draw.c
OBJS=$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
LIBFT_DIR=libs/libft_tools/
LIBFT=$(addprefix $(LIBFT_DIR), libft.a)
MACROLIBX_DIR=libs/MacroLibX/
MACROLIBX=$(addprefix $(MACROLIBX_DIR), libmlx.so)
NAME=fdf

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MACROLIBX)
	@$(CC) $(CFLAGS) -lSDL2 -lm -o $@ $^
	@echo "Finished compiling FdF"

$(OBJS_DIR)%.o: %.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(LIBFT):
	@make -sC $(LIBFT_DIR) all
	@echo "Compiled library Libft"

$(MACROLIBX):
	@make -sC $(MACROLIBX_DIR) all -j
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
