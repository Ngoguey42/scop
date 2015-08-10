/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cogconf2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/08 14:03:56 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/10 13:14:20 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

#define FTVU ftv_uninitialized()
#define MESH(P, U, F) {(U), (P), (F), FTVU, FTVU, {0, 0, 0}}
#define TEXTURE(FN) {TEXTURE_PATH(FN), {0, 0}, 0}
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
