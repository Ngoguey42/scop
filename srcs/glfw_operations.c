/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/13 12:53:24 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/13 12:54:18 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	error_callback(int error, const char *description)
{
	qprintf("GLFW ERROR(%d): \"\033[35m%s\033[0m\"\n", error, description);
	(void)error;
	(void)description;
}

static void	key_callback(GLFWwindow *w, int k, int sc, int a, int m)
{
	if (a == GLFW_PRESS)
		sp_keydown(sp_instance(), w, k, m);
	if (a == GLFW_RELEASE)
		sp_keyup(sp_instance(), w, k, m);
	(void)sc;
	return ;
}

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
	glEnable(GL_DEPTH_TEST);
	return (0);
}

void		sp_disable_glfw(t_env *e)
{
	glfwDestroyWindow(e->win);
	glfwTerminate();
	return ;
}
