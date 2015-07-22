/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objmodel_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 08:26:17 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/22 18:32:38 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "scop.h"
#include "objmodel_parsing.h"

void		sp_clean_objmodel(t_objmodel *m)
{
	free(m->filepath);
	if (m->mtllib)
		free(m->mtllib);
	if (m->name)
		free(m->name);
	if (m->usemtl)
		free(m->usemtl);
	ftv_release(&m->vertices, NULL);
	ftv_release(&m->faces, NULL);
	ftv_release(&m->coords, NULL);
	//(more...);
	return ;
}

static int	init_vertices(t_objmodel *m)
{
	size_t	size;

	if (m->coords.size < 3 || m->faces.size == 0)
		return (1);
	size = 3;
	if (m->textures.size > 0)
		size += 2;
	if (m->normals.size > 0)
		size += 3;
	if (ftv_init_instance(&m->vertices, sizeof(float) * size))
		sp_enomem();
	return (0);
}

void		op_init_faces(t_objmodel *m)
{
	size_t	size;

	size = 3;
	if (m->textures.size > 0)
		size += 2;
	if (m->normals.size > 0)
		size += 3;
	if (ftv_init_instance(&m->faces, sizeof(unsigned int) * size))
		sp_enomem();
	return ;
}

int			op_build_vertices(t_objmodel *m)
{
	m->vertices = m->coords;

	return (0);
}
