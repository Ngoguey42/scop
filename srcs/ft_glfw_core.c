/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glfw_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 13:18:23 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/30 17:26:17 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void error_callback(int error, const char* description)
{
	qprintf("GLFW ERROR(%d): \"\033[35m%s\033[0m\"\n", error, description);
	(void)error;
	(void)description;
}

static void key_callback(GLFWwindow* window, int key, int a, int action, int b)
{
	t_env		*e;

	e = sp_instance();
	if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)
		glfwSetWindowShouldClose(window, GL_TRUE);
	(void)action;
	(void)e;
	(void)a;
	(void)b;
}

#include <fcntl.h>
#include <stdlib.h>

int			sp_init_glfw(t_env *e)
{
	glfwSetErrorCallback(error_callback);
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	e->win = glfwCreateWindow(WIN_WIDTHI, WIN_HEIGHTI, "Scop", NULL, NULL);
	if (!e->win)
		return (glfwTerminate(), DEBUG("Could not create window"), 1);
	glfwSetKeyCallback(e->win, key_callback);
	glfwMakeContextCurrent(e->win);
	glViewport(0, 0, WIN_WIDTHI, WIN_HEIGHTI);
	return (0);
}

void		sp_disable_glfw(t_env *e)
{
	glfwDestroyWindow(e->win);
	glfwTerminate();
	return ;
}