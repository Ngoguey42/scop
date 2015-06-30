/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 16:49:56 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/30 16:52:54 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void				sp_clean_shaders(t_env *e)
{
	glDetachShader(e->program_shader, e->vert_shader);
	glDeleteShader(e->vert_shader);
	glDetachShader(e->program_shader, e->frag_shader);
	glDeleteShader(e->frag_shader);
	glDeleteProgram(e->program_shader);
}
