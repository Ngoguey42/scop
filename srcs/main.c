/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 11:48:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/18 14:47:44 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <math.h>
#include <stdlib.h>

int						main(int ac, char *av[])
{
	t_env		e[1];
	double		last_time;
	double		cur_time;
	double		el_time;
	
	if (sp_init_env(e))
		return (ERROR("sp_init_env()"), 1);
	if (sp_init_glfw(e))
		return (ERROR("sp_init_glfw()"), 1);
	if (sp_init_shaders(e))
		return (ERROR("sp_init_shaders()"), 1);
	if (sp_init_programs(e))
		return (ERROR("sp_init_programs()"), 1);
	/* sp_register_objmodel(e, OBJ_PATH "42.obj"); */
	/* sp_register_objmodel(e, OBJ_PATH "teapot.obj"); */
	sp_register_objmodel(e, OBJ_PATH "teapot2.obj");
	if (sp_init_objmodels(e))
		return (ERROR("sp_init_objmodels()"), 1);
	sp_wrap_texture_planxy(e->models.data, 1.f, 442.f / 405.f);
	
	T;
	(void)ac;
	(void)av;
	if (sp_load_texture(PORCELAIN_PATH, &e->tex))
		return (T, 1);	
	sp_create_drawables(e);
	
	last_time = glfwGetTime();
	e->itempos = ATOV3(0.f, 6.f, 0.f);
	while (!glfwWindowShouldClose(e->win))
	{
		/* env update */
		cur_time = glfwGetTime();
		el_time = cur_time - last_time;
		sp_update_states(e, el_time);
		e->view = m4_lookat(
			ATOV3(e->cpos.x, e->cpos.y, e->cpos.z),
			v3_add(ATOV3(e->cpos.x, e->cpos.y, e->cpos.z),
				   v3_frontnormed(e->cangles))
			);

		/* opengl buffers cleaning */
		glClearColor(0.3f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sp_render_drawables(e);
		
		/* image validation */
		glfwSwapBuffers(e->win);
		glfwPollEvents();
		last_time = cur_time;
	}
	sp_delete_programs(e);
	sp_delete_shaders(e);
	sp_disable_glfw(e);
	sp_clean_env(e);
	/* ft_leaks(); */
	return (0);
}
