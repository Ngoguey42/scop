/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals_calculation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/27 16:22:14 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/28 11:39:51 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <assert.h>
#include "scop.h"
#include "objmodel_parsing.h"

#define DATA_WIDTH sizeof(t_vector3)
#define DST_(PTR, I) ((void*)(PTR) + DATA_WIDTH * (I))

#define DSTPTR_V3(PTR, I) ((t_vector3*)DST_((PTR), (I)))

#define SRCPTR_V3(VEC, I) ((t_vector3*)((VEC)->data + (VEC)->chunk_size * (I)))

#define ADD_V3(DST, OTHER) (DST) = v3_add((DST), (OTHER))

static void	normalize(void *const dst, size_t const nvert)
{
	size_t	i;

	i = 0;
	while (i < nvert)
	{
		*DSTPTR_V3(dst, i) = v3_normalize(*DSTPTR_V3(dst, i));
		i++;
	}
	return ;
}

static void	calc_normals(void *const dst, t_ftvector const *vert,
							t_ftvector const *faces)
{
	t_ui const			*f = faces->data;
	t_ui const *const	faceend = ftv_end(faces);
	t_vector3			fvect[3];

	while (f < faceend)
	{
		fvect[0] = v3_sub(*SRCPTR_V3(vert, f[0]), *SRCPTR_V3(vert, f[1]));
		fvect[1] = v3_sub(*SRCPTR_V3(vert, f[1]), *SRCPTR_V3(vert, f[2]));
		fvect[2] = v3_sub(*SRCPTR_V3(vert, f[2]), *SRCPTR_V3(vert, f[0]));
		ADD_V3(*DSTPTR_V3(dst, f[0]), v3_cross(v3_inv(fvect[0]), fvect[2]));
		ADD_V3(*DSTPTR_V3(dst, f[1]), v3_cross(v3_inv(fvect[1]), fvect[0]));
		ADD_V3(*DSTPTR_V3(dst, f[2]), v3_cross(v3_inv(fvect[2]), fvect[1]));
		f += 3;
	}
	normalize(dst, vert->size);
	return ;
}

static void	build_new_vertices(t_ftvector *newv, t_ftvector const *oldv,
								t_ftvector const *normals)
{
	float const		*vertex = oldv->data;
	float const		*vertexend = ftv_end(oldv);
	float const		*normal = normals->data;
	size_t const	old_num_floats = oldv->chunk_size / sizeof(float);
	float			tmp[old_num_floats + 3];

	while (vertex < vertexend)
	{
		memcpy(tmp, vertex, oldv->chunk_size);
		memcpy(tmp + old_num_floats, normal, DATA_WIDTH);
		ftv_push_back_unsafe(newv, tmp);
		vertex += old_num_floats;
		normal = (void*)normal + DATA_WIDTH;
	}
	return ;
}

void		sp_normals_add(t_ftvector *vertices, t_ftvector const *faces)
{
	t_ftvector	normals[1];
	t_ftvector	newv[1];

	assert(vertices->size > 0);
	if (ftv_init_instance(normals, DATA_WIDTH))
		sp_enomem();
	ftv_push_back_unsafe(normals, normals->data);
	bzero(normals->data, normals->chunk_size);
	if (ftv_insert_count(normals, normals->data, vertices->size - 1))
		sp_enomem();
	calc_normals(normals->data, vertices, faces);
	if (ftv_init_instance(newv, vertices->chunk_size + DATA_WIDTH))
		sp_enomem();
	if (ftv_reserve(newv, vertices->size))
		sp_enomem();
	build_new_vertices(newv, vertices, normals);
	ftv_release(normals, NULL);
	ftv_release(vertices, NULL);
	memcpy(vertices, newv, sizeof(t_ftvector));
	return ;
}
