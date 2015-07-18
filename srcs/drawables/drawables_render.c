/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawables_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/18 14:18:18 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/18 14:30:58 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		render_drawable(t_env *e, t_drawable *d)
{
	size_t		i;

	glUseProgram(e->programs[d->prog]);
	i = 0;
	while (i < d->n_textures)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, d->textures[i]);
		i++;
	}
	glBindVertexArray(d->mesh.desc[0]);
	sp_update_uniforms(e, d->prog, e->programs[d->prog]);
	glDrawElements(GL_TRIANGLES, d->mesh.n_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	return ;
}

void			sp_render_drawables(t_env *e)
{
	t_drawable	*d;
	t_drawable	*end;

	d = e->drawables.data;
	end = e->drawables.data + sizeof(t_drawable) * e->drawables.size;
	while (d != end)
		render_drawable(e, d++);
	return ;
}
