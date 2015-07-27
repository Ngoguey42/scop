/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 12:53:00 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/27 14:48:04 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

#ifndef NARG
# define NARG_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,N,...) N
# define NARG(...) NARG_(__VA_ARGS__,11,10,9,8,7,6,5,4,3,2,1)
#endif

#define PROG(VS,FS) {VS, FS, 0}

#define LOC(N, S) ((t_location){N, (S)})

#define FTVU ftv_uninitialized()
#define MESH(US, P, IN, FI) {(US), (P), (IN), (FI), FTVU, FTVU, {0, 0, 0}}

#define VSHADER(N, F, ...) {SHD_PATH(N), F, NARG(__VA_ARGS__), {__VA_ARGS__}, 0}
#define FSHADER(N, F) {SHD_PATH(N), F, 0}

int				sp_loadconf_vshaders(t_env *e)
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
	};
	memcpy(&e->vshaders, &tmp, sizeof(tmp));
	return (0);
}

int				sp_loadconf_fshaders(t_env *e)
{
	t_fshader const		tmp[sp_num_fshaders] = {

	FSHADER("co_identity.frag", NULL),
	FSHADER("uv_identity.frag", NULL),
	FSHADER("couv_blend.frag", NULL),
	FSHADER("couv_uv.frag", NULL),
	FSHADER("uvno_uvli.frag", &sp_unif_light),
	};
	memcpy(&e->fshaders, &tmp, sizeof(tmp));
	return (0);
}

int				sp_loadconf_programs(t_env *e)
{
	t_program const		tmp[sp_num_programs] = {

	PROG(sp_po_to_co_vshader, sp_co_identity_fshader),
	PROG(sp_pocote_to_couv_vshader, sp_couv_uv_fshader),
	PROG(sp_pote_to_couv_vshader, sp_couv_uv_fshader),
	PROG(sp_poco_to_co_vshader, sp_co_identity_fshader),
	PROG(sp_poteno_to_uv_vshader, sp_uvno_uvli_fshader),
	/* PROG(sp_poteno_to_uv_vshader, sp_uv_identity_fshader), */
	};
	memcpy(&e->programs, &tmp, sizeof(tmp));
	return (0);
}

int				sp_loadconf_textures(t_env *e)
{
	t_texture const		tmp[sp_num_textures] = {

	{TEXTURE_PATH("Porcelain.tga"), 0},
	{TEXTURE_PATH("Wall.tga"), 0},
	{TEXTURE_PATH("Metal.tga"), 0},
	};
	memcpy(&e->textures, &tmp, sizeof(tmp));
	return (0);
}

int				sp_loadconf_meshes(t_env *e)
{
	t_mesh const		tmp[sp_num_meshes] = {

	MESH(GL_STATIC_DRAW, sp_pt_program, true, &sp_meshfill_plane),
	MESH(GL_STATIC_DRAW, sp_p_program, true, &sp_meshfill_square),
	MESH(GL_STATIC_DRAW, sp_land_program, true, &sp_meshfill_land),
	MESH(GL_STATIC_DRAW, sp_ptn_program, true, &sp_meshfill_item2),
	};
	memcpy(&e->meshes, &tmp, sizeof(tmp));
	return (0);
}

int				sp_loadconf_models(t_env *e)
{
	t_model const		tmp[sp_num_models] = {

	{sp_plane_mesh, sp_metal_texture, &sp_unif_model},
	{sp_square_mesh, sp_no_texture, &sp_unif_model},
	{sp_land_mesh, sp_no_texture, &sp_unif_land},
	{sp_ptn_mesh, sp_metal_texture, &sp_unif_model},
	};
	memcpy(&e->models, &tmp, sizeof(tmp));
	return (0);
}
