/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   land_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/16 08:05:58 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/16 11:55:34 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>
#include <math.h>
/*
static void	generate_land_levels(t_env *e)
{
	return ;
}
*/

int			sp_init_land(t_env *e)
{
	t_land_tmp		landdat[1];

	landdat->grid_npoints = (int)pow(4.f, (float)(LAND_NDEPTHLOOPSI + 1));
	landdat->grid_width = (int)pow(2.f, (float)(LAND_NDEPTHLOOPSI + 1));
	bzero(landdat, sizeof(landdat));
	
	glGenTextures(1, e->land_handles + 0);
	glBindTexture(GL_TEXTURE_2D, e->land_handles[0]);
	glTexImage2D(
		/* GL_TEXTURE_2D, 0, GL_RGBA */
		/* , landdat->grid_width, landdat->grid_width */
		/* , 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 */
		GL_TEXTURE_2D, 0,GL_RGB
		, landdat->grid_width, landdat->grid_width
		, 0,GL_RGB, GL_UNSIGNED_BYTE, 0
		);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	
	glGenFramebuffers(1, e->land_handles + 1);
	glBindFramebuffer(GL_FRAMEBUFFER, e->land_handles[1]);

	
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
						 e->land_handles[0], 0);
	glDrawBuffers(1, e->land_handles + 1);
	
	/* glReadBuffer(GL_NONE); */
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return (ERROR("Framebuffer not complete!\n"));
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	/* glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT); //TODO */
	/* glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT); //TODO */
	/* glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT); //TODO */
	return (0);
}
