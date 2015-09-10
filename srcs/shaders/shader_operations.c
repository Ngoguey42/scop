/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/01 12:15:52 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/09 18:32:05 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BADLOAD_FMT "Could not open %s \"\033[35m%s\033[0m\""
#define BADCREATE_FMT "Error in glCreateShader(%d)"

static int		check_shader_error(GLuint shader, GLuint flag)
{
	GLint		success[1];
	GLchar		msg[256];

	glGetShaderiv(shader, flag, success);
	if (*success == GL_FALSE)
	{
		glGetShaderInfoLog(shader, sizeof(msg), NULL, msg);
		ERRORF("Shader compilation: \n\033[35m%s\033[0m", msg);
		return (1);
	}
	return (0);
}

static int		sp_load_shader(char const *filepath, char **ptr)
{
	int		fd;
	int		ret;
	char	buffer[512];

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (ERRORNOF("fopen(\"%s\")", filepath));
	*ptr = NULL;
	while ((ret = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[ret] = '\0';
		if (*ptr == NULL)
			*ptr = ft_strdup(buffer);
		else
			*ptr = ft_strjoinfree(*ptr, buffer, 1, 0);
		if (*ptr == NULL)
			sp_enomem();
	}
	close(fd);
	if (ret < 0 || *ptr == NULL)
		return (ERRORF("Error while reading %s", filepath));
	return (0);
}

static int		sp_new_shader(char const *filepath, GLuint *handle, GLenum t)
{
	char	*text[1];
	GLint	len[1];

	if (sp_load_shader(filepath, text))
		return (ERROR("sp_load_shader(...)"));
	*handle = glCreateShader(t);
	if (*handle == 0)
	{
		free(*text);
		return (ERRORF(BADCREATE_FMT, *handle));
	}
	*len = strlen(*text);
	glShaderSource(*handle, 1, (char const **)text, len);
	free(*text);
	glCompileShader(*handle);
	return (check_shader_error(*handle, GL_COMPILE_STATUS));
}

void			sp_delete_shaders(t_env *e)
{
	int		i;

	i = 0;
	while (i < sp_num_vshaders)
		glDeleteShader(e->vshaders[i++].handle);
	i = 0;
	while (i < sp_num_fshaders)
		glDeleteShader(e->fshaders[i++].handle);
	return ;
}

int				sp_init_shaders(t_env *e)
{
	int		i;

	i = -1;
	while (++i < sp_num_vshaders)
		if (sp_new_shader(e->vshaders[i].filepath, &e->vshaders[i].handle
						, GL_VERTEX_SHADER))
			return (ERRORF("sp_new_vshader(%d)", i));
	i = -1;
	while (++i < sp_num_fshaders)
		if (sp_new_shader(e->fshaders[i].filepath, &e->fshaders[i].handle
							, GL_FRAGMENT_SHADER))
			return (ERRORF("sp_new_fshader(%d)", i));
	i = -1;
	while (++i < sp_num_gshaders)
		if (sp_new_shader(e->gshaders[i].filepath, &e->gshaders[i].handle
							, GL_GEOMETRY_SHADER))
			return (ERRORF("sp_new_gshader(%d)", i));
	return (0);
}
