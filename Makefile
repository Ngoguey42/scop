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

# Makefiles to call (directory)
LIBS := libft

# Modules to init (directory)
MODULES := libft

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
	obj/srcs/configuration/cogconf.o \
	obj/srcs/configuration/mesh_fill.o \
	obj/srcs/configuration/obs_fill.o \
	obj/srcs/configuration/obs_update.o \
	obj/srcs/configuration/unif_update.o \
	obj/srcs/controls/controls.sun.o \
	obj/srcs/controls/controls_apply.o \
	obj/srcs/controls/controls_inputs.o \
	obj/srcs/controls/controls_movements.o \
	obj/srcs/ftmath/matrix4.o \
	obj/srcs/ftmath/matrix4_invtranslate.o \
	obj/srcs/ftmath/matrix4_miscop.o \
	obj/srcs/ftmath/matrix4_rotation.o \
	obj/srcs/ftmath/matrix4_scale.o \
	obj/srcs/ftmath/matrix4_translate.o \
	obj/srcs/ftmath/vector3.o \
	obj/srcs/ftmath/vector3_basicop.o \
	obj/srcs/land/generate_land_rgb.o \
	obj/srcs/land/generate_land_xyz.o \
	obj/srcs/land/generate_land_y.o \
	obj/srcs/meshes/mesh_creation.o \
	obj/srcs/meshes/mesh_operations.o \
	obj/srcs/meshes/normals_calculation.o \
	obj/srcs/meshes/uv_calculation_plan_oxy.o \
	obj/srcs/objmodel/obj_faces_operations.o \
	obj/srcs/objmodel/obj_insert_face.o \
	obj/srcs/objmodel/obj_parsing.o \
	obj/srcs/objmodel/obj_parsing_faces.o \
	obj/srcs/objmodel/obj_parsing_floats.o \
	obj/srcs/objmodel/obj_parsing_misc.o \
	obj/srcs/objmodel/obj_parsing_mtl.o \
	obj/srcs/objmodel/objmodel_operations.o \
	obj/srcs/obs/obs_operations.o \
	obj/srcs/obs/obs_render.o \
	obj/srcs/shaders/shader_operations.o \
	obj/srcs/textures/parse_tga.o \
	obj/srcs/textures/textures_operations.o

O_DIRS := obj/srcs/textures obj/srcs/shaders obj/srcs/obs obj/srcs/objmodel obj/srcs/meshes obj/srcs/land obj/srcs/ftmath obj/srcs/controls obj/srcs/configuration obj/srcs

MSG_0 := printf '\033[0;32m%-41.41s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-41.41s\033[0;0m\n'
MSG_END := printf '\n'

.SILENT:

all: $(addsuffix /.git,$(MODULES)) $(LIBS) $(NAME)
.PHONY: all

$(NAME): $(O_FILES)
	@$(MSG_0) $@ ; $(LD_CC) -o $@ $(O_FILES) $(LD_FLAGS) && $(MSG_END) || $(MSG_1) $@

