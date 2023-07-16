CC = gcc
FLAGS = -Wall -Werror -Wextra

# part 1 - Mandatory (LIBC FUNCTIONS)
LIBC_IS = ft_isalnum.c ft_isascii.c ft_isprint.c ft_isdigit.c ft_isalpha.c
LIBC_MEM = ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c 
LIBC_TO = ft_toupper.c ft_tolower.c ft_atoi.c
LIBC_STR = ft_strchr.c ft_strrchr.c ft_strlen.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c 
LIBC_STR_MEM = ft_strdup.c ft_calloc.c
LIBC = ${LIBC_IS} ${LIBC_MEM} ${LIBC_TO} ${LIBC_STR} ${LIBC_STR_MEM}

# part 2 - Mandatory (ADDC FUNCTIONS)
ADDC_STR_MEM = ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c 
ADDC_STR_MEM_ITER = ft_strmapi.c 
ADDC_STR_ITER = ft_striteri.c
ADDC_TO_MEM = ft_itoa.c
ADDC_PUT = ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
ADDC = ${ADDC_STR_MEM} ${ADDC_STR_MEM_ITER} ${ADDC_STR_ITER} ${ADDC_TO_MEM} ${ADDC_PUT}

GNL = get_next_line.c get_next_line_utils.c
SRCS = $(LIBC) $(ADDC) $(GNL)
OBJS = $(SRCS:.c=.o)

# bonus part
BONUS_ADDC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
BONUS_SRCS = $(BONUS_ADDC)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

NAME = libft.a
RM = rm -rf

# any file ending in .o depends on the same filename ending in .c
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)


# main commands
all: $(NAME)

bonus : $(NAME) $(BONUS_OBJS)
	ar -rcs $(NAME) $(BONUS_OBJS)

# clean & re 
clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# norm
check:
	@echo "\n";
	@norminette -R CheckForbiddenSourceHeader ft_*.c *.h;
	@echo "----------------------";

.PHONY : all clean fclean re check
