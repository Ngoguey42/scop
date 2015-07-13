/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 13:21:56 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/13 10:42:42 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include "scop.h"
#include "obj_parsing.h"

#define OFFSET(P) (offsetof(struct s_objmodel, P))

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

#undef OFFSET

/*
** ** Comparing functions:
** Compare unary	char*A		A==NULL
** Compare unary	uintA		A==0u
** Compare binary	uintA uintB	A!=0u && A>=B
** Compare unary	triboolA	A==undefined
** **
** ** Saving functions:
** objmodel *m		char **dst			char const *src
** objmodel *m		t_tribool *dst		char const *src
** objmodel *m		t_ftvertex *dst		char const *src
** **
** ** Matching functions:
** 
**
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

int     sp_parse_obj(t_objmodel *m)
{
	FILE*	stream;
	size_t	i;
	int		ret;

	stream = fopen(m->filepath, "r");
	if (stream == NULL)
		return (1); //could not open file
	while (1)
	{
		/* qprintf("START LOOP\n"); */
		i = 0;
		while (i < sizeof(g_tokens) / sizeof(t_token))
		{
			DEBUGF("trying '%s'", g_tokens[i].h);
			ret = g_tokens[i].fun(stream, g_tokens[i].h, (void*)m +
									g_tokens[i].pad);
			if (ret == -1)
				return (DEBUGF("Error while matching '%s'", g_tokens[i].h), 1);
			if (ret == 1)
			{
				DEBUGF("ENDLOOP MATCHED '%s'", g_tokens[i].h);
				break;
			}
			i++;
		}
		if (feof(stream))
			break ;
		if (i >= sizeof(g_tokens) / sizeof(t_token))
			return (1); //no match
	}

	qprintf("Found %u vertices\n", m->vertices.size);
	qprintf("Found %u faces\n", m->faces.size);
	fclose(stream);
	return (0);
}
