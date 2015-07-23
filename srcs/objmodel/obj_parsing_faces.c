/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing_faces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/23 10:12:13 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/23 11:34:02 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "objmodel_parsing.h"

static int	parse_width3(FILE *stream, t_objmodel *m)
{
	size_t			b[12];
	int				ret;

	ret = fscanf(stream, "%zu %zu %zu %zu\n", b, b + 3, b + 6, b + 9);
	if (ret < 3)
		return (ERRORF("Read %u uints", ret), -1);
	if (ferror(stream))
		return (ERRORNO("fscanf(...)"), -1);
	b[0] -= 1;
	b[3] -= 1;
	b[6] -= 1;
	b[9] -= 1;
	if (b[0] > m->coords.size || b[3] > m->coords.size || b[6] > m->coords.size)
		return (ERRORF("bad index (%zu,%zu,%zu)", b[0], b[3], b[6]), -1);
	op_insert_face(m, (size_t*)b);
	if (ret == 4)
	{
		b[3] = b[0];
		if (b[9] > m->coords.size)
			return (ERRORF("bad index (%zu,%zu,%zu)", b[3], b[6], b[9]), -1);
		op_insert_face(m, (size_t*)b + 3);
	}
	return (1);	
}

int			op_match_faces(FILE *stream, char const *h, t_objmodel *m)
{
	fpos_t			pos;

	if (fgetpos(stream, &pos))
		return (ERRORNOF("fgetpos(...)"), -1);
	if (fgetc(stream) != 'f' || fgetc(stream) != ' ')
		return (fsetpos(stream, &pos) || 0);
	if (m->width == 0)
		op_init_meshvectors(m);
	if (m->width == 3)
		return (parse_width3(stream, m));
	/* else if (m->width == 5) */
	/* 	; */
	/* else if (m->width == 6) */
	/* 	; */
	/* else if (m->width == 8) */
	/* 	; */
	return (ERRORF("Faces width == %d", m->width), -1);
	(void)h;
}
