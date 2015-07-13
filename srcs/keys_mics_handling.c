/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_mics_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/13 13:26:14 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/13 13:39:07 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		sp_toggle_mouse_state(GLFWwindow *w, t_env *e)
{
	if (glfwGetInputMode(w, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
		glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwGetCursorPos(w, e->mpos, e->mpos + 1);
	return ;
}
