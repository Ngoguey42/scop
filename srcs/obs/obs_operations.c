/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/21 09:02:18 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/27 12:02:03 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void        sp_delete_obs(t_env *e)
{
	int		i;

	i = 0;
	while (i < sp_num_programs)
		ftv_release(e->obs + i++, NULL);
	return ;
}

int         sp_init_obs(t_env *e)
{
	int		i;

	i = 0;
	while (i < sp_num_programs)
	{
		if (ftv_init_instance(e->obs + i, sizeof(t_ob)))
			sp_enomem();
		i++;
	}
	sp_fill_obs(e);
	return (0);
}
