/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objmodel_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 08:26:17 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/28 15:56:12 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "scop.h"
#include "objmodel_parsing.h"

void		sp_clean_objmodel(t_objmodel *m)
{
	ftv_release(&m->textures, NULL);
	ftv_release(&m->coords, NULL);
	ftv_release(&m->normals, NULL);
	if (m->faces.data != NULL)
	{
		ftv_release(&m->faces, NULL);
		ftv_release(&m->vertices, NULL);
	}
	return ;
}

void		op_init_meshvectors(t_objmodel *m)
{
	m->width = 3;
	if (m->textures.size > 0)
		m->width += 2;
	if (m->normals.size > 0)
		m->width += 3;
	if (ftv_init_instance(&m->faces, sizeof(unsigned int) * 3))
		sp_enomem();
	if (ftv_init_instance(&m->vertices, sizeof(float) * m->width))
		sp_enomem();
	return ;
}

void		op_swap_vectors(t_objmodel *m, t_ftvector *v, t_ftvector *f)
{
	if (v->data != NULL)
		ftv_release(v, NULL);
	if (f->data != NULL)
		ftv_release(f, NULL);
	memcpy(v, &m->vertices, sizeof(t_ftvector));
	if (m->faces.data != NULL)
		memcpy(f, &m->faces, sizeof(t_ftvector));
	bzero(&m->vertices, sizeof(t_ftvector));
	bzero(&m->faces, sizeof(t_ftvector));
	return ;
}
