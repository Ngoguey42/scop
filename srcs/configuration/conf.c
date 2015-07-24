/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 12:53:00 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/24 15:06:26 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

#ifndef NARG
# define NARG_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,N,...) N
# define NARG(...) NARG_(__VA_ARGS__,11,10,9,8,7,6,5,4,3,2,1)
#endif

#define PROG(VS,FS,P,...) {VS, FS, P, NARG(__VA_ARGS__), {__VA_ARGS__}, 0}

#define LOC(N, S) ((t_location){N, (S)})

#define FTVU ftv_uninitialized()
#define MESH(US, P, IN, FI) {(US), (P), (IN), (FI), FTVU, FTVU, {0, 0, 0}}

int				sp_loadconf_shaders(t_env *e)
{
	t_shader const		tmp[sp_num_shaders] = {

	{SHADER_PATH("scop.vert"), GL_VERTEX_SHADER, 0},
	{SHADER_PATH("scop.frag"), GL_FRAGMENT_SHADER, 0},
	{SHADER_PATH("tex.vert"), GL_VERTEX_SHADER, 0},
	{SHADER_PATH("tex.frag"), GL_FRAGMENT_SHADER, 0},
	{SHADER_PATH("item.vert"), GL_VERTEX_SHADER, 0},
	{SHADER_PATH("item.frag"), GL_FRAGMENT_SHADER, 0},
	{SHADER_PATH("land.vert"), GL_VERTEX_SHADER, 0},
	{SHADER_PATH("land.frag"), GL_FRAGMENT_SHADER, 0},
	{SHADER_PATH("ptn.vert"), GL_VERTEX_SHADER, 0},
	{SHADER_PATH("ptn.frag"), GL_FRAGMENT_SHADER, 0},
	};
	memcpy(&e->shaders, &tmp, sizeof(tmp));
	return (0);
}

int				sp_loadconf_programs(t_env *e)
{
	t_program const		tmp[sp_num_programs] = {

	PROG(sp_p_vertex, sp_p_fragment, &sp_unif_viewproj2,
	LOC("position", 3)),
	PROG(sp_pct_vertex, sp_pct_fragment, &sp_unif_viewproj2,
	LOC("position", 3), LOC("color", 3), LOC("texCoord", 2)),
	PROG(sp_pt_vertex, sp_pt_fragment, &sp_unif_viewproj2,
	LOC("position", 3), LOC("texCoord", 2)),
	PROG(sp_land_vertex, sp_land_fragment, &sp_unif_viewproj,
	LOC("position", 3), LOC("color", 3)),
	PROG(sp_ptn_vertex, sp_ptn_fragment, &sp_unif_viewproj2,
	LOC("position", 3), LOC("texCoord", 2), LOC("normal", 3)),
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

	MESH(GL_STATIC_DRAW, sp_pt_program, true, &sp_meshfill_item),
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

	{sp_item_mesh, sp_metal_texture, &sp_unif_model},
	{sp_square_mesh, sp_no_texture, &sp_unif_model},
	{sp_land_mesh, sp_no_texture, &sp_unif_land},
	{sp_plane_mesh, sp_metal_texture, &sp_unif_model},
	};
	memcpy(&e->models, &tmp, sizeof(tmp));
	return (0);
}
