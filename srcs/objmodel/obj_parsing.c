/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 13:21:56 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/23 15:52:12 by ngoguey          ###   ########.fr       */
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

static int		(*const g_tokens[])(FILE *stream, t_objmodel *m) =
{
	&op_match_f,
	&op_match_v,
	&op_match_vt,
	&op_match_vn,
	&op_match_comment,
	&op_match_group,
	&op_match_smooth,
	&op_match_mtllib,
	&op_match_usemtl,
	&op_match_name,
};

static void		print_no_match(FILE *stream)
{
	char	buf[128];
	char	*ptr;

	ptr = fgets(buf, sizeof(buf), stream);
	if (ptr != NULL)
	{
		ptr = strchr(buf, '\n');
		if (ptr != NULL)
			*ptr = '\0';
		ERRORF("no matching token \033[32m'%s'\033[0m", buf);
	}
	else
		ERROR("no matching token \033[32m'NULL'\033[0m");
	return ;
}

int				op_parse_obj(t_objmodel *m)
{
	FILE	*stream;
	size_t	i;
	int		ret;

	if ((stream = fopen(m->filepath, "r")) == NULL)
		return (ERRORNOF("fopen(\"%s\")", m->filepath), 1);
	while (1)
	{
		i = 0;
		while (i < sizeof(g_tokens) / sizeof(*g_tokens))
		{
			if ((ret = g_tokens[i](stream, m)) == -1)
				return (ERRORF("g_tokens[%d]", i), 1);
			else if (ret == 1)
				break ;
			i++;
		}
		if (feof(stream))
			break ;
		if (i >= sizeof(g_tokens) / sizeof(*g_tokens))
			return (print_no_match(stream), 1);
	}
	return (fclose(stream), 0);
}

// void printvertice(void *env, float *vert, int i)
// {
	// qprintf("%2d: (% 5.2f, % 5.2f, % 5.2f)\n", i, vert[0], vert[1], vert[2]);	
// }
// void printuint(void *env, unsigned int *vert, int i)
// {
	// qprintf("%2d: (% 5.2u, % 5.2u, % 5.2u)\n", i, vert[0], vert[1], vert[2]);	
// }

void			op_swap_vectors(t_objmodel *m, t_ftvector *v, t_ftvector *f)
{
	memcpy(v, &m->vertices, sizeof(t_ftvector));
	if (m->faces.data != NULL)
		memcpy(f, &m->faces, sizeof(t_ftvector));
	/* T; */
	/* ftv_foreachi(&m->vertices, &printvertice, NULL); */
	/* ftv_foreachi(&m->faces, &printuint, NULL); */
	bzero(&m->vertices, sizeof(t_ftvector));
	bzero(&m->faces, sizeof(t_ftvector));
	return ;
}
