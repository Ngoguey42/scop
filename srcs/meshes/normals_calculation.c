/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals_calculation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/27 16:22:14 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/09 16:44:36 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include <assert.h>
#include "scop.h"

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
	vbo->nnor = 3;
	return ;
	(void)e;
}
