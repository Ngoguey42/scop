/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals_calculation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/27 16:22:14 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/27 17:24:04 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <assert.h>
#include "scop.h"
#include "objmodel_parsing.h"

#define DATA_WIDTH (sizeof(t_vector3) + sizeof(t_ui))
#define DST_(PTR, I) ((void*)(PTR) + DATA_WIDTH * (I))

#define DSTPTR_V3(PTR, I) ((t_vector3*)DST_((PTR), (I)))
#define DSTPTR_COUNT(PTR, I) ((t_ui*)(DST_((PTR), (I)) + sizeof(t_vector3)))

#define SRCPTR_V3(VEC, I) ((t_vector3*)((VEC)->data + (VEC)->chunk_size * (I)))

#define ADD_V3(DST, OTHER) (DST) = v3_add((DST), (OTHER))

static void	devide_and_normalize(void *const dst, size_t const nvert)
{
	size_t	i;

	i = 0;
	while (i < nvert)
	{
		v3_normalize(
			v3_div_scalar(*DSTPTR_V3(dst, i), (float)*DSTPTR_COUNT(dst, i)));
		i++;
	}
	return ;
}

static void	calc_normals(void *const dst, t_ftvector const *vert,
						 t_ftvector const *faces)
{
	t_ui const			*f = faces->data;
	t_ui const *const	faceend = f + faces->chunk_size;
	t_vector3			fvect[3];

	while (f < faceend)
	{
		fvect[0] = v3_sub(*SRCPTR_V3(vert, f[0]), *SRCPTR_V3(vert, f[1]));
		fvect[1] = v3_sub(*SRCPTR_V3(vert, f[1]), *SRCPTR_V3(vert, f[2]));
		fvect[2] = v3_sub(*SRCPTR_V3(vert, f[2]), *SRCPTR_V3(vert, f[0]));
		ADD_V3(*DSTPTR_V3(dst, f[0]), v3_cross(v3_inv(fvect[0]), fvect[2]));
		ADD_V3(*DSTPTR_V3(dst, f[1]), v3_cross(v3_inv(fvect[1]), fvect[0]));
		ADD_V3(*DSTPTR_V3(dst, f[2]), v3_cross(v3_inv(fvect[2]), fvect[1]));
		(*DSTPTR_COUNT(dst, f[0]))++;
		(*DSTPTR_COUNT(dst, f[1]))++;
		(*DSTPTR_COUNT(dst, f[2]))++;
		f += 3;
	}
	devide_and_normalize(dst, vert->size);
	return ;
}

void		sp_normals_add(t_ftvector *vertices, t_ftvector const *faces)
{
	t_ftvector	normals[1];
	/* t_ftvector	newv[1]; */

	assert(vertices->size > 0);
	if (ftv_init_instance(normals, DATA_WIDTH))
		sp_enomem();
	ftv_push_back_unsafe(normals, normals->data);	
	bzero(normals->data, normals->chunk_size);
	if (ftv_insert_count(normals, normals->data, vertices->size - 1))
		sp_enomem();
	calc_normals(normals->data, vertices, faces);
	return ;
}
