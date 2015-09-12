/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cog_loadconf2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/12 09:34:39 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/12 09:49:56 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

#define PROG(VS,FS,GS,TEXI) {VS, FS, GS, TEXI, 0}
#define TEXI(...) {__VA_ARGS__}
#define FTVU ftv_uninitialized()
#define MESH(...) {__VA_ARGS__, 0, {0, 0, 0}, false}
#define TEXTURE(FN) {TEXTURE_PATH(FN), GL_TEXTURE_2D, {0, 0}, 0}
#define MODEL(ME, TE, F) {(ME), (TE), (F)}


/*
**	[[[cog
**	import cog
**	cog.outl("*" "/")
**	from confloader import output_cconf2
**	output_cconf2()
**	cog.outl("/" "*")
**	]]]
*/
int			sp_loadconf_programs(t_env *e)
{
	t_program const		tmp[sp_num_programs] = {

	PROG(sp_pocono_to_co_nomodel_vshader, sp_cono_coli_fshader, sp_no_gshader
	, TEXI(0, -1)),
	PROG(sp_poteno_to_uv_vshader, sp_couvno_blendli_fshader
	, sp_face_grey_gshader, TEXI(1, 0)),
	PROG(sp_pocono_to_co_vshader, sp_cono_coli_fshader, sp_no_gshader
	, TEXI(-1, 0)),
	PROG(sp_poin_poout_mvptrans_vshader, sp_co_sun_fshader
	, sp_po_facegrey_gshader, TEXI(-1, -1)),
	PROG(sp_po_to_noop_noviewproj_vshader, sp_depth01_fshader
	, sp_pos_to_cubemap_gshader, TEXI(-1, -1)),
	};
	memcpy(&e->programs, &tmp, sizeof(tmp));
	return (0);
}

int			sp_loadconf_textures(t_env *e)
{
	t_texture const		tmp[sp_num_textures] = {

	TEXTURE("Porcelain.tga"),
	TEXTURE("Wall.tga"),
	TEXTURE("metal.tga"),
	};
	memcpy(&e->textures, &tmp, sizeof(tmp));
	return (0);
}

int			sp_loadconf_meshes(t_env *e)
{
	t_mesh const		tmp[sp_num_meshes] = {

	MESH(GL_DYNAMIC_DRAW, sp_ptn_program, sp_teapot1_objfile, &sp_meshfill_main
	, true, sp_no_ebogrouping, false, sp_box_texwrapping, {0.5f, 0.5f}),
	MESH(GL_STATIC_DRAW, sp_ptn_program, sp_cessna_objfile, &sp_meshfill_plane
	, false, sp_no_ebogrouping, false, sp_spherical_texwrapping, {1.0f, 1.0f}),
	MESH(GL_STATIC_DRAW, sp_sun_program, sp_dodecahedron_objfile
	, &sp_meshfill_sun, true, sp_no_ebogrouping, false, sp_spherical_texwrapping
	, {1.0f, 1.0f}),
	MESH(GL_STATIC_DRAW, sp_land_program, sp_ft_objfile, &sp_meshfill_land
	, false, sp_no_ebogrouping, false, sp_spherical_texwrapping, {1.0f, 1.0f}),
	};
	memcpy(&e->meshes, &tmp, sizeof(tmp));
	return (0);
}

int			sp_loadconf_models(t_env *e)
{
	t_model const		tmp[sp_num_models] = {

	MODEL(sp_main_mesh, sp_porcelain_texture, &sp_unif_model_mix),
	MODEL(sp_plane_mesh, sp_wall_texture, &sp_unif_model),
	MODEL(sp_land_mesh, sp_no_texture, NULL),
	MODEL(sp_sun_mesh, sp_no_texture, &sp_unif_model),
	};
	memcpy(&e->models, &tmp, sizeof(tmp));
	return (0);
}

/*
**	[[[end]]]
*/
