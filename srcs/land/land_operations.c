/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   land_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/16 08:05:58 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/17 17:07:56 by ngoguey          ###   ########.fr       */
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

static void	generate_land(t_env e[1], t_land_tmp ld[1])
{
	t_program const		*p;
	int					stride;
	float				land_range;
	int					depth_loop;

	glBindFramebuffer(GL_FRAMEBUFFER, *ld->fbo_handle);
	glViewport(0, 0, ld->grid_width, ld->grid_width);
	glBindVertexArray(*ld->vao_handle);

	p = e->programs + sp_landgen_notrel_program;
	glUseProgram(p->handle);
	UNIF(p, m1i, "level_stride", ld->grid_width / 2);
	UNIF(p, m1iv, "phase_startoffset", 2, (int[]){0, 0});
	UNIF(p, m2fv, "random_seeds", 1, (float[]){ft_randf01(), ft_randf01()});
	UNIF(p, m1f, "land_average_y", LAND_YF);
	UNIF(p, m1f, "land_range_y", LAND_RANGEF);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glFlush();//flush!!
	
	stride = ld->grid_width;
	land_range = LAND_RANGEF;
	depth_loop = 0;
	while (++depth_loop <= LAND_NDEPTHLOOPSI)
	{
		land_range *= 0.55f;
		stride /= 2;
		qprintf("stride %d  range %.2f\n", stride, land_range);
		p = e->programs + sp_landgen_diag_program;
		glUseProgram(p->handle);
		UNIF(p, m1i, "level_stride", stride);
		UNIF(p, m1iv, "phase_startoffset", 2, (int[]){stride / 2, stride / 2});
		UNIF(p, m2fv, "random_seeds", 1, (float[]){ft_randf01(), ft_randf01()});
		UNIF(p, m1f, "land_average_y", LAND_YF);
		UNIF(p, m1f, "land_range_y", land_range);
		UNIF(p, m1i, "tex", 0);
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, *ld->ytex_handle);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glFlush();//flush!!
		p = e->programs + sp_landgen_horiz_program;
		glUseProgram(p->handle);
		UNIF(p, m1i, "level_stride", stride);
		UNIF(p, m2fv, "random_seeds", 1, (float[]){ft_randf01(), ft_randf01()});
		UNIF(p, m1f, "land_average_y", LAND_YF);
		UNIF(p, m1f, "land_range_y", land_range);
		UNIF(p, m1i, "tex", 0);
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, *ld->ytex_handle);
		UNIF(p, m1iv, "phase_startoffset", 2, (int[]){stride / 2, 0});
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		UNIF(p, m1iv, "phase_startoffset", 2, (int[]){0, stride / 2});
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glFlush();//flush!!
	}
	
	glBindVertexArray(0);
	glUseProgram(0);
	return ;
}

static void	setup_vao(t_env e[1], t_land_tmp ld[1])
{
	GLfloat const	 vertices[] = {
	-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f};

	glGenVertexArrays(1, ld->vao_handle);
	glBindVertexArray(*ld->vao_handle);
	glGenBuffers(1, ld->vbo_handle);
	glBindBuffer(GL_ARRAY_BUFFER, *ld->vbo_handle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	/* glDeleteBuffers(1, &quad_vbo); */
	(void)e;
	return ;
}

static int	setup_textures_fbo(t_land_tmp ld[1])
{
	glGenTextures(1, ld->ytex_handle);
	glBindTexture(GL_TEXTURE_2D, *ld->ytex_handle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0
				 , GL_R32F
				 , ld->grid_width , ld->grid_width, 0
				 , GL_RED
				 , GL_FLOAT
				 , NULL);
	glGenFramebuffers(1, ld->fbo_handle);
	glBindFramebuffer(GL_FRAMEBUFFER, *ld->fbo_handle);
	glFramebufferTexture(GL_FRAMEBUFFER
						 , GL_COLOR_ATTACHMENT0
						 , *ld->ytex_handle, 0);
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
	if (setup_textures_fbo(ld))
		return (ERROR("setup_textures_fbo(...)"));
	setup_vao(e, ld);
	generate_land(e, ld);
	e->land_tex1 = (t_texture){NULL, GL_TEXTURE_2D
			   , {ld->grid_width, ld->grid_width}, *ld->ytex_handle};
	/* e->land_handles[1] = ld->; */
	/* glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT); //TODO */
	return (0);
}
