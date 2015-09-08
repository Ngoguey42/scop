/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cog_loadconf2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/24 15:54:06 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/03 18:59:49 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

#define FTVU ftv_uninitialized()
#define MESH(...) {__VA_ARGS__, 0, {0, 0, 0}, false}
/* #define MESH(P, U, F) {(U), (P), "", (F), NULL, NULL, true, true, {1.f, 1.f}, 0.f, {0, 0, 0}, true} */
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
