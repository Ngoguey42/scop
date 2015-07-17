/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_uniforms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 14:27:18 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/17 14:29:37 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <math.h>

void		item_tex_model(t_env const *e, GLuint loc)
{
	t_matrix4 const	mat = m4_translate_nonuniform((float[3]){0.f, 4.f, 0.f});

	glUniformMatrix4fv(loc, 1, GL_TRUE, (float*)&mat);
	(void)e;
	return ;
}

void		item_tex_view(t_env const *e, GLuint loc)
{
	glUniformMatrix4fv(loc, 1, GL_TRUE, (float*)&e->view);	
	return ;
}

void		item_tex_projection(t_env const *e, GLuint loc)
{
	glUniformMatrix4fv(loc, 1, GL_TRUE, (float*)&e->projection);
	return ;
}
