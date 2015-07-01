/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 12:16:50 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/01 14:52:26 by ngoguey          ###   ########.fr       */
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


t_matrix4		m4_scale_nonuniform(float vect[3]);
t_matrix4		m4_scale_uniform(float fact);
t_matrix4		m4_scaleref_nonuniform(t_matrix4 const *ref, float vect[3]);
t_matrix4		m4_scaleref_uniform(t_matrix4 const *ref, float fact);

t_matrix4		m4_translate_nonuniform(float vect[3]);
t_matrix4		m4_translate_uniform(float fact);
t_matrix4		m4_translateref_nonuniform(t_matrix4 const *ref, float vect[3]);
t_matrix4		m4_translateref_uniform(t_matrix4 const *ref, float fact);

void			m4_print(t_matrix4 mat);
#endif
