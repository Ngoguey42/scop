/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/27 12:01:57 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/27 12:12:44 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	render_ob(t_env const *e, t_ob *ob)
{
	t_model const *const	mo = MOOFOB(e, ob);
	t_mesh const *const		me = MEOFMO(e, mo);

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
	ob->mat = m4_translate_nonuniform(ob->position);
	ob->mat = m4_rotationref_axis(&ob->mat, z_axis, ob->rotation.x);
	ob->mat = m4_rotationref_axis(&ob->mat, y_axis, ob->rotation.y);
	ob->mat = m4_rotationref_axis(&ob->mat, x_axis, ob->rotation.z);
	ob->mat = m4_scaleref_nonuniform(&ob->mat, ob->scale);
	ob->modified = false;
	return ;
	(void)e;
}

static t_bool	do_draw(t_env const *e, t_ob *ob)
{
	return (ob->hidden ? false : true);
	(void)e;
}

static t_bool	do_update(t_env const *e, t_ob *ob)
{
	return (ob->modified ? true : false);
	(void)e;
}

void		render_prog_obs(t_env const *e, t_program_index i)
{
	t_program const		*p = e->programs + i;
	t_ftvector const	*prv = e->obs + i;
	void				(*vsunif_update)();
	void				(*fsunif_update)();

	vsunif_update = VSOFP(e, p)->unif_update;
	fsunif_update = FSOFP(e, p)->unif_update;
	glUseProgram(p->handle);
	if (vsunif_update != NULL)
		vsunif_update(e, p);
	if (fsunif_update != NULL)
		fsunif_update(e, p);
	ftv_foreach_if((void*)prv, &update_ob, (void*)e, &do_update);
	ftv_foreach_if((void*)prv, &render_ob, (void*)e, &do_draw);
	return ;
}

void		sp_render_obs(t_env const *e)
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
}
