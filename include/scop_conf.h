/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_conf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 10:33:54 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 12:11:57 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_CONFIG_H
# define SCOP_CONFIG_H

# include "libft.h"
# include "ftmath.h"

typedef enum				e_shader_index
{
	sp_basic_vertex,
	sp_basic_fragment,
	sp_tex_vertex,
	sp_tex_fragment,
	sp_item_vertex,
	sp_item_fragment,
	sp_num_shaders
}							t_shader_index;

typedef enum				e_program_index
{
	sp_basic_program,
	sp_tex_program,
	sp_item_program,
	sp_num_programs
}							t_program_index;

typedef enum				e_mesh_index
{
	sp_item_mesh,
	sp_num_meshes,
}							t_mesh_index;

typedef enum				e_texture_index
{
	sp_porcelain_texture,
	sp_num_textures,
	sp_no_texture
}							t_texture_index;

typedef enum				e_model_index
{
	sp_item_model,
	sp_num_models,
}							t_model_index;

/*
** TEXTURES
*/
# define RESSOURCES_PATH "res/"

/*
** CONFIG MACROES
*/
# define WIN_WIDTHI 1000
/* # define WIN_RATIOF (4.f / 4.f) */
# define WIN_RATIOF (4.f / 3.f)
/* # define WIN_RATIOF (16.f / 9.f) */
/* # define WIN_RATIOF (2.39f / 1.f) */
# define WIN_FOVF 45.f
# define WIN_NEARF 0.1f
# define WIN_FARF 100.f

# define MOUSE_SENSITIVITYF 0.005f 
# define MOVEMENT_SPEEDF 4.f

/*
** CALCULATED MACROES
*/
# define WIN_WIDTHF ((float)WIN_WIDTHI)
# define WIN_HEIGHTF (WIN_WIDTHF / WIN_RATIOF)
# define WIN_HEIGHTI ROUND_FTOI(WIN_HEIGHTF)

# define CAMERA_POSBOUNDF (M_PI / 2 * 0.98)

#endif