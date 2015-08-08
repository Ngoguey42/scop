/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 12:53:00 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/08 12:18:59 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

#ifndef NARG
# define NARG_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,N,...) N
# define NARG(...) NARG_(__VA_ARGS__,11,10,9,8,7,6,5,4,3,2,1)
#endif

#define PROG(VS,FS,GS) {VS, FS, GS, 0}

#define LOC(N, S) ((t_location){N, (S)})

#define FTVU ftv_uninitialized()

#define VSHADER(N,F,...) {VSHD_PATH(N),F,NARG(__VA_ARGS__),{__VA_ARGS__},0}
#define FSHADER(N, F) {FSHD_PATH(N), (F), 0}
#define GSHADER(N, F) {GSHD_PATH(N), (F), 0}
#define MESH(P, U, F) {(U), (P), true, (F), FTVU, FTVU, {0, 0, 0}}
#define TEXTURE(FN) {TEXTURE_PATH(FN), {0, 0}, 0}
#define MODEL(ME, TE, F) {(ME), (TE), (F)}

/*
**	[[[cog
**	import cog
**	cog.outl("*" "/")
**	from scop_confloader import output_cconf
**	output_cconf()
**	cog.outl("/" "*")
**	]]]
*/
int			sp_loadconf_vshaders(t_env *e)
{
	t_vshader const		tmp[sp_num_vshaders] = {

	VSHADER("po_to_co.vert", &sp_unif_viewproj2,
	LOC("position", 3)),
	VSHADER("pocote_to_couv.vert", &sp_unif_viewproj2,
	LOC("position", 3), LOC("color", 3), LOC("texCoord", 2)),
	VSHADER("pote_to_couv.vert", &sp_unif_viewproj2,
	LOC("position", 3), LOC("texCoord", 2)),
	VSHADER("poco_to_co.vert", &sp_unif_viewproj,
	LOC("position", 3), LOC("color", 3)),
	VSHADER("poteno_to_uv.vert", &sp_unif_viewproj,
	LOC("position", 3), LOC("texCoord", 2), LOC("normal", 3)),
	VSHADER("pocono_to_co.vert", &sp_unif_viewproj,
	LOC("position", 3), LOC("color", 3), LOC("normal", 3)),
	VSHADER("po_to_noop.vert", &sp_unif_viewproj,
	LOC("position", 3)),
	};
	memcpy(&e->vshaders, &tmp, sizeof(tmp));
	return (0);
}

int			sp_loadconf_fshaders(t_env *e)
{
	t_fshader const		tmp[sp_num_fshaders] = {

	FSHADER("co_identity.frag", NULL),
	FSHADER("uv_identity.frag", NULL),
	FSHADER("couv_blend.frag", NULL),
	FSHADER("couv_uv.frag", NULL),
	FSHADER("uvno_uvli.frag", &sp_unif_light),
	FSHADER("cono_coli.frag", &sp_unif_light),
	FSHADER("couvno_blendli.frag", &sp_unif_light),
	FSHADER("co_sun.frag", &sp_unif_suncolor),
	};
	memcpy(&e->fshaders, &tmp, sizeof(tmp));
	return (0);
}

int			sp_loadconf_gshaders(t_env *e)
{
	t_gshader const		tmp[sp_num_gshaders] = {

	GSHADER("test.geom", NULL),
	};
	memcpy(&e->gshaders, &tmp, sizeof(tmp));
	return (0);
}

int			sp_loadconf_programs(t_env *e)
{
	t_program const		tmp[sp_num_programs] = {

	PROG(sp_po_to_co_vshader, sp_co_identity_fshader, sp_no_gshader),
	PROG(sp_pocote_to_couv_vshader, sp_couv_uv_fshader, sp_no_gshader),
	PROG(sp_pote_to_couv_vshader, sp_couv_uv_fshader, sp_no_gshader),
	PROG(sp_pocono_to_co_vshader, sp_cono_coli_fshader, sp_no_gshader),
	PROG(sp_poteno_to_uv_vshader, sp_couvno_blendli_fshader, sp_test_gshader),
	PROG(sp_pocono_to_co_vshader, sp_cono_coli_fshader, sp_no_gshader),
	PROG(sp_po_to_noop_vshader, sp_co_sun_fshader, sp_no_gshader),
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

	MESH(sp_ptn_program, GL_STATIC_DRAW, &sp_meshfill_plane),
	MESH(sp_pcn_program, GL_STATIC_DRAW, &sp_meshfill_square),
	MESH(sp_land_program, GL_STATIC_DRAW, &sp_meshfill_land),
	MESH(sp_ptn_program, GL_STATIC_DRAW, &sp_meshfill_ptn),
	MESH(sp_sun_program, GL_STATIC_DRAW, &sp_meshfill_sun),
	};
	memcpy(&e->meshes, &tmp, sizeof(tmp));
	return (0);
}

int			sp_loadconf_models(t_env *e)
{
	t_model const		tmp[sp_num_models] = {

	MODEL(sp_plane_mesh, sp_porcelain_texture, &sp_unif_model),
	MODEL(sp_square_mesh, sp_no_texture, &sp_unif_model),
	MODEL(sp_land_mesh, sp_no_texture, &sp_unif_model),
	MODEL(sp_ptn_mesh, sp_metal_texture, &sp_unif_model),
	MODEL(sp_sun_mesh, sp_no_texture, &sp_unif_model),
	};
	memcpy(&e->models, &tmp, sizeof(tmp));
	return (0);
}

/*
**	[[[end]]]
*/
