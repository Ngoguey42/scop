/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 11:48:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/30 18:16:17 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int						main(int ac, char *av[])
{
	t_env		e[1];

	if (sp_init_env(e))
		return (DEBUG("Scop: Could not init env"), 1);
	if (sp_init_glfw(e))
		return (DEBUG("Scop: Could not init glfw"), 1);
	if (sp_init_shaders(e))
		return (DEBUG("Scop: Could not init shaders"), 1);
	(void)ac;
	(void)av;

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	glUseProgram(e->program_shader);
	/* glGenVertexArrays(1, &vertex_array_id); */
	glGenVertexArrays(1, &e->vao);
	glBindVertexArray(e->vao);
	{
		glGenBuffers(1, &e->vab);
		glBindBuffer(GL_ARRAY_BUFFER, e->vab);
		glBufferData(GL_ARRAY_BUFFER,
					 /* npoints, */
					 /* sizeof(GLfloat) * 3 * npoints, */
					 sizeof(vertices),
					 vertices,
					 GL_STATIC_DRAW
			);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	glBindVertexArray(0);
		
	while (!glfwWindowShouldClose(e->win))
	{
		glClearColor(0.3f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		/* bind shader */
		/* hellotriangle(); */

		/* draw mesh */
		glBindVertexArray(e->vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		/* /draw mesh */
		
		
		glfwSwapBuffers(e->win);
		glfwPollEvents();
	}
	sp_clean_shaders(e);
	sp_disable_glfw(e);
	ft_leaks();
	return (0);
}
