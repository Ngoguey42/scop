/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_scale.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/01 14:03:07 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/01 15:11:06 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath.h"

extern t_matrix4	g_emptym4;
extern t_matrix4	g_identitym4;

t_matrix4			m4_scale_uniform(float fact)
{
	t_matrix4		ret;

	ret = g_identitym4;
	ret.i[0].j[0] = fact;
	ret.i[1].j[1] = fact;
	ret.i[2].j[2] = fact;
	return (ret);
}

t_matrix4			m4_scale_nonuniform(float vect[3])
{
	t_matrix4		ret;

	ret = g_identitym4;
	ret.i[0].j[0] = vect[0];
	ret.i[1].j[1] = vect[1];
	ret.i[2].j[2] = vect[2];
	return (ret);
}

t_matrix4			m4_scaleref_uniform(t_matrix4 const *ref, float fact)
{
	t_matrix4		ret;

	ret = *ref;
	ret.i[0].j[0] *= fact;
	ret.i[1].j[1] *= fact;
	ret.i[2].j[2] *= fact;
	return (ret);
}

t_matrix4			m4_scaleref_nonuniform(t_matrix4 const *ref, float vect[3])
{
	t_matrix4		ret;

	ret = *ref;
	ret.i[0].j[0] *= vect[0];
	ret.i[1].j[1] *= vect[1];
	ret.i[2].j[2] *= vect[2];
	return (ret);
}
