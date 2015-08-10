/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 13:44:32 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/10 12:56:50 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <math.h>

static void	push_ob(t_env *e, t_ob const *ob)
{
	t_program_index const	pi = MEOFOB(e, ob)->program;

	if (ftl_push_back(e->obs + pi, (t_ftlist_node const*)ob))
		sp_enomem();
	return ;
}

t_ob		default_ob(t_model_index moi)
{
	return ((t_ob){{NULL, NULL}, false, true, false, moi,
			{0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}
			, m4_identity(), NULL, {0.f}, {0}});
}

int			sp_fill_obs(t_env *e)
{
	{
		t_ob    ob[1];

		*ob = default_ob(sp_plane_model);
		push_ob(e, ob);
	}
	{
		t_ob    ob[1];

		*ob = default_ob(sp_square_model);
		ob->scale = ATOV3(4.f, 4.f, 4.f);
		ob->position = ATOV3(0.f, -5.f, 2.f);
		push_ob(e, ob);
	}
	{
		t_ob    ob[1];

		*ob = default_ob(sp_land_model);
		push_ob(e, ob);
	}
	{
		t_ob    ob[1];

		*ob = default_ob(sp_ptn_model);
		ob->rotation = ATOV3(0.f, 0.f, -M_PI / 2.f);
		ob->scale = ATOV3(1.f, 1.f, 1.f);
		ob->position = ATOV3(-45.f, -0.f, -40.f);
		push_ob(e, ob);
	}
	{
		t_ob    ob[1];

		*ob = default_ob(sp_sun_model);
		ob->update = &sp_obupdate_sun;
		ob->moved = false;
		push_ob(e, ob);
	}
	return (0);
}
