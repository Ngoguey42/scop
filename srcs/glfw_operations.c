/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/13 12:53:24 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/17 16:03:45 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#define SHHELD(V) ((V) & GLFW_MOD_SHIFT ? sp_shift_held : 0)
#define COHELD(V) ((V) & GLFW_MOD_CONTROL ? sp_control_held : 0)
#define ALHELD(V) ((V) & GLFW_MOD_ALT ? sp_alt_held : 0)
#define SUHELD(V) ((V) & GLFW_MOD_SUPER ? sp_super_held : 0)
#define MODCONV(V) (SHHELD((V)) | COHELD((V)) | ALHELD((V)) | SUHELD((V)))

#define ISSHKEY(V) ((V) == GLFW_KEY_LEFT_SHIFT || (V) == GLFW_KEY_RIGHT_SHIFT)
#define ISCOKEY(V) ((V) == GLFW_KEY_LEFT_CONTROL||(V) == GLFW_KEY_RIGHT_CONTROL)
#define ISALKEY(V) ((V) == GLFW_KEY_LEFT_ALT || (V) == GLFW_KEY_RIGHT_ALT)
#define ISSUKEY(V) ((V) == GLFW_KEY_LEFT_SUPER || (V) == GLFW_KEY_RIGHT_SUPER)
#define SHKEY(V) (ISSHKEY((V)) ? sp_shift_held : 0)
#define COKEY(V) (ISCOKEY((V)) ? sp_control_held : 0)
#define ALKEY(V) (ISALKEY((V)) ? sp_alt_held : 0)
#define SUKEY(V) (ISSUKEY((V)) ? sp_super_held : 0)
#define MODPRESSCONV(K) (SHKEY(K) | COKEY(K) | ALKEY(K) | SUKEY(K))

static void	error_callback(int error, const char *description)
{
	qprintf("GLFW ERROR(%d): \"\033[35m%s\033[0m\"\n", error, description);
	(void)error;
	(void)description;
}

static void	key_callback(GLFWwindow *w, int k, int sc, int a, int m)
{
	t_env		*e;
	t_keystate	state;

	if (a == GLFW_PRESS)
	{
		e = sp_instance();
		state = MODCONV(m) | sp_is_held;
		sp_keystate(e, k, state);
		sp_keyevent(e, k, state);
	}
	else if (a == GLFW_RELEASE)
	{
		e = sp_instance();
		sp_keystate(e, k, sp_not_held);
		sp_keymodrelease(e, MODPRESSCONV(k));
		if (k == GLFW_KEY_ESCAPE || k == GLFW_KEY_Q)
			glfwSetWindowShouldClose(w, GL_TRUE);
	}
	(void)sc;
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
