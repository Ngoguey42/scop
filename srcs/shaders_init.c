/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 16:52:38 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/30 17:42:05 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int		check_program_error(GLuint program, GLuint flag)
{
	GLint		success[1];
	GLchar		msg[256];

	glGetProgramiv(program, flag, success);
	if(*success == GL_FALSE)
	{
		glGetProgramInfoLog(program, sizeof(msg), NULL, msg);
		DEBUGF("Error with program: \"\033[35m%s\033[0m\"", msg);
		return (1);
	}
	return (0);
}

int				sp_init_shaders(t_env *e)
{
	e->program_shader = glCreateProgram();

	if (sp_create_shader(VSHADER_PATH, GL_VERTEX_SHADER, &e->vert_shader))
		return (DEBUGF("Error while creating %s", VSHADER_PATH), 1);
	if (sp_create_shader(FSHADER_PATH, GL_FRAGMENT_SHADER, &e->frag_shader))
		return (DEBUG("Error while loading fragment shader"), 1);
	glAttachShader(e->program_shader, e->vert_shader);
	glAttachShader(e->program_shader, e->frag_shader);
	glBindAttribLocation(e->program_shader, 0, "position");
	glLinkProgram(e->program_shader);
	if (check_program_error(e->program_shader, GL_LINK_STATUS))
		return (DEBUG("Error while linking program shader"), 1);
	glValidateProgram(e->program_shader);
	if (check_program_error(e->program_shader, GL_LINK_STATUS))
		return (DEBUG("Error while validating program shader"), 1);
	return (0);
}
