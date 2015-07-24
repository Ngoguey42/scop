/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/21 09:02:18 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/24 14:55:42 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	render_ob(t_env const *e, t_ob *ob)
{
	t_model const	*mo = MOOFOB(e, ob);
	t_mesh const	*me = MEOFMO(e, mo);
	
	if (mo->update_uniforms != NULL)
		mo->update_uniforms(e, ob);
	if (mo->texture != sp_no_texture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TOFMO(e, mo)->handle);
	}
	glBindVertexArray(me->handles[0]);
	glDrawElements(GL_TRIANGLES, 3 * me->faces.size, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	return ;
}

static void	update_ob(t_env const *e, t_ob *ob)
{
	if (ob->modified)
	{
		ob->mat = m4_translate_nonuniform(ob->position);
		ob->mat = m4_rotationref_axis(&ob->mat, z_axis, ob->rotation.x);
		ob->mat = m4_rotationref_axis(&ob->mat, y_axis, ob->rotation.y);
		ob->mat = m4_rotationref_axis(&ob->mat, x_axis, ob->rotation.z);
		ob->mat = m4_scaleref_nonuniform(&ob->mat, ob->scale);
		ob->modified = false;
	}
	return ;
	(void)e;
}


void		render_prog_obs(t_env const *e, t_program_index i)
{
	t_program const		*p = e->programs + i;
	t_ftvector const	*prv = e->obs + i;

	glUseProgram(p->handle);
	if (p->update_uniforms != NULL)
		p->update_uniforms(e, p);
	ftv_foreach((void*)prv, &update_ob, (void*)e);
	ftv_foreach((void*)prv, &render_ob, (void*)e);
	return ;
}

void		sp_render_obs(t_env const *e, double el)
{
	t_program_index		i;

	i = -1;
	while (++i < sp_num_programs)
	{
		if (e->obs[i].size == 0)
			continue ;
		render_prog_obs(e, i);
	}
	return ;
	(void)el;
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
