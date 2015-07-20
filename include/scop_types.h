/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 10:07:19 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 11:47:10 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_TYPES_H
# define SCOP_TYPES_H

# include "libft.h"
# include <GLFW/glfw3.h>
# include "ft_vector.h"
# include "scop_config.h"

/*
** Updating uniforms:
** 	A shader defines some updates from scop's env.
**	A model  defines some updates from scop's env + a given t_ob.
*/

/*
** SHADERS
** A shader is tied to several <program>
*/
typedef struct					s_shader
{
	char const					*filepath;
	GLenum const				type;
	void						(*const update_uniforms)();
	GLuint						handle;
}								t_shader;

/*
** PROGRAMS
** A program is tied to several <mesh>
*/
typedef struct					s_location
{
	char const * const			name;
	size_t						size;
}								t_location;

typedef struct					s_program
{
	t_shader_index const		vshader;
	t_shader_index const		fshader;
	size_t const				n_locations;
	t_location const * const	locations;	
	GLuint						handle;
}								t_program;

/*
** MESH
** A mesh is tied to several <model>
*/
typedef struct					s_mesh
{
	GLenum const				usage;
	t_program_index const		program;
	t_ftvertex					*vertices;
	t_bool						has_indices;
	t_ftvertex					*indices;
	// lighting datas etc...
	GLuint						handles[3];
}								t_mesh;

/*
** TEXTURE
** A texture is tied to several <model>
*/
typedef struct					s_texture
{
	char const * const			filepath;
	GLuint						handle;
}								t_texture;

/*
** MODEL
** A model is tied to several <ob>
*/
typedef struct					s_model
{
	t_mesh_index				mesh;
	t_texture_index				texture;
	void						(*update_uniforms)();
}

/*
** OB (object)
*/
typedef struct					s_ob
{
	t_model_index				model;
	t_vector3					position;
	t_vector3					rotation;
	t_vector3					scale;
	t_bool						modified;
	t_matrix4					mat;
}								t_ob;
	
/*
** ENV
*/
typedef struct					s_env
{
	GLFWwindow					*win;
	int							states[sp_num_keys];

	t_shader					shaders[sp_num_shaders];
	t_program					programs[sp_num_programs];
	t_mesh						meshes[sp_num_meshes];
	t_texture					textures[sp_num_textures];
	t_model						models[sp_num_models];
	t_ftvector					obs[sp_num_programs];

	t_matrix4					projection;
	t_matrix4					view;	

	double						mpos[2];
	float						cangles[2];
	t_vector3					cpos;
	/* float						pos[3]; */
}							t_env;

#endif
