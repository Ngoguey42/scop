/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_conf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 10:33:54 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/30 10:40:47 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_CONFIG_H
# define SCOP_CONFIG_H

# include "libft.h"
# include "ftmath.h"

# define SHD_PATH(FILENAME) ("srcs/shaders/" FILENAME)

/*
** RESSOURCES
*/
# define RESSOURCES_PATH "res/"
# define TEXTURE_PATH(FILENAME) (RESSOURCES_PATH FILENAME)

/*
** CONFIG MACROES
*/
# define WIN_WIDTHI 1600
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
# define MOVEMENT_SPEEDF 40.f

/*
** CALCULATED MACROES
*/
# define WIN_WIDTHF ((float)WIN_WIDTHI)
# define WIN_HEIGHTF (WIN_WIDTHF / WIN_RATIOF)
# define WIN_HEIGHTI ROUND_FTOI(WIN_HEIGHTF)

# define CAMERA_POSBOUNDF (M_PI / 2 * 0.98)

# define LAND_SIDEHALFF (LAND_SIDEF / 2.f)


typedef enum				e_vshader_index
{
	sp_po_to_co_vshader,
	sp_pocote_to_couv_vshader,
	sp_pote_to_couv_vshader,
	sp_poco_to_co_vshader,
	sp_poteno_to_uv_vshader,
	sp_pocono_to_co_vshader,
	sp_num_vshaders
}							t_vshader_index;

typedef enum				e_fshader_index
{
	sp_co_identity_fshader,
	sp_uv_identity_fshader,
	sp_couv_blend_fshader,
	sp_couv_uv_fshader,
	sp_uvno_uvli_fshader,
	sp_cono_coli_fshader,
	sp_couvno_blendli_fshader,
	sp_num_fshaders,
}							t_fshader_index;

typedef enum				e_gshader_index
{
	sp_test_gshader,
	sp_num_gshaders,
	sp_no_gshader
}							t_gshader_index;

typedef enum				e_program_index
{
	sp_p_program,
	sp_pct_program,
	sp_pt_program,
	sp_land_program,
	sp_ptn_program,
	sp_pcn_program,
	sp_num_programs
}							t_program_index;

typedef enum				e_mesh_index
{
	sp_plane_mesh,
	sp_square_mesh,
	sp_land_mesh,
	sp_ptn_mesh,
	sp_num_meshes,
}							t_mesh_index;

typedef enum				e_texture_index
{
	sp_porcelain_texture,
	sp_wall_texture,
	sp_metal_texture,
	sp_num_textures,
	sp_no_texture
}							t_texture_index;

typedef enum				e_model_index
{
	sp_plane_model,
	sp_square_model,
	sp_land_model,
	sp_ptn_model,
	sp_num_models,
}							t_model_index;

#endif
