/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_apply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 11:35:09 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/15 13:44:13 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include "scop.h"

static void		updade_pos(t_env *e, float elms)
{
	int const	mvx = e->states[sp_a_key] - e->states[sp_d_key];
	int const	mvy = e->states[sp_space_key] - e->states[sp_c_key];
	int const	mvz = e->states[sp_w_key] - e->states[sp_s_key];
	float const	nb = (float)(mvx * mvx + mvy * mvy + mvz * mvz);
	float		fact;

	if (mvx)
	{
		fact = elms / nb * (float)mvx;
		e->cpos.z += sin(e->cangles[0] - (M_PI / 2)) * fact;
		e->cpos.x += cos(e->cangles[0] - (M_PI / 2)) * fact;
	}
	if (mvz)
	{
		fact = elms / nb * (float)mvz;
		e->cpos.z += sin(e->cangles[0]) * fact;
		e->cpos.x += cos(e->cangles[0]) * fact;
	}
	if (mvy)
	{
		fact = elms / nb * (float)mvy;
		e->cpos.y += fact;
	}
	return ;
}

static void		update_angles_mouse(t_env *e)
{
	double		mpos[2];

	glfwGetCursorPos(e->win, mpos, mpos + 1);
	e->cangles[0] += (mpos[0] - e->mpos[0]) * MOUSE_SENSITIVITYF;
	e->cangles[1] -= (mpos[1] - e->mpos[1]) * MOUSE_SENSITIVITYF;
	memcpy(e->mpos, mpos, sizeof(mpos));
	return ;
}

static void		update_angles_keyboard(t_env *e, float el)
{
	int const	mvya = e->states[sp_right_key] - e->states[sp_left_key];
	int const	mvpi = e->states[sp_up_key] - e->states[sp_down_key];

	if (mvya)
		e->cangles[0] += 1.0 * mvya / (float)(mvpi * mvpi + 1) * el;
	if (mvpi)
		e->cangles[1] += 1.0 * mvpi / (float)(mvya * mvya + 1) * el;
	return ;
}

void			sp_update_states(t_env *e, double el)
{
	if (glfwGetInputMode(e->win, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
		update_angles_mouse(e);
	update_angles_keyboard(e, el);
	updade_pos(e, (float)el * MOVEMENT_SPEEDF);
	if (e->cangles[1] > CAMERA_POSBOUNDF)
		e->cangles[1] = CAMERA_POSBOUNDF;
	if (e->cangles[1] < -CAMERA_POSBOUNDF)
		e->cangles[1] = -CAMERA_POSBOUNDF;
	return ;
}
