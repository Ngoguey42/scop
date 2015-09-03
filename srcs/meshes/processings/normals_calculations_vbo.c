/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals_calculations_vbo.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 16:26:31 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/03 18:14:21 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>
#include <math.h>

static void	bzero_normals(void *ignore, t_vertex_basic *vert)
{
	bzero(&vert->nor, sizeof(vert->nor));
	return ;
	(void)ignore;
}

static void	sum_normals(t_vertex_basic *verts, t_face_basic const *f)
{
	int		i;
	int		j;
	float	angle;

	i = 0;
	j = 2;
	while (i < 3)
	{
		angle = acos(v3_dot_normed(v3_inv(f->vec[i]), f->vec[j % 3]));
		*(t_vec3*)&verts[f->indices[i]].nor =
			v3_add(*(t_vec3*)&verts[f->indices[i]].nor
				   , v3_mul_scalar(f->nor, angle));
		i++;
		j++;
	}
	return ;
}

static void	normalize_normals(void *ignore, t_vertex_basic *vert)
{
	*(t_vec3*)&vert->nor = v3_normalize(*(t_vec3*)&vert->nor);
	return ;
	(void)ignore;
}

void    sp_build_vbo_normals(t_vao_basic *vao)
{
	ftv_foreach(&vao->vbo.vertices, &bzero_normals, NULL);
	ftv_foreach(&vao->ebo.faces, &sum_normals, vao->vbo.vertices.data);
	ftv_foreach(&vao->vbo.vertices, &normalize_normals, NULL);
	return ;
}
