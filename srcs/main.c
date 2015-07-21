/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 12:08:19 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/21 14:25:38 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>
#include <time.h>

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
    if (sp_init_meshes(e))
		return (ERROR("sp_init_meshes(e)"), 1);
    if (sp_init_textures(e))
		return (ERROR("sp_init_textures(e)"), 1);
	return (0);
}

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
		glClearColor(0.3f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sp_render_obs(e, el_time);
		glfwSwapBuffers(e->win);
		glfwPollEvents();
		last_time = cur_time;
	}
	return ;
}

static void		end(t_env *e)
{
	/* clean everything */
	(void)e;
	return ;
}

int				main(void)
{
	t_env					*e;

	srand(time(NULL));
	qprintf("sizeof(t_env) = %u\n", sizeof(*e));
	e = malloc(sizeof(*e));
	if (e == NULL)
		return (1);
	if (begin(e))
		return (1);
	loop(e);
	end(e);
	free(e);
	/* ft_leaks(); */
	return (0);
}
