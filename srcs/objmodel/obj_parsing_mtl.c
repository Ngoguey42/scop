/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing_mtl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/24 10:24:07 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/24 10:25:13 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "objmodel_parsing.h"

int             op_match_group(FILE *stream, t_objmodel *m, char const *buf)
{
	(void)stream;
	(void)m;
	(void)buf;
	return (0);
}

int             op_match_mtllib(FILE *stream, t_objmodel *m, char const *buf)
{
	(void)stream;
	(void)m;
	(void)buf;
	return (0);
}

int             op_match_usemtl(FILE *stream, t_objmodel *m, char const *buf)
{
	(void)stream;
	(void)m;
	(void)buf;
	return (0);
}

int             op_match_name(FILE *stream, t_objmodel *m, char const *buf)
{
	(void)stream;
	(void)m;
	(void)buf;
	return (0);
}
