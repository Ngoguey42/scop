/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/01 12:32:53 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 14:15:28 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int		check_program_error(GLuint program, GLuint flag)
{
	GLint		success[1];
	GLchar		msg[256];

	glGetProgramiv(program, flag, success);
	if (*success == GL_FALSE)
	{
		glGetProgramInfoLog(program, sizeof(msg), NULL, msg);
		qprintf("\033[35m%s\033[0m", msg);
		return (1);
	}
	return (0);
}

static int		new_program(t_env const *e, t_program *p)
{
	size_t		i;

	p->handle = glCreateProgram();
	glAttachShader(p->handle, e->shaders[p->vshader].handle);
	glAttachShader(p->handle, e->shaders[p->fshader].handle);
	i = 0;	
	while (i < p->n_locations)
	{
		glBindAttribLocation(p->handle, i, p->locations[i].name);
		i++;
	}
	glLinkProgram(p->handle);
	if (check_program_error(p->handle, GL_LINK_STATUS))
		return (ERROR("glLinkProgram(...)"), 1);
	glValidateProgram(p->handle);
	if (check_program_error(p->handle, GL_LINK_STATUS))
		return (ERROR("glValidateProgram(...)"), 1);
	return (0);
}

void			sp_delete_programs(t_env *e)
{
	t_program			*p;
	t_program const		*end = e->programs + sp_num_programs;

	p = e->programs;
	while (p < end)
	{
		glDetachShader(p->handle, e->shaders[p->vshader].handle);
		glDetachShader(p->handle, e->shaders[p->fshader].handle);
		glDeleteProgram(p->handle);
		p++;
	}
	return ;
}

int				sp_init_programs(t_env *e)
{
	int		i;

	lprintf("Initializing programs...");
	i = 0;
	while (i < sp_num_programs)
	{
		if (new_program(e, e->programs + i))
			return (ERRORF("new_program(%d)", i), 1);
		i++;
	}
	return (0);
}
