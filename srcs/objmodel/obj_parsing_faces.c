/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing_faces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/23 10:12:13 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/23 15:46:46 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "objmodel_parsing.h"

#define ALL12INDEX b, b+1, b+2, b+3, b+4, b+5, b+6, b+7, b+8, b+9, b+10, b+11
#define CTINDICES b, b+1, b+3, b+4, b+6, b+7, b+9, b+10
#define CNINDICES b, b+2, b+3, b+5, b+6, b+8, b+9, b+11

void		op_faces_decr_indices(size_t b[12])
{
	int		i;

	i = 0;
	while (i < 12)
		b[i++]--;
	return ;
}

t_bool		op_faces_indices_valid(t_objmodel const *m, size_t const b[9])
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

static int	parse_width3(FILE *stream, t_objmodel *m)
{
	size_t			b[12];
	int				ret;

	ret = fscanf(stream, "%zu %zu %zu %zu\n", b, b + 3, b + 6, b + 9);
	if (ret < 3)
		return (ERRORF("Read %u uints", ret), -1);
	if (ferror(stream))
		return (ERRORNO("fscanf(...)"), -1);
	op_faces_decr_indices(b);
	if (!op_faces_indices_valid(m, b))
		return (ERRORF("bad index (%zu,%zu,%zu)", b[0], b[3], b[6]), -1);
	op_insert_face(m, (size_t*)b);
	if (ret == 4)
	{
		b[3] = b[0];
		if (!op_faces_indices_valid(m, b + 3))
			return (ERRORF("bad index (%zu,%zu,%zu)", b[3], b[6], b[9]), -1);
		op_insert_face(m, (size_t*)b + 3);
	}
	return (1);	
}

static int	parse_width8(FILE *stream, t_objmodel *m)
{
	size_t			b[12];
	int				ret;

	ret = fscanf(stream, "%zu/%zu/%zu %zu/%zu/%zu %zu/%zu/%zu %zu/%zu/%zu\n",
				 ALL12INDEX);
	if (ret != 9 && ret != 12)
		return (ERRORF("Read %u uints", ret), -1);
	if (ferror(stream))
		return (ERRORNO("fscanf(...)"), -1);
	op_faces_decr_indices(b);
	if (!op_faces_indices_valid(m, b))
		return (ERROR("bad index somewhere"), -1);
	op_insert_face(m, (size_t*)b);
	if (ret == 12)
	{
		memcpy(b + 3, b, sizeof(size_t) * 3);
		if (!op_faces_indices_valid(m, b + 3))
			return (ERROR("bad index somewhere"), -1);
		op_insert_face(m, (size_t*)b + 3);
	}
	return (1);
}

static int	parse_width5(FILE *stream, t_objmodel *m)
{
	size_t			b[12];
	int				ret;

	ret = fscanf(stream, "%zu/%zu %zu/%zu %zu/%zu %zu/%zu\n",
				 CTINDICES);
	if (ret != 6 && ret != 8)
		return (ERRORF("Read %u uints", ret), -1);
	if (ferror(stream))
		return (ERRORNO("fscanf(...)"), -1);
	op_faces_decr_indices(b);
	if (!op_faces_indices_valid(m, b))
		return (ERROR("bad index somewhere"), -1);
	op_insert_face(m, (size_t*)b);
	if (ret == 8)
	{
		memcpy(b + 3, b, sizeof(size_t) * 3);
		if (!op_faces_indices_valid(m, b + 3))
			return (ERROR("bad index somewhere"), -1);
		op_insert_face(m, (size_t*)b + 3);
	}
	return (1);
}

static int	parse_width6(FILE *stream, t_objmodel *m)
{
	size_t			b[12];
	int				ret;

	ret = fscanf(stream, "%zu//%zu %zu//%zu %zu//%zu %zu//%zu\n",
				 CNINDICES);
	if (ret != 6 && ret != 8)
		return (ERRORF("Read %u uints", ret), -1);
	if (ferror(stream))
		return (ERRORNO("fscanf(...)"), -1);
	op_faces_decr_indices(b);
	if (!op_faces_indices_valid(m, b))
		return (ERROR("bad index somewhere"), -1);
	op_insert_face(m, (size_t*)b);
	if (ret == 8)
	{
		memcpy(b + 3, b, sizeof(size_t) * 3);
		if (!op_faces_indices_valid(m, b + 3))
			return (ERROR("bad index somewhere"), -1);
		op_insert_face(m, (size_t*)b + 3);
	}
	return (1);
}

int			op_match_faces(FILE *stream, char const *h, t_objmodel *m)
{
	fpos_t			pos;
	char			c;
	
	/* T; */
	if (fgetpos(stream, &pos))
		return (ERRORNOF("fgetpos(...)"), -1);
	/* T; */
	while (ft_isspace((c = fgetc(stream))))
		;
	/* T; */
	/* qprintf("coords %u \n", m->coords.size); */
	/* qprintf("textures %u \n", m->textures.size); */
	/* qprintf("normals %u \n", m->normals.size); */
	/* qprintf("'%c'\n", c); */
	if (c != 'f' || fgetc(stream) != ' ')
		return (fsetpos(stream, &pos) || 0);
	/* T; */
	if (m->width == 0)
		op_init_meshvectors(m);
	if (m->width == 3)
		return (parse_width3(stream, m));
	else if (m->width == 5)
		return (parse_width5(stream, m));
	else if (m->width == 6)
		return (parse_width6(stream, m));
	else if (m->width == 8)
		return (parse_width8(stream, m));
	return (ERRORF("Faces width == %d", m->width), -1);
	(void)h;
}
