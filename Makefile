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
	obj/srcs/program_operations.o \
	obj/srcs/configuration/conf.o \
	obj/srcs/configuration/mesh_fill.o \
	obj/srcs/configuration/obs_fill.o \
	obj/srcs/configuration/unif_update.o \
	obj/srcs/configuration/land/generate_land_rgb.o \
	obj/srcs/configuration/land/generate_land_xyz.o \
	obj/srcs/configuration/land/generate_land_y.o \
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
	obj/srcs/meshes/mesh_operations.o \
	obj/srcs/objmodel/obj_insert_face.o \
	obj/srcs/objmodel/obj_parsing.o \
	obj/srcs/objmodel/obj_parsing_faces.o \
	obj/srcs/objmodel/obj_parsing_floats.o \
	obj/srcs/objmodel/obj_parsing_misc.o \
	obj/srcs/objmodel/obj_parsing_mtl.o \
	obj/srcs/objmodel/objmodel_operations.o \
	obj/srcs/obs/obs_operations.o \
	obj/srcs/shaders/shader_operations.o \
	obj/srcs/textures/load_texture.o \
	obj/srcs/textures/mapping_xy.o \
	obj/srcs/textures/parse_tga.o

MSG_0 := printf '\033[0;32m%-47.47s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-47.47s\033[0;0m\n'
MSG_END := printf '\n'

.SILENT:

all: $(LIBS) $(NAME)
.PHONY: all

$(NAME): $(O_FILES)
	@$(MSG_0) $@ ; $(LD_CC) -o $@ $(O_FILES) $(LD_FLAGS) && $(MSG_END) || $(MSG_1) $@

obj/srcs/env_operations.o: srcs/env_operations.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/error.o: srcs/error.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/glfw_operations.o: srcs/glfw_operations.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/main.o: srcs/main.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/program_operations.o: srcs/program_operations.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/conf.o: srcs/configuration/conf.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/configuration 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/mesh_fill.o: srcs/configuration/mesh_fill.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/configuration 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/obs_fill.o: srcs/configuration/obs_fill.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/configuration 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/unif_update.o: srcs/configuration/unif_update.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/configuration 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/land/generate_land_rgb.o: srcs/configuration/land/generate_land_rgb.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/configuration/land 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/land/generate_land_xyz.o: srcs/configuration/land/generate_land_xyz.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/configuration/land 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/land/generate_land_y.o: srcs/configuration/land/generate_land_y.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/configuration/land 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/controls/controls_apply.o: srcs/controls/controls_apply.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/controls 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/controls/controls_inputs.o: srcs/controls/controls_inputs.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/controls 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4.o: srcs/ftmath/matrix4.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_invtranslate.o: srcs/ftmath/matrix4_invtranslate.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_miscop.o: srcs/ftmath/matrix4_miscop.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_rotation.o: srcs/ftmath/matrix4_rotation.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_scale.o: srcs/ftmath/matrix4_scale.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_translate.o: srcs/ftmath/matrix4_translate.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/vector3.o: srcs/ftmath/vector3.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/vector3_basicop.o: srcs/ftmath/vector3_basicop.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/ftmath 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/meshes/mesh_operations.o: srcs/meshes/mesh_operations.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/meshes 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_insert_face.o: srcs/objmodel/obj_insert_face.c include/fterror.h include/ftmath.h include/objmodel.h include/objmodel_parsing.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/objmodel 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing.o: srcs/objmodel/obj_parsing.c include/fterror.h include/ftmath.h include/objmodel.h include/objmodel_parsing.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/objmodel 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing_faces.o: srcs/objmodel/obj_parsing_faces.c include/fterror.h include/ftmath.h include/objmodel.h include/objmodel_parsing.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/objmodel 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing_floats.o: srcs/objmodel/obj_parsing_floats.c include/fterror.h include/ftmath.h include/objmodel.h include/objmodel_parsing.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/objmodel 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing_misc.o: srcs/objmodel/obj_parsing_misc.c include/fterror.h include/ftmath.h include/objmodel.h include/objmodel_parsing.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/objmodel 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing_mtl.o: srcs/objmodel/obj_parsing_mtl.c include/fterror.h include/ftmath.h include/objmodel.h include/objmodel_parsing.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/objmodel 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/objmodel_operations.o: srcs/objmodel/objmodel_operations.c include/fterror.h include/ftmath.h include/objmodel.h include/objmodel_parsing.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/objmodel 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/obs/obs_operations.o: srcs/obs/obs_operations.c include/fterror.h include/ftmath.h include/objmodel.h include/objmodel_parsing.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/obs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/shaders/shader_operations.o: srcs/shaders/shader_operations.c include/fterror.h include/ftmath.h include/objmodel.h include/objmodel_parsing.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/shaders 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/textures/load_texture.o: srcs/textures/load_texture.c include/fterror.h include/ftmath.h include/objmodel.h include/objmodel_parsing.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/textures 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/textures/mapping_xy.o: srcs/textures/mapping_xy.c include/fterror.h include/ftmath.h include/objmodel.h include/objmodel_parsing.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/textures 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/textures/parse_tga.o: srcs/textures/parse_tga.c include/fterror.h include/ftmath.h include/objmodel.h include/objmodel_parsing.h include/scop.h include/scop_conf.h include/scop_types.h
	@mkdir -p obj/srcs/textures 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

$(LIBS):
	@make -C $@
.PHONY: $(LIBS)

clean:
	@rm -f $(O_FILES) 2> /dev/null || true
	@rmdir -p obj/srcs/textures obj/srcs/shaders obj/srcs/obs obj/srcs/objmodel obj/srcs/meshes obj/srcs/ftmath obj/srcs/controls obj/srcs/configuration/land obj/srcs/configuration obj/srcs $(O_DIR) 2> /dev/null || true
.PHONY: clean

fclean: clean
	@rm -f $(NAME)
.PHONY: fclean

re: fclean all
.PHONY: re
