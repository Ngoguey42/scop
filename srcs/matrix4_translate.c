/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_translate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/01 14:36:19 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/01 15:03:42 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath.h"

extern t_matrix4	g_emptym4;
extern t_matrix4	g_identitym4;

t_matrix4		m4_translate_uniform(float fact)
{
	t_matrix4		ret;

	ret = g_identitym4;
	ret.i[0].j[3] = fact;
	ret.i[1].j[3] = fact;
	ret.i[2].j[3] = fact;
	/* ret.i[3].j[3] = 1.f; */
	return (ret);
}

t_matrix4		m4_translate_nonuniform(float vect[3])
{
	t_matrix4		ret;

	ret = g_identitym4;
	ret.i[0].j[3] = vect[0];
	ret.i[1].j[3] = vect[1];
	ret.i[2].j[3] = vect[2];
	/* ret.i[3].j[3] = 1.f; */
	return (ret);
}

t_matrix4		m4_translateref_uniform(t_matrix4 const *ref, float fact)
{
	t_matrix4		ret;

	ret = *ref;
	ret.i[0].j[3] += fact;
	ret.i[1].j[3] += fact;
	ret.i[2].j[3] += fact;
	/* ret.i[3].j[3] = 1.f; */
	return (ret);
}

t_matrix4		m4_translateref_nonuniform(t_matrix4 const *ref, float vect[3])
{
	t_matrix4		ret;

	ret = *ref;
	ret.i[0].j[3] += vect[0];
	ret.i[1].j[3] += vect[1];
	ret.i[2].j[3] += vect[2];
	/* ret.i[3].j[3] = 1.f; */
	return (ret);
}
