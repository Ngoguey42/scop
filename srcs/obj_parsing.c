/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 13:21:56 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/02 17:48:38 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include "scop.h"
#include "obj_parsing.h"

#define BADLOAD_FMT "Could not open %s \"\033[35m%s\033[0m\""

#define OFFSET(P) (offsetof(struct s_objmodel, P))
#define OP_COMMENT (t_token){"#", &skip_line, 0}
#define OP_MTLLIB (t_token){"mtllib ", &parse_word, OFFSET(mtllib)}
#define OP_O (t_token){"o ", &parse_word, OFFSET(name)}
#define OP_USEMTL (t_token){"usemtl ", &parse_word, OFFSET(usemtl)}
#define OP_S (t_token){"s ", &parse_state, OFFSET(smooth)}
#define OP_V (t_token){"v ", &parse_3float, OFFSET(vertices)}
#define OP_F (t_token){"f ", &parse_3uint, OFFSET(faces)}
#define OP_NONE	(t_token){"", NULL, 0}

static const t_token	g_phases[4][4] =
{
	{OP_COMMENT, OP_MTLLIB, OP_O, OP_NONE},
	{OP_COMMENT, OP_V, OP_NONE, OP_NONE},
	{OP_COMMENT, OP_USEMTL, OP_S, OP_NONE},
	{OP_COMMENT, OP_F, OP_NONE, OP_NONE},
};

static const size_t		g_num_phases = sizeof(g_phases) / sizeof(*g_phases);

static int		match_index(char const *buf, t_token const *phase_tokens)
{
	int		i;

	i = 0;
	while (phase_tokens[i].fun != NULL)
	{
		if (!strcmp(phase_tokens[i].header, buf))
			return (i);
		i++;
	}
	return (-1);
}

static int		find_match(FILE *stream, t_token *match, size_t *p)
{
	char	buf[16];
	int		bufi;
	int		matchi;

	bzero(buf, sizeof(buf));
	bufi = -1;
	while (bufi < 15)
	{
		T;
		qprintf("%s\n", buf);
		if (bufi > 0 && ft_isspace(buf[bufi]))
			*p += 1;
		else
		{
			buf[++bufi] = fgetc(stream);
			if (STREAM_STATUS_BAD2)
				return (STREAM_ERR_MSG, 1);
		}
		if (*p >= g_num_phases)
			return (1);
		else if ((matchi = match_index(buf, g_phases[*p])) >= 0)
			return (memcpy(match, g_phases[*p] + matchi, sizeof(t_token)), 0);
	}
	return (DEBUG("Left keyword too long"), 1);
}

int				sp_parse_obj(t_objmodel *m)
{
	FILE		*stream;
	size_t		phase;
	t_token		match;

	stream = fopen(m->filepath, "r");
	if (stream == NULL)
		return (DEBUGF(BADLOAD_FMT, m->filepath, strerror(errno)), 1);
	phase = 0;
	while (!feof(stream))
	{
		if (find_match(stream, &match, &phase))
			return (DEBUG("Could not find match in obj file"), 1);
		if (match.fun(stream, (void*)m + match.pad))
			return (DEBUG("Matching function failed"), 1);
	}
	if (m->vertices.size <= 0)
		return (DEBUG("No vertices found in file"), 1);
	if (m->faces.size <= 0)
		return (DEBUG("No faces found in file"), 1);
	qprintf("Found %u vertices\n", m->vertices.size);
	qprintf("Found %u faces\n", m->faces.size);
	fclose(stream);
	return (0);
}
