/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_scale.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/01 14:03:07 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 12:28:13 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath.h"

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

t_matrix4			m4_scale_nonuniform(t_vector3 vect)
{
	t_matrix4		ret;

	ret = g_identitym4;
	ret.i[0].j[0] = vect.x;
	ret.i[1].j[1] = vect.y;
	ret.i[2].j[2] = vect.z;
	return (ret);
}

t_matrix4			m4_scaleref_uniform(t_matrix4 const *ref, float fact)
{
	t_matrix4 const		tmp = m4_scale_uniform(fact);

	return (m4_dotprod(ref, &tmp));
}

t_matrix4			m4_scaleref_nonuniform(t_matrix4 const *ref, t_vector3 vect)
{
	t_matrix4 const		tmp = m4_scale_nonuniform(vect);

	return (m4_dotprod(ref, &tmp));
}
