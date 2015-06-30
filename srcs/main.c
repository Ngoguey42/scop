/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 11:48:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/30 16:05:33 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void					hellotriangle(void)
{
	/* GLfloat vertices[] = { */
	/* 	-0.5f, -0.5f, 0.0f, */
	/* 	0.5f, -0.5f, 0.0f, */
	/* 	0.0f,  0.5f, 0.0f */
	/* };   */
	/* GLuint VBO; */
	/* glGenBuffers(1, &VBO); */
	
	/* glBindBuffer(GL_ARRAY_BUFFER, VBO); */
	/* glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); */

	
	
	
	return ;
}

#include <fcntl.h>
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
	while (e->loop && !glfwWindowShouldClose(e->win))
	{
		glClearColor(0.3f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		
		hellotriangle();

		
		
		glfwSwapBuffers(e->win);
		glfwPollEvents();
	}
	sp_disable_glfw(e);
	return (0);
}
