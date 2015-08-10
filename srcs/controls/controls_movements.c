/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_movements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/30 15:25:51 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/10 14:24:04 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include "scop.h"

static void		updade_pos(t_env *e, float elms, t_bool *up)
{
	int const	mvx = e->keystates[sp_a_key] - e->keystates[sp_d_key];
	int const	mvy = e->keystates[sp_space_key] - e->keystates[sp_c_key];
	int const	mvz = e->keystates[sp_w_key] - e->keystates[sp_s_key];
	float const	nb = (float)(mvx * mvx + mvy * mvy + mvz * mvz);
	float		fact;

	if (mvx && (*up = true))
	{
		fact = elms / nb * (float)mvx;
		e->cpos.z += sin(e->cangles[0] - (M_PI / 2)) * fact;
		e->cpos.x += cos(e->cangles[0] - (M_PI / 2)) * fact;
	}
	if (mvz && (*up = true))
	{
		fact = elms / nb * (float)mvz;
		e->cpos.z += sin(e->cangles[0]) * fact;
		e->cpos.x += cos(e->cangles[0]) * fact;
	}
	if (mvy && (*up = true))
	{
		fact = elms / nb * (float)mvy;
		e->cpos.y += fact;
	}
	return ;
}

static void		update_angles_mouse(t_env *e, t_bool *up)
{
	double		mpos[2];

	*up = true;
	glfwGetCursorPos(e->win, mpos, mpos + 1);
	e->cangles[0] += (mpos[0] - e->mpos[0]) * MOUSE_SENSITIVITYF;
	e->cangles[1] -= (mpos[1] - e->mpos[1]) * MOUSE_SENSITIVITYF;
	memcpy(e->mpos, mpos, sizeof(mpos));
	return ;
}

static void		update_angles_keyboard(t_env *e, t_bool *up)
{
	int const	mvya = e->keystates[sp_right_key] - e->keystates[sp_left_key];
	int const	mvpi = e->keystates[sp_up_key] - e->keystates[sp_down_key];

	if (mvya)
	{
		*up = true;
		e->cangles[0] += 1.0 * mvya / (float)(mvpi * mvpi + 1) * e->time_el;
	}
	if (mvpi)
	{
		*up = true;
		e->cangles[1] += 1.0 * mvpi / (float)(mvya * mvya + 1) * e->time_el;
	}
	return ;
}

void			sp_update_movements(t_env *e)
{
	t_bool	update;

	update = false;
	if (glfwGetInputMode(e->win, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
		update_angles_mouse(e, &update);
	update_angles_keyboard(e, &update);
	updade_pos(e, (float)e->time_el * MOVEMENT_SPEEDF, &update);
	if (update)
	{
		if (e->cangles[1] > CAMERA_POSBOUNDF)
			e->cangles[1] = CAMERA_POSBOUNDF;
		else if (e->cangles[1] < -CAMERA_POSBOUNDF)
			e->cangles[1] = -CAMERA_POSBOUNDF;
		e->view = m4_lookat(ATOV3(e->cpos.x, e->cpos.y, e->cpos.z),
							v3_add(ATOV3(e->cpos.x, e->cpos.y, e->cpos.z),
									v3_frontnormed(e->cangles)));
		e->viewproj = m4_dotprod(&e->projection, &e->view);
	}
	return ;
}
