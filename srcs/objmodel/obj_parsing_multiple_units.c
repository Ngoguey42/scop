/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing_multiple_units.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 09:20:55 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/23 10:12:21 by ngoguey          ###   ########.fr       */
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
