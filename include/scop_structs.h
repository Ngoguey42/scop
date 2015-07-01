/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 12:48:16 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/01 13:13:25 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_STRUCTS_H
# define SCOP_STRUCTS_H

# include "libft.h"
# include <GLFW/glfw3.h>


/*
** SHADERS
*/
typedef struct				s_shader_metadata
{
	char					*filepath;
	GLenum					type;
}							t_shader_metadata;

/*
** PROGRAMS
*/
typedef struct				s_program_metadata
{
	GLuint					vertex_shaderid;
	GLuint					fragment_shaderid;
	int						num_attrib_locations;
	char					*attrib_locations[64];
}							t_program_metadata;

/*
** ENV
*/
typedef struct				s_env
{
	t_bool					loop;
	GLFWwindow				*win;

	GLuint					shaders[sc_num_shaders];
	GLuint					programs[sc_num_programs];
	GLuint					vao;
	GLuint					vab;
}							t_env;

#endif