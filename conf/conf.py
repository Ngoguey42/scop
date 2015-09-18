# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    conf.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/08/10 13:13:01 by ngoguey           #+#    #+#              #
#    Updated: 2015/09/17 16:26:09 by ngoguey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from confclasses import *
import math

vshaders = [
	Vshader("pocono_to_co_nomodel", "pocono_to_co_nomodel.vert", "viewproj",
	("pos", 3), ("col", 3), ("nor", 3), ), #land
	Vshader("poteno_to_uv", "poteno_to_uv.vert", "viewproj",
	("pos", 3), ("tex", 2), ("nor", 3), ), #ptn
	Vshader("poin_poout_mvptrans", "poIn_poOut_mvpTrans.vert", "",
	("pos", 3), ), #sun
	Vshader("po_to_noop_noviewproj", "po_to_noop_noviewproj.vert", "",
	("pos", 3), ), #sbox
	Vshader("po2_noop", "po2_noop.vert", "",
	("pos", 2), ), #
]
fshaders = [
	Fshader("cono_coli", "cono_coli.frag", "lightstruct"), #land
	Fshader("couvno_blendli", "couvno_blendli.frag", "lightstruct"), #ptn
	Fshader("co_sun", "co_sun.frag", "sunfrag"), #sun
	Fshader("depth01", "depth01.frag", ""), #sbox
	Fshader("landgen_normals", "landgen_normals.frag", ""), #landgen_diag
	Fshader("landgen_diag", "landgen_diag.frag", ""), #landgen_diag
	Fshader("landgen_horiz", "landgen_horiz.frag", ""), #landgen_horiz
	Fshader("landgen_notrel", "landgen_notrel.frag", ""), #landgen_notrel
	Fshader("debug_print_sampler", "debug_print_sampler.frag", ""), #ampler
]
gshaders = [
	Gshader("face_grey", "pouvno_facegrey.geom", ""),
	Gshader("po_facegrey", "po_facegrey.geom", "sungeom"),
	Gshader("pos_to_cubemap", "pos_to_cubemap.geom", ""),
]
tcshaders = [
	Tcshader("test", "test.tesc", "suntesc")
]
teshaders = [
	Teshader("test", "test.tese", "")
]
programs = [
	Program("land", "pocono_to_co_nomodel", "cono_coli", img1=0),
	Program("sun", "poin_poout_mvptrans", "co_sun", gsname="po_facegrey", tcsname="test", tesname="test"),
	Program("pointshadow", "po_to_noop_noviewproj", "depth01", gsname="pos_to_cubemap"),
	Program("ptn", "poteno_to_uv", "couvno_blendli"
			, gsname="face_grey"
			, sbox=0, img1=1),
	Program("landgen_normals", "po2_noop", "landgen_normals"),
	Program("landgen_diag", "po2_noop", "landgen_diag"),
	Program("landgen_horiz", "po2_noop", "landgen_horiz"),
	Program("landgen_notrel", "po2_noop", "landgen_notrel"),

	Program("debug_print_sampler", "po2_noop", "debug_print_sampler"),
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
#	Mesh("sun", "sun", objfile_enum="tetrahedron", recenter="true"),

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
