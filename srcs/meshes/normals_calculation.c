/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals_calculation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/27 16:22:14 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/09 16:39:35 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include <assert.h>
#include "scop.h"

#define DATA_WIDTH sizeof(t_vector3)
#define DST_(PTR, I) ((void*)(PTR) + DATA_WIDTH * (I))

#define DSTPTR_V3(PTR, I) ((t_vector3*)DST_((PTR), (I)))

#define SRCPTR_V3(VEC, I) ((t_vector3*)((VEC)->data + (VEC)->chunk_size * (I)))

#define ADD_V3(DST, OTHER) (DST) = v3_add((DST), (OTHER))

#define ANGLE_BETWEEN(V1, V2) (acos(v3_dot_normed((V1), (V2))))

static void	normalize_all(void *const dst, size_t const nvert)
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

static void	sum_normals_all(void *const dst, t_ftvector const *vert,
							t_ftvector const *faces)
{
	t_ui const			*f = faces->data;
	t_ui const *const	faceend = ftv_end(faces);
	t_vector3			fvect[3];
	t_vector3			normal;

	while (f < faceend)
	{
		fvect[0] = v3_normalize(
			v3_sub(*SRCPTR_V3(vert, f[0]), *SRCPTR_V3(vert, f[1])));
		fvect[1] = v3_normalize(
			v3_sub(*SRCPTR_V3(vert, f[1]), *SRCPTR_V3(vert, f[2])));
		fvect[2] = v3_normalize(
			v3_sub(*SRCPTR_V3(vert, f[2]), *SRCPTR_V3(vert, f[0])));
		normal = v3_cross(v3_inv(fvect[0]), fvect[2]);
		ADD_V3(*DSTPTR_V3(dst, f[0]), v3_mul_scalar(normal,
			ANGLE_BETWEEN(v3_inv(fvect[0]), fvect[2])));
		ADD_V3(*DSTPTR_V3(dst, f[1]), v3_mul_scalar(normal,
			ANGLE_BETWEEN(v3_inv(fvect[1]), fvect[0])));
		ADD_V3(*DSTPTR_V3(dst, f[2]), v3_mul_scalar(normal,
			ANGLE_BETWEEN(v3_inv(fvect[2]), fvect[1])));
		f += 3;
	}
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

void		sp_inject_normals(t_ftvector *vertices, t_ftvector const *faces)
{
	t_ftvector	normals[1];
	t_ftvector	newv[1];

	lprintf("    Creating some Normal coords");
	assert(vertices->size > 0);
	if (ftv_init_instance(normals, DATA_WIDTH))
		sp_enomem();
	ftv_push_back_unsafe(normals, normals->data);
	bzero(normals->data, normals->chunk_size);
	if (ftv_insert_count(normals, normals->data, vertices->size - 1))
		sp_enomem();
	sum_normals_all(normals->data, vertices, faces);
	normalize_all(normals->data, vertices->size);
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

#define SRCPOS(VEC, I) (&((((t_vertex_basic*)((VEC)->data)) + (I))->pos))
#define SRCPOS_V3(VEC, I) ((t_vector3*)SRCPOS((VEC), (I)))

#define DSTNOR(VEC, I) (&((((t_vertex_basic*)((VEC)->data)) + (I))->nor))
#define DSTNOR_V3(VEC, I) ((t_vector3*)DSTNOR((VEC), (I)))

#define ADD_V3(DST, OTHER) (DST) = v3_add((DST), (OTHER))
#define ANGLE_BETWEEN(V1, V2) (acos(v3_dot_normed((V1), (V2))))

static void	sum_normals_allNEW(t_ftvector *v, t_ftvector const *faces)
{
	t_ui const			*f = faces->data;
	t_ui const *const	faceend = ftv_end(faces);
	t_vector3			fvect[3];
	t_vector3			normal;

	while (f < faceend)
	{
		fvect[0] = v3_normalize(
			v3_sub(*SRCPOS_V3(v, f[0]), *SRCPOS_V3(v, f[1])));
		fvect[1] = v3_normalize(
			v3_sub(*SRCPOS_V3(v, f[1]), *SRCPOS_V3(v, f[2])));
		fvect[2] = v3_normalize(
			v3_sub(*SRCPOS_V3(v, f[2]), *SRCPOS_V3(v, f[0])));
		normal = v3_cross(v3_inv(fvect[0]), fvect[2]);
		ADD_V3(*DSTNOR_V3(v, f[0]), v3_mul_scalar(normal,
			ANGLE_BETWEEN(v3_inv(fvect[0]), fvect[2])));
		ADD_V3(*DSTNOR_V3(v, f[1]), v3_mul_scalar(normal,
			ANGLE_BETWEEN(v3_inv(fvect[1]), fvect[0])));
		ADD_V3(*DSTNOR_V3(v, f[2]), v3_mul_scalar(normal,
			ANGLE_BETWEEN(v3_inv(fvect[2]), fvect[1])));
		f += 3;
	}
	return ;
}

static void	bzero_normals(void *ignore, t_vertex_basic *vert)
{
	bzero(&vert->nor, sizeof(vert->nor));
	return ;
	(void)ignore;
}

static void	normalize_normals(void *ignore, t_vertex_basic *vert)
{
	t_vector3	const	tmp[1] = {v3_normalize(*(t_vector3*)&vert->nor)};

	memcpy(&vert->nor, tmp, sizeof(t_vector3));
	return ;
	(void)ignore;
}

void		sp_calc_normals(t_env const *e, t_mesh const *me
							, t_vbo_basic *vbo)
{
	lprintf("    Creating some Normal coords");
	ftv_foreach(&vbo->vertices, &bzero_normals, NULL);
	sum_normals_allNEW(&vbo->vertices, &me->faces);
	ftv_foreach(&vbo->vertices, &normalize_normals, NULL);
	return ;
	(void)e;
}
