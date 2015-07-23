/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 13:44:32 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/23 14:10:57 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	push_ob(t_env *e, t_ob const *ob)
{
	t_program_index const	pi = MEOFOB(e, ob)->program;

	ftv_push_back(e->obs + pi, ob);
	return ;
}

int			sp_fill_obs(t_env *e)
{
	(void)e;
	(void)push_ob;
	t_ob    ob[1];

	ob->model = sp_item_model;
	ob->rotation = ATOV3(0.f, 0.f, 0.f);
	ob->scale = ATOV3(1.f, 1.f, 1.f);
	ob->position = ATOV3(-0.f, -0.f, 0.f);
	/* ob->mat = m4_translate_nonuniform(ob->position); */
	push_ob(e, ob);
	
	ob->model = sp_square_model;
	ob->rotation = ATOV3(0.f, 0.f, 0.f);
	ob->scale = ATOV3(1.f, 1.f, 1.f);
	ob->position = ATOV3(0.f, 0.f, -5.f);
	/* ob->mat = m4_translate_nonuniform(ob->position); */
	push_ob(e, ob);

	ob->model = sp_land_model;
	push_ob(e, ob);
	
	ob->model = sp_item2_model;
	ob->position = ATOV3(-5.f, -0.f, -5.f);
	ob->rotation = ATOV3(0.f, 0.f, 0.f);
	ob->scale = ATOV3(.5f, .5f, .5f);
	push_ob(e, ob);
	return (0);
}
