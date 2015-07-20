/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 12:07:31 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 13:42:34 by ngoguey          ###   ########.fr       */
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
** PROTOTYPES
** CORE FUNCTIONS
*/


/*
** CONTROLS
*/
void        sp_toggle_mouse_state(GLFWwindow *w, t_env *e);
void        sp_keystate(t_env *e, int a, t_bool newstate);
void            sp_update_states(t_env *e, double el);

/*
** ENV
*/
int             sp_init_env(t_env *e);
t_env           *sp_instance(void);
void            sp_clean_env(t_env *e);

int             sp_loadconf_shaders(t_env *e);
int             sp_loadconf_programs(t_env *e);

/*
** GLFW
*/
int         sp_init_glfw(t_env *e);
void        sp_disable_glfw(t_env *e);

/*
** SHADERS
*/
void            sp_delete_shaders(t_env *e);
int             sp_init_shaders(t_env *e);

/*
** 
*/

/*
** 
*/

/*
** 
*/




#endif
