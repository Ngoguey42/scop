# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    scop_conf.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/08/08 11:56:00 by ngoguey           #+#    #+#              #
#    Updated: 2015/08/09 18:00:14 by ngoguey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from scop_confclasses import *

vshaders = [
	# po_to_co fait ceci cela
	Vshader("po_to_co", "po_to_co.vert", "viewproj2",
		("pos", 3), ),

	# pocote_to_couv fait ceci cela
	Vshader("pocote_to_couv", "pocote_to_couv.vert", "viewproj2",
		("pos", 3), ("col", 3), ("tex", 2), ),

	# pote_to_couv fait ceci cela
	Vshader("pote_to_couv", "pote_to_couv.vert", "viewproj2",
		("pos", 3), ("tex", 2), ),

	# poco_to_co fait ceci cela
	Vshader("poco_to_co", "poco_to_co.vert", "viewproj",
		("pos", 3), ("col", 3), ),

	# poteno_to_uv fait ceci cela
	Vshader("poteno_to_uv", "poteno_to_uv.vert", "viewproj",
		("pos", 3), ("tex", 2), ("nor", 3), ),

	# pocono_to_co fait ceci cela
	Vshader("pocono_to_co", "pocono_to_co.vert", "viewproj",
		("pos", 3), ("col", 3), ("nor", 3), ),

	# po_to_noop fait ceci cela
	Vshader("po_to_noop", "po_to_noop.vert", "viewproj",
		("pos", 3), ),
]
fshaders = [
	# co_identity fait ceci cela
	Fshader("co_identity", "co_identity.frag", ""),
	# uv_identity fait ceci cela
	Fshader("uv_identity", "uv_identity.frag", ""),
	# couv_blend fait ceci cela
	Fshader("couv_blend", "couv_blend.frag", ""),
	# couv_uv fait ceci cela
	Fshader("couv_uv", "couv_uv.frag", ""),
	# uvno_uvli fait ceci cela
	Fshader("uvno_uvli", "uvno_uvli.frag", "light"),
	# cono_coli fait ceci cela
	Fshader("cono_coli", "cono_coli.frag", "light"),
	# couvno_blendli fait ceci cela
	Fshader("couvno_blendli", "couvno_blendli.frag", "light"),
	# co_sun fait ceci cela
	Fshader("co_sun", "co_sun.frag", "suncolor"),
]
gshaders = [
	# test fait ceci cela
	Gshader("test", "test.geom", ""),
]
programs = [
	# p fait ceci cela
	Program("p", "po_to_co", "co_identity", "no"),
	# pct fait ceci cela
	Program("pct", "pocote_to_couv", "couv_uv", "no"),
	# pt fait ceci cela
	Program("pt", "pote_to_couv", "couv_uv", "no"),
	# land fait ceci cela
	Program("land", "pocono_to_co", "cono_coli", "no"),
	# ptn fait ceci cela
	Program("ptn", "poteno_to_uv", "couvno_blendli", "test"),
	# pcn fait ceci cela
	Program("pcn", "pocono_to_co", "cono_coli", "no"),
	# sun fait ceci cela
	Program("sun", "po_to_noop", "co_sun", "no"),
]
textures = [
	# porcelain fait ceci cela
	Texture("porcelain", "Porcelain.tga"),
	# wall fait ceci cela
	Texture("wall", "Wall.tga"),
	# metal fait ceci cela
	Texture("metal", "metal.tga"),
]
meshes = [
	# plane fait ceci cela
	Mesh("plane", "ptn", "GL_STATIC_DRAW","""{
	t_objmodel	m[1];

	/* if (op_parse_obj(m, "res/cessna.obj")) */
	/* if (op_parse_obj(m, "res/teapot.obj")) */
	if (op_parse_obj(m, "res/teapot2.obj"))
		return (ERROR("op_parse_obj(m)"), 1);
        op_retreive_data(m, vbo, &me->faces);
        sp_calc_uv_plan_oxy(e, me, vbo);
        sp_calc_normals(e, me, vbo);
	sp_clean_objmodel(m);
	return (0);\n\t(void)e;\n\t(void)me;\n}"""),

	# # square fait ceci cela
	# Mesh("square", "pcn", "GL_STATIC_DRAW","""{
        # /*
	# t_ftvector		vert[1];

	# GLfloat vertices[] = {
	# 	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // Top Right
	# 	 0.5f, -0.5f, 2.0f,   0.0f, 1.0f, 0.0f,  // Bottom Right
	# 	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // Bottom Left
	# 	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // Top Left
	# };
	# GLuint indices[] = {  // Note that we start from 0!
	# 	0, 1, 3,  // First Triangle
	# 	1, 2, 3   // Second Triangle
	# };
	# (void)ftv_init_instance(vert, sizeof(float) * 6);
	# (void)ftv_insert_range(vert, vertices, 4);
	# (void)ftv_insert_range(&me->faces, indices, 2);
	# sp_inject_normals(vert, &me->faces);
	# memcpy(&me->vertices, vert, sizeof(t_ftvector));
        # */
	# return (0);\n\t(void)e;\n\t(void)me;\n}"""),

	# land fait ceci cela
	# Mesh("land", "land", "GL_STATIC_DRAW","""{
        # /*
	# t_ftvector		lines[1];
	# size_t const	line_points = (int)pow(2., (double)POINTS_DEPTHI);
	# float			bounds[2];

	# if (ftv_init_instance(lines, sizeof(float) * line_points))
	# 	sp_enomem();
	# if (ftv_insert_count(lines, lines->data, line_points))
	# 	sp_enomem();
	# sp_fill_landgrid(lines);
	# //fuite sur me->vertices
 	# if (ftv_init_instance(&me->vertices, 6 * sizeof(float)))
	# 	sp_enomem();
 	# if (ftv_reserve(&me->vertices, lines->size * lines->size))
	# 	sp_enomem();
	# sp_fill_landvertices(lines, &me->vertices, bounds);
	# if (ftv_reserve(&me->faces, (lines->size - 1) * (lines->size - 1) * 2))
	# 	sp_enomem();
	# sp_fill_landfaces(lines, &me->faces);
	# sp_fill_landrgb(&me->vertices, bounds);
	# ftv_release(lines, NULL);
	# sp_inject_normals(&me->vertices, &me->faces);
        # */
	# return (0);\n\t(void)e;\n\t(void)me;\n}"""),

	# ptn fait ceci cela
	Mesh("ptn", "ptn", "GL_STATIC_DRAW","""{
	t_objmodel	m[1];

	if (op_parse_obj(m, "res/alfa147.obj"))
		return (ERROR("op_parse_obj(m)"), 1);
        op_retreive_data(m, vbo, &me->faces);
	sp_clean_objmodel(m);
	return (0);\n\t(void)e;\n\t(void)me;\n}"""),

	# sun fait ceci cela
	Mesh("sun", "sun", "GL_STATIC_DRAW","""{
	t_vertex_basic	vertices[8] = {
		BVERT_POS(-1.0f, 1.0f, -1.0f),
		BVERT_POS(-1.0f, -1.0f, -1.0f),
		BVERT_POS(-1.0f, 1.0f, 1.0f),
		BVERT_POS(-1.0f, -1.0f, 1.0f),
		BVERT_POS(1.0f, 1.0f, 1.0f),
		BVERT_POS(1.0f, -1.0f, 1.0f),
		BVERT_POS(1.0f, 1.0f, -1.0f),
		BVERT_POS(1.0f, -1.0f, -1.0f)
	};
	GLuint indices[36] = {
		0,1,2,2,1,3,
		4,5,6,6,5,7,
		3,1,5,5,1,7,
		0,2,6,6,2,4,
		6,7,0,0,7,1,
		2,3,4,4,3,5
	};
        vbo->npos = 3;
	(void)ftv_insert_range(
		&vbo->vertices, vertices, sizeof(vertices) / sizeof(*vertices));
	(void)ftv_insert_range(
		&me->faces, indices, sizeof(indices) / sizeof(*indices) / 3);
        ftv_print(&vbo->vertices, "fff");
	return (0);\n\t(void)e;\n\t(void)me;\n}"""),
]
models = [
	# plane fait ceci cela
	Model("plane", "plane", "porcelain", "model"),
	# # square fait ceci cela
	# Model("square", "square", "no", "model"),
	# # land fait ceci cela
	# Model("land", "land", "no", "model"),
	# ptn fait ceci cela
	Model("ptn", "ptn", "metal", "model"),
	# sun fait ceci cela
	Model("sun", "sun", "no", "model"),
]
