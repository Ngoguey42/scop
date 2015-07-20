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

O_FILES := obj/srcs/main.o \
	obj/srcs/ftmath/matrix4.o \
	obj/srcs/ftmath/matrix4_invtranslate.o \
	obj/srcs/ftmath/matrix4_miscop.o \
	obj/srcs/ftmath/matrix4_rotation.o \
	obj/srcs/ftmath/matrix4_scale.o \
	obj/srcs/ftmath/matrix4_translate.o \
	obj/srcs/ftmath/vector3.o \
	obj/srcs/ftmath/vector3_basicop.o

MSG_0 := printf '\033[0;32m%-38.38s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-38.38s\033[0;0m\n'
MSG_END := printf '\n'

.SILENT:

all: $(LIBS) $(NAME)
.PHONY: all

$(NAME): $(O_FILES)
	@$(MSG_0) $@ ; $(LD_CC) -o $@ $(O_FILES) $(LD_FLAGS) && $(MSG_END) || $(MSG_1) $@

obj/srcs/main.o: srcs/main.c include/fterror.h include/ftmath.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4.o: srcs/ftmath/matrix4.c include/fterror.h include/ftmath.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_invtranslate.o: srcs/ftmath/matrix4_invtranslate.c include/fterror.h include/ftmath.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_miscop.o: srcs/ftmath/matrix4_miscop.c include/fterror.h include/ftmath.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_rotation.o: srcs/ftmath/matrix4_rotation.c include/fterror.h include/ftmath.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_scale.o: srcs/ftmath/matrix4_scale.c include/fterror.h include/ftmath.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_translate.o: srcs/ftmath/matrix4_translate.c include/fterror.h include/ftmath.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/vector3.o: srcs/ftmath/vector3.c include/fterror.h include/ftmath.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/vector3_basicop.o: srcs/ftmath/vector3_basicop.c include/fterror.h include/ftmath.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

$(LIBS):
	@make -C $@
.PHONY: $(LIBS)

clean:
	@rm -f $(O_FILES) 2> /dev/null || true
	@rmdir -p obj/srcs/ftmath obj/srcs $(O_DIR) 2> /dev/null || true
.PHONY: clean

fclean: clean
	@rm -f $(NAME)
.PHONY: fclean

re: fclean all
.PHONY: re
