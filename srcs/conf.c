/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 12:53:00 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 15:59:24 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

#ifndef NARG
# define NARG_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,N,...) N
# define NARG(...) NARG_(__VA_ARGS__,11,10,9,8,7,6,5,4,3,2,1)
#endif

#define PROG(VS,FS,P,...) {VS, FS, P, NARG(__VA_ARGS__), {__VA_ARGS__}, NULL, 0}

#define LOC_FLOAT(N, S) ((t_location){N, sizeof(GLfloat) * (S)})

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
	};
	memcpy(&e->shaders, &tmp, sizeof(tmp));
	return (0);
}

int				sp_loadconf_programs(t_env *e)
{
	t_program const		tmp[sp_num_programs] = {

	PROG(sp_basic_vertex, sp_basic_fragment, NULL,
	LOC_FLOAT("position", 3)),
	PROG(sp_tex_vertex, sp_tex_fragment, NULL,
	LOC_FLOAT("position", 3), LOC_FLOAT("color", 3), LOC_FLOAT("texCoord", 2)),
	PROG(sp_item_vertex, sp_item_fragment, NULL,
	LOC_FLOAT("position", 3), LOC_FLOAT("texCoord", 2)),
	};
	memcpy(&e->programs, &tmp, sizeof(tmp));
	return (0);
}

int				sp_loadconf_textures(t_env *e)
{
	t_texture const		tmp[sp_num_textures] = {

	{TEXTURE_PATH("Porcelain.tga"), 0},
	{TEXTURE_PATH("Wall.tga"), 0},
	};
	memcpy(&e->textures, &tmp, sizeof(tmp));
	return (0);
}

int				sp_loadconf_meshes(t_env *e)
{
	t_mesh const		tmp[sp_num_meshes] = {

	MESH(GL_STATIC_DRAW, sp_item_program, true, &sp_meshfill_item),
	};
	memcpy(&e->meshes, &tmp, sizeof(tmp));
	return (0);
}


int				sp_loadconf_models(t_env *e)
{
	// t_model const		tmp[sp_num_models] = {

		
	// };
	// memcpy(&e->models, &tmp, sizeof(tmp));
	(void)e;
	return (0);
}
