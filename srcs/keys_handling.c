/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/13 11:49:04 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/13 12:53:00 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#define OFFSET(P) (offsetof(struct s_env, P))
#define STATE_OFFSET(I) (OFFSET(states) + sizeof(int) * (I))
#define POS_OFFSET(I) (OFFSET(pos) + sizeof(float) * (I))

static const t_keymap		g_keymap[] =
{
	(t_keymap){STATE_OFFSET(sp_w_key), POS_OFFSET(0), -1.},
	(t_keymap){STATE_OFFSET(sp_s_key), POS_OFFSET(0), 1.},
	(t_keymap){STATE_OFFSET(sp_a_key), POS_OFFSET(2), -1.},
	(t_keymap){STATE_OFFSET(sp_d_key), POS_OFFSET(2), 1.},
	(t_keymap){STATE_OFFSET(sp_space_key), POS_OFFSET(1), 1.},
	(t_keymap){STATE_OFFSET(sp_c_key), POS_OFFSET(1), -1.},
};

static void			swap_state(t_env *e, int a, t_bool newstate)
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
	return ;
}

void				sp_keydown(t_env *e, GLFWwindow *w, int a, int m)
{
	swap_state(e, a, true);
	(void)e;
	(void)w;
	(void)a;
	(void)m;
	return ;
}

void				sp_keyup(t_env *e, GLFWwindow *w, int a, int m)
{
	if (a == GLFW_KEY_ESCAPE || a == GLFW_KEY_Q)
		glfwSetWindowShouldClose(w, GL_TRUE);
	swap_state(e, a, false);
	(void)e;
	(void)w;
	(void)a;
	(void)m;
	return ;
}

void				sp_update_states(t_env *e, double el)
{
	size_t		i;

	i = 0;
	while (i < sp_num_keys)
	{
		if (*(t_bool*)((void*)e + g_keymap[i].state))
			*(float*)((void*)e + g_keymap[i].dst) += g_keymap[i].delta * el;
		i++;
	}
	return ;
}
