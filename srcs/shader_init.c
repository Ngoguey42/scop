/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 15:42:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/30 16:15:31 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int				sp_init_shaders(t_env *e)
{
	if (sp_create_shader(VSHADER_PATH, GL_VERTEX_SHADER, &e->vert_shader))
		return (DEBUG("Error while loading vertex shader"), 1);
	if (sp_create_shader(FSHADER_PATH, GL_FRAGMENT_SHADER, &e->frag_shader))
		return (DEBUG("Error while loading fragment shader"), 1);
	
	return (0);
}
