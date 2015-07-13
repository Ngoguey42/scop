/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_invtranslate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/13 12:31:47 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/13 12:55:28 by ngoguey          ###   ########.fr       */
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

t_matrix4	m4_invtranslate_nonuniform(float vect[3])
{
	t_matrix4		ret;

	ret = g_identitym4;
	ret.i[0].j[3] = -vect[0];
	ret.i[1].j[3] = -vect[1];
	ret.i[2].j[3] = -vect[2];
	return (ret);
}

t_matrix4	m4_invtranslateref_uniform(t_matrix4 const *ref, float fact)
{
	return (m4_dotprod(*ref, m4_invtranslate_uniform(fact)));
}

t_matrix4	m4_invtranslateref_nonuniform(t_matrix4 const *ref, float vect[3])
{
	return (m4_dotprod(*ref, m4_invtranslate_nonuniform(vect)));
}
