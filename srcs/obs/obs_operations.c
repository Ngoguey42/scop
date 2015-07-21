/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/21 09:02:18 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/21 09:20:18 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"


static void	render_ob(t_env const *e, double el, t_ob *ob)
{
	t_model const	*mo = MOOFOB(e, ob);
	t_mesh const	*me = MEOFMO(e, mo);
	t_program const	*p = POFME(e, me);

	if (mo->update_uniforms != NULL)
		mo->update_uniforms(e, ob);
	if (p->update_uniforms != NULL)
		p->update_uniforms(e, p);
	glUseProgram(p->handle);
	glBindVertexArray(me->handles[0]);
	glDrawElements(GL_TRIANGLES, 3 * me->faces.size, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	return ;
	(void)el;
}

void		sp_render_obs(t_env const *e, double el)
{
	t_ob		*ob;
	t_ob const	*end = ((t_ob*)e->obs.data) + e->obs.size;

	ob = e->obs.data;
	while (ob < end)
	{
		render_ob(e, el, ob);
		ob++;
	}
	return ;
}

void        sp_delete_obs(t_env *e)
{
	ftv_release(&e->obs, NULL); //todo
	return ;
}

int         sp_init_obs(t_env *e)
{
	if (ftv_init_instance(&e->obs, sizeof(t_ob)))
		sp_enomem();

	t_ob	ob[1];

	ob->model = sp_square_model;
	ob->position = ATOV3(0.f, 0.5f, 0.f);;
	ob->mat = m4_translate_nonuniform(ob->position);
	ftv_push_back(&e->obs, ob);
	return (0);
}
