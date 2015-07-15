/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/13 11:49:04 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/15 10:46:11 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include "scop.h"

void			sp_update_angles(t_env *e, float offx, float offy)
{
	// X changes the yaw		LEFTRIGHT	0
	// Y changes the pitch		UPDOWN		1
	e->cangles[0] += offx * MOUSE_SENSITIVITYF; //yaw
	e->cangles[1] -= offy * MOUSE_SENSITIVITYF; //pitch
	if (e->cangles[1] > CAMERA_POSBOUNDF)
		e->cangles[1] = CAMERA_POSBOUNDF;
	if (e->cangles[1] < -CAMERA_POSBOUNDF)
		e->cangles[1] = -CAMERA_POSBOUNDF;
	return ;
}

void			sp_keystate(t_env *e, int a, t_bool newstate)
{
	if (a == GLFW_KEY_A)
		e->states[sp_a_key] = newstate;
	else if (a == GLFW_KEY_D)
		e->states[sp_d_key] = newstate;
	else if (a == GLFW_KEY_W)
		e->states[sp_w_key] = newstate;
	else if (a == GLFW_KEY_S)
		e->states[sp_s_key] = newstate;
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
