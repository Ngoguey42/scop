/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 10:07:19 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/21 16:32:02 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_TYPES_H
# define SCOP_TYPES_H

# include "libft.h"
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include "ft_vector.h"
# include "scop_conf.h"

/*
** KEYS
*/
enum                        e_keyindex
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
	sp_num_keys
};

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
	char const					filepath[64];
	GLenum const				type;
	GLuint						handle;
}								t_shader;

/*
** PROGRAMS
** A program is tied to several <mesh>
*/
typedef struct					s_location
{
	char const					name[64];
	size_t						size;
}								t_location;

typedef struct					s_program
{
	t_shader_index const		vshader;
	t_shader_index const		fshader;
	void						(*const update_uniforms)();
	size_t const				n_locations;
	t_location const			locations[4];
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
	t_bool const				has_indices;
	int							(*const fill)();
	t_ftvector					vertices;
	t_ftvector					faces;
	// lighting datas etc...
	GLuint						handles[3];
}								t_mesh;

/*
** TEXTURE
** A texture is tied to several <model>
*/
typedef struct					s_texture
{
	char const					filepath[64];
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
}								t_model;

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
	float						values[3];
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
	t_ftvector					obs;

	t_matrix4					projection;
	double						mpos[2];
	
	float						cangles[2];
	t_vector3					cpos;	
	t_matrix4					view;	
}								t_env;

# define VSOFP(E, P)	(&(E)->shaders[(P)->vshader])
# define FSOFP(E, P)	(&(E)->shaders[(P)->fshader])

# define POFME(E, ME)	(&(E)->programs[(ME)->program])
# define VSOFME(E, ME)	VSOFP((E), POFME((E), ME))
# define FSOFME(E, ME)	FSOFP((E), POFME((E), ME))

# define TOFMO(E, MO)	(&(E)->textures[(MO)->texture])
# define MEOFMO(E, MO)	(&(E)->meshes[(MO)->mesh])
# define POFMO(E, MO)	POFME((E), MEOFMO((E), MO))
# define VSOFMO(E, MO)	VSOFME((E), MEOFMO((E), MO))
# define FSOFMO(E, MO)	FSOFME((E), MEOFMO((E), MO))

# define MOOFOB(E, OB)	(&(E)->models[(OB)->model])
# define TOFOB(E, OB)	TOFMO((E), MOOFOB((E), OB))
# define MEOFOB(E, OB)	MEOFMO((E), MOOFOB((E), OB))
# define POFOB(E, OB)	POFMO((E), MOOFOB((E), OB))
# define VSOFOB(E, OB)	VSOFMO((E), MOOFOB((E), OB))
# define FSOFOB(E, OB)	FSOFMO((E), MOOFOB((E), OB))

/*
# define VS<-P(E, P)	((E)->shaders[(P)->vshader])
# define FS<-P(E, P)	((E)->shaders[(P)->fshader])

# define P<-ME(E, ME)	((E)->programs[(ME)->program])
# define VS<-ME(E, ME)	<-P((E), P<-ME((E), ME))
# define FS<-ME(E, ME)	<-P((E), P<-ME((E), ME))

# define T<-MO(E, MO)	((E)->textures[(MO)->texture])
# define ME<-MO(E, MO)	((E)->meshes[(MO)->mesh])
# define P<-MO(E, MO)	<-ME((E), ME<-MO((E), MO))
# define VS<-MO(E, MO)	<-ME((E), ME<-MO((E), MO))
# define FS<-MO(E, MO)	<-ME((E), ME<-MO((E), MO))

# define MO<-OB(E, OB)	((E)<-models[(OB)<-model])
# define T<-OB(E, OB)	<-MO((E), MO<-OB((E), OB))
# define ME<-OB(E, OB)	<-MO((E), MO<-OB((E), OB))
# define P<-OB(E, OB)	<-MO((E), MO<-OB((E), OB))
# define VS<-OB(E, OB)	<-MO((E), MO<-OB((E), OB))
# define FS<-OB(E, OB)	<-MO((E), MO<-OB((E), OB))
*/

#endif
