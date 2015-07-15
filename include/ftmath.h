/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 12:16:50 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/15 09:58:47 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMATH_H
# define FTMATH_H

# include "libft.h"

/*
** Macroes
*/
# define FLOORF(A) ()
# define CEILF(A) ()
# define ROUND_FTOI(A) ((A) > 0.f ? (int)((A) + 0.5f) : (int)((A) - 0.5f))

/*
** ATOV3		Absolute to vector3
** ATOM4		Absolute to matrix4
*/
# define ATOV3(...) (t_vector3){__VA_ARGS__}
# define ATOM4(...) (t_matrix4){{__VA_ARGS__}}

typedef enum	e_axis
{
	x_axis,
	y_axis,
	z_axis
}				t_axis;

/*
** VECTOR3
*/

typedef struct	s_vector3
{
	float				x;
	float				y;
	float				z;
}				t_vector3;

void			v3_print(t_vector3 v);
t_vector3		v3_normalize(t_vector3 v);
t_vector3		v3_frontnormed(float const angles[2]);
t_vector3		v3_cross(t_vector3 a, t_vector3 b);
t_vector3		v3_sub(t_vector3 a, t_vector3 b);
t_vector3		v3_add(t_vector3 a, t_vector3 b);

/*
** MATRIX4
*/
struct			s_vectorj4
{
	float				j[4];
};

typedef struct	s_vector4
{
	float				i[4];
}				t_vector4;

typedef union	u_matrix4
{
	float				raw[16];
	struct s_vectorj4	i[4];
}				t_matrix4;
# define MAT4 t_matrix4

MAT4			m4_scale_nonuniform(float vect[3]);
MAT4			m4_scale_uniform(float fact);
MAT4			m4_scaleref_nonuniform(MAT4 const *ref, float vect[3]);
MAT4			m4_scaleref_uniform(MAT4 const *ref, float fact);

MAT4			m4_translate_nonuniform(float vect[3]);
MAT4			m4_translate_uniform(float fact);
MAT4			m4_translateref_nonuniform(MAT4 const *ref, float vect[3]);
MAT4			m4_translateref_uniform(MAT4 const *ref, float fact);

MAT4			m4_invtranslate_nonuniform(float vect[3]);
MAT4			m4_invtranslate_uniform(float fact);
MAT4			m4_invtranslateref_nonuniform(MAT4 const *ref, float vect[3]);
MAT4			m4_invtranslateref_uniform(MAT4 const *ref, float fact);

MAT4			m4_rotation_axis(t_axis a, float fact);
MAT4			m4_rotationref_axis(MAT4 const *ref, t_axis a, float fact);

MAT4			m4_dotprod(MAT4 mata, MAT4 matb);
MAT4			m4_fovprojection(float fov, float ratio, float near, float far);

void			m4_print(MAT4 mat);
MAT4			m4_lookat(t_vector3 eye, t_vector3 at);

# undef MAT4

#endif
