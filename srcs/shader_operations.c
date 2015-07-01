/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/01 12:15:52 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/01 13:01:37 by ngoguey          ###   ########.fr       */
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

static const t_shader_metadata	g_data[] =
{
	SHADERS_ATTRIBUTES_LIST
};

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
		return (DEBUGF(BADLOAD_FMT, filepath, strerror(errno)), 1);
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

static int		sp_new_shader(int index, GLuint *ptr)
{
	char	*text[1];
	GLuint	shaderid;
	GLint	len[1];

	if (sp_load_shader(g_data[index].filepath, text))
		return (DEBUG("Error in sp_load_shader"), 1);
	shaderid = glCreateShader(g_data[index].type);
	if (shaderid == 0)
		return (DEBUGF(BADCREATE_FMT, shaderid), free(*text), 1);
	*len = strlen(*text);
	glShaderSource(shaderid, 1, (char const *const*)text, len);
	free(*text);
	glCompileShader(shaderid);
	*ptr = shaderid;
	return (check_shader_error(shaderid, GL_COMPILE_STATUS));
}

void			sp_delete_shaders(t_env *e)
{
	int		i;

	i = 0;
	while (i < sc_num_shaders)
		glDeleteShader(e->shaders[i++]);
	return ;
}

int				sp_init_shaders(t_env *e)
{
	int		i;

	i = 0;
	while (i < sc_num_shaders)
	{
		if (sp_new_shader(i, e->shaders + i))
			return (DEBUGF("Error in sp_new_shader(%d)", i), 1);
		i++;
	}
	return (0);
}
