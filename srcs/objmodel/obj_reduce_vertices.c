/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_reduce_vertices.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/24 13:54:47 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/24 14:08:16 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "objmodel_parsing.h"

void		update_indices(t_objmodel *m, float *vertex, size_t index)
{
	
	return ;
}

void		op_reduce_num_vertices(t_objmodel *m)
{
	t_ftvector	indicesupdates;

	ftv_init_instance(&indicesupdates, sizeof(t_ui) * 2);
	ftv_foreachi(m->vertices, &foreach_vertices, m);
	
	
	
	return ;
}
