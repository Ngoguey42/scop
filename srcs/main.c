/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 11:48:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/01 17:59:42 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <math.h>
/* #include <glm/glm.hpp> */

void					build_mesh(t_env *e)
{
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	glGenVertexArrays(1, &e->vao);
	glBindVertexArray(e->vao);
	{
		glGenBuffers(1, &e->vab);
		glBindBuffer(GL_ARRAY_BUFFER, e->vab);
		glBufferData(GL_ARRAY_BUFFER,
					 sizeof(vertices),
					 vertices,
					 GL_STATIC_DRAW
			);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	glBindVertexArray(0);
	return ;
}


int						main(int ac, char *av[])
{
	t_env		e[1];

	if (sp_init_env(e))
		return (DEBUG("Scop: sp_init_env failed..."), 1);
	if (sp_init_glfw(e))
		return (DEBUG("Scop: sp_init_glfw failed..."), 1);
	if (sp_init_shaders(e))
		return (DEBUG("Scop: sp_init_shaders failed..."), 1);
	if (sp_init_programs(e))
		return (DEBUG("Scop: sp_init_programs failed..."), 1);
	(void)ac;
	(void)av;


	
	build_mesh(e);
	
	while (!glfwWindowShouldClose(e->win))
	{
		glClearColor(0.3f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(PROG0);
	
		t_matrix4		mat = m4_scale_uniform(1.f);
		mat = m4_translateref_nonuniform(&mat, (float [3]){-0.55f, 0.0f, 0.0f});
		
		mat = m4_rotationref_axis(&mat, x_axis, 1.2 * (GLfloat)glfwGetTime());
		/* mat = m4_rotationref_axis(&mat, y_axis, 1.4 * (GLfloat)glfwGetTime()); */
		/* mat = m4_rotationref_axis(&mat, z_axis, 1.6 * (GLfloat)glfwGetTime()); */
	
		mat = m4_scaleref_uniform(&mat, 0.25f);
		
		GLuint transformLoc = glGetUniformLocation(PROG0, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_TRUE, (float*)&mat);
	

		/* draw mesh */
		glBindVertexArray(e->vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		/* /draw mesh */
		
		glfwSwapBuffers(e->win);
		glfwPollEvents();
	}
	sp_delete_programs(e);
	sp_delete_shaders(e);
	sp_disable_glfw(e);
	/* ft_leaks(); */
	return (0);
}
