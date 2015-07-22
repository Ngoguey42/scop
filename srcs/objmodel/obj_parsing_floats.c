/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing_floats.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 17:32:29 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/22 18:31:37 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "objmodel_parsing.h"

int			op_match_v(FILE *stream, char const *h, t_objmodel *m)
{
	float	buf[3];
	int		ret;
	fpos_t	pos;

	if (fgetpos(stream, &pos))
		return (ERRORNOF("fgetpos(...)"), -1);
	ret = fscanf(stream, "v %f %f %f\n", buf, buf + 1, buf + 2);
	if (ret < 3)
		return (fsetpos(stream, &pos) || 0);
	if (ferror(stream))
		return (ERRORNO("fscanf(...)"), -1);
	if (ftv_push_back(&m->coords, buf))
		sp_enomem();
	return (1);
	(void)h;
}

int			op_match_vt(FILE *stream, char const *h, t_objmodel *m)
{
	float	buf[2];
	int		ret;
	fpos_t	pos;

	if (fgetpos(stream, &pos))
		return (ERRORNOF("fgetpos(...)"), -1);
	ret = fscanf(stream, "vt %f %f\n", buf, buf + 1);
	if (ret < 2)
		return (fsetpos(stream, &pos) || 0);
	if (ferror(stream))
		return (ERRORNO("fscanf(...)"), -1);
	if (ftv_push_back(&m->textures, buf))
		sp_enomem();
	return (1);
	(void)h;
}

int			op_match_vn(FILE *stream, char const *h, t_objmodel *m)
{
	float	buf[3];
	int		ret;
	fpos_t	pos;

	if (fgetpos(stream, &pos))
		return (ERRORNOF("fgetpos(...)"), -1);
	ret = fscanf(stream, "vn %f %f %f\n", buf, buf + 1, buf + 2);
	if (ret < 3)
		return (fsetpos(stream, &pos) || 0);
	if (ferror(stream))
		return (ERRORNO("fscanf(...)"), -1);
	if (ftv_push_back(&m->normals, buf))
		sp_enomem();
	return (1);
	(void)h;
}
