/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objmodel_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 08:26:17 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/23 13:48:45 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "scop.h"
#include "objmodel_parsing.h"

void		sp_clean_objmodel(t_objmodel *m)
{
	// if (m->filepath)
		free(m->filepath);
	// if (m->mtllib)
		// free(m->mtllib);
	// if (m->name)
		// free(m->name);
	// if (m->usemtl)
		// free(m->usemtl);
	// if (m->textures.data != NULL)
		ftv_release(&m->textures, NULL);
	// if (m->coords.data != NULL)
		ftv_release(&m->coords, NULL);
	// if (m->normals.data != NULL)
		ftv_release(&m->normals, NULL);
	if (m->faces.data != NULL)
	{
		ftv_release(&m->faces, NULL);
	// if (m->vertices.data != NULL)
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
	qprintf("Vertex width = %u\n", m->width);
	if (ftv_init_instance(&m->faces, sizeof(unsigned int) * 3))
		sp_enomem();
	if (ftv_init_instance(&m->vertices, sizeof(float) * m->width))
		sp_enomem();
	return ;
}

void			op_init_instance(t_objmodel *m, char const *filepath)
{
	bzero(m, sizeof(*m));
	// m->smooth = undefined;
	m->filepath = strdup(filepath);
	if (filepath == NULL)
		sp_enomem();
	if (ftv_init_instance(&m->coords, sizeof(float) * 3))
		sp_enomem();
	if (ftv_init_instance(&m->textures, sizeof(float) * 2))
		sp_enomem();
	if (ftv_init_instance(&m->normals, sizeof(float) * 3))
		sp_enomem();
	return ;
}
