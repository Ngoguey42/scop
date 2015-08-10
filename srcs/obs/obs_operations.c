/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/21 09:02:18 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/10 13:51:36 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		sp_delete_obs(t_env *e)
{
	int		i;

	i = 0;
	while (i < sp_num_programs)
		ftl_release(e->obs + i++, NULL);
	return ;
}

int			sp_init_obs(t_env *e)
{
	int		i;

	i = 0;
	while (i < sp_num_programs)
		ftl_init_instance(e->obs + i++, sizeof(t_ob));
	sp_fill_obs(e);
	return (0);
}

t_bool		sp_ob_getnot_hidden(t_env const *e, t_ob const *ob)
{
	return (!ob->hidden);
	(void)e;
}

t_bool		sp_ob_get_moved(t_env const *e, t_ob const *ob)
{
	return (ob->moved);
	(void)e;
}

t_ob		sp_default_ob(t_model_index moi)
{
	return ((t_ob){{NULL, NULL}, false, true, false, moi,
		{0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}
		, m4_identity(), NULL, {0.f}, {0}});
}
