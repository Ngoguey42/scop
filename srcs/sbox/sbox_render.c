/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sbox_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/22 12:21:49 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/12 08:35:09 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <math.h>
#include <string.h>

static void	render_ob(t_env const *const e, t_ob const *const ob)
{
	t_mesh const *const		me = MEOFOB(e, ob);
	t_program const *const	p = e->programs + sp_pointshadow_program;

	UNIF(p, mMatrix4fv, "model", 1, GL_TRUE, (float*)&ob->mat);
	glBindVertexArray(me->handles[0]);
	glDrawElements(GL_TRIANGLES, me->faces3, GL_UNSIGNED_INT, 0);
	return ;
}

static void	update_uniforms(t_env const *e, t_program const *p)
{
	int			i;
	char		buf[32];

	strcpy(buf, "shadowMatrices[?]");
	i = 0;
	while (i < 6)
	{
		buf[15] = i + '0';
		UNIF(p, mMatrix4fv, buf, 1, GL_TRUE, (float*)(e->sbox_viewproj + i));
		i++;
	}
	UNIF(p, m1f, "far", e->sbox_farplane);
	UNIF(p, m3fv, "lpos", 1, (float*)&e->sunpos_cartesian);
	return ;
}

void		sp_render_sbox(t_env const *e)
{
	t_program const *const	p = e->programs + sp_pointshadow_program;
	t_program_index			i;

	glBindFramebuffer(GL_FRAMEBUFFER, e->sbox_fbo);
	glViewport(0, 0, e->sbox_texture.dim[0], e->sbox_texture.dim[1]);
	glClear(GL_DEPTH_BUFFER_BIT);
	glUseProgram(p->handle);
	update_uniforms(e, p);
	i = -1;
	while (++i < sp_num_programs)
		ftl_foreach_if(e->obs + i, &render_ob, (void*)e, &sp_ob_get_shadow);
	glBindVertexArray(0);
	return ;
}
