/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/30 13:49:29 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/16 19:09:06 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <math.h>

void		sp_obupdate_mainob(t_env const *e, t_ob *ob)
{
	if (ob->vali[0] > 0)
	{
		ob->valf[0] += e->time_el / 2;
		if (ob->valf[0] > 1.f)
		{
			ob->vali[0] = 0;
			ob->valf[0] = 1.f;
		}
	}
	else if (ob->vali[0] < 0)
	{
		ob->valf[0] -= e->time_el / 2;
		if (ob->valf[0] < 0.f)
		{
			ob->vali[0] = 0;
			ob->valf[0] = 0.f;
		}
	}
	return ;
}

void		sp_obupdate_sun(t_env const *e, t_ob *ob)
{
	ob->mat = m4_translate_nonuniform(e->sunpos_cartesian);
	return ;
}
