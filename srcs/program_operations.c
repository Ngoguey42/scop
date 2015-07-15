/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/01 12:32:53 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/15 13:27:30 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static const t_program_metadata		g_data[] =
{
	PROGRAMS_ATTRIBUTES_LIST
};

static int		check_program_error(GLuint program, GLuint flag)
{
	GLint		success[1];
	GLchar		msg[256];

	glGetProgramiv(program, flag, success);
	if (*success == GL_FALSE)
	{
		glGetProgramInfoLog(program, sizeof(msg), NULL, msg);
		DEBUGF("Error with program: \"\033[35m%s\033[0m\"", msg);
		return (1);
	}
	return (0);
}

static int		new_program(int index, GLuint *ptr, t_env const *e)
{
	int							i;
	t_program_metadata const	*dat = g_data + index;

	*ptr = glCreateProgram();
	glAttachShader(*ptr, e->shaders[dat->vertex_shaderid]);
	glAttachShader(*ptr, e->shaders[dat->fragment_shaderid]);
	i = 0;
	while (i < g_data[index].num_locations)
	{
		glBindAttribLocation(*ptr, i, g_data[index].locations[i]);
		i++;
	}
	glLinkProgram(*ptr);
	if (check_program_error(*ptr, GL_LINK_STATUS))
		return (DEBUG("glLinkProgram failed"), 1);
	glValidateProgram(*ptr);
	if (check_program_error(*ptr, GL_LINK_STATUS))
		return (DEBUG("glValidateProgram failed"), 1);
	return (0);
}

void			sp_delete_programs(t_env *e)
{
	int		i;

	i = 0;
	while (i < sc_num_programs)
	{
		glDetachShader(e->programs[i], e->shaders[g_data[i].vertex_shaderid]);
		glDetachShader(e->programs[i], e->shaders[g_data[i].fragment_shaderid]);
		glDeleteProgram(e->programs[i]);
		i++;
	}
	return ;
}

int				sp_init_programs(t_env *e)
{
	int		i;

	i = 0;
	while (i < sc_num_programs)
	{
		if (new_program(i, e->programs + i, e))
			return (DEBUGF("Error in new_program(%d)", i), 1);
		i++;
	}
	return (0);
}

void			sp_update_uniforms(t_env const *e, int prid, GLuint prog)
{
	t_program_metadata const	*d = g_data + prid;
	int							i;

	i = 0;
	while (i < d->num_uniforms)
	{
		d->uniforms[i].fun(e, glGetUniformLocation(prog, d->uniforms[i].name));
		i++;
	}
	return ;
}
