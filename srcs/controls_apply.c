/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 10:17:12 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/15 10:59:11 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include "scop.h"

#define OFFSET(P) (offsetof(t_env, P))
#define STATE_OFFSET(I) (OFFSET(states[I]))
#define POS_OFFSET(I) (OFFSET(pos[I]))
#define ANG_OFFSET(I) (OFFSET(cangles[I]))

#define MS MOVEMENT_SPEEDF
/*
static const t_keymap		g_keymap[] =
{
	(t_keymap){STATE_OFFSET(sp_w_key), POS_OFFSET(0), -MOVEMENT_SPEEDF},
	(t_keymap){STATE_OFFSET(sp_s_key), POS_OFFSET(0), MOVEMENT_SPEEDF},
	(t_keymap){STATE_OFFSET(sp_a_key), POS_OFFSET(2), -MOVEMENT_SPEEDF},
	(t_keymap){STATE_OFFSET(sp_d_key), POS_OFFSET(2), MOVEMENT_SPEEDF},
	(t_keymap){STATE_OFFSET(sp_space_key), POS_OFFSET(1), MOVEMENT_SPEEDF},
	(t_keymap){STATE_OFFSET(sp_c_key), POS_OFFSET(1), -MOVEMENT_SPEEDF},

	(t_keymap){STATE_OFFSET(sp_up_key), ANG_OFFSET(1), 0.5f},
	(t_keymap){STATE_OFFSET(sp_down_key), ANG_OFFSET(1), -0.5f},
	(t_keymap){STATE_OFFSET(sp_left_key), ANG_OFFSET(0), -0.5f},
	(t_keymap){STATE_OFFSET(sp_right_key), ANG_OFFSET(0), 0.5f},
};
*/
void				sp_update_states(t_env *e, double el)
{
	int const	mvz = (e->states[sp_w_key] - e->states[sp_s_key]);
	int const	mvx = (e->states[sp_a_key] - e->states[sp_d_key]);
	float		fact;
	
	double		mpos[2];
	if (glfwGetInputMode(e->win, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
	{
		glfwGetCursorPos(e->win, mpos, mpos + 1);
		qprintf("x: %f, y:%f\n", *mpos, mpos[1]);
		sp_update_angles(e, mpos[0] - e->mpos[0], mpos[1] - e->mpos[1]);
		memcpy(e->mpos, mpos, sizeof(mpos));
	}
	if (mvx)
	{
		fact = MS * el / (float)(mvz * mvz + 1) * (float)mvx;
		e->pos[2] += sin(e->cangles[0] - (M_PI / 2)) * fact;
		e->pos[0] += cos(e->cangles[0] - (M_PI / 2)) * fact;
	}
	if (mvz)
	{
		fact = MS * el / (float)(mvx * mvx + 1) * (float)mvz;
		e->pos[2] += sin(e->cangles[0]) * fact;
		e->pos[0] += cos(e->cangles[0]) * fact;
	}
	
	/* if (mvz) */
		/* e->pos[0] += MS * el / (mvx ? 2.f : 1.f); */

	return ;
}
/*
void				sp_update_states2(t_env *e, double el)
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
*/
