/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 13:06:40 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/30 13:58:07 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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

int				sp_init_env(t_env *e)
{
	ft_bzero(e, sizeof(*e));
	sp_register_instance(e);
	e->loop = true;
	return (0);
}

