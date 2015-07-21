/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 11:47:48 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 12:44:49 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int const		g_codes[] =
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
	GLFW_KEY_RIGHT
};

void		sp_keystate(t_env *e, int a, t_bool newstate)
{
	int		i;

	i = 0;
	while (i < sp_num_keys)
	{
		if (g_codes[i] == a)
		{
			e->states[i] = newstate;
			return ;
		}
		i++;
	}
	return ;
}

void		sp_toggle_mouse_state(GLFWwindow *w, t_env *e)
{
	if (glfwGetInputMode(w, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
		glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwGetCursorPos(w, e->mpos, e->mpos + 1);
	return ;
}
