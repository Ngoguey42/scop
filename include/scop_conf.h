/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_conf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 10:33:54 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/23 13:04:21 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_CONFIG_H
# define SCOP_CONFIG_H

# include "libft.h"
# include "ftmath.h"

# define SHADER_PATH(FILENAME) ("srcs/shaders/" FILENAME)

/*
** RESSOURCES
*/
# define RESSOURCES_PATH "res/"
# define TEXTURE_PATH(FILENAME) (RESSOURCES_PATH FILENAME)

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
# define WIN_FARF 200.f

# define LAND_SIDEF 100.f
# define LAND_RANGEF 28.f
# define LAND_COLORRAND 0.05f
# define POINTS_DEPTHI 9
# define LAND_YF -15.f

# define MOUSE_SENSITIVITYF 0.005f
# define MOVEMENT_SPEEDF 4.f

/*
** CALCULATED MACROES
*/
# define WIN_WIDTHF ((float)WIN_WIDTHI)
# define WIN_HEIGHTF (WIN_WIDTHF / WIN_RATIOF)
# define WIN_HEIGHTI ROUND_FTOI(WIN_HEIGHTF)

# define CAMERA_POSBOUNDF (M_PI / 2 * 0.98)

# define LAND_SIDEHALFF (LAND_SIDEF / 2.f)


typedef enum				e_shader_index
{
	sp_basic_vertex,
	sp_basic_fragment,
	sp_tex_vertex,
	sp_tex_fragment,
	sp_item_vertex,
	sp_item_fragment,
	sp_land_vertex,
	sp_land_fragment,
	sp_ptn_vertex,
	sp_ptn_fragment,
	sp_num_shaders
}							t_shader_index;

typedef enum				e_program_index
{
	sp_basic_program,
	sp_tex_program,
	sp_item_program,
	sp_land_program,
	sp_ptn_program,
	sp_num_programs
}							t_program_index;

typedef enum				e_mesh_index
{
	sp_item_mesh,
	sp_square_mesh,
	sp_land_mesh,
	sp_item2_mesh,
	sp_num_meshes,
}							t_mesh_index;

typedef enum				e_texture_index
{
	sp_porcelain_texture,
	sp_wall_texture,
	sp_num_textures,
	sp_no_texture
}							t_texture_index;

typedef enum				e_model_index
{
	sp_item_model,
	sp_square_model,
	sp_land_model,
	sp_item2_model,
	sp_num_models,
}							t_model_index;

#endif
