/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 13:06:40 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/13 15:02:59 by ngoguey          ###   ########.fr       */
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
	ftv_release(&e->models, &sp_clean_models);
	return ;
}

int				sp_init_env(t_env *e)
{
	bzero(e, sizeof(*e));
	e->pos[0] = 0.f;
	e->pos[1] = 2.f;
	e->pos[2] = 6.f;
	e->cangles[0] = -(M_PI / 2);
	e->cangles[1] = 0.f;
	sp_register_instance(e);
	e->loop = true;
	if (ftv_init_instance(&e->models, sizeof(t_objmodel)))
		sp_enomem();
	return (0);
}
