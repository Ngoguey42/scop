/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 10:07:19 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/09 08:45:06 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_TYPES_H
# define SCOP_TYPES_H

# include "libft.h"
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include "ft_vector.h"
# include "ft_list.h"
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
	sp_t_key,
	sp_g_key,
	sp_f_key,
	sp_h_key,
	sp_r_key,
	sp_y_key,
	sp_num_keys
};

enum                        e_stateindex
{
	sp_window_focused_state,
	sp_num_states
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
typedef struct					s_location
{
	char const					name[64];
	size_t						size;
}								t_location;

typedef struct					s_vshader
{
	char const					filepath[64];
	void						(*const unif_update)();
	size_t const				n_locations;
	t_location const			locations[4];
	GLuint						handle;
}								t_vshader;
typedef struct					s_fshader
{
	char const					filepath[64];
	void						(*const unif_update)();
	GLuint						handle;
}								t_fshader;
typedef struct					s_gshader
{
	char const					filepath[64];
	void						(*const unif_update)();
	GLuint						handle;
}								t_gshader;

/*
** PROGRAMS
** A program is tied to several <mesh>
*/
typedef struct					s_program
{
	t_vshader_index const		vshader;
	t_fshader_index const		fshader;
	t_gshader_index const		gshader;
	GLuint						handle;
}								t_program;

/*
** MESH
** A mesh is tied to several <model>
** Pos.x, Pos.y, Pos.z[, Co.r, Co.g, Co.b][, Tex.u, , Tex.v][, No.x, No.y, No.z]
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
	t_ui						dim[2];
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
	t_ftlist_node				list;
	t_bool						hidden:1;
	t_bool						moved:1;
	t_bool						delete:1;
	t_model_index				model:5;
	t_vector3					position;
	t_vector3					rotation;
	t_vector3					scale;
	t_matrix4					mat;
	void						(*update)();
	float						valf[1];
	int							vali[1];
}								t_ob;

/*
** ENV
*/
typedef struct					s_env
{
	GLFWwindow					*win;

	t_vshader					vshaders[sp_num_vshaders];
	t_fshader					fshaders[sp_num_fshaders];
	t_gshader					gshaders[sp_num_gshaders];
	t_program					programs[sp_num_programs];
	t_mesh						meshes[sp_num_meshes];
	t_texture					textures[sp_num_textures];
	t_model						models[sp_num_models];
	/* t_ftvector					obs[sp_num_programs]; */
	t_ftlist					obs[sp_num_programs];

	int							keystates[sp_num_keys];
	int							states[sp_num_states];
	double						mpos[2];

	float						cangles[2];
	t_vector3					cpos;
	t_matrix4					view;

	t_matrix4					projection;
	t_matrix4					viewproj;

	t_vector3					sunpos_spherical;
	t_vector3					sunpos_cartesian;
	t_vector3					suncolor;
	
	double						time_start;
	double						time_cur;
	double						time_el;
}								t_env;

# define ITEND_VSHADERS(E)	((E)->vshaders + sp_num_vshaders)
# define ITEND_FSHADERS(E)	((E)->fshaders + sp_num_fshaders)
# define ITEND_GSHADERS(E)	((E)->gshaders + sp_num_gshaders)
# define ITEND_PROGRAMS(E)	((E)->programs + sp_num_programs)
# define ITEND_MESHES(E)	((E)->meshes + sp_num_meshes)
# define ITEND_TEXTURES(E)	((E)->textures + sp_num_textures)
# define ITEND_MODELS(E)	((E)->models + sp_num_models)
# define ITEND_OBS(E)		((E)->obs + sp_num_programs)

# define VSOFP(E, P)		(&(E)->vshaders[(P)->vshader])
# define FSOFP(E, P)		(&(E)->fshaders[(P)->fshader])
# define GSOFP(E, P)		(&(E)->gshaders[(P)->gshader])

# define POFME(E, ME)		(&(E)->programs[(ME)->program])
# define VSOFME(E, ME)		VSOFP((E), POFME((E), ME))
# define FSOFME(E, ME)		FSOFP((E), POFME((E), ME))
# define GSOFME(E, ME)		GSOFP((E), POFME((E), ME))

# define TOFMO(E, MO)		(&(E)->textures[(MO)->texture])
# define MEOFMO(E, MO)		(&(E)->meshes[(MO)->mesh])
# define POFMO(E, MO)		POFME((E), MEOFMO((E), MO))
# define VSOFMO(E, MO)		VSOFME((E), MEOFMO((E), MO))
# define FSOFMO(E, MO)		FSOFME((E), MEOFMO((E), MO))
# define GSOFMO(E, MO)		GSOFME((E), MEOFMO((E), MO))

# define MOOFOB(E, OB)		(&(E)->models[(OB)->model])
# define TOFOB(E, OB)		TOFMO((E), MOOFOB((E), OB))
# define MEOFOB(E, OB)		MEOFMO((E), MOOFOB((E), OB))
# define POFOB(E, OB)		POFMO((E), MOOFOB((E), OB))
# define VSOFOB(E, OB)		VSOFMO((E), MOOFOB((E), OB))
# define FSOFOB(E, OB)		FSOFMO((E), MOOFOB((E), OB))
# define GSOFOB(E, OB)		GSOFMO((E), MOOFOB((E), OB))

#endif
