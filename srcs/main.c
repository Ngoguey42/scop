/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 11:48:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/01 15:09:01 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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

	glUseProgram(PROG0);
	GLuint transformLoc = glGetUniformLocation(PROG0, "transform");
	/* GLfloat mat[] = { */
	/* 	0.5f, 0.0f, 0.0f, 0.0f, */
	/* 	0.0f, 1.0f, 0.0f, 0.0f, */
	/* 	0.0f, 0.0f, 1.0f, 0.0f, */
	/* 	0.0f, 0.0f, 0.0f, 1.0f		 */
	/* }; */
	t_matrix4		mat;
	/* mat = m4_scale_uniform(0.5f); */
	/* mat = m4_scaleref_uniform(&mat, 1.g5f); */
	/* mat = m4_translate_uniform(0.f); */
	mat = m4_translate_nonuniform((float [3]){-0.25f, 0.0f, 0.0f});
	/* mat = m4_translate_nonuniform((float [3]){0.0f, 0.0f, 0.9f}); */
	m4_print(mat);
	/* mat = m4_translate_nonuniform((float [3]){0.5f, 0.f, 0.f}); */
	glUniformMatrix4fv(transformLoc, 1, GL_TRUE, (float*)&mat);
	/* glUniformMatrix4fv(transformLoc, 1, GL_FALSE, (float*)&mat); */
	
	
	build_mesh(e);
	
	while (!glfwWindowShouldClose(e->win))
	{
		glClearColor(0.3f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		
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
