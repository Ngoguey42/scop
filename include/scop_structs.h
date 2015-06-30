/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 12:48:16 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/30 17:56:10 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_STRUCTS_H
# define SCOP_STRUCTS_H

# include "libft.h"
# include <GLFW/glfw3.h>

typedef struct				s_env
{
	t_bool					loop;
	GLFWwindow				*win;

	
	GLuint	program_shader;
	GLuint	vert_shader;
	GLuint	frag_shader;
	GLuint	vao;
	GLuint	vab;
}							t_env;

#endif
