/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/01 14:35:20 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/01 14:53:58 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath.h"
#include "ft_debug.h"

const t_matrix4		g_emptym4 =
{
	{0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
	0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f}
};

const t_matrix4		g_identitym4 =
{
	{1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f}
};

void			m4_print(t_matrix4 mat)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (i % 4 == 3)
			qprintf("% 5.2f\n", mat.raw[i]);
		else
			qprintf("% 5.2f, ", mat.raw[i]);
		i++;
	}
	return ;
}
	
