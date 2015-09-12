# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    conf.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/08/10 13:13:01 by ngoguey           #+#    #+#              #
#    Updated: 2015/09/12 11:08:39 by ngoguey          ###   ########.fr        #
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
	Vshader("poin_poout_mvptrans", "poIn_poOut_mvpTrans.vert", "",
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
	Fshader("co_sun", "co_sun.frag", "sunfrag"),
	Fshader("depth01", "depth01.frag", ""),
]
gshaders = [
	Gshader("face_rgb", "face_rgb.geom", ""),
	Gshader("face_grey", "pouvno_facegrey.geom", ""),
	Gshader("po_facegrey", "po_facegrey.geom", "viewproj"),
	Gshader("pos_to_cubemap", "pos_to_cubemap.geom", ""),
]
tcshaders = [
	Tcshader("test", "test.tesc", "tesc")
]
teshaders = [
	Teshader("test", "test.tese", "")
]
programs = [
	# land fait ceci cela
	Program("land", "pocono_to_co_nomodel", "cono_coli", img1=0),
	# ptn fait ceci cela
	Program("ptn", "poteno_to_uv", "couvno_blendli", gsname="face_grey", sbox=0, img1=1),
	# pcn fait ceci cela
	Program("pcn", "pocono_to_co", "cono_coli", sbox=0),
	# sun fait ceci cela
Program("sun", "poin_poout_mvptrans", "co_sun", gsname="po_facegrey"),
# Program("sun", "poin_poout_mvptrans", "co_sun", gsname="po_facegrey", tcsname="test", tesname="test"),
	Program("pointshadow", "po_to_noop_noviewproj", "depth01", gsname="pos_to_cubemap"),
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
	Mesh("main", "ptn", usage="GL_DYNAMIC_DRAW"
		 , objfile_enum="teapot1", recenter="true"
		 , tex_enum="box", texscale=(0.5, 0.5)
	 ),
	Mesh("plane", "ptn", objfile_enum="cessna"),
	Mesh("sun", "sun", objfile_enum="dodecahedron", recenter="true"),

	Mesh("land", "land"
		 , fill_funbody="""{
	t_vbo_basic		*vbo;
	t_ftvector		lines[1];
	size_t const	line_points = (int)pow(2., (double)POINTS_DEPTHI);
	float			bounds[2];

	vbo = &vao->vbo;
	if (ftv_init_instance(lines, sizeof(float) * line_points))
		sp_enomem();
	if (ftv_insert_count(lines, lines->data, line_points))
		sp_enomem();
	sp_fill_landgrid(lines);
	if (ftv_reserve(&vbo->vertices, lines->size * lines->size))
		sp_enomem();
	sp_fill_landvertices(lines, vbo, bounds);
	if (ftv_reserve(&vao->ebo.faces, (lines->size - 1) * (lines->size - 1) * 2))
		sp_enomem();
	sp_fill_landfaces(lines, &vao->ebo.faces);
	sp_fill_landrgb(vbo, bounds);
	ftv_release(lines, NULL);
	return (0);\n\t(void)me;\n}"""),
]

models = [
	Model("main", "main", "porcelain", "model_mix"),
	Model("plane", "plane", "wall", "model"),
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
