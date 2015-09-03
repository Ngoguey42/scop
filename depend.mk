O_FILES :=	o/srcs/configuration/cog_loadconf1.o \
			o/srcs/configuration/cog_loadconf2.o \
			o/srcs/configuration/cog_meshfill1.o \
			o/srcs/configuration/cog_meshfill2.o \
			o/srcs/configuration/obs_fill.o o/srcs/configuration/obs_update.o \
			o/srcs/configuration/unif_update.o \
			o/srcs/configuration/unif_update_light.o \
			o/srcs/controls/controls_apply.o o/srcs/controls/controls_events.o \
			o/srcs/controls/controls_inputs.o o/srcs/controls/update_campos.o \
			o/srcs/controls/update_mainobpos.o o/srcs/controls/update_sunpos.o \
			o/srcs/env_operations.o o/srcs/ftmath/matrix4.o \
			o/srcs/ftmath/matrix4_invtranslate.o \
			o/srcs/ftmath/matrix4_miscop.o o/srcs/ftmath/matrix4_rotation.o \
			o/srcs/ftmath/matrix4_scale.o o/srcs/ftmath/matrix4_translate.o \
			o/srcs/ftmath/vector3.o o/srcs/ftmath/vector3_basicop.o \
			o/srcs/ftmath/vector3_scalarop.o o/srcs/glfw_operations.o \
			o/srcs/land/generate_land_rgb.o o/srcs/land/generate_land_xyz.o \
			o/srcs/land/generate_land_y.o o/srcs/main.o \
			o/srcs/mainob/mainob_operations.o o/srcs/meshes/mesh_creation.o \
			o/srcs/meshes/mesh_dumb_fill.o o/srcs/meshes/mesh_operations.o \
			o/srcs/meshes/mesh_refresh.o o/srcs/meshes/primary_vao.o \
			o/srcs/objmodel/obj_faces_operations.o \
			o/srcs/objmodel/obj_insert_face.o o/srcs/objmodel/obj_parsing.o \
			o/srcs/objmodel/obj_parsing_faces.o \
			o/srcs/objmodel/obj_parsing_floats.o \
			o/srcs/objmodel/obj_parsing_misc.o \
			o/srcs/objmodel/obj_parsing_mtl.o \
			o/srcs/objmodel/objmodel_operations.o \
			o/srcs/objmodel/objmodel_retreive.o o/srcs/obs/obs_booleans.o \
			o/srcs/obs/obs_operations.o o/srcs/obs/obs_render.o \
			o/srcs/obs/obs_update.o o/srcs/program_operations.o \
			o/srcs/sbox/sbox_operations.o o/srcs/sbox/sbox_render.o \
			o/srcs/shaders/shader_operations.o o/srcs/textures/parse_tga.o \
			o/srcs/textures/textures_operations.o

o/srcs/configuration/cog_loadconf1.o: srcs/configuration/cog_loadconf1.c \
	include/scop.h include/ftmath.h include/configuration/scop_conf.h \
	include/ftmath.h include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/configuration
o/srcs/configuration/cog_loadconf2.o: srcs/configuration/cog_loadconf2.c \
	include/scop.h include/ftmath.h include/configuration/scop_conf.h \
	include/ftmath.h include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/configuration
o/srcs/configuration/cog_meshfill1.o: srcs/configuration/cog_meshfill1.c \
	include/scop.h include/ftmath.h include/configuration/scop_conf.h \
	include/ftmath.h include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h include/objmodel/objmodel.h include/meshes/vao.h \
	| o/srcs/configuration
o/srcs/configuration/cog_meshfill2.o: srcs/configuration/cog_meshfill2.c \
	include/scop.h include/ftmath.h include/configuration/scop_conf.h \
	include/ftmath.h include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h include/objmodel/objmodel.h include/meshes/vao.h \
	| o/srcs/configuration
o/srcs/configuration/obs_fill.o: srcs/configuration/obs_fill.c include/scop.h \
	include/ftmath.h include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/configuration
