/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/13 14:09:03 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/13 15:44:00 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath.h"
#include <math.h>

void		v3_print(t_vector3 v)
{
	qprintf("% 5.2f % 5.2f % 5.2f\n", v.x, v.y, v.z);
	return ;
}

t_vector3	v3_normalize(t_vector3 v)
{
	float const	coef = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

	v.x /= coef;
	v.y /= coef;
	v.z /= coef;
	return (v);
}

t_vector3	v3_frontnormed(float const angles[2])
{
	return (v3_normalize((t_vector3){
				cos(angles[0]) * cos(angles[1]),
					sin(angles[1]),
					sin(angles[0]) * cos(angles[1]),
					}));
}

/*
 */

t_vector3	v3_cross(t_vector3 a, t_vector3 b)
{	
	return ((t_vector3){
			a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
				});
}

t_vector3	v3_add(t_vector3 a, t_vector3 b)
{	
	return ((t_vector3){
			a.x + b.x,
			a.y + b.y,
			a.z + b.z,
				});
}

t_vector3	v3_sub(t_vector3 a, t_vector3 b)
{	
	return ((t_vector3){
			a.x - b.x,
			a.y - b.y,
			a.z - b.z,
				});
}

