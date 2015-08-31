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
LD_FLAGS := -Llibft -lft -lglfw -lGL -lGLEW -lm

# C include flags
C_HEADS := -I include -I libft/includes

NICE_OUTPUT := 0

#
# Internal
#

O_FILES := obj/srcs/env_operations.o \
	obj/srcs/glfw_operations.o \
	obj/srcs/main.o \
	obj/srcs/program_operations.o \
	obj/srcs/configuration/cog_loadconf1.o \
	obj/srcs/configuration/cog_loadconf2.o \
	obj/srcs/configuration/cog_meshfill1.o \
	obj/srcs/configuration/cog_meshfill2.o \
	obj/srcs/configuration/obs_fill.o \
	obj/srcs/configuration/obs_update.o \
	obj/srcs/configuration/unif_update.o \
	obj/srcs/configuration/unif_update_light.o \
	obj/srcs/controls/controls_apply.o \
	obj/srcs/controls/controls_events.o \
	obj/srcs/controls/controls_inputs.o \
	obj/srcs/controls/update_campos.o \
	obj/srcs/controls/update_mainobpos.o \
	obj/srcs/controls/update_sunpos.o \
	obj/srcs/ftmath/matrix4.o \
	obj/srcs/ftmath/matrix4_invtranslate.o \
	obj/srcs/ftmath/matrix4_miscop.o \
	obj/srcs/ftmath/matrix4_rotation.o \
	obj/srcs/ftmath/matrix4_scale.o \
	obj/srcs/ftmath/matrix4_translate.o \
	obj/srcs/ftmath/vector3.o \
	obj/srcs/ftmath/vector3_basicop.o \
	obj/srcs/ftmath/vector3_scalarop.o \
	obj/srcs/land/generate_land_rgb.o \
	obj/srcs/land/generate_land_xyz.o \
	obj/srcs/land/generate_land_y.o \
	obj/srcs/mainob/mainob_operations.o \
	obj/srcs/meshes/add_normal_ebo.o \
	obj/srcs/meshes/mesh_creation.o \
	obj/srcs/meshes/mesh_dumb_fill.o \
	obj/srcs/meshes/mesh_operations.o \
	obj/srcs/meshes/mesh_refresh.o \
	obj/srcs/meshes/mesh_vbo_operations.o \
	obj/srcs/meshes/normals_calculation.o \
	obj/srcs/meshes/positions_calculations.o \
	obj/srcs/meshes/transpose_ebo.o \
	obj/srcs/meshes/uv_calculations.o \
	obj/srcs/meshes/uv_calculations_wrapfuns.o \
	obj/srcs/objmodel/obj_faces_operations.o \
	obj/srcs/objmodel/obj_insert_face.o \
	obj/srcs/objmodel/obj_parsing.o \
	obj/srcs/objmodel/obj_parsing_faces.o \
	obj/srcs/objmodel/obj_parsing_floats.o \
	obj/srcs/objmodel/obj_parsing_misc.o \
	obj/srcs/objmodel/obj_parsing_mtl.o \
	obj/srcs/objmodel/objmodel_operations.o \
	obj/srcs/objmodel/objmodel_retreive.o \
	obj/srcs/obs/obs_booleans.o \
	obj/srcs/obs/obs_operations.o \
	obj/srcs/obs/obs_render.o \
	obj/srcs/obs/obs_update.o \
	obj/srcs/sbox/sbox_operations.o \
	obj/srcs/sbox/sbox_render.o \
	obj/srcs/shaders/shader_operations.o \
	obj/srcs/textures/parse_tga.o \
	obj/srcs/textures/textures_operations.o

O_DIRS := obj/srcs/textures obj/srcs/shaders obj/srcs/sbox obj/srcs/obs obj/srcs/objmodel obj/srcs/meshes obj/srcs/mainob obj/srcs/land obj/srcs/ftmath obj/srcs/controls obj/srcs/configuration obj/srcs

MSG_0 := printf '\033[0;32m%s\033[0;0m\n'
MSG_1 := printf '\033[0;31m%s\033[0;0m\n'
MSG_END := true

.SILENT:

all: $(addsuffix /.git,$(MODULES)) $(LIBS) $(NAME)
.PHONY: all

$(NAME): $(O_FILES)
	@$(MSG_0) $@ ; $(LD_CC) -o $@ $(O_FILES) $(LD_FLAGS) && $(MSG_END) || $(MSG_1) $@

