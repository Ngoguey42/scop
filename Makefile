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

O_FILES := obj/srcs/env_operations.o \
	obj/srcs/error.o \
	obj/srcs/glfw_operations.o \
	obj/srcs/main.o \
	obj/srcs/matrix4.o \
	obj/srcs/matrix4_misc.o \
	obj/srcs/matrix4_rotation.o \
	obj/srcs/matrix4_scale.o \
	obj/srcs/matrix4_translate.o \
	obj/srcs/model_operations.o \
	obj/srcs/obj_parsing.o \
	obj/srcs/obj_parsing_matching.o \
	obj/srcs/program_operations.o \
	obj/srcs/shader_operations.o

MSG_0 := printf '\033[0;32m%-31.31s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-31.31s\033[0;0m\n'
MSG_END := printf '\n'

.SILENT:

all: $(LIBS) $(NAME)
.PHONY: all

$(NAME): $(O_FILES)
	@$(MSG_0) $@ ; $(LD_CC) -o $@ $(O_FILES) $(LD_FLAGS) && $(MSG_END) || $(MSG_1) $@

obj/srcs/env_operations.o: srcs/env_operations.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/error.o: srcs/error.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/glfw_operations.o: srcs/glfw_operations.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/main.o: srcs/main.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/matrix4.o: srcs/matrix4.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/matrix4_misc.o: srcs/matrix4_misc.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/matrix4_rotation.o: srcs/matrix4_rotation.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/matrix4_scale.o: srcs/matrix4_scale.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/matrix4_translate.o: srcs/matrix4_translate.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/model_operations.o: srcs/model_operations.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/obj_parsing.o: srcs/obj_parsing.c include/config.h include/ftmath.h include/obj_parsing.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/obj_parsing_matching.o: srcs/obj_parsing_matching.c include/config.h include/ftmath.h include/obj_parsing.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/program_operations.o: srcs/program_operations.c include/config.h include/ftmath.h include/obj_parsing.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/shader_operations.o: srcs/shader_operations.c include/config.h include/ftmath.h include/obj_parsing.h include/scop.h include/scop_structs.h
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
