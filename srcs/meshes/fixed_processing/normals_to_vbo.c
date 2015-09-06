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

static void	bzero_normals(t_vertex_basic *vert)
{
	bzero(&vert->nor, sizeof(vert->nor));
	return ;
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
/*
		t_vec3 v3 = *(t_vec3*)&verts[f->indices[i]].nor; //d

#define VALID(v) (v < 10.f && v > -10.f && !isnan(v))
		if (!VALID(v3.x)
			|| !VALID(v3.y)
			|| !VALID(v3.z)
			|| !VALID(angle)
			)
		{
			qprintf("angle: %-10.2f\n", angle);
			qprintf("face normal: "); v3_print(f->nor);
			
//			v3_print(v3); //d
			qprintf("\n");
		}
*/		
		i++;
		j++;
	}
	return ;
}

static void	normalize_normals(t_vertex_basic *vert)
{

//	t_vec3 v3prev = *(t_vec3*)&vert->nor;
	
	*(t_vec3*)&vert->nor = v3_normalize(*(t_vec3*)&vert->nor);
/*
	t_vec3 v3 = *(t_vec3*)&vert->nor;
	if (!VALID(v3.x)
		|| !VALID(v3.y)
		|| !VALID(v3.z)
		)
	{
		v3_print(v3prev);
		v3_print(v3);
		qprintf("\n");

	}
*/	
	return ;
}

void		sp_normals_to_vbo(t_vao_basic *vao)
{
	ftv_foreach0(&vao->vbo.vertices, &bzero_normals);
	ftv_foreach(&vao->ebo.faces, &sum_normals, vao->vbo.vertices.data);
	ftv_foreach0(&vao->vbo.vertices, &normalize_normals);
	vao->vbo.nnor = 3;
	return ;
}
