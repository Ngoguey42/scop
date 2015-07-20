/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 13:21:56 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/15 09:27:00 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "objmodel_parsing.h"

#define OFFSET(P) (offsetof(struct s_objmodel, P))

/*
** ** Tokens traces:
** #comments
** mtllib	name			if filenamePtr == NULL
** usemtl	name			if numUsemtlPtr == NULL
** o		name			if numOPtr == NULL
** s		state			if numS == undefined
** v		3floats			if numF == 0u
** f		N(3 to 4 uint)	if N <= numV
** *
** Converting faces to triangles
** Vertices must be 3floats
*/

static const t_token	g_tokens[] =
{
	(t_token){"#", &op_match_comment, 0},
	(t_token){"s", &op_match_bool, OFFSET(smooth)},
	(t_token){"v", &op_match_vertices, 0},
	(t_token){"f", &op_match_faces, 0},
	(t_token){"mtllib", &op_match_str, OFFSET(mtllib)},
	(t_token){"o", &op_match_str, OFFSET(name)},
	(t_token){"usemtl", &op_match_str, OFFSET(usemtl)},
};

int		op_parse_obj(t_objmodel *m)
{
	FILE	*stream;
	size_t	i;
	int		ret;

	if ((stream = fopen(m->filepath, "r")) == NULL)
		return (ERRORNOF("fopen(\"%s\")", m->filepath), 1);
	while (1)
	{
		i = 0;
		while (i < sizeof(g_tokens) / sizeof(t_token))
		{
			ret = g_tokens[i].fun(stream, g_tokens[i].h, (void*)m +
									g_tokens[i].pad);
			if (ret == -1)
				return (ERRORF("g_tokens[%d].fun", i), 1);
			if (ret == 1)
				break ;
			i++;
		}
		if (feof(stream))
			break ;
		if (i >= sizeof(g_tokens) / sizeof(t_token))
			return (ERROR("no matching token"), 1);
	}
	return (fclose(stream), 0);
}