obj/srcs/env_operations.o: srcs/env_operations.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/glfw_operations.o: srcs/glfw_operations.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/main.o: srcs/main.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/program_operations.o: srcs/program_operations.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/cog_loadconf1.o: srcs/configuration/cog_loadconf1.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/configuration
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/cog_loadconf2.o: srcs/configuration/cog_loadconf2.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/configuration
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/cog_meshfill1.o: srcs/configuration/cog_meshfill1.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/configuration
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/cog_meshfill2.o: srcs/configuration/cog_meshfill2.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/configuration
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/obs_fill.o: srcs/configuration/obs_fill.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/configuration
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/obs_update.o: srcs/configuration/obs_update.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/configuration
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/unif_update.o: srcs/configuration/unif_update.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/configuration
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/configuration/unif_update_light.o: srcs/configuration/unif_update_light.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/configuration
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/controls/controls_apply.o: srcs/controls/controls_apply.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/controls
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/controls/controls_events.o: srcs/controls/controls_events.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/controls
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/controls/controls_inputs.o: srcs/controls/controls_inputs.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/controls
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/controls/update_campos.o: srcs/controls/update_campos.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/controls
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/controls/update_mainobpos.o: srcs/controls/update_mainobpos.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/controls
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/controls/update_sunpos.o: srcs/controls/update_sunpos.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/controls
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

obj/srcs/ftmath/vector3_scalarop.o: srcs/ftmath/vector3_scalarop.c include/ftmath.h | obj/srcs/ftmath
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/land/generate_land_rgb.o: srcs/land/generate_land_rgb.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/land
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/land/generate_land_xyz.o: srcs/land/generate_land_xyz.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/land
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/land/generate_land_y.o: srcs/land/generate_land_y.c include/cog_enums.h include/ftmath.h include/scop_conf.h | obj/srcs/land
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/mainob/mainob_operations.o: srcs/mainob/mainob_operations.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/mainob
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/meshes/add_normal_ebo.o: srcs/meshes/add_normal_ebo.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/meshes
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/meshes/mesh_creation.o: srcs/meshes/mesh_creation.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/meshes
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/meshes/mesh_dumb_fill.o: srcs/meshes/mesh_dumb_fill.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/meshes
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/meshes/mesh_operations.o: srcs/meshes/mesh_operations.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/meshes
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/meshes/mesh_refresh.o: srcs/meshes/mesh_refresh.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/meshes
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/meshes/mesh_vbo_operations.o: srcs/meshes/mesh_vbo_operations.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/meshes
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/meshes/normals_calculation.o: srcs/meshes/normals_calculation.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/meshes
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/meshes/positions_calculations.o: srcs/meshes/positions_calculations.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/meshes
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/meshes/transpose_ebo.o: srcs/meshes/transpose_ebo.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/meshes
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/meshes/uv_calculations.o: srcs/meshes/uv_calculations.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/meshes
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/meshes/uv_calculations_wrapfuns.o: srcs/meshes/uv_calculations_wrapfuns.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/meshes
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_faces_operations.o: srcs/objmodel/obj_faces_operations.c include/objmodel.h include/objmodel_parsing.h include/vbo.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_insert_face.o: srcs/objmodel/obj_insert_face.c include/objmodel.h include/objmodel_parsing.h include/vbo.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing.o: srcs/objmodel/obj_parsing.c include/objmodel.h include/objmodel_parsing.h include/vbo.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing_faces.o: srcs/objmodel/obj_parsing_faces.c include/objmodel.h include/objmodel_parsing.h include/vbo.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing_floats.o: srcs/objmodel/obj_parsing_floats.c include/objmodel.h include/objmodel_parsing.h include/vbo.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing_misc.o: srcs/objmodel/obj_parsing_misc.c include/objmodel.h include/objmodel_parsing.h include/vbo.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/obj_parsing_mtl.o: srcs/objmodel/obj_parsing_mtl.c include/objmodel.h include/objmodel_parsing.h include/vbo.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/objmodel_operations.o: srcs/objmodel/objmodel_operations.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/objmodel_parsing.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/objmodel/objmodel_retreive.o: srcs/objmodel/objmodel_retreive.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/objmodel_parsing.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/objmodel
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/obs/obs_booleans.o: srcs/obs/obs_booleans.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/obs
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/obs/obs_operations.o: srcs/obs/obs_operations.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/obs
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/obs/obs_render.o: srcs/obs/obs_render.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/obs
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/obs/obs_update.o: srcs/obs/obs_update.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/obs
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/sbox/sbox_operations.o: srcs/sbox/sbox_operations.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/sbox
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/sbox/sbox_render.o: srcs/sbox/sbox_render.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/sbox
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/shaders/shader_operations.o: srcs/shaders/shader_operations.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/shaders
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/textures/parse_tga.o: srcs/textures/parse_tga.c | obj/srcs/textures
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

obj/srcs/textures/textures_operations.o: srcs/textures/textures_operations.c include/cog_enums.h include/cog_meshfill.h include/ftmath.h include/objmodel.h include/scop.h include/scop_conf.h include/scop_types.h include/vbo.h | obj/srcs/textures
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
