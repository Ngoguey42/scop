/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_normal_ebo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 15:56:24 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/25 17:17:50 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>

typedef struct s_facenormals
{
	t_ui        indices[3];
	t_vec3   normal;
} t_facenormals;

void		sp_get_facenormals(t_ftvector *facenormals
							   , t_vbo_basic const *vbo
							   , t_ftvector const *faces)
{
	t_vec3 const			*ver[3];
	t_ui const				*face;
	t_ui const *const		faceend = ftv_end(faces);
	t_facenormals			tmp[1];

	ftv_init_instance(facenormals, sizeof(t_facenormals));
	ftv_summarize(facenormals);
	ftv_reserve(facenormals, faces->size);
	ftv_summarize(facenormals);
	face = faces->data;
	while (face != faceend)
	{
		tmp->indices[0] = face[0];
		tmp->indices[1] = face[1];
		tmp->indices[2] = face[2];
		ver[0] = (t_vec3*)&((t_vertex_basic*)(vbo->vertices.data
		+ vbo->vertices.chunk_size * face[0]))->pos;
		ver[1] = (t_vec3*)&((t_vertex_basic*)(vbo->vertices.data
		+ vbo->vertices.chunk_size * face[1]))->pos;
		ver[2] = (t_vec3*)&((t_vertex_basic*)(vbo->vertices.data
		+ vbo->vertices.chunk_size * face[2]))->pos;
		tmp->normal = v3_cross(v3_inv(v3_normalize(v3_sub(*ver[0], *ver[1])))
							   , v3_normalize(v3_sub(*ver[2], *ver[0])));
		v3_print(tmp->normal);
		ftv_push_back_unsafe(facenormals, tmp);
		face = (void*)face + faces->chunk_size;
	}
	ftv_summarize(facenormals);	
	return ;
}
