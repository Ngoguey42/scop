/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 11:48:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/18 15:46:24 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <math.h>
#include <stdlib.h>

static int		begin(t_env *e)
{
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
	if (sp_load_texture(PORCELAIN_PATH, &e->tex))
		return (T, 1);
	sp_create_drawables(e);
	e->itempos = ATOV3(0.f, 6.f, 0.f);
	return (0);
}

#define NARG_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,N,...) N
#define NARG(...) NARG_(__VA_ARGS__,11,10,9,8,7,6,5,4,3,2,1)

static void		loop(t_env *e)
{
	double		cur_time;
	double		el_time;
	double		last_time;

	last_time = glfwGetTime();
	while (!glfwWindowShouldClose(e->win))
	{
		cur_time = glfwGetTime();
		el_time = cur_time - last_time;
		sp_update_states(e, el_time);
		e->view = m4_lookat(ATOV3(e->cpos.x, e->cpos.y, e->cpos.z),
							v3_add(ATOV3(e->cpos.x, e->cpos.y, e->cpos.z),
							v3_frontnormed(e->cangles)));
		glClearColor(0.3f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sp_render_drawables(e);
		glfwSwapBuffers(e->win);
		glfwPollEvents();
		last_time = cur_time;
	}
	return ;
}

static void		end(t_env *e)
{
	sp_delete_programs(e);
	sp_delete_shaders(e);
	sp_disable_glfw(e);
	sp_clean_env(e);
	return ;
}

int				main(int ac, char *av[])
{
	t_env		e[1];

	(void)ac;
	(void)av;
	if (begin(e))
		return (1);
	loop(e);
	end(e);
	/* ft_leaks(); */
	return (0);
}
