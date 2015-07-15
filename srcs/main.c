/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 11:48:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/15 13:30:04 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <math.h>
#include <stdlib.h>

#define NUMINDICES ((t_objmodel*)e->models.data)->faces.size * 3

void					build_mesh(t_env *e)
{
	t_objmodel	*m = e->models.data;
	GLfloat		*vertices = m->vertices.data;
	GLuint		*indices = m->faces.data;
	
	glGenVertexArrays(1, &e->vao);	// array object
	glGenBuffers(1, &e->vab); // vab = vbo array buffer / buffer object
	glGenBuffers(1, &e->ebo); //
	
	
	glBindVertexArray(e->vao);
	{		
		glBindBuffer(GL_ARRAY_BUFFER, e->vab);
		glBufferData(GL_ARRAY_BUFFER,
					 sizeof(float) * 3 * m->vertices.size,
					 vertices,
					 GL_STATIC_DRAW
			);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					 sizeof(unsigned int) * 3 * m->faces.size,
					 indices,
					 GL_STATIC_DRAW
			);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
							  (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}
	glBindVertexArray(0);
	
	return ;
}

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
	T;
	/* exit(0); */
	(void)ac;
	(void)av;

	
	build_mesh(e);

	

	last_time = glfwGetTime();
	while (!glfwWindowShouldClose(e->win))
	{
		cur_time = glfwGetTime();
		el_time = cur_time - last_time;
		sp_update_states(e, el_time);
		glClearColor(0.3f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(PROG0);
		/* update lookat */
		e->view = m4_lookat(
			(t_vector3){e->pos[0], e->pos[1], e->pos[2]},
			v3_add((t_vector3){e->pos[0], e->pos[1], e->pos[2]},
				   v3_frontnormed(e->cangles))
			);
		/* update uniforms */
		sp_update_uniforms(e, 0, PROG0);
		/* draw mesh */
		glBindVertexArray(e->vao);
		glDrawElements(GL_TRIANGLES, NUMINDICES, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		/* /draw mesh */
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
