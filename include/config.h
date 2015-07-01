/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/01 12:09:19 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/01 13:13:32 by ngoguey          ###   ########.fr       */
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
	sc_num_shaders
}							t_shader_index;

# define SHADERS_PATH "srcs/shaders/"
# define SHDATT1 {SHADERS_PATH "scop.vert", GL_VERTEX_SHADER},
# define SHDATT2 {SHADERS_PATH "scop.frag", GL_FRAGMENT_SHADER},
# define SHADERS_ATTRIBUTES_LIST SHDATT1 SHDATT2

/*
** PROGRAMS ATTRIBUTES
*/
typedef enum				s_program_index
{
	sc_basic_program,
	sc_num_programs
}							t_program_index;

# define PROGATT1 {sc_basic_vertex, sc_basic_fragment, 1, {"position"}},
# define PROGRAMS_ATTRIBUTES_LIST PROGATT1

/*
** CONFIG MACROES
*/
# define WIN_WIDTHI 1000
# define WIN_RATIOF (4.f / 3.f)

/*
** CALCULATED MACROES
*/
# define WIN_WIDTHF ((float)WIN_WIDTHI)
# define WIN_HEIGHTF (WIN_WIDTHF / WIN_RATIOF)
# define WIN_HEIGHTI ROUND_FTOI(WIN_HEIGHTF)

#endif
