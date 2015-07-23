/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing_unique_units.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 09:20:50 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/23 13:17:17 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "objmodel_parsing.h"

int		op_match_str(FILE *stream, char const *h, char **dst)
{
	char	hbuf[64];
	char	buf[64];
	int		ret;
	size_t	len;
	fpos_t	pos;

	if (fgetpos(stream, &pos))
		return (ERRORNO("fgetpos(...)"), -1);
	*hbuf = '\0';
	*buf = '\0';
	ret = fscanf(stream, "%63s %63s\n", hbuf, buf);
	if (ret < 2 || strcmp(hbuf, h) != 0)
		return (fsetpos(stream, &pos) || 0);
	if (ferror(stream))
		return (ERRORNO("fscanf(...)"), -1);
	/* if (*dst != NULL) */
		/* return (ERRORF("duplicate for \"%s\"", hbuf), -1); */
	len = strlen(buf);
	if (len >= 63)
		return (ERRORF("word too long for \"%s\"", hbuf), -1);
	/* *dst = strdup(buf); */
	/* if (*dst == NULL) */
		/* sp_enomem(); */
	return (1);
}

int		op_match_bool(FILE *stream, char const *h, t_bool *dst)
{
	char	hbuf[64];
	int		ret;
	fpos_t	pos;

	if (fgetpos(stream, &pos))
		return (ERRORNOF("fgetpos(...)"), -1);
	ret = fscanf(stream, "%63s off\n", hbuf);
	if (ret == 1 && strcmp(hbuf, h) == 0)
	{
		if (*dst != undefined)
			return (ERRORF("duplicate for \"%s\"", hbuf), -1);
		*dst = false;
		return (1);
	}
	ret = fscanf(stream, "%63s on\n", hbuf);
	if (ret == 1 && strcmp(hbuf, h) == 0)
	{
		if (*dst != undefined)
			return (ERRORF("duplicate for \"%s\"", hbuf), -1);
		*dst = false;
		return (1);
	}
	if (ferror(stream))
		return (ERRORNO("fscanf(...)"), -1);
	return (fsetpos(stream, &pos) || 0);
}
