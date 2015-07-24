/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 13:21:56 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/24 14:42:15 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "objmodel_parsing.h"
#include "fterror.h"

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

#define TOKEN(NAME, FUN) {(NAME), strlen((NAME)), (FUN)}
#define NTOKENS (sizeof(g_tokens) / sizeof(*g_tokens))
#define EMPTY_LINE (NTOKENS + 1)

static const t_token	g_tokens[] = {
	TOKEN("f ", &op_match_f),
	TOKEN("v ", &op_match_v),
	TOKEN("vt ", &op_match_vt),
	TOKEN("vn ", &op_match_vn),
	TOKEN("#", &op_match_comment),
	TOKEN("g", &op_match_group),
	TOKEN("s ", &op_match_smooth),
	TOKEN("mtllib ", &op_match_mtllib),
	TOKEN("usemtl ", &op_match_usemtl),
	TOKEN("o ", &op_match_name),
};

static int		get_index(char buf[BFSZ], char const *endptr)
{
	size_t			i;
	static size_t	j = 0;

	i = 0;
	while (i < NTOKENS)
	{
		if (memcmp(buf, g_tokens[j].str, g_tokens[j].len) == 0)
		{
			memmove(buf, buf + g_tokens[j].len, endptr - buf + 1);
			return (j);
		}
		i++;
		j = (j + 1) % NTOKENS;
	}
	return (ERRORF("token not found '%s'", buf), -2);
}

static int		next_line_index(FILE *stream, char buf[BFSZ])
{
	char	*ptr;

	if (fgets(buf, BFSZ, stream) == NULL)
	{
		if (feof(stream))
			return (-1);
		if (ferror(stream))
			return (ERRORNO("fgets(...)"), -2);
		return (ERROR("while reading"), -2);
	}
	if ((ptr = strchr(buf, '\n')) == NULL)
		return (ERRORF("no eol '%s'", buf), -2);
	if (buf == ptr)
		return (EMPTY_LINE);
	*ptr = '\0';
	return (get_index(buf, ptr));
}

int				op_parse_obj(t_objmodel *m)
{
	FILE			*stream;
	int				i;
	char			buf[BFSZ];

	if ((stream = fopen(m->filepath, "r")) == NULL)
		return (ERRORNOF("fopen(\"%s\")", m->filepath), 1);
	while ((i = next_line_index(stream, buf)) >= 0)
	{
		if (i == EMPTY_LINE)
			continue ;
		if (g_tokens[i].fun(m, buf))
			return (ERRORF("g_tokens[i].fun(..., '%s')", buf), 1);
	}
	if (i != -1)
		return (ERROR("parsing failed"), 1);
	qprintf("Got %08d coords, ", m->coords.size);
	qprintf("Got %08d textures, ", m->textures.size);
	qprintf("Got %08d normals, ", m->normals.size);
	qprintf("Got %08d faces, ", m->faces.size);
	qprintf("Got %08d vertices\n", m->vertices.size);	
	return (fclose(stream), 0);
}
