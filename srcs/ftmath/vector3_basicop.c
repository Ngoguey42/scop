/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_basicop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 09:37:05 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/15 09:50:10 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath.h"
#include <math.h>

#define DO_OP(A, B) (a.A * b.B - a.B * b.A)

t_vector3	v3_cross(t_vector3 a, t_vector3 b)
{
	return (ATOV3(DO_OP(y, z), DO_OP(z, x), DO_OP(x, y)));
}

t_vector3	v3_add(t_vector3 a, t_vector3 b)
{
	return (ATOV3(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vector3	v3_sub(t_vector3 a, t_vector3 b)
{
	return (ATOV3(a.x - b.x, a.y - b.y, a.z - b.z));
}
