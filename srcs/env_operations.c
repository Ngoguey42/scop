/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 13:44:48 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/18 13:53:32 by ngoguey          ###   ########.fr       */
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
	ftv_release(&e->models, &sp_clean_objmodels);
	return ;
}

int				sp_init_env(t_env *e)
{
	bzero(e, sizeof(*e));
	e->cpos = ATOV3(0.f, 2.f, 6.f);
	e->cangles[0] = -(M_PI / 2);
	e->cangles[1] = 0.f;
	sp_register_instance(e);
	e->projection = m4_fovprojection(WIN_FOVF, WIN_RATIOF, WIN_NEARF, WIN_FARF);
	if (ftv_init_instance(&e->models, sizeof(t_objmodel)))
		sp_enomem();
	if (ftv_init_instance(&e->drawables, sizeof(t_drawable)))
		sp_enomem();
	return (0);
}
