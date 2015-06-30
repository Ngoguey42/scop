/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 15:14:42 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/30 17:45:54 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

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
		return (DEBUGF("Could not open %s \"\033[35m%s\033[0m\"",
					   filepath, strerror(errno)), 1);
	*ptr = NULL;
	while (bzero(buffer, sizeof(buffer)),
			(ret = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		if (*ptr == NULL)
			*ptr = ft_strdup(buffer);
		else
			*ptr = ft_strjoinfree(*ptr, buffer, 1, 0);
		if (*ptr == NULL)
			sp_enomem();
	}
	if (ret < 0 || *ptr == NULL)
		return (DEBUGF("Error while reading %s", filepath), 1);
	return (0);
}

int				sp_create_shader(char const *filepath, GLenum type, GLuint *ptr)
{
	char	*text[1];
	GLuint	shaderid;
	GLint	len[1];

	if (sp_load_shader(filepath, text))
		return (DEBUG("Error in sp_load_shader"), 1);
	shaderid = glCreateShader(type);
	if (shaderid == 0)
		return (DEBUGF("Error in glCreateShader(%d)", shaderid), free(*text),
				1);
	*len = strlen(*text);
	glShaderSource(shaderid, 1, (char const *const*)text, len);
	free(*text);
	glCompileShader(shaderid);
	*ptr = shaderid;
	return (check_shader_error(shaderid, GL_COMPILE_STATUS));
}
