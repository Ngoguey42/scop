/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/27 12:01:57 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/15 16:54:36 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#define NORM_AT_42_IS_WTF(E, OB, MO) (MO)->update_uniforms((E), (OB))

static void		render_ob(t_env const *e, t_ob *ob)
{
	t_model const *const	mo = MOOFOB(e, ob);
	t_mesh const *const		me = MEOFMO(e, mo);

	if (mo->update_uniforms != NULL)
		NORM_AT_42_IS_WTF(e, ob, mo);
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

static void		update_matrix_ob(t_env const *e, t_ob *ob)
{
	ob->mat = m4_translate_nonuniform(ob->position);
	ob->mat = m4_rotationref_axis(&ob->mat, z_axis, ob->rotation.x);
	ob->mat = m4_rotationref_axis(&ob->mat, y_axis, ob->rotation.y);
	ob->mat = m4_rotationref_axis(&ob->mat, x_axis, ob->rotation.z);
	ob->mat = m4_scaleref_nonuniform(&ob->mat, ob->scale);
	ob->moved = false;
	return ;
	(void)e;
}

void			render_prog_obs(t_env const *e, t_program_index i)
{
	t_program const	*const	p = e->programs + i;
	t_ftlist const *const	prl = e->obs + i;
	void					(*vsunif_update)();
	void					(*fsunif_update)();

	vsunif_update = VSOFP(e, p)->unif_update;
	fsunif_update = FSOFP(e, p)->unif_update;
	glUseProgram(p->handle);
	if (vsunif_update != NULL)
		vsunif_update(e, p);
	if (fsunif_update != NULL)
		fsunif_update(e, p);
	ftl_foreach_if((void*)prl, &update_matrix_ob, (void*)e, &sp_ob_get_moved);
	ftl_foreach_if((void*)prl, &render_ob, (void*)e, &sp_ob_getnot_hidden);
	return ;
}

void			sp_render_obs(t_env const *e)
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
