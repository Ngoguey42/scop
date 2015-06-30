/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 12:07:31 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/30 18:15:25 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

# include "libft.h"

# include "ftmath.h"
# include "scop_structs.h"

/*
** DEBUG
*/
# include "ft_debug.h"
# define DEBUG(ARG) qprintf("%s\n", (ARG))
# define DEBUGF(...) qprintf(__VA_ARGS__), ft_putchar_fd('\n', 2)

/*
** ERROR
*/

/*
** CONFIG MACROES
*/
#define WIN_WIDTHI 1000
#define WIN_RATIOF (4.f / 3.f)
#define SHADERS_PATH "srcs/shaders/"
#define VSHADER_PATH (SHADERS_PATH "scop.vert")
#define FSHADER_PATH (SHADERS_PATH "scop.frag")

/*
** CALCULATED MACROES
*/
#define WIN_WIDTHF ((float)WIN_WIDTHI)
#define WIN_HEIGHTF (WIN_WIDTHF / WIN_RATIOF)
#define WIN_HEIGHTI ROUND_FTOI(WIN_HEIGHTF)

/*
** PROTOTYPES
** CORE FUNCTIONS
*/
int					sp_init_env(t_env *e);
int					sp_init_glfw(t_env *e);
void				sp_disable_glfw(t_env *e);
t_env				*sp_instance(void);

/*
** SHADER FUNCTIONS
*/
int					sp_create_shader(char const *filepath, GLenum type,
									GLuint *ptr);
int					sp_init_shaders(t_env *e);
void				sp_clean_shaders(t_env *e);

/*
** ERRORS
*/
void				sp_enomem(void);

#endif
