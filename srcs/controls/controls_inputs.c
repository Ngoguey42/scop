/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 11:47:48 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/16 18:10:37 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "scop.h"
#define CONV(...) (t_keyevents){__VA_ARGS__}

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
	GLFW_KEY_SEMICOLON,
	GLFW_KEY_P,
	GLFW_KEY_L,
	GLFW_KEY_APOSTROPHE,
	GLFW_KEY_EQUAL,
	GLFW_KEY_MINUS,
};

static void	toggle_mouse_state(t_env *e)
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

static void	reset_campos(t_env *e)
{
	e->cpos = DEFAULT_CPOS_V3;
	memcpy(&e->cangles, DEFAULT_CANGLES, sizeof(DEFAULT_CANGLES));
	sp_update_movements(e, true);
	return ;
}

static void	reset_mainobpos(t_env *e)
{
	t_ob		*ob;

	ob = e->mainob;
	ob->position = D_MAINOBPOS_V3;
	ob->rotation = D_MAINOBANGLES_V3;
	ob->moved = true;
	return ;
}

static t_keyevents const	g_keyevents[] =
{
	CONV(&sp_mainob_model_remapuv, uvwrap_oxy, GLFW_KEY_8, sp_is_held, 0),
	CONV(&sp_mainob_model_remapuv, uvwrap_spherical, GLFW_KEY_9, sp_is_held, 0),
	CONV(&sp_mainob_model_remapuv, uvwrap_box, GLFW_KEY_0, sp_is_held, 0),
	CONV(&toggle_mouse_state, 42, GLFW_KEY_TAB, sp_is_held, 0),
	CONV(&reset_campos, 42, GLFW_KEY_R, sp_is_held, sp_control_held),
	CONV(&reset_mainobpos, 42, GLFW_KEY_R, sp_is_held | sp_control_held, 0),
};

void		sp_keyevent(t_env *e, int a, t_keystate ks)
{
	t_keyevents const			*ke;
	t_keyevents const *const	end = END_ARRAY(g_keyevents);

	if (a >= GLFW_KEY_1 && a < GLFW_KEY_1 + sp_num_models)
		sp_mainob_changemodel(e, a - GLFW_KEY_1);
	else
	{
		ke = g_keyevents;
		while (ke < end)
		{
			if (ke->key == a
				&& !(ks & ke->noheld) && ((ks & ke->held) == ke->held))
			{
				ke->fun(e, ke->dat);
				return ;
			}
			ke++;
		}
	}
	return ;
}

void		sp_keystate(t_env *e, int a, t_keystate newstate)
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
