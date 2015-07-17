/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 11:48:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/17 15:06:29 by ngoguey          ###   ########.fr       */
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

void	build_triangle_mesh(GLuint tri[3])
{
	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	
	glGenVertexArrays(1, tri);	// array object
	glGenBuffers(1, tri + 1); // vab = vbo array buffer / buffer object
	glGenBuffers(1, tri + 2);
	
	glBindVertexArray(*tri);
	{		
		glBindBuffer(GL_ARRAY_BUFFER, tri[1]);
		glBufferData(GL_ARRAY_BUFFER,
					 sizeof(vertices),
					 vertices,
					 GL_STATIC_DRAW
			);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri[2]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					 sizeof(indices),
					 indices,
					 GL_STATIC_DRAW
			);


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
							  (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
							  (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
							  (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		
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


	if (sp_load_texture(WALL_PATH, &e->tex))
		return (T, 1);
	qprintf("gl descriptor: %u\n", e->tex);
	
	GLuint	tri[3];

	
	build_triangle_mesh(tri);
	
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

		/* program operations */
		glUseProgram(PROG0);
		glBindVertexArray(e->vao);
		sp_update_uniforms(e, 0, PROG0);
		glDrawElements(GL_TRIANGLES, NUMINDICES, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);



		
		glUseProgram(PROG1);		
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, e->tex);
		
		glUniform1i(glGetUniformLocation(PROG1, "ourTexture"), 0);
		
		glBindVertexArray(tri[0]);
		sp_update_uniforms(e, 1, PROG1);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);  
		
		
		
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
