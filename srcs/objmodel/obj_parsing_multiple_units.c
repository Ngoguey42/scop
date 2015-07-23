/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing_multiple_units.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 09:20:55 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/23 15:54:27 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "objmodel_parsing.h"

int			op_match_comment(FILE *stream)
{
	fpos_t	pos;
	char	c;

	if (fgetpos(stream, &pos))
		return (ERRORNOF("fgetpos(...)"), -1);
	while (ft_isspace((c = fgetc(stream))))
		;
	/* T; */
	if (c != '#' && c != 'g' && c != 's')
	/* if (c != '#' && c != 'g') */
		return (fsetpos(stream, &pos) || 0);
	qprintf("'%c'\n", c);
	T;
	while (fgetc(stream) != '\n' && !feof(stream))
	{
		if (ferror(stream))
			return (ERRORNO("fgetc(...)"), -1);
	}
	T;
	return (1);
}
