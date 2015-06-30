#
# scop
#
# Makefile
#

#
# Config
#

# Project name
NAME := scop

# Project directories
DIRS := srcs include

# Obj directory
O_DIR := obj

# Makefiles to call
LIBS := libft

# Number of threads
THREADS := 1

# C compiler
C_CC := clang

# Linking compiler
LD_CC := clang

# C flags
C_FLAGS := -Wall -Wextra -O2 -g

# Linking flags
LD_FLAGS := -L ~/.brew/lib -lglfw3 -L libft -lft -framework OpenGL

# C include flags
C_HEADS := -I include -I libft/includes -I ~/.brew/include

#
# Internal
#

O_FILES := obj/srcs/env_init.o \
	obj/srcs/error.o \
	obj/srcs/ft_glfw_core.o \
	obj/srcs/main.o \
	obj/srcs/shader_create.o \
	obj/srcs/shader_init.o

MSG_0 := printf '\033[0;32m%-24.24s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-24.24s\033[0;0m\n'
MSG_END := printf '\n'

.SILENT:

all: $(LIBS) $(NAME)
.PHONY: all

$(NAME): $(O_FILES)
	@$(MSG_0) $@ ; $(LD_CC) -o $@ $(O_FILES) $(LD_FLAGS) && $(MSG_END) || $(MSG_1) $@

obj/srcs/env_init.o: srcs/env_init.c include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/error.o: srcs/error.c include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ft_glfw_core.o: srcs/ft_glfw_core.c include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/main.o: srcs/main.c include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/shader_create.o: srcs/shader_create.c include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/shader_init.o: srcs/shader_init.c include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

$(LIBS):
	@make -C $@
.PHONY: $(LIBS)

clean:
	@rm -f $(O_FILES) 2> /dev/null || true
	@rmdir -p obj/srcs $(O_DIR) 2> /dev/null || true
.PHONY: clean

fclean: clean
	@rm -f $(NAME)
.PHONY: fclean

re: fclean all
.PHONY: re
