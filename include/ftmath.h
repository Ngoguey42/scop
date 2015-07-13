/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 12:16:50 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/13 15:40:47 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMATH_H
# define FTMATH_H

# include "libft.h"

/*
** Macroes
*/
/* #define MIN(A, B) () */
/* #define MAX(A, B) () */
/* #define ABS(A) () */

#define FLOORF(A) ()
#define CEILF(A) ()
#define ROUND_FTOI(A) ((A) > 0.f ? (int)((A) + 0.5f) : (int)((A) - 0.5f))

typedef struct			s_vector3
{
	float				x;
	float				y;
	float				z;
}						t_vector3;

struct					s_vectorj4
{
	float				j[4];
};

typedef struct			s_vector4
{
	float				i[4];
}						t_vector4;

typedef union			u_matrix4
{
	float				raw[16];
	struct s_vectorj4	i[4];
}						t_matrix4;

typedef enum			e_axis
{
	x_axis,
	y_axis,
	z_axis
}						t_axis;

t_matrix4	m4_scale_nonuniform(float vect[3]);
t_matrix4	m4_scale_uniform(float fact);
t_matrix4	m4_scaleref_nonuniform(t_matrix4 const *ref, float vect[3]);
t_matrix4	m4_scaleref_uniform(t_matrix4 const *ref, float fact);

t_matrix4	m4_translate_nonuniform(float vect[3]);
t_matrix4	m4_translate_uniform(float fact);
t_matrix4	m4_translateref_nonuniform(t_matrix4 const *ref, float vect[3]);
t_matrix4	m4_translateref_uniform(t_matrix4 const *ref, float fact);

t_matrix4	m4_invtranslate_nonuniform(float vect[3]);
t_matrix4	m4_invtranslate_uniform(float fact);
t_matrix4	m4_invtranslateref_nonuniform(t_matrix4 const *ref, float vect[3]);
t_matrix4	m4_invtranslateref_uniform(t_matrix4 const *ref, float fact);

t_matrix4	m4_rotation_axis(t_axis a, float fact);
t_matrix4	m4_rotationref_axis(t_matrix4 const *ref, t_axis a, float fact);

t_matrix4	m4_dotprod(t_matrix4 mata, t_matrix4 matb);
t_matrix4	m4_fovprojection(float fov, float ratio, float near, float far);

void			m4_print(t_matrix4 mat);
t_matrix4   m4_lookat(t_vector3 eye, t_vector3 at);

void        v3_print(t_vector3 v);
t_vector3   v3_normalize(t_vector3 v);
t_vector3   v3_frontnormed(float const angles[2]);
t_vector3   v3_cross(t_vector3 a, t_vector3 b);
t_vector3   v3_sub(t_vector3 a, t_vector3 b);
t_vector3   v3_add(t_vector3 a, t_vector3 b);

#endif
