/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_land_z.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/21 15:54:14 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/28 16:07:34 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_conf.h"
#include "fterror.h"
#include "libft.h"
#include "ft_vector.h"
#include <stdlib.h>

#define DELTA(X, Y) (get_delta((X), (Y), lines->size))
#define GETRAND(R) (get_rand((R)))

static int		get_delta(int x, int y, int size)
{
	while (x < 0)
		x += size;
	while (y < 0)
		y += size;
	while (x >= size)
		x -= size;
	while (y >= size)
		y -= size;
	return (x + y * size);
}

static float	get_rand(float range)
{
	return ((((float)(rand() % 10000)) / 10000.f - 0.5f) * range);
}

static void		apply_floats_diag(t_ftvector *lines, float range, int idt)
{
	int			ix;
	int			iy;
	float		*ptr;
	int const	hidt = idt / 2;

	iy = hidt;
	ptr = lines->data;
	while (iy < (int)lines->size)
	{
		ix = hidt;
		while (ix < (int)lines->size)
		{
			(ptr + DELTA(ix, iy))[0] = GETRAND(range) +
				(ptr + DELTA(ix - hidt, iy - hidt))[0] / 4.f +
				(ptr + DELTA(ix + hidt, iy - hidt))[0] / 4.f +
				(ptr + DELTA(ix - hidt, iy + hidt))[0] / 4.f +
				(ptr + DELTA(ix + hidt, iy + hidt))[0] / 4.f;
			ix += idt;
		}
		iy += idt;
	}
	return ;
}

static void		apply_floats_side(t_ftvector *lines, float range, int idt,
	int ipos[0])
{
	int			ix;
	int			iy;
	float		*ptr;
	int const	hidt = idt / 2;

	iy = ipos[0];
	ptr = lines->data;
	while (iy < (int)lines->size)
	{
		ix = ipos[1];
		while (ix < (int)lines->size)
		{
			(ptr + DELTA(ix, iy))[0] = GETRAND(range)
				+ (ptr + DELTA(ix - hidt, iy))[0] / 4.f
				+ (ptr + DELTA(ix + hidt, iy))[0] / 4.f
				+ (ptr + DELTA(ix, iy - hidt))[0] / 4.f
				+ (ptr + DELTA(ix, iy + hidt))[0] / 4.f;
			ix += idt;
		}
		iy += idt;
	}
	return ;
}

void			sp_fill_landgrid(t_ftvector *lines)
{
	int		depth;
	int		idt;
	float	*ptr;
	float	range;

	range = LAND_RANGEF;
	idt = lines->size / 2;
	ptr = lines->data;
	(ptr + DELTA(0, 0))[0] = GETRAND(range) + LAND_YF;
	(ptr + DELTA(idt, 0))[0] = GETRAND(range) + LAND_YF;
	(ptr + DELTA(0, idt))[0] = GETRAND(range) + LAND_YF;
	(ptr + DELTA(idt, idt))[0] = GETRAND(range) + LAND_YF;
	depth = 2;
	while (depth <= POINTS_DEPTHI)
	{
		range *= 0.60f;
		apply_floats_diag(lines, range, idt);
		apply_floats_side(lines, range, idt, (int[2]){idt / 2, 0});
		apply_floats_side(lines, range, idt, (int[2]){0, idt / 2});
		idt /= 2;
		depth++;
	}
	return ;
}
