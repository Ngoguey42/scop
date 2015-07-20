/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/01 12:15:52 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 14:09:40 by ngoguey          ###   ########.fr       */
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
		DEBUGF("Error compiling shader: \"\033[35m%s\033[0m\"", msg);
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
		return (ERRORNOF("fopen(\"%s\")", filepath), 1);
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
		return (DEBUGF("Error while reading %s", filepath), 1);
	return (0);
}

static int		sp_new_shader(t_shader *s)
{
	char	*text[1];
	GLint	len[1];

	if (sp_load_shader(s->filepath, text))
		return (ERROR("sp_load_shader(...)"), 1);
	s->handle = glCreateShader(s->type);
	if (s->handle == 0)
		return (DEBUGF(BADCREATE_FMT, s->handle), free(*text), 1);
	*len = strlen(*text);
	glShaderSource(s->handle, 1, (char const *const*)text, len);
	free(*text);
	glCompileShader(s->handle);
	return (check_shader_error(s->handle, GL_COMPILE_STATUS));
}

void			sp_delete_shaders(t_env *e)
{
	int		i;

	i = 0;
	while (i < sp_num_shaders)
		glDeleteShader(e->shaders[i++].handle);
	return ;
}

int				sp_init_shaders(t_env *e)
{
	int		i;

	i = 0;
	while (i < sp_num_shaders)
	{
		if (sp_new_shader(e->shaders + i))
			return (ERRORF("sp_new_shader(%d)", i), 1);
		i++;
	}
	return (0);
}