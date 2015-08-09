/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_cogconf_enums.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/08 12:37:33 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/08 12:38:04 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_COGCONF_ENUMS_H
# define SCOP_COGCONF_ENUMS_H

/*
**  [[[cog
**  import cog
**  cog.outl("*" "/")
**  from scop_confloader import output_enums
**  output_enums()
**  cog.out("/" "*")
**  ]]]
*/
typedef enum				e_vshader_index
{
	sp_po_to_co_vshader,
	sp_pocote_to_couv_vshader,
	sp_pote_to_couv_vshader,
	sp_poco_to_co_vshader,
	sp_poteno_to_uv_vshader,
	sp_pocono_to_co_vshader,
	sp_po_to_noop_vshader,
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
	sp_co_sun_fshader,
	sp_num_fshaders
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
	sp_sun_program,
	sp_num_programs
}							t_program_index;

typedef enum				e_texture_index
{
	sp_porcelain_texture,
	sp_wall_texture,
	sp_metal_texture,
	sp_num_textures,
	sp_no_texture
}							t_texture_index;

typedef enum				e_mesh_index
{
	sp_plane_mesh,
	sp_num_meshes
}							t_mesh_index;

typedef enum				e_model_index
{
	sp_plane_model,
	sp_num_models
}							t_model_index;

/*
**  [[[end]]]
*/

#endif
