/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_land_xyz.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/21 15:54:37 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/21 16:21:17 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_conf.h"
#include "fterror.h"
#include "libft.h"
#include "ft_vector.h"
#include <stdlib.h>

void	sp_fill_landvertices(t_ftvector const *lines, t_ftvector *vertices)
{
	int		x;
	int		y;
	float	tmp[3];
	float const		fact = LAND_SIDEF / (float)lines->size;
	
	y = 0;
	while (y < lines->size)
	{
		tmp[2] = (float)y * fact - LAND_SIDEHALFF;
		x = 0;
		while (x < lines->size)
		{
			tmp[0] = (float)x * fact - LAND_SIDEHALFF;
			tmp[1] = *(((float*)lines->data) + x + y * lines->size);
			ftv_push_back(vertices, &tmp);
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
			ftv_push_back(faces, &tmp);
			tmp[0] = (x - 1) + (y - 1) * lines->size;
			tmp[1] = (x + 0) + (y - 1) * lines->size;
			tmp[2] = (x + 0) + (y + 0) * lines->size;
			ftv_push_back(faces, &tmp);
			x += 1;
		}
		y += 1;
	}
	
	return ;
}
