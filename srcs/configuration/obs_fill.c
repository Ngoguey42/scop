/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 13:44:32 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/27 18:33:44 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <math.h>

static void	push_ob(t_env *e, t_ob const *ob)
{
	t_program_index const	pi = MEOFOB(e, ob)->program;

	if (ftv_push_back(e->obs + pi, ob))
		sp_enomem();
	return ;
}

int			sp_fill_obs(t_env *e)
{
	{
		t_ob    ob[1];

		ob->hidden = false;
		ob->modified = true;
		ob->model = sp_plane_model;
		ob->rotation = ATOV3(0.f, 0.f, 0.f);
		ob->scale = ATOV3(1.f, 1.f, 1.f);
		/* ob->scale = ATOV3(0.1f, 0.1f, 0.1f); */
		ob->position = ATOV3(-0.f, -0.f, -0.f);
		push_ob(e, ob);
	}
	{
		t_ob    ob[1];

		ob->hidden = false;
		ob->modified = true;
		ob->model = sp_square_model;
		ob->rotation = ATOV3(0.f, 0.f, 0.f);
		ob->scale = ATOV3(1.f, 1.f, 1.f);
		ob->position = ATOV3(0.f, 0.f, 2.f);
		push_ob(e, ob);
	}
	{
		t_ob    ob[1];

		ob->hidden = false;
		ob->modified = true;
		ob->model = sp_land_model;
		push_ob(e, ob);	
	}
	{
		t_ob    ob[1];

		ob->hidden = false;
		ob->modified = true;
		ob->model = sp_ptn_model;
		/* ob->rotation = ATOV3(0.f, 0.f, 0.f); */
		ob->rotation = ATOV3(0.f, 0.f, -M_PI / 2.f);
		ob->scale = ATOV3(0.2f, 0.2f, 0.2f);
		/* ob->scale = ATOV3(0.05f, 0.05f, 0.05f); */
		/* ob->scale = ATOV3(1.f, 1.f, 1.f); */
		ob->position = ATOV3(-0.f, -0.f, -20.f);
		push_ob(e, ob);
	}
	return (0);
}
