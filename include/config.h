/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/01 12:09:19 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/18 14:46:19 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "libft.h"

/*
** SHADERS ATTRIBUTES
*/
typedef enum				s_shader_index
{
	sc_basic_vertex,
	sc_basic_fragment,
	sc_tex_vertex,
	sc_tex_fragment,
	sc_item_vertex,
	sc_item_fragment,
	sc_num_shaders
}							t_shader_index;

# define SHADERS_PATH "srcs/shaders/"
# define SHDATT1 {SHADERS_PATH "scop.vert", GL_VERTEX_SHADER},
# define SHDATT2 {SHADERS_PATH "scop.frag", GL_FRAGMENT_SHADER},
# define SHDATT3 {SHADERS_PATH "tex.vert", GL_VERTEX_SHADER},
# define SHDATT4 {SHADERS_PATH "tex.frag", GL_FRAGMENT_SHADER},
# define SHDATT5 {SHADERS_PATH "item.vert", GL_VERTEX_SHADER},
# define SHDATT6 {SHADERS_PATH "item.frag", GL_FRAGMENT_SHADER},
# define SHADERS_ATTRIBUTES_LIST SHDATT1 SHDATT2 SHDATT3 SHDATT4 SHDATT5 SHDATT6

/*
** PROGRAMS ATTRIBUTES
*/
typedef enum				s_program_index
{
	sc_basic_program,
	sc_tex_program,
	sc_item_program,
	sc_num_programs
}							t_program_index;

# define LOCS1 {"position", "color"}
# define UNIF1A {"model", &item_unif_model}
# define UNIF1B {"view", &item_unif_view}
# define UNIF1C {"projection", &item_unif_projection}
# define UNIF1 {UNIF1A, UNIF1B, UNIF1C}
# define PROGATT1 {sc_basic_vertex, sc_basic_fragment, 2, LOCS1, 3, UNIF1},

# define LOCS2 {"position", "color", "texCoord"}
# define UNIF2A {"model", &tex_unif_model}
# define UNIF2B {"view", &tex_unif_view}
# define UNIF2C {"projection", &tex_unif_projection}
# define UNIF2D {"ourTexture", &tex_unif_texture}
# define UNIF2 {UNIF2A, UNIF2B, UNIF2C, UNIF2D}
# define PROGATT2 {sc_tex_vertex, sc_tex_fragment, 3, LOCS2, 4, UNIF2},

/* # define LOCS3 {"position"} */
# define LOCS3 {"position", "texCoord"}
# define UNIF3A {"model", &item_unif_model}
# define UNIF3B {"view", &item_unif_view}
# define UNIF3C {"projection", &item_unif_projection}
# define UNIF3D {"ourTexture", &item_unif_texture}
# define UNIF3 {UNIF3A, UNIF3B, UNIF3C, UNIF3D}
# define PROGATT3 {sc_item_vertex, sc_item_fragment, 2, LOCS3, 4, UNIF3},

# define PROGRAMS_ATTRIBUTES_LIST PROGATT1 PROGATT2 PROGATT3

/*
** OBJ
*/
# define OBJ_PATH "res/"

/*
** TEXTURES
*/
# define OBJ_PATH "res/"
# define WALL_PATH (OBJ_PATH "Wall.tga")
# define PORCELAIN_PATH (OBJ_PATH "Porcelain.tga")

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
# define CAMERA_POSBOUNDF (M_PI / 2 * 0.98)
# define MOVEMENT_SPEEDF 4.f

/*
** CALCULATED MACROES
*/
# define WIN_WIDTHF ((float)WIN_WIDTHI)
# define WIN_HEIGHTF (WIN_WIDTHF / WIN_RATIOF)
# define WIN_HEIGHTI ROUND_FTOI(WIN_HEIGHTF)

#endif
