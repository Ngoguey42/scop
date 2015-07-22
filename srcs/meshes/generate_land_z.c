/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_land_z.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/21 15:54:14 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/22 14:28:48 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_conf.h"
#include "fterror.h"
#include "libft.h"
#include "ft_vector.h"
#include <stdlib.h>

#define DELTA(X, Y) (get_delta((X), (Y), lines->size))

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

#define GETRAND(R) (get_rand((R)))

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
			/* qprintf("[%03d]", DELTA(ix, iy)); */
			(ptr + DELTA(ix, iy))[0] = GETRAND(range) +
				(ptr + DELTA(ix - hidt, iy - hidt))[0] / 4.f +
				(ptr + DELTA(ix + hidt, iy - hidt))[0] / 4.f +
				(ptr + DELTA(ix - hidt, iy + hidt))[0] / 4.f +
				(ptr + DELTA(ix + hidt, iy + hidt))[0] / 4.f;
			/* qprintf("(%02d/%02d)", iy, ix); */
			/* qprintf("%+5.2f/", (ptr + DELTA(ix - hidt, iy - hidt))[0]); */
			/* qprintf("%+5.2f/", (ptr + DELTA(ix + hidt, iy - hidt))[0]); */
			/* qprintf("%+5.2f/", (ptr + DELTA(ix - hidt, iy + hidt))[0]); */
			/* qprintf("%+5.2f  ", (ptr + DELTA(ix + hidt, iy + hidt))[0]); */
			ix += idt;
		}
		iy += idt;
		/* lprintf(""); */
	}
	/* lprintf(""); */
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
			/* qprintf("[%03d]", DELTA(ix, iy)); */
			(ptr + DELTA(ix, iy))[0] = GETRAND(range)
				+ (ptr + DELTA(ix - hidt, iy))[0] / 4.f
				+ (ptr + DELTA(ix + hidt, iy))[0] / 4.f
				+ (ptr + DELTA(ix, iy - hidt))[0] / 4.f
				+ (ptr + DELTA(ix, iy + hidt))[0] / 4.f;
			/* qprintf("(%02d/%02d)", iy, ix); */
			/* qprintf("%+5.2f/", (ptr + DELTA(ix - hidt, iy))[0]); */
			/* qprintf("%+5.2f/", (ptr + DELTA(ix + hidt, iy))[0]); */
			/* qprintf("%+5.2f/", (ptr + DELTA(ix, iy - hidt))[0]); */
			/* qprintf("%+5.2f  ", (ptr + DELTA(ix, iy + hidt))[0]); */
			ix += idt;
		}
		iy += idt;
		/* lprintf(""); */
	}
	/* lprintf(""); */
	return ;
}

void		sp_fill_landgrid(t_ftvector *lines)
{
	int		depth;
	int		idt;
	float	*ptr;
	float	range;

	size_t i ;
	(void)i;
	
#define TEST \
	for (i = 0; i < lines->size * lines->size; i++)\
	{	\
		if (i % lines->size)\
			qprintf("%+5.2f ", (ptr + i)[0]);\
		else\
			qprintf("\n%+5.2f ", (ptr + i)[0]);		\
	}\
	qprintf("\n")

	
	range = LAND_RANGEF;
	idt = lines->size / 2;
	ptr = lines->data;
	(ptr + DELTA(0, 0))[0] = GETRAND(range);
	(ptr + DELTA(idt, 0))[0] = GETRAND(range);
	(ptr + DELTA(0, idt))[0] = GETRAND(range);
	(ptr + DELTA(idt, idt))[0] = GETRAND(range);
	depth = 2;
	while (depth <= POINTS_DEPTHI)
	{
		lprintf("Solving depth %u", depth);
		range *= 0.7f;
		/* range /= 2.f; */
		apply_floats_diag(lines, range, idt);
		/* TEST; */
		apply_floats_side(lines, range, idt, (int[2]){idt / 2, 0});
		/* TEST; */
		apply_floats_side(lines, range, idt, (int[2]){0, idt / 2});
		/* TEST; */
		idt /= 2;
		depth++;
	}	

	/* TEST; */
	return ;
}
