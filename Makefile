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
	obj/srcs/load_texture.o \
	obj/srcs/main.o \
	obj/srcs/mesh_operations.o \
	obj/srcs/program_operations.o \
	obj/srcs/shader_operations.o \
	obj/srcs/controls/controls_apply.o \
	obj/srcs/controls/controls_inputs.o \
	obj/srcs/ftmath/matrix4.o \
	obj/srcs/ftmath/matrix4_invtranslate.o \
	obj/srcs/ftmath/matrix4_miscop.o \
	obj/srcs/ftmath/matrix4_rotation.o \
	obj/srcs/ftmath/matrix4_scale.o \
	obj/srcs/ftmath/matrix4_translate.o \
	obj/srcs/ftmath/vector3.o \
	obj/srcs/ftmath/vector3_basicop.o \
	obj/srcs/objmodel/obj_parsing.o \
	obj/srcs/objmodel/obj_parsing_multiple_units.o \
	obj/srcs/objmodel/obj_parsing_unique_units.o \
	obj/srcs/objmodel/objmodel_operations.o \
	obj/srcs/textures/mapping_xy.o \
	obj/srcs/tga/parse_tga.o \
	obj/srcs/uniforms/item_uniforms.o \
	obj/srcs/uniforms/tex_uniforms.o

MSG_0 := printf '\033[0;32m%-46.46s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-46.46s\033[0;0m\n'
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

obj/srcs/load_texture.o: srcs/load_texture.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/main.o: srcs/main.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/mesh_operations.o: srcs/mesh_operations.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/program_operations.o: srcs/program_operations.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/shader_operations.o: srcs/shader_operations.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/controls/controls_apply.o: srcs/controls/controls_apply.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs/controls 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/controls/controls_inputs.o: srcs/controls/controls_inputs.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs/controls 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4.o: srcs/ftmath/matrix4.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_invtranslate.o: srcs/ftmath/matrix4_invtranslate.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_miscop.o: srcs/ftmath/matrix4_miscop.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_rotation.o: srcs/ftmath/matrix4_rotation.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_scale.o: srcs/ftmath/matrix4_scale.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_translate.o: srcs/ftmath/matrix4_translate.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/vector3.o: srcs/ftmath/vector3.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/vector3_basicop.o: srcs/ftmath/vector3_basicop.c include/config.h include/ftmath.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing.o: srcs/objmodel/obj_parsing.c include/config.h include/ftmath.h include/objmodel_parsing.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs/objmodel 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing_multiple_units.o: srcs/objmodel/obj_parsing_multiple_units.c include/config.h include/ftmath.h include/objmodel_parsing.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs/objmodel 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing_unique_units.o: srcs/objmodel/obj_parsing_unique_units.c include/config.h include/ftmath.h include/objmodel_parsing.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs/objmodel 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/objmodel_operations.o: srcs/objmodel/objmodel_operations.c include/config.h include/ftmath.h include/objmodel_parsing.h include/scop.h include/scop_structs.h
	@mkdir -p obj/srcs/objmodel 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/textures/mapping_xy.o: srcs/textures/mapping_xy.c include/config.h include/ftmath.h include/objmodel_parsing.h include/scop.h include/scop_structs.h include/texture_mapping.h
	@mkdir -p obj/srcs/textures 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/tga/parse_tga.o: srcs/tga/parse_tga.c include/config.h include/ftmath.h include/objmodel_parsing.h include/scop.h include/scop_structs.h include/texture_mapping.h
	@mkdir -p obj/srcs/tga 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/uniforms/item_uniforms.o: srcs/uniforms/item_uniforms.c include/config.h include/ftmath.h include/objmodel_parsing.h include/scop.h include/scop_structs.h include/texture_mapping.h
	@mkdir -p obj/srcs/uniforms 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/uniforms/tex_uniforms.o: srcs/uniforms/tex_uniforms.c include/config.h include/ftmath.h include/objmodel_parsing.h include/scop.h include/scop_structs.h include/texture_mapping.h
	@mkdir -p obj/srcs/uniforms 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

$(LIBS):
	@make -C $@
.PHONY: $(LIBS)

clean:
	@rm -f $(O_FILES) 2> /dev/null || true
	@rmdir -p obj/srcs/uniforms obj/srcs/tga obj/srcs/textures obj/srcs/objmodel obj/srcs/ftmath obj/srcs/controls obj/srcs $(O_DIR) 2> /dev/null || true
.PHONY: clean

fclean: clean
	@rm -f $(NAME)
.PHONY: fclean

re: fclean all
.PHONY: re
