/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 11:47:48 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/03 18:15:20 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "scop.h"
#define CONV(...) (t_keyevents){__VA_ARGS__}
#define NORM_AT_42_IS_WTF ke->fun

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

static t_keyevents const	g_keyevents[] =
{
	/* CONV(&sp_mainob_model_remapuv, uvwrap_oxy, GLFW_KEY_8, sp_is_held, 0), */
	/* CONV(&sp_mainob_model_remapuv, uvwrap_spherical, GLFW_KEY_9, sp_is_held, 0), */
	/* CONV(&sp_mainob_model_remapuv, uvwrap_box, GLFW_KEY_0, sp_is_held, 0), */
	CONV(&sp_kevent_toggle_mouse_state, 42, GLFW_KEY_TAB, sp_is_held, 0),
	CONV(&sp_kevent_reset_campos, 42, GLFW_KEY_R, sp_is_held, sp_control_held),
	CONV(&sp_mainob_resetpos, 42, GLFW_KEY_R, sp_is_held | sp_control_held, 0),
	CONV(&sp_kevent_mix_item, +1, GLFW_KEY_PAGE_UP, sp_is_held, 0),
	CONV(&sp_kevent_mix_item, -1, GLFW_KEY_PAGE_DOWN, sp_is_held, 0),
};

void		sp_keyevent(t_env *e, int a, t_keystate ks)
{
	t_keyevents const			*ke;
	t_keyevents const *const	end = END_ARRAY(g_keyevents);

	if (a >= GLFW_KEY_F1 && a < GLFW_KEY_F1 + sp_num_models)
		sp_mainob_changemodel(e, a - GLFW_KEY_F1);
	else
	{
		ke = g_keyevents;
		while (ke < end)
		{
			if (ke->key == a
				&& !(ks & ke->noheld) && ((ks & ke->held) == ke->held))
			{
				NORM_AT_42_IS_WTF(e, ke->dat);
				return ;
			}
			ke++;
		}
	}
	return ;
}

void		sp_keymodrelease(t_env *e, t_keystate a)
{
	int		i;

	if (a != 0)
	{
		a = ~a;
		i = 0;
		while (i < sp_num_keys)
			e->keystates[i++] &= a;
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
