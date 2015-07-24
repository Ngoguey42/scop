/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing_faces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/23 10:12:13 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/24 12:35:23 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "objmodel_parsing.h"

void		op_faces_decr_indices(t_ui b[9], int i, int end)
{
	while (i < end)
		b[i++]--;
	return ;
}

t_bool		op_faces_indices_valid(t_objmodel const *m, t_ui const b[9])
{
	size_t	s;

	s = m->coords.size;
	if (b[0] > s || b[3] > s || b[6] > s)
		return (false);
	if (m->width == 5 || m->width == 8)
	{
		s = m->textures.size;
		if (b[1] > s || b[4] > s || b[7] > s)
			return (false);
	}
	if (m->width == 6 || m->width == 8)
	{
		s = m->normals.size;
		if (b[2] > s || b[5] > s || b[8] > s)
			return (false);
	}
	return (true);
}

static int	parse_width3(t_objmodel *m, char const *buf)
{
	t_ui	uibuf[9];
	int		i;

	i = 0;	
	while (1)
	{
		uibuf[i] = (t_ui)strtoul(buf, (char**)&buf, 10);
		if (buf == NULL)
			return (1); //error parsing uint
		i += 3;
		if (i >= 8)
			break ;
	}
	op_faces_decr_indices(uibuf, 0, 9);
	if (!op_faces_indices_valid(m, uibuf))
		return (1);
	op_insert_face(m, uibuf);
	return (0);
}

static int	parse_width5(t_objmodel *m, char const *buf)
{
	t_ui	uibuf[9];

	(void)m;
	(void)buf;
	(void)uibuf;
	return (0);
}

static int	parse_width6(t_objmodel *m, char const *buf)
{
	t_ui	uibuf[9];

	(void)m;
	(void)buf;
	(void)uibuf;
	return (0);
}

static int	parse_width8(t_objmodel *m, char const *buf)
{
	t_ui	uibuf[9];
	int		i;

	i = -1;
	while (1)
	{
		uibuf[++i] = (t_ui)strtoul(buf, (char **)&buf, 10);
		if (buf == NULL)
			return (1); //error parsing uint
		if (i == 8)
			break ;
		if (i % 3 != 2 && *buf++ != '/')
			return (1); //error parsing uints
	}
	op_faces_decr_indices(uibuf, 0, 9);
	if (!op_faces_indices_valid(m, uibuf))
		return (1);
	op_insert_face(m, uibuf);
	return (0);
}

int			op_match_f(t_objmodel *m, char const *buf)
{
	static int		(*fun)(t_objmodel *m, char const *buf) = NULL;

	if (m->width == 0)
	{
		op_init_meshvectors(m);
		if (m->width == 3)
			fun = &parse_width3;
		else if (m->width == 5)
			fun = &parse_width5;
		else if (m->width == 6)
			fun = &parse_width6;
		else if (m->width == 8)
			fun = &parse_width8;
	}
	return (fun(m, buf));
}
