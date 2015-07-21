/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 13:44:48 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/21 11:29:11 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>
#include <math.h>

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
	sp_delete_obs(e);
	return ;
}

int				sp_init_env(t_env *e)
{
	sp_register_instance(e);
	bzero(e, sizeof(*e));
	e->cpos = ATOV3(0.f, 2.f, 6.f);
	e->cangles[0] = -(M_PI / 2);
	e->cangles[1] = 0.f;
	e->projection = m4_fovprojection(WIN_FOVF, WIN_RATIOF, WIN_NEARF, WIN_FARF);
	e->view = m4_lookat(ATOV3(e->cpos.x, e->cpos.y, e->cpos.z),
						v3_add(ATOV3(e->cpos.x, e->cpos.y, e->cpos.z),
						v3_frontnormed(e->cangles)));
	sp_init_obs(e);
	if (sp_loadconf_shaders(e) || sp_loadconf_programs(e)
		|| sp_loadconf_textures(e) || sp_loadconf_meshes(e)
		|| sp_loadconf_models(e))
		return (1);
	return (0);
}
