/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 13:44:48 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/27 16:59:17 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>
#include <math.h>

#define CONCAT(NAME) sp_loadconf_ ## NAME
#define L(NAME, ENV) CONCAT(NAME)(ENV)
#define COMP_LIT(TYPE) (TYPE){__VA_ARGS__}
#define FUCK_NORM (t_texture){NULL, GL_TEXTURE_CUBE_MAP, {1024, 1024}, 0}

static t_env	*sp_register_instance(t_env *e)
{
	static t_env		*ptr = NULL;

	if (e != NULL)
		ptr = e;
	return (ptr);
}

t_env			*sp_instance(void)
{
	return (sp_register_instance(NULL));
}

void			sp_clean_env(t_env *e)
{
	(void)e;
	return ;
}

int				sp_init_env(t_env *e)
{
	sp_register_instance(e);
	bzero(e, sizeof(*e));
	e->sunpos_spherical = ATOV3(30.f, M_PI / 4.f, M_PI / 4.f);
	e->sunka = ATOV3(255.f / 255.f, 203.f / 255.f, 92.f / 255.f);
	e->sunkd = ATOV3(255.f / 255.f, 203.f / 255.f, 92.f / 255.f);
	e->sunks = ATOV3(255.f / 255.f, 203.f / 255.f, 92.f / 255.f);
	memcpy(&e->sundat, ((float[2]){0.007, 0.0002}), sizeof(float[2]));
	memcpy(&e->sbox_texture, &(FUCK_NORM), sizeof(t_texture));
	e->sbox_farplane = 150.f;
	e->sbox_proj = m4_fovprojection(M_PI / 2.f, 1.f, 1.f, e->sbox_farplane);
	sp_update_sunpos(e, true);
	e->cpos = DEFAULT_CPOS_V3;
	memcpy(&e->cangles, DEFAULT_CANGLES, sizeof(DEFAULT_CANGLES));
	e->projection = m4_fovprojection(WIN_FOVF, WIN_RATIOF, WIN_NEARF, WIN_FARF);
	sp_update_campos(e, true);
	e->states[sp_window_focused_state] = 1;
	if (L(vshaders, e) || L(fshaders, e) || L(gshaders, e) || L(programs, e)
		|| L(textures, e) || L(meshes, e) || L(models, e))
		return (1);
	return (0);
}
