/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_land_xyz.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 17:08:03 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/27 10:01:19 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_conf.h"
#include "fterror.h"
#include "libft.h"
#include "ft_vector.h"
#include <stdlib.h>

void	sp_fill_landvertices(t_ftvector const *lines, t_ftvector *vertices,
							 float bounds[2])
{
	size_t			x;
	size_t			y;
	float			tmp[3];
	float const		fact = LAND_SIDEF / (float)lines->size;
	
	bounds[0] = *(float*)lines->data;
	bounds[1] = *(float*)lines->data;
	y = 0;
	while (y < lines->size)
	{
		tmp[2] = (float)y * fact - LAND_SIDEHALFF;
		x = 0;
		while (x < lines->size)
		{
			tmp[0] = (float)x * fact - LAND_SIDEHALFF;
			tmp[1] = *(((float*)lines->data) + x + y * lines->size);
			ftv_push_back_unsafe(vertices, &tmp);
			if (tmp[1] > bounds[1])
				bounds[1] = tmp[1];
			else if (tmp[1] < bounds[0])
				bounds[0] = tmp[1];
			x += 1;
		}
		y += 1;
	}
	return ;
}

void	sp_fill_landfaces(t_ftvector const *lines, t_ftvector *faces)
{
	size_t			x;
	size_t			y;
	unsigned int	tmp[3];

	y = 1;
	while (y < lines->size)
	{
		x = 1;
		while (x < lines->size)
		{
			tmp[0] = (x - 1) + (y - 1) * lines->size;
			tmp[1] = (x + 0) + (y + 0) * lines->size;
			tmp[2] = (x - 1) + (y + 0) * lines->size;
			ftv_push_back_unsafe(faces, &tmp);
			tmp[0] = (x - 1) + (y - 1) * lines->size;
			tmp[1] = (x + 0) + (y - 1) * lines->size;
			tmp[2] = (x + 0) + (y + 0) * lines->size;
			ftv_push_back_unsafe(faces, &tmp);
			x += 1;
		}
		y += 1;
	}	
	return ;
}
