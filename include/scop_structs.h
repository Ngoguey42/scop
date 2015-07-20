/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 12:48:16 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 11:19:58 by ngoguey          ###   ########.fr       */
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
	char					*filepath;			//ok
	GLenum					type;				//ok
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
	GLuint					vertex_shaderid;	//ok
	GLuint					fragment_shaderid;	//ok
	int						num_locations;		//ok
	char					*locations[16];		//ok
	int						num_uniforms;		//ok
	t_program_uniform		uniforms[16];		//ok
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
** MESH
*/
typedef struct				s_meshattribs
{
	GLuint					size;				//ok to program
	GLuint const			*data;				//ok to program
	t_bool					has_indices;		//ok to mesh
}							t_meshattribs;
typedef struct				s_mesh
{
	GLuint					desc[3];			//ok
	GLuint					n_floats;			//ok
	GLfloat const			*floats;			//ok
	GLuint					n_indices;			//ok
	GLuint const			*indices;			//ok
}							t_mesh;

/*
** DRAWABLES
*/
typedef struct				s_drawable
{
	t_program_index			prog;				// ok to mesh
	size_t					n_textures;			// ok to model
	GLuint					*textures;			// ok to model
	t_mesh					mesh;				// ok to model
}							t_drawable;


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

	t_ftvector				drawables;
	
	GLuint					tex;
	

	double					mpos[2];
	float					cangles[2];
	t_vector3				cpos;
	/* float					pos[3]; */
}							t_env;

#endif
