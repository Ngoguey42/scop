/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing_matching.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/13 08:48:45 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/13 10:17:32 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "scop.h"
#include "obj_parsing.h"

int		op_match_str(FILE *stream, char const *h, char **dst)
{
	char	hbuf[64];
	char	buf[64];
	int		ret;
	size_t	len;
	fpos_t	pos;
	
	if (fgetpos(stream, &pos))
		return (-1); // error on file stream (pos)
	ret = fscanf(stream, "%63s %63s\n", hbuf, buf);
	/* qprintf("ret: %d ('%s' '%s')\n", ret, hbuf, buf); */
	if (ret < 2 || strcmp(hbuf, h) != 0)
		return (fsetpos(stream, &pos) || 0); // does not match
	if (ferror(stream))
		return (-1); // error on file stream
	if (*dst != NULL)
		return (-1); // h already exists
	len = strlen(buf);
	if (len >= 63)
		return (-1); // word too long
	if ((*dst = malloc(sizeof(char) * (len + 1))) == NULL)
		sp_enomem();
	strlcpy(*dst, buf, len + 1);
	return (1); // saving successfully
}

int		op_match_comment(FILE *stream)
{
	int		ret;
	fpos_t	pos;

	if (fgetpos(stream, &pos))
		return (-1); // error on file stream (pos)
	if (fgetc(stream) != '#')
		return (fsetpos(stream, &pos) || 0); //is not comment
	while (fgetc(stream) != '\n' && !feof(stream))
	{
		if (ferror(stream))
			return (-1); // error on file stream
	}
	return (1); // matching successfully
}

int		op_match_bool(FILE *stream, char const *h, t_bool *dst)
{
	char	hbuf[64];
	int		ret;
	fpos_t	pos;
	
	if (fgetpos(stream, &pos))
		return (-1); // error on file stream (pos)
	ret = fscanf(stream, "%63s off\n", hbuf);
	if (ret == 1 && strcmp(hbuf, h) == 0)
	{
		if (*dst != undefined)
			return (-1); // h already exists
		*dst = false;
		return (1); // saving successfully
	}
	ret = fscanf(stream, "%63s on\n", hbuf);
	if (ret == 1 && strcmp(hbuf, h) == 0)
	{
		if (*dst != undefined)
			return (-1); // h already exists
		*dst = false;		
		return (1);
	}
	if (ferror(stream))
		return (-1); // error on file stream
	return (fsetpos(stream, &pos) || 0); // is not a bool
}

int		op_match_vertices(FILE *stream, char const *h, t_objmodel *m)
{
	char	hbuf[64];
	float	buf[3];
	int		ret;
	fpos_t	pos;
	
	if (fgetpos(stream, &pos))
		return (-1); // error on file stream (pos)
	ret = fscanf(stream, "%63s %f %f %f\n", hbuf, buf, buf + 1, buf + 2);
	if (ret < 4 || strcmp(hbuf, h) != 0)
		return (fsetpos(stream, &pos) || 0); // does not match
	if (m->faces.size != 0)
		return (-1); // already parsed faces
	if (ferror(stream))
		return (-1); // error on file stream
	if (ftv_push_back(&m->vertices, buf))
		sp_enomem();
	return (1);
}

int		op_match_faces(FILE *stream, char const *h, t_objmodel *m)
{
	char			hbuf[64];
	unsigned int	buf[4];
	int				ret;
	fpos_t	pos;
	
	if (fgetpos(stream, &pos))
		return (-1); // error on file stream (pos)
	ret = fscanf(stream, "%63s %u %u %u %u\n", hbuf, buf, buf + 1,
				 buf + 2, buf + 3);
	if (ret < 4 || strcmp(hbuf, h) != 0)
		return (fsetpos(stream, &pos) || 0); // does not match
	if (ferror(stream))
		return (-1); // error on file stream
	if (buf[0] == 0u || buf[0] > m->vertices.size ||
		buf[1] == 0u || buf[1] > m->vertices.size ||
		buf[2] == 0u || buf[2] > m->vertices.size)
		return (-1); //wrong index
	if (ftv_push_back(&m->faces, buf))
		sp_enomem();
	if (ret == 5)
	{
		if (buf[3] == 0u || buf[3] > m->vertices.size)
			return (-1); //wrong index
		if (ftv_push_back(&m->faces, buf + 1))
			sp_enomem();
	}
	return (1);
}
