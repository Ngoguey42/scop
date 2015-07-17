/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 12:48:16 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/17 14:11:04 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_STRUCTS_H
# define SCOP_STRUCTS_H

# include "libft.h"
# include <GLFW/glfw3.h>
# include "ft_vector.h"


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
typedef struct				s_program_uniform
{
	char					*name;
	void					(*fun)();
}							t_program_uniform;

typedef struct				s_program_metadata
{
	GLuint					vertex_shaderid;
	GLuint					fragment_shaderid;
	int						num_locations;
	char					*locations[16];
	int						num_uniforms;
	t_program_uniform		uniforms[16];
}							t_program_metadata;

/*
** OBJ 
*/
typedef struct				s_objmodel
{
	char					*filepath;
	t_ftvector				vertices;
	t_ftvector				faces;
	char					*mtllib;
	char					*name;
	char					*usemtl;
	t_bool					smooth;
}							t_objmodel;

/*
** KEYS
*/
enum						e_keyindex
{
	sp_w_key,
	sp_s_key,
	sp_a_key,
	sp_d_key,
	sp_space_key,
	sp_c_key,
	sp_up_key,
	sp_down_key,
	sp_left_key,
	sp_right_key,
	/* sp__key, */
	sp_num_keys
};

/*
** ENV
*/
typedef struct				s_env
{
	GLFWwindow				*win;

	GLuint					shaders[sc_num_shaders];
	GLuint					programs[sc_num_programs];
	t_ftvector				models;
	int						states[sp_num_keys];
	t_matrix4				projection;
	t_matrix4				view;
	t_vector3				itempos;

	GLuint					tex;
	
	GLuint					vao;
	GLuint					vab;
	GLuint					ebo;

	double					mpos[2];
	float					cangles[2];
	t_vector3				cpos;
	/* float					pos[3]; */
}							t_env;

#endif
