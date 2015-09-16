/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 12:08:19 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/16 11:45:13 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>
#include <time.h>

#define ANNOUNCE(STR) lprintf("\033[36mInitializing %s...\033[0m", (STR))
#define INIT(MODULE) ANNOUNCE(#MODULE), (sp_init_ ## MODULE)(e)

static int		begin(t_env *e)
{
	if (INIT(env))
		return (ERROR("sp_init_env(e)"));
	if (INIT(glfw))
		return (ERROR("sp_init_glfw(e)"));
	if (INIT(shaders))
		return (ERROR("sp_init_shaders(e)"));
	if (INIT(programs))
		return (ERROR("sp_init_programs(e)"));
	if (INIT(textures))
		return (ERROR("sp_init_textures(e)"));
	if (INIT(meshes))
		return (ERROR("sp_init_meshes(e)"));
	if (INIT(obs))
		return (ERROR("sp_init_obs(e)"));
	if (INIT(sbox))
		return (ERROR("sp_init_sbox(e)"));
	if (INIT(land))
		return (ERROR("sp_init_land(e)"));
	sp_timings_init(e);
	return (0);
}



static void		loop(t_env *e)
{
	/* glPatchParameteri(GL_PATCH_VERTICES, 3); //move */

	GLuint quad_vao;
	GLuint quad_vbo;
	
	glGenVertexArrays(1, &quad_vao);
	glBindVertexArray(quad_vao);

	const GLfloat vertices[] = {
		-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f };
	glGenBuffers(1, &quad_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	/* glDeleteBuffers(1, &quad_vbo); //a faire ?! */



	
	while (!glfwWindowShouldClose(e->win))
	{
		sp_timings_handle_nofocus(e);
		sp_timings_update(e);
		sp_update_states(e);
		sp_update_obs(e);
		sp_render_sbox(e);
		sp_render_obs(e);
/*		qprintf("in(%.0f)  out(%.0f) dist(%.1f) fps(%.1f)\n"
				, e->sunskin_tessin
				, e->sunskin_tessout[0]
				, v3_dist(e->sunpos_cartesian, e->cpos)
				, e->fps
				);*/

		t_program *p = e->programs + sp_landgen_notrel_program;
		int phase_startoffset[2] = {10, 10};
		float random_seeds[2] = {ft_randf01(), ft_randf01()};

		glViewport(0, 0, WIN_WIDTHI, WIN_HEIGHTI);
		glUseProgram(p->handle);
		UNIF(p, m1i, "level_stride", 500);
		UNIF(p, m1iv, "phase_startoffset", 2, phase_startoffset);
		UNIF(p, m2fv, "random_seeds", 1, (float*)random_seeds);
		glBindVertexArray(quad_vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		
		
		glfwSwapBuffers(e->win);
		glfwPollEvents();
	}
	return ;
}

static void		end(t_env *e)
{
	/* clean sbox ?? */
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
	PRINTSIZEOF(t_env);
	PRINTSIZEOF(t_ob);
	e = malloc(sizeof(*e));
	if (e == NULL)
		return (ERROR("Env allocation failed"));
	if (begin(e))
		return (1);
	loop(e);
	end(e);
	free(e);
	/* ft_leaks(); */
	return (0);
}
