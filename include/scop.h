/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 12:07:31 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/30 13:12:50 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <GLFW/glfw3.h>

# include "libft.h"

# include "ftmath.h"
# include "scop_structs.h"

/*
** DEBUG
*/
# include "ft_debug.h"
# define DEBUG(ARG) lprintf("%s", (ARG))
# define DEBUGF(...) lprintf(__VA_ARGS__)

/*
** CONFIG MACROES
*/
#define WIN_WIDTHI 1000
#define WIN_RATIOF (4.f / 3.f)

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


#endif
