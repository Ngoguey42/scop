/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_uniforms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 13:06:52 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/15 13:24:00 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <math.h>

void		item_unif_model(t_env const *e, GLuint loc)
{
	t_matrix4 const	mat = m4_translate_nonuniform((float [3]){0.f, 4.0f, 0.f});

	glUniformMatrix4fv(loc, 1, GL_TRUE, (float*)&mat);
	(void)e;
	return ;
}

void		item_unif_view(t_env const *e, GLuint loc)
{
	glUniformMatrix4fv(loc, 1, GL_TRUE, (float*)&e->view);	
	return ;
}

void		item_unif_projection(t_env const *e, GLuint loc)
{
	glUniformMatrix4fv(loc, 1, GL_TRUE, (float*)&e->projection);
	return ;
}
