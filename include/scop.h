/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 12:07:31 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 12:15:33 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

# include "libft.h"

# include "ftmath.h"
# include "scop_conf.h"
# include "scop_types.h"
# include "fterror.h"

/*
** DEBUG
*/
# include "ft_debug.h"
# define DEBUG(ARG) qprintf("%s\n", (ARG))
# define DEBUGF(...) qprintf(__VA_ARGS__), ft_putchar_fd('\n', 2)

/*
** OBJMODEL
*/


/*
** PROTOTYPES
** CORE FUNCTIONS
*/
/*
** CONTROLS
*/
/*
** SHADER FUNCTIONS
*/

#endif
