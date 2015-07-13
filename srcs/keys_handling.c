/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/13 11:49:04 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/13 16:16:18 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include "scop.h"

#define OFFSET(P) (offsetof(struct s_env, P))
#define STATE_OFFSET(I) (OFFSET(states) + sizeof(int) * (I))
#define POS_OFFSET(I) (OFFSET(pos) + sizeof(float) * (I))
#define ANG_OFFSET(I) (OFFSET(cangles) + sizeof(float) * (I))

static const t_keymap		g_keymap[] =
{
	(t_keymap){STATE_OFFSET(sp_w_key), POS_OFFSET(0), -1.},
	(t_keymap){STATE_OFFSET(sp_s_key), POS_OFFSET(0), 1.},
	(t_keymap){STATE_OFFSET(sp_a_key), POS_OFFSET(2), -1.},
	(t_keymap){STATE_OFFSET(sp_d_key), POS_OFFSET(2), 1.},
	(t_keymap){STATE_OFFSET(sp_space_key), POS_OFFSET(1), 1.},
	(t_keymap){STATE_OFFSET(sp_c_key), POS_OFFSET(1), -1.},

	(t_keymap){STATE_OFFSET(sp_up_key), ANG_OFFSET(1), 0.5f},
	(t_keymap){STATE_OFFSET(sp_down_key), ANG_OFFSET(1), -0.5f},
	(t_keymap){STATE_OFFSET(sp_left_key), ANG_OFFSET(0), -0.5f},
	(t_keymap){STATE_OFFSET(sp_right_key), ANG_OFFSET(0), 0.5f},
};

void			sp_update_angles(t_env *e, float offx, float offy)
{
	// X changes the yaw		LEFTRIGHT	0
	// Y changes the pitch		UPDOWN		1
	e->cangles[0] += offx * MOUSE_SENSITIVITY; //yaw
	e->cangles[1] -= offy * MOUSE_SENSITIVITY; //pitch
	if (e->cangles[1] > CAMERA_POSBOUND)
		e->cangles[1] = CAMERA_POSBOUND;
	if (e->cangles[1] < -CAMERA_POSBOUND)
		e->cangles[1] = -CAMERA_POSBOUND;
	return ;
}

void			sp_keystate(t_env *e, int a, t_bool newstate)
{
	if (a == GLFW_KEY_A)
		e->states[sp_w_key] = newstate;
	else if (a == GLFW_KEY_D)
		e->states[sp_s_key] = newstate;
	else if (a == GLFW_KEY_W)
		e->states[sp_a_key] = newstate;
	else if (a == GLFW_KEY_S)
		e->states[sp_d_key] = newstate;
	else if (a == GLFW_KEY_SPACE)
		e->states[sp_space_key] = newstate;
	else if (a == GLFW_KEY_C)
		e->states[sp_c_key] = newstate;
	else if (a == GLFW_KEY_UP)
		e->states[sp_up_key] = newstate;
	else if (a == GLFW_KEY_DOWN)
		e->states[sp_down_key] = newstate;
	else if (a == GLFW_KEY_LEFT)
		e->states[sp_left_key] = newstate;
	else if (a == GLFW_KEY_RIGHT)
		e->states[sp_right_key] = newstate;
	return ;
}

void				sp_update_states(t_env *e, double el)
{
	size_t		i;
	double		mpos[2];

	i = 0;
	while (i < sp_num_keys)
	{
		if (*(t_bool*)((void*)e + g_keymap[i].state))
			*(float*)((void*)e + g_keymap[i].dst) += g_keymap[i].delta * el;
		i++;
	}
	sp_update_angles(e, 0.f, 0.f);
	if (glfwGetInputMode(e->win, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
	{
		glfwGetCursorPos(e->win, mpos, mpos + 1);
		qprintf("x: %f, y:%f\n", *mpos, mpos[1]);
		sp_update_angles(e, mpos[0] - e->mpos[0], mpos[1] - e->mpos[1]);
		memcpy(e->mpos, mpos, sizeof(mpos));
	}
	return ;
}
