/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing_multiple_units.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 09:20:55 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/22 18:22:56 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "objmodel_parsing.h"

int			op_match_comment(FILE *stream)
{
	fpos_t	pos;

	if (fgetpos(stream, &pos))
		return (ERRORNOF("fgetpos(...)"), -1);
	if (fgetc(stream) != '#')
		return (fsetpos(stream, &pos) || 0);
	while (fgetc(stream) != '\n' && !feof(stream))
	{
		if (ferror(stream))
			return (ERRORNO("fgetc(...)"), -1);
	}
	return (1);
}

static int	disass_quad(t_objmodel *m, unsigned int b[4])
{
	b[1] = b[0];
	if (b[3] > m->coords.size)
		return (ERRORF("bad index (%u,%u,%u)", b[1], b[2], b[3]), -1);
	if (ftv_push_back(&m->faces, b + 1))
		sp_enomem();
	return (1);
}

int			op_match_faces(FILE *stream, char const *h, t_objmodel *m)
{
	unsigned int	b[4];
	int				ret;
	fpos_t			pos;

	if (fgetpos(stream, &pos))
		return (ERRORNOF("fgetpos(...)"), -1);
	ret = fscanf(stream, "f %u %u %u %u\n", b, b + 1, b + 2, b + 3);
	if (ret < 3)
		return (fsetpos(stream, &pos) || 0);
	if (ferror(stream))
		return (ERRORNO("fscanf(...)"), -1);
	if (m->faces.data == NULL)
		op_init_faces(m);
	b[0] -= 1;
	b[1] -= 1;
	b[2] -= 1;
	b[3] -= 1;
	if (b[0] > m->coords.size || b[1] > m->coords.size ||
		b[2] > m->coords.size)
		return (ERRORF("bad index (%u,%u,%u)", b[0], b[1], b[2]), -1);
	if (ftv_push_back(&m->faces, b))
		sp_enomem();
	if (ret == 4)
		return (disass_quad(m, b));
	return (1);
	(void)h;
}
