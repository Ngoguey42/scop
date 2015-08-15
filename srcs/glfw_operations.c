/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/13 12:53:24 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/15 12:01:33 by ngoguey          ###   ########.fr       */
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
	t_env	*e;

	if (a == GLFW_PRESS)
	{
		e = sp_instance();
		sp_keystate(e, k, true);
		if (k == GLFW_KEY_TAB)
			sp_toggle_mouse_state(w, e);
		else if (k == GLFW_KEY_8)
			sp_mainitem_remapuv(e, uvwrap_oxy);
		else if (k == GLFW_KEY_9)
			sp_mainitem_remapuv(e, uvwrap_spherical);
		else if (k == GLFW_KEY_0)
			sp_mainitem_remapuv(e, uvwrap_box);
	}
	if (a == GLFW_RELEASE)
	{
		sp_keystate(sp_instance(), k, false);
		if (k == GLFW_KEY_ESCAPE || k == GLFW_KEY_Q)
			glfwSetWindowShouldClose(w, GL_TRUE);
	}
	(void)sc;
	(void)m;
	return ;
}

static void	focus_callback(GLFWwindow *w, int state)
{
	t_env	*e;

	e = sp_instance();
	e->states[sp_window_focused_state] = (state == GL_TRUE ? 1 : 0);
	(void)w;
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
	glfwSetWindowFocusCallback(e->win, &focus_callback);
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