obj/srcs/env_operations.o: srcs/env_operations.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/error.o: srcs/error.c include/fterror.h | obj/srcs
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/glfw_operations.o: srcs/glfw_operations.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/main.o: srcs/main.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/program_operations.o: srcs/program_operations.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/cogconf.o: srcs/configuration/cogconf.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/configuration
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/mesh_fill.o: srcs/configuration/mesh_fill.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/configuration
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/obs_fill.o: srcs/configuration/obs_fill.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/configuration
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/obs_update.o: srcs/configuration/obs_update.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/configuration
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/unif_update.o: srcs/configuration/unif_update.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/configuration
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/controls/controls.sun.o: srcs/controls/controls.sun.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/controls
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/controls/controls_apply.o: srcs/controls/controls_apply.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/controls
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/controls/controls_inputs.o: srcs/controls/controls_inputs.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/controls
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/controls/controls_movements.o: srcs/controls/controls_movements.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/controls
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4.o: srcs/ftmath/matrix4.c include/ftmath.h | obj/srcs/ftmath
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_invtranslate.o: srcs/ftmath/matrix4_invtranslate.c include/ftmath.h | obj/srcs/ftmath
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_miscop.o: srcs/ftmath/matrix4_miscop.c include/ftmath.h | obj/srcs/ftmath
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_rotation.o: srcs/ftmath/matrix4_rotation.c include/ftmath.h | obj/srcs/ftmath
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_scale.o: srcs/ftmath/matrix4_scale.c include/ftmath.h | obj/srcs/ftmath
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/matrix4_translate.o: srcs/ftmath/matrix4_translate.c include/ftmath.h | obj/srcs/ftmath
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/vector3.o: srcs/ftmath/vector3.c include/ftmath.h | obj/srcs/ftmath
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/ftmath/vector3_basicop.o: srcs/ftmath/vector3_basicop.c include/ftmath.h | obj/srcs/ftmath
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/land/generate_land_rgb.o: srcs/land/generate_land_rgb.c include/fterror.h include/ftmath.h include/scop_cogconf_enums.h include/scop_conf.h | obj/srcs/land
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/land/generate_land_xyz.o: srcs/land/generate_land_xyz.c include/fterror.h include/ftmath.h include/scop_cogconf_enums.h include/scop_conf.h | obj/srcs/land
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/land/generate_land_y.o: srcs/land/generate_land_y.c include/fterror.h include/ftmath.h include/scop_cogconf_enums.h include/scop_conf.h | obj/srcs/land
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/meshes/mesh_creation.o: srcs/meshes/mesh_creation.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/meshes
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/meshes/mesh_operations.o: srcs/meshes/mesh_operations.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/meshes
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/meshes/normals_calculation.o: srcs/meshes/normals_calculation.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/meshes
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/meshes/uv_calculation_plan_oxy.o: srcs/meshes/uv_calculation_plan_oxy.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/meshes
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_faces_operations.o: srcs/objmodel/obj_faces_operations.c include/fterror.h include/objmodel.h include/objmodel_parsing.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_insert_face.o: srcs/objmodel/obj_insert_face.c include/fterror.h include/objmodel.h include/objmodel_parsing.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing.o: srcs/objmodel/obj_parsing.c include/fterror.h include/objmodel.h include/objmodel_parsing.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing_faces.o: srcs/objmodel/obj_parsing_faces.c include/fterror.h include/objmodel.h include/objmodel_parsing.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing_floats.o: srcs/objmodel/obj_parsing_floats.c include/fterror.h include/objmodel.h include/objmodel_parsing.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing_misc.o: srcs/objmodel/obj_parsing_misc.c include/fterror.h include/objmodel.h include/objmodel_parsing.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing_mtl.o: srcs/objmodel/obj_parsing_mtl.c include/fterror.h include/objmodel.h include/objmodel_parsing.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/objmodel_operations.o: srcs/objmodel/objmodel_operations.c include/fterror.h include/ftmath.h include/objmodel.h include/objmodel_parsing.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/obs/obs_operations.o: srcs/obs/obs_operations.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/obs
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/obs/obs_render.o: srcs/obs/obs_render.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/obs
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/shaders/shader_operations.o: srcs/shaders/shader_operations.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/shaders
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/textures/parse_tga.o: srcs/textures/parse_tga.c include/fterror.h | obj/srcs/textures
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/textures/textures_operations.o: srcs/textures/textures_operations.c include/fterror.h include/ftmath.h include/objmodel.h include/scop.h include/scop_cogconf_enums.h include/scop_conf.h include/scop_types.h | obj/srcs/textures
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

$(LIBS):
	@make -C $@
.PHONY: $(LIBS)

$(addsuffix /.git,$(MODULES)):
	@git submodule init $(@:.git=)
	@git submodule update $(@:.git=)

$(O_DIRS):
	@mkdir -p $@ 2> /dev/null || true

clean:
	@rm -f $(O_FILES) 2> /dev/null || true
	@rmdir -p $(O_DIRS) $(O_DIR) 2> /dev/null || true
.PHONY: clean

fclean: clean
	@rm -f $(NAME)
.PHONY: fclean

re: fclean all
.PHONY: re
