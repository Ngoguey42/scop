# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    conf.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/08/10 13:13:01 by ngoguey           #+#    #+#              #
#    Updated: 2015/08/18 16:29:53 by ngoguey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from confclasses import *
import math

vshaders = [
	Vshader("po_to_co", "po_to_co.vert", "viewproj2",
	("pos", 3), ),
	Vshader("pocote_to_couv", "pocote_to_couv.vert", "viewproj2",
	("pos", 3), ("col", 3), ("tex", 2), ),
	Vshader("pote_to_couv", "pote_to_couv.vert", "viewproj2",
	("pos", 3), ("tex", 2), ),
	Vshader("poco_to_co", "poco_to_co.vert", "viewproj",
	("pos", 3), ("col", 3), ),
	Vshader("poteno_to_uv", "poteno_to_uv.vert", "viewproj",
	("pos", 3), ("tex", 2), ("nor", 3), ),
	Vshader("pocono_to_co", "pocono_to_co.vert", "viewproj",
	("pos", 3), ("col", 3), ("nor", 3), ),
	Vshader("pocono_to_co_nomodel", "pocono_to_co_nomodel.vert", "viewproj",
	("pos", 3), ("col", 3), ("nor", 3), ),
	Vshader("po_to_noop", "po_to_noop.vert", "viewproj",
	("pos", 3), ),
	Vshader("po_to_noop_noviewproj", "po_to_noop_noviewproj.vert", "",
	("pos", 3), ),
]
fshaders = [
	Fshader("co_identity", "co_identity.frag", ""),
	Fshader("uv_identity", "uv_identity.frag", ""),
	Fshader("couv_blend", "couv_blend.frag", ""),
	Fshader("couv_uv", "couv_uv.frag", ""),
	Fshader("uvno_uvli", "uvno_uvli.frag", "light"),
	Fshader("cono_coli", "cono_coli.frag", "lightstruct"),
	Fshader("couvno_blendli", "couvno_blendli.frag", "lightstruct"),
	Fshader("co_sun", "co_sun.frag", "suncolor"),
	Fshader("depth01", "depth01.frag", "lightdepth"),
]
gshaders = [
	Gshader("face_rgb", "face_rgb.geom", ""),
	Gshader("face_grey", "face_grey.geom", ""),
	Gshader("pos_to_cubemap", "pos_to_cubemap.geom", "shadowmat6"),
]
programs = [
	# p fait ceci cela
	Program("p", "po_to_co", "co_identity", "no"),
	# pct fait ceci cela
	Program("pct", "pocote_to_couv", "couv_uv", "no"),
	# pt fait ceci cela
	Program("pt", "pote_to_couv", "couv_uv", "no"),
	# land fait ceci cela
	Program("land", "pocono_to_co_nomodel", "cono_coli", "no"),
	# ptn fait ceci cela
	Program("ptn", "poteno_to_uv", "couvno_blendli", "face_grey"),
	# pcn fait ceci cela
	Program("pcn", "pocono_to_co", "cono_coli", "no"),
	# sun fait ceci cela
	Program("sun", "po_to_noop", "co_sun", "no"),
	Program("pointshadow", "po_to_noop_noviewproj", "depth01", "pos_to_cubemap"),
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
	Mesh("teapot1", "ptn", "GL_DYNAMIC_DRAW","""{
	return (sp_meshfillbumb_objmodel(e, me, vbo, "res/teapot.obj"));\n}"""),
	Mesh("teapot2", "ptn", "GL_DYNAMIC_DRAW","""{
	return (sp_meshfillbumb_objmodel(e, me, vbo, "res/teapot2.obj"));\n}"""),
	Mesh("ft", "ptn", "GL_DYNAMIC_DRAW","""{
	return (sp_meshfillbumb_objmodel(e, me, vbo, "res/42.obj"));\n}"""),
	Mesh("csie", "ptn", "GL_DYNAMIC_DRAW","""{
	return (sp_meshfillbumb_objmodel(e, me, vbo, "res/new_csie_b1.obj"));\n}"""),
	Mesh("alpha", "ptn", "GL_STATIC_DRAW","""{
	return (sp_meshfillbumb_objmodel(e, me, vbo, "res/alfa147.obj"));\n}"""),
	Mesh("plane", "ptn", "GL_STATIC_DRAW","""{
	return (sp_meshfillbumb_objmodel(e, me, vbo, "res/cessna.obj"));\n}"""),

	# square fait ceci cela
	Mesh("square", "pcn", "GL_STATIC_DRAW","""{
	t_vertex_basic	vertices[] = {

	BVERT_POSCOL( 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f),  // Top Right
	BVERT_POSCOL(0.5f, -0.5f, 2.0f,   0.0f, 1.0f, 0.0f),  // Bottom Right
	BVERT_POSCOL(-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f),  // Bottom Left
	BVERT_POSCOL(-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f),  // Top Left
        };
	GLuint			indices[] = {  // Note that we start from 0!
		3, 1, 0,  // First Triangle
		3, 2, 1   // Second Triangle
	};
	vbo->npos = 3;
	vbo->ncol = 3;
	(void)ftv_insert_range(
	&vbo->vertices, vertices, sizeof(vertices) / sizeof(*vertices));
	(void)ftv_insert_range(
	&me->faces, indices, sizeof(indices) / sizeof(*indices) / 3);
        sp_calc_normals(e, me, vbo);        
	return (0);\n\t(void)e;\n\t(void)me;\n}"""),

	# land fait ceci cela
	Mesh("land", "land", "GL_STATIC_DRAW","""{
	t_ftvector		lines[1];
	size_t const	line_points = (int)pow(2., (double)POINTS_DEPTHI);
	float			bounds[2];

	if (ftv_init_instance(lines, sizeof(float) * line_points))
		sp_enomem();
	if (ftv_insert_count(lines, lines->data, line_points))
		sp_enomem();
	sp_fill_landgrid(lines);
 	if (ftv_reserve(&vbo->vertices, lines->size * lines->size))
		sp_enomem();
	sp_fill_landvertices(lines, vbo, bounds);
	if (ftv_reserve(&me->faces, (lines->size - 1) * (lines->size - 1) * 2))
		sp_enomem();
	sp_fill_landfaces(lines, &me->faces);
	sp_fill_landrgb(vbo, bounds);
	ftv_release(lines, NULL);
	sp_calc_normals(e, me, vbo);
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
	return (0);\n\t(void)e;\n\t(void)me;\n}"""),
]
models = [
	Model("teapot1", "teapot1", "porcelain", "model_mix"),
	Model("teapot2", "teapot2", "porcelain", "model_mix"),
	Model("ft", "ft", "metal", "model_mix"),
	Model("csie", "csie", "wall", "model"),
	Model("alpha", "alpha", "metal", "model"),
	Model("plane", "plane", "wall", "model"),
	
	Model("square", "square", "no", "model"),
	Model("land", "land", "no", ""),
	Model("sun", "sun", "no", "model"),
]
obs = {
    # Ob("teapot2"),
    # Ob("square", sca = 4., pos = (0., -5., 2.)),
	# Ob("land"),
	# Ob("ptn", pos = (-45., -0., -40.), rot = (0., 0., -math.pi / 2.)),
	# Ob("sun", up = "sp_obupdate_sun", mov = False)
}
