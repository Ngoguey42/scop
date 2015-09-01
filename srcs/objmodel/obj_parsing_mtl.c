/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing_mtl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/24 10:24:07 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/28 15:51:05 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "objmodel/_parsing.h"

int			op_match_group(t_objmodel *m, char const *buf)
{
	(void)m;
	(void)buf;
	return (0);
}

int			op_match_mtllib(t_objmodel *m, char const *buf)
{
	(void)m;
	(void)buf;
	return (0);
}

int			op_match_usemtl(t_objmodel *m, char const *buf)
{
	(void)m;
	(void)buf;
	return (0);
}

int			op_match_name(t_objmodel *m, char const *buf)
{
	(void)m;
	(void)buf;
	return (0);
}
