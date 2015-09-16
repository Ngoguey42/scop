/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   land_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/16 08:05:58 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/16 14:31:23 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>
#include <math.h>

static void	setup_ld(t_land_tmp ld[1])
{
	bzero(ld, sizeof(*ld));
	ld->grid_npoints = (int)pow(4.f, (float)(LAND_NDEPTHLOOPSI + 1));
	ld->grid_width = (int)pow(2.f, (float)(LAND_NDEPTHLOOPSI + 1));
	qprintf("grid_npoints:%d grid_width:%d\n", ld->grid_npoints
			, ld->grid_width);
	return ;
}

static void	generate_land(t_env *e, t_land_tmp ld[1])
{
	t_program const		*p;

	p = e->programs + sp_landgen_notrel_program;
	glBindFramebuffer(GL_FRAMEBUFFER, ld->fbo_handle);
	glViewport(0, 0, ld->grid_width, ld->grid_width);
	glBindVertexArray(ld->vao_handle);

	glUseProgram(p->handle);
	UNIF(p, m1i, "level_stride", ld->grid_width / 2);
	UNIF(p, m1iv, "phase_startoffset", 2, (int[]){0, 0});
	UNIF(p, m2fv, "random_seeds", 1, (float[]){ft_randf01(), ft_randf01()});
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
	glUseProgram(0);
	return ;
}

static void	setup_vao(t_env e[1], t_land_tmp ld[1])
{
	GLfloat const	 vertices[] = {
	-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f};

	glGenVertexArrays(1, &ld->vao_handle);
	glBindVertexArray(ld->vao_handle);
	glGenBuffers(1, &ld->vbo_handle);
	glBindBuffer(GL_ARRAY_BUFFER, ld->vbo_handle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	/* glDeleteBuffers(1, &quad_vbo); */
	(void)e;
	return ;
}

static int	setup_textures_fbo(t_env e[1], t_land_tmp ld[1])
{
	glGenTextures(1, &ld->fbo_handle);
	glBindTexture(GL_TEXTURE_2D, ld->fbo_handle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, ld->grid_width
				 , ld->grid_width, 0, GL_RGBA, GL_FLOAT, NULL);
	glGenFramebuffers(1, e->land_handles + 0);
	glBindFramebuffer(GL_FRAMEBUFFER, e->land_handles[0]);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0
						 , ld->fbo_handle, 0);
	glDrawBuffers(1, (GLenum[]){GL_COLOR_ATTACHMENT0});
	glReadBuffer(GL_NONE);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return (ERROR("Framebuffer not complete!"));
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return (0);
}

int			sp_init_land(t_env *e)
{
	t_land_tmp		ld[1];

	setup_ld(ld);
	if (setup_textures_fbo(e, ld))
		return (ERROR("setup_textures_fbo(...)"));
	setup_vao(e, ld);
	generate_land(e, ld);
	/* glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT); //TODO */
	return (0);
}
