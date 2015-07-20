/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_invtranslate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/13 12:31:47 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 12:28:20 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath.h"

extern t_matrix4	g_identitym4;

t_matrix4	m4_invtranslate_uniform(float fact)
{
	t_matrix4		ret;

	ret = g_identitym4;
	ret.i[0].j[3] = -fact;
	ret.i[1].j[3] = -fact;
	ret.i[2].j[3] = -fact;
	return (ret);
}

t_matrix4	m4_invtranslate_nonuniform(t_vector3 vect)
{
	t_matrix4		ret;

	ret = g_identitym4;
	ret.i[0].j[3] = -vect.x;
	ret.i[1].j[3] = -vect.y;
	ret.i[2].j[3] = -vect.z;
	return (ret);
}

t_matrix4	m4_invtranslateref_uniform(t_matrix4 const *ref, float fact)
{
	t_matrix4 const		tmp = m4_invtranslate_uniform(fact);

	return (m4_dotprod(ref, &tmp));
}

t_matrix4	m4_invtranslateref_nonuniform(t_matrix4 const *ref, t_vector3 vect)
{
	t_matrix4 const		tmp = m4_invtranslate_nonuniform(vect);

	return (m4_dotprod(ref, &tmp));
}
