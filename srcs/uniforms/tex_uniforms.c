/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_uniforms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 14:27:18 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/18 13:48:07 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <math.h>

void		tex_unif_model(t_env const *e, GLuint loc)
{
	t_matrix4 const	mat = m4_translate_nonuniform((float[3]){0.f, 4.f, 0.f});

	glUniformMatrix4fv(loc, 1, GL_TRUE, (float*)&mat);
	(void)e;
	return ;
}

void		tex_unif_view(t_env const *e, GLuint loc)
{
	glUniformMatrix4fv(loc, 1, GL_TRUE, (float*)&e->view);
	return ;
}

void		tex_unif_projection(t_env const *e, GLuint loc)
{
	glUniformMatrix4fv(loc, 1, GL_TRUE, (float*)&e->projection);
	return ;
}

void		tex_unif_texture(t_env const *e, GLuint loc)
{
	glUniform1i(loc, 0);
	(void)e;
	return ;
}
