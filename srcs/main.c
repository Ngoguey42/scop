/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 12:08:19 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/28 18:55:30 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static int		begin(t_env *e)
{
	if (sp_init_env(e))
		return (ERROR("sp_init_env(e)"), 1);
	if (sp_init_glfw(e))
		return (ERROR("sp_init_glfw(e)"), 1);
	if (sp_init_shaders(e))
		return (ERROR("sp_init_shaders(e)"), 1);
	if (sp_init_programs(e))
		return (ERROR("sp_init_programs(e)"), 1);
	if (sp_init_textures(e))
		return (ERROR("sp_init_textures(e)"), 1);
	if (sp_init_meshes(e))
		return (ERROR("sp_init_meshes(e)"), 1);
	if (sp_init_obs(e))
		return (ERROR("sp_init_obs(e)"), 1);
	return (0);
}

static void		loop(t_env *e)
{
	double		last_time;
	double		sleep_time;

	e->time_start = glfwGetTime();
	e->time_cur = e->time_start;
	last_time = e->time_start;
	while (!glfwWindowShouldClose(e->win))
	{
		e->time_cur = glfwGetTime();
		e->time_el = e->time_cur - last_time;
		sp_update_states(e);
		glClearColor(155. / 256., 216. / 256., 220. / 256., 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sp_render_obs(e);
		glfwSwapBuffers(e->win);
		glfwPollEvents();
		if (e->States[sp_window_focused_state] == 0
			&& (sleep_time = 0.5 - (glfwGetTime() - e->time_cur)) < 0.5)
			usleep(sleep_time * 1000000.);
		last_time = e->time_cur;
	}
	return ;
}

static void		end(t_env *e)
{
	sp_delete_obs(e);
	sp_delete_textures(e);
	sp_delete_meshes(e);
	sp_delete_programs(e);
	sp_delete_shaders(e);
	sp_disable_glfw(e);
	sp_clean_env(e);
	return ;
}

int				main(void)
{
	t_env					*e;

	srand(time(NULL));
	qprintf("sizeof(t_env) = %uBytes\n", sizeof(*e));
	e = malloc(sizeof(*e));
	if (e == NULL)
		return (ERROR("Env allocation failed"), 1);
	if (begin(e))
		return (1);
	loop(e);
	end(e);
	free(e);
	/* ft_leaks(); */
	return (0);
}
