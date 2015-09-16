/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   land_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/16 08:05:58 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/16 08:16:04 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	generate_land_levels(t_env *e)
{
	if (ftv_init_instance(&e->land_levels))
	return ;
}


int			sp_init_land(t_env *e)
{
	glGenTextures(1, e->land_handles);
	glBindTexture(GL_TEXTURE_2D, e->land_handles[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, );
	return (0);
}
