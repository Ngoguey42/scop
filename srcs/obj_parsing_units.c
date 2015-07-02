/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing_units.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 16:01:37 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/02 17:36:22 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "scop.h"
#include "obj_parsing.h"

int			skip_line(FILE *stream)
{
	while (fgetc(stream) != '\n')
		if (STREAM_STATUS_BAD)
			return (DEBUG("Error in skip_line"), STREAM_ERR_MSG, 1);
	return (0);
}

int			parse_word(FILE *stream, char **dst)
{
	char	buf[64];

	if (*dst != NULL)
		free(*dst);
	if (fscanf(stream, "%63s\n", buf) <= 0)
		return (DEBUG("String matching: failed"), 1);
	if (STREAM_STATUS_BAD)
		return (DEBUG("Error in parse_word"), STREAM_ERR_MSG, 1);
	else if (strlen(buf) >= 63)
		return (DEBUG("Word too long"), 1);
	*dst = strdup(buf);
	if (*dst == NULL)
		sp_enomem();
	return (0);
}

int			parse_state(FILE *stream, t_bool *dst)
{
	char	buf[64];
	int		i;

	bzero(buf, sizeof(buf));
	i = 0;
	while ((buf[i++] = fgetc(stream)) != '\n')
	{
		if (STREAM_STATUS_BAD)
			return (DEBUG("Error in parse_state"), STREAM_ERR_MSG, 1);
		else if (i >= 63)
			return (DEBUG("State string too long"), 1);
	}
	if (!strcmp(buf, "on\n"))
		*dst = true;
	else if (!strcmp(buf, "off\n"))
		*dst = false;
	else
		return (DEBUG("State matching: failed"), 1);
	return (0);
}

int			parse_3float(FILE *stream, t_ftvector *dst)
{
	float	f[3];

	if (fscanf(stream, "%f %f %f\n", f, f + 1, f + 2) <= 0)
		return (DEBUG("Triple float matchin: failed"), 1);
	if (STREAM_STATUS_BAD)
		return (DEBUG("Error in parse_3float"), STREAM_ERR_MSG, 1);
	if (ftv_push_back(dst, f))
		sp_enomem();
	return (0);
}

int			parse_3uint(FILE *stream, t_ftvector *dst)
{
	unsigned int	ui[3];

	if (fscanf(stream, "%u %u %u\n", ui, ui + 1, ui + 2) <= 0)
		return (DEBUG("Triple uint matchin: failed"), 1);
	if (STREAM_STATUS_BAD)
		return (DEBUG("Error in parse_3uint"), STREAM_ERR_MSG, 1);
	if (ftv_push_back(dst, ui))
		sp_enomem();
	return (0);
}