o/srcs/configuration/obs_update.o: srcs/configuration/obs_update.c \
	include/scop.h include/ftmath.h include/configuration/scop_conf.h \
	include/ftmath.h include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/configuration
o/srcs/configuration/unif_update.o: srcs/configuration/unif_update.c \
	include/scop.h include/ftmath.h include/configuration/scop_conf.h \
	include/ftmath.h include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/configuration
o/srcs/configuration/unif_update_light.o: \
	srcs/configuration/unif_update_light.c include/scop.h include/ftmath.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/configuration
o/srcs/controls/controls_apply.o: srcs/controls/controls_apply.c \
	include/scop.h include/ftmath.h include/configuration/scop_conf.h \
	include/ftmath.h include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/controls
o/srcs/controls/controls_events.o: srcs/controls/controls_events.c \
	include/scop.h include/ftmath.h include/configuration/scop_conf.h \
	include/ftmath.h include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/controls
o/srcs/controls/controls_inputs.o: srcs/controls/controls_inputs.c \
	include/scop.h include/ftmath.h include/configuration/scop_conf.h \
	include/ftmath.h include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/controls
o/srcs/controls/update_campos.o: srcs/controls/update_campos.c include/scop.h \
	include/ftmath.h include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/controls
o/srcs/controls/update_mainobpos.o: srcs/controls/update_mainobpos.c \
	include/scop.h include/ftmath.h include/configuration/scop_conf.h \
	include/ftmath.h include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/controls
o/srcs/controls/update_sunpos.o: srcs/controls/update_sunpos.c include/scop.h \
	include/ftmath.h include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/controls
o/srcs/env_operations.o: srcs/env_operations.c include/scop.h include/ftmath.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs
o/srcs/ftmath/matrix4.o: srcs/ftmath/matrix4.c include/ftmath.h | o/srcs/ftmath
o/srcs/ftmath/matrix4_invtranslate.o: srcs/ftmath/matrix4_invtranslate.c \
	include/ftmath.h | o/srcs/ftmath
o/srcs/ftmath/matrix4_miscop.o: srcs/ftmath/matrix4_miscop.c include/ftmath.h \
	| o/srcs/ftmath
o/srcs/ftmath/matrix4_rotation.o: srcs/ftmath/matrix4_rotation.c \
	include/ftmath.h | o/srcs/ftmath
o/srcs/ftmath/matrix4_scale.o: srcs/ftmath/matrix4_scale.c include/ftmath.h \
	| o/srcs/ftmath
o/srcs/ftmath/matrix4_translate.o: srcs/ftmath/matrix4_translate.c \
	include/ftmath.h | o/srcs/ftmath
o/srcs/ftmath/vector3.o: srcs/ftmath/vector3.c include/ftmath.h | o/srcs/ftmath
o/srcs/ftmath/vector3_basicop.o: srcs/ftmath/vector3_basicop.c \
	include/ftmath.h | o/srcs/ftmath
o/srcs/ftmath/vector3_scalarop.o: srcs/ftmath/vector3_scalarop.c \
	include/ftmath.h | o/srcs/ftmath
o/srcs/glfw_operations.o: srcs/glfw_operations.c include/scop.h \
	include/ftmath.h include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs
o/srcs/land/generate_land_rgb.o: srcs/land/generate_land_rgb.c include/scop.h \
	include/ftmath.h include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/land
o/srcs/land/generate_land_xyz.o: srcs/land/generate_land_xyz.c include/scop.h \
	include/ftmath.h include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/land
o/srcs/land/generate_land_y.o: srcs/land/generate_land_y.c \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h | o/srcs/land
o/srcs/main.o: srcs/main.c include/scop.h include/ftmath.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs
o/srcs/mainob/mainob_operations.o: srcs/mainob/mainob_operations.c \
	include/scop.h include/ftmath.h include/configuration/scop_conf.h \
	include/ftmath.h include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/mainob
o/srcs/meshes/mesh_creation.o: srcs/meshes/mesh_creation.c | o/srcs/meshes
o/srcs/meshes/mesh_dumb_fill.o: srcs/meshes/mesh_dumb_fill.c include/scop.h \
	include/ftmath.h include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/meshes
