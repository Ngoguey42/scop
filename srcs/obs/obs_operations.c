/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/21 09:02:18 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/10 16:19:40 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#define HATEIT1(MOI) .list={NULL, NULL}, false, true, false, (MOI)
#define HATEIT2 {0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}
#define HATEIT3 m4_identity(), NULL, {0.f}, {0}

#define OB(MOI) ((t_ob){HATEIT1((MOI)), HATEIT2, HATEIT3})

t_ob		sp_default_ob(t_model_index moi)
{
	return ((t_ob){HATEIT1(moi), HATEIT2, HATEIT3});
}

#include <string.h>

void		sp_delete_obs(t_env *e)
{
	int		i;

	/* t_ob		ob; */

	/* memcpy(&ob, &OB(sp_plane_model), sizeof(t_ob)); */
	/* memcpy(&ob, (t_ob[1]){sp_default_ob(sp_plane_model)}, sizeof(t_ob)); */
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
