/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/21 09:02:18 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/22 14:30:41 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	render_ob(t_env const *e, double el, t_ob *ob)
{
	t_model const	*mo = MOOFOB(e, ob);
	t_mesh const	*me = MEOFMO(e, mo);
	/* t_program const	*p = POFME(e, me); */

	/* glUseProgram(p->handle); */
	if (mo->update_uniforms != NULL)
		mo->update_uniforms(e, ob);
	/* if (p->update_uniforms != NULL) */
	/* 	p->update_uniforms(e, p); */
	if (mo->texture != sp_no_texture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TOFMO(e, mo)->handle);
	}
	glBindVertexArray(me->handles[0]);
	glDrawElements(GL_TRIANGLES, 3 * me->faces.size, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	return ;
	(void)el;
}

void		render_prog_obs(t_env const *e, double el, t_program_index i)
{
	t_program const		*p = e->programs + i;
	t_ftvector const	*prv = e->obs + i;
	t_ob				*ob;
	t_ob const			*obend;

	glUseProgram(p->handle);
	if (p->update_uniforms != NULL)
		p->update_uniforms(e, p);
	ob = prv->data;
	obend = ob + prv->size;
	while (ob < obend)
	{
		render_ob(e, el, ob);
		ob++;
	}
	return ;
	(void)el;
}

void		sp_render_obs(t_env const *e, double el)
{
	t_program_index		i;

	i = 0;
	while (i < sp_num_programs)
	{
		if (e->obs[i].size == 0)
			continue ;
		render_prog_obs(e, el, i);
		i++;
	}	
	return ;
}

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
	t_ob	ob[1];

	i = 0;
	while (i < sp_num_programs)
	{
		if (ftv_init_instance(e->obs + i, sizeof(t_ob)))
			sp_enomem();
		i++;
	}
	sp_fill_obs(e);
	/* ob->scale = ; */
	ob->model = sp_item_model;
	/* ob->position = ATOV3(-0.f, -0.f, 0.f);; */
	/* ob->mat = m4_translate_nonuniform(ob->position); */
	/* ftv_push_back(&e->obs, ob); */
	/* ob->model = sp_square_model; */
	/* ob->position = ATOV3(0.f, 0.f, -5.f);; */
	/* ob->mat = m4_translate_nonuniform(ob->position); */
	/* ftv_push_back(&e->obs, ob); */
	/* ob->model = sp_land_model; */
	/* ob->position = ATOV3(0.f, -15.f, 0.f);; */
	/* ob->mat = m4_translate_nonuniform(ob->position); */
	/* ftv_push_back(&e->obs, ob); */
	return (0);
}
