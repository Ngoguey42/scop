/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_land_rgb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 17:07:12 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/22 18:26:15 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_conf.h"
#include "fterror.h"
#include "libft.h"
#include "ft_vector.h"
#include <stdlib.h>
#include <string.h>

#define CTOF(V) ((V) / 256.f)
#define NUM_COLORS (sizeof(g_colors) / sizeof(*g_colors))
#define COLOR_UP(C) ((C)[3] + (C)[4])
#define COLOR_LO(C) ((C)[3] - (C)[4])
#define COLOR_RATIO(R, C) (1.f - ABS((R - (C)[3]) / (C)[4]))

static float	g_colors[][5] =
{
	{CTOF(220.f), CTOF(220.f), CTOF(220.f), 0.925f, 0.075f},//snow
	{CTOF(94.f), CTOF(71.f), CTOF(64.f), 0.8f, 0.10f},		//rock
	{CTOF(13.f), CTOF(55.f), CTOF(13.f), 0.675f, 0.125f},	//dark forest
	{CTOF(55.f), CTOF(170.f), CTOF(80.f), 0.400f, 0.225f},	//grass1
	{CTOF(34.f), CTOF(156.f), CTOF(13.f), 0.300f, 0.1f},	//disneyland
	{CTOF(109.f), CTOF(61.f), CTOF(39.f), 0.4f, 0.05f},		//earth
	{CTOF(237.f), CTOF(200.f), CTOF(85.f), 0.175f, 0.025f},	//sand
	{CTOF(94.f), CTOF(97.f), CTOF(186.f), 0.075f, 0.075f},	//water
};

static void	normalize_prop(float proportions[NUM_COLORS])
{
	size_t	i;
	float	sum;

	i = 0;
	sum = 0.f;
	while (i < NUM_COLORS)
		sum += proportions[i++];
	i = 0;
	while (i < NUM_COLORS)
		proportions[i++] /= sum;
	return ;
}

static void	calc_color_ratio(float proportions[NUM_COLORS], float ratio)
{
	size_t		i;

	i = 0;
	while (i < NUM_COLORS)
	{
		if (ratio < COLOR_UP(g_colors[i]) && ratio > COLOR_LO(g_colors[i]))
			proportions[i] = COLOR_RATIO(ratio, g_colors[i]);
		else
			proportions[i] = 0.f;
		i++;
	}
	return ;
}

static void	input_color(float *rgb, float ratio)
{
	float		tmp[3];
	float		proportions[NUM_COLORS];
	size_t		i;

	calc_color_ratio(proportions, ratio);
	normalize_prop(proportions);
	i = 0;
	tmp[0] = 0.f;
	tmp[1] = 0.f;
	tmp[2] = 0.f;
	while (i < NUM_COLORS)
	{
		if (proportions[i] > 0.f)
		{
			tmp[0] += g_colors[i][0] * proportions[i];
			tmp[1] += g_colors[i][1] * proportions[i];
			tmp[2] += g_colors[i][2] * proportions[i];
		}
		i++;
	}
	memcpy(rgb, tmp, sizeof(tmp));
	return ;
}

static float    get_rand(float init)
{
	float nb;

	nb = (((float)(rand() % 10000)) / 10000.f - 0.5f) * LAND_COLORRAND + init;
	if (nb > 1.f)
		return (1.f);
	else if (nb < 0.f)
		return (0.f);
	return (nb);
}

void		sp_fill_landrgb(t_ftvector *vertices, float const bounds[2])
{
	float const		delta = bounds[1] - bounds[0];
	size_t			i;
	float			*ptr;

	i = 0;
	ptr = vertices->data;
	while (i < vertices->size)
	{
		input_color(ptr + 3, get_rand((ptr[1] - bounds[0]) / delta));		
		ptr += 6;
		i++;
	}
	return ;
}
