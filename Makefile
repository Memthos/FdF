CC=cc
CFLAGS=-Wall -Wextra -Werror -I$(HEADERS) -g
VPATH=srcs
OBJS_DIR=objs/
HEADERS=includes/
SRCS=fdf.c file_checks.c hooks.c line_draw.c parser.c quit.c transforms.c \
	utils.c
SRCS_BONUS=fdf_bonus.c file_checks_bonus.c hooks_bonus.c line_draw_bonus.c \
	parser_bonus.c projections_bonus.c quit_bonus.c transforms_bonus.c \
	utils_bonus.c
OBJS=$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS_BONUS=$(addprefix $(OBJS_DIR), $(SRCS_BONUS:.c=.o))
LIBFT_DIR=libs/libft_tools/
LIBFT=$(addprefix $(LIBFT_DIR), libft.a)
MACROLIBX_DIR=libs/MacroLibX/
MACROLIBX=$(addprefix $(MACROLIBX_DIR), libmlx.so)
NAME=fdf

all: $(OBJS_DIR).manda

$(OBJS_DIR).manda: $(OBJS) $(LIBFT) $(MACROLIBX)
	@rm -f $(OBJS_DIR).bonus $(NAME)
	@$(CC) $(CFLAGS) -lSDL2 -lm -o $(NAME) $^
	@touch $(OBJS_DIR).manda
	@echo "Finished compiling FdF"

bonus: $(OBJS_DIR).bonus

$(OBJS_DIR).bonus: $(OBJS_BONUS) $(LIBFT) $(MACROLIBX)
	@rm -f $(OBJS_DIR).manda $(NAME)
	@$(CC) $(CFLAGS) -lSDL2 -lm -o $(NAME) $^
	@touch $(OBJS_DIR).bonus
	@echo "Finished compiling FdF bonuses"

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

.PHONY: all clean fclean re bonus