o/srcs/meshes/mesh_operations.o: srcs/meshes/mesh_operations.c include/scop.h \
	include/ftmath.h include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/meshes
o/srcs/meshes/mesh_refresh.o: srcs/meshes/mesh_refresh.c include/scop.h \
	include/ftmath.h include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/meshes
o/srcs/meshes/primary_vao.o: srcs/meshes/primary_vao.c | o/srcs/meshes
o/srcs/objmodel/obj_faces_operations.o: srcs/objmodel/obj_faces_operations.c \
	include/objmodel/objmodel_parsing.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/objmodel
o/srcs/objmodel/obj_insert_face.o: srcs/objmodel/obj_insert_face.c \
	include/objmodel/objmodel_parsing.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/objmodel
o/srcs/objmodel/obj_parsing.o: srcs/objmodel/obj_parsing.c \
	include/objmodel/objmodel_parsing.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/objmodel
o/srcs/objmodel/obj_parsing_faces.o: srcs/objmodel/obj_parsing_faces.c \
	include/objmodel/objmodel_parsing.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/objmodel
o/srcs/objmodel/obj_parsing_floats.o: srcs/objmodel/obj_parsing_floats.c \
	include/objmodel/objmodel_parsing.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/objmodel
o/srcs/objmodel/obj_parsing_misc.o: srcs/objmodel/obj_parsing_misc.c \
	include/objmodel/objmodel_parsing.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/objmodel
o/srcs/objmodel/obj_parsing_mtl.o: srcs/objmodel/obj_parsing_mtl.c \
	include/objmodel/objmodel_parsing.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/objmodel
o/srcs/objmodel/objmodel_operations.o: srcs/objmodel/objmodel_operations.c \
	include/scop.h include/ftmath.h include/configuration/scop_conf.h \
	include/ftmath.h include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h include/objmodel/objmodel_parsing.h \
	include/objmodel/objmodel.h include/meshes/vao.h | o/srcs/objmodel
o/srcs/objmodel/objmodel_retreive.o: srcs/objmodel/objmodel_retreive.c \
	include/scop.h include/ftmath.h include/configuration/scop_conf.h \
	include/ftmath.h include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h include/objmodel/objmodel_parsing.h \
	include/objmodel/objmodel.h include/meshes/vao.h | o/srcs/objmodel
o/srcs/obs/obs_booleans.o: srcs/obs/obs_booleans.c include/scop.h \
	include/ftmath.h include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/obs
o/srcs/obs/obs_operations.o: srcs/obs/obs_operations.c include/scop.h \
	include/ftmath.h include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/obs
o/srcs/obs/obs_render.o: srcs/obs/obs_render.c include/scop.h include/ftmath.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/obs
o/srcs/obs/obs_update.o: srcs/obs/obs_update.c include/scop.h include/ftmath.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/obs
o/srcs/program_operations.o: srcs/program_operations.c include/scop.h \
	include/ftmath.h include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs
o/srcs/sbox/sbox_operations.o: srcs/sbox/sbox_operations.c include/scop.h \
	include/ftmath.h include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/sbox
o/srcs/sbox/sbox_render.o: srcs/sbox/sbox_render.c include/scop.h \
	include/ftmath.h include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/sbox
o/srcs/shaders/shader_operations.o: srcs/shaders/shader_operations.c \
	include/scop.h include/ftmath.h include/configuration/scop_conf.h \
	include/ftmath.h include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/shaders
o/srcs/textures/parse_tga.o: srcs/textures/parse_tga.c | o/srcs/textures
o/srcs/textures/textures_operations.o: srcs/textures/textures_operations.c \
	include/scop.h include/ftmath.h include/configuration/scop_conf.h \
	include/ftmath.h include/configuration/cog_enums.h include/scop_types.h \
	include/configuration/scop_conf.h include/ftmath.h \
	include/configuration/cog_enums.h include/meshes/vao.h \
	include/configuration/cog_meshfill.h include/objmodel/objmodel.h \
	include/meshes/vao.h | o/srcs/textures
