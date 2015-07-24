/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing_faces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/23 10:12:13 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/24 13:18:53 by ngoguey          ###   ########.fr       */
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
static int	op_parse_uiblock(char const **buf, t_ui uibuf[9],
							 int const *indices)
{
	int		i;
	char	*ptr[1];

	i = 0;
	while (1)
	{
		if (indices[i] == -1)
		{
			if (*(*buf)++ != '/')
				return (-1);
		}
		else if (indices[i] == -2)
			break ;
		else
		{
			uibuf[indices[i]] = (t_ui)strtoul(*buf, ptr, 10);
			if (*ptr == NULL)
				return (-1);
			if (*buf == *ptr)
				return (i == 0 ? 1 : -1);
			*buf = *ptr;
		}
		i++;
	}
	return (0);
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
	int		ret;
	/* int		i; */

	/* i = 0;	 */
	/* while (1) */
	/* { */
	/* 	uibuf[i] = (t_ui)strtoul(buf, (char**)&buf, 10); */
	/* 	if (buf == NULL) */
	/* 		return (1); //error parsing uint */
	/* 	i += 3; */
	/* 	if (i >= 8) */
	/* 		break ; */
	/* } */
	op_parse_uiblock(&buf, uibuf, (int[]){0, 3, 6, -2});
	op_faces_decr_indices(uibuf, 0, 9);
	if (!op_faces_indices_valid(m, uibuf))
		return (1);
	op_insert_face(m, uibuf);
	while (1)
	{
		/* memmove(uibuf + 6, uibuf + 3, sizeof(t_ui) * 3); */
		uibuf[3] = uibuf[6];
		ret = op_parse_uiblock(&buf, uibuf, (int[]){6, -2});
		if (ret == -1)
			return (1);
		else if (ret == 1)
			break ;
		op_faces_decr_indices(uibuf, 6, 7);
		if (!op_faces_indices_valid(m, uibuf))
			return (1);
		T;
		op_insert_face(m, uibuf);
	}
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
	int		ret;
	
	op_parse_uiblock(&buf, uibuf, (int[]){0, -1, 1, -1, 2,
				3, -1, 4, -1, 5,
				6, -1, 7, -1, 8, -2});
	op_faces_decr_indices(uibuf, 0, 9);
	if (!op_faces_indices_valid(m, uibuf))
		return (1);
	op_insert_face(m, uibuf);
	while (1)
	{
		memmove(uibuf + 6, uibuf + 3, sizeof(t_ui) * 3);
		ret = op_parse_uiblock(&buf, uibuf, (int[]){6, -1, 7, -1, 8, -2});
		if (ret == -1)
			return (1);
		else if (ret == 1)
			break ;
		op_faces_decr_indices(uibuf, 6, 9);
		if (!op_faces_indices_valid(m, uibuf))
			return (1);
		T;
		op_insert_face(m, uibuf);
	}
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
