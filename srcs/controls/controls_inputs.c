/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 11:47:48 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/16 12:18:32 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int const		g_keystates[] =
{
	GLFW_KEY_W,
	GLFW_KEY_S,
	GLFW_KEY_A,
	GLFW_KEY_D,
	GLFW_KEY_SPACE,
	GLFW_KEY_C,
	GLFW_KEY_UP,
	GLFW_KEY_DOWN,
	GLFW_KEY_LEFT,
	GLFW_KEY_RIGHT,
	GLFW_KEY_T,
	GLFW_KEY_G,
	GLFW_KEY_F,
	GLFW_KEY_H,
	GLFW_KEY_R,
	GLFW_KEY_Y,
};

typedef struct s_keyevents{void (*fun)(); int dat; int key;} t_keyevents;

static t_keyevents const	g_keyevents[] =
{
	(t_keyevents){&sp_mainob_model_remapuv, uvwrap_oxy, GLFW_KEY_8},
	(t_keyevents){&sp_mainob_model_remapuv, uvwrap_spherical, GLFW_KEY_9},
	(t_keyevents){&sp_mainob_model_remapuv, uvwrap_box, GLFW_KEY_0},
	(t_keyevents){&sp_toggle_mouse_state, 42, GLFW_KEY_TAB},
};

void		sp_keyevent(t_env *e, int a)
{
	t_ui		i;

	i = 0;
	while (i < SIZE_ARRAY(g_keyevents))
	{
		if (g_keyevents[i].key == a)
		{
			g_keyevents[i].fun(e, g_keyevents[i].dat);
			return ;
		}
		i++;
	}
	return ;
}

void		sp_keystate(t_env *e, int a, t_bool newstate)
{
	int		i;

	i = 0;
	while (i < sp_num_keys)
	{
		if (g_keystates[i] == a)
		{
			e->keystates[i] = newstate;
			return ;
		}
		i++;
	}
	return ;
}

void		sp_toggle_mouse_state(t_env *e)
{
	GLFWwindow	*w;

	w = e->win;
	if (glfwGetInputMode(w, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
		glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwGetCursorPos(w, e->mpos, e->mpos + 1);
	return ;
}
