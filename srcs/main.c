/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 11:48:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/30 12:57:02 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <GLFW/glfw3.h>

# include "scop.h"

static void error_callback(int error, const char* description)
{
	(void)error;
	(void)description;
}

static void key_callback(GLFWwindow* window, int key, int a, int action, int b)
{
	(void)window;
	(void)key;
	(void)action;
	(void)a;
	(void)b;
}

int						main(int ac, char *av[])
{
	t_env		e[1];

	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		return (1);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 8);
	(void)glfwCreateWindow(WIN_WIDTHI, WIN_HEIGHTI, "Scop", NULL, NULL);
	(void)ac;
	(void)av;
	while (e->loop);
	
	return (0);
}
