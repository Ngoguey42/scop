/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 12:07:31 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/17 14:27:49 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

# include "libft.h"

# include "ftmath.h"
# include "config.h"
# include "scop_structs.h"

/*
** DEBUG
*/
# include "ft_debug.h"
# define DEBUG(ARG) qprintf("%s\n", (ARG))
# define DEBUGF(...) qprintf(__VA_ARGS__), ft_putchar_fd('\n', 2)

/*
** OBJMODEL
*/
int			sp_init_objmodels(t_env *e);
void		sp_clean_objmodels(void *modelptr);
void		sp_register_objmodel(t_env *e, char const *filepath);
int			op_parse_obj(t_objmodel *m);


/*
** PROTOTYPES
** CORE FUNCTIONS
*/
int			sp_init_env(t_env *e);
void		sp_clean_env(t_env *e);
t_env		*sp_instance(void);

int			sp_init_glfw(t_env *e);
void		sp_disable_glfw(t_env *e);
int     sp_load_texture(char const *filepath, GLuint *desc);
int         parse_tga(char const *filepath, t_ftvector *v, int dim[2]);

/*
** CONTROLS
*/
void		sp_keystate(t_env *e, int a, t_bool newstate);
void		sp_update_states(t_env *e, double el);
void		sp_toggle_mouse_state(GLFWwindow *w, t_env *e);

/*
** SHADER FUNCTIONS
*/
#define PROG0 (e->programs[0])
#define PROG1 (e->programs[1])

int			sp_init_shaders(t_env *e);
void		sp_delete_shaders(t_env *e);

int			sp_init_programs(t_env *e);
void		sp_delete_programs(t_env *e);

void        item_unif_projection(t_env const *e, GLuint loc);
void        item_unif_view(t_env const *e, GLuint loc);
void        item_unif_model(t_env const *e, GLuint loc);

void        item_tex_projection(t_env const *e, GLuint loc);
void        item_tex_view(t_env const *e, GLuint loc);
void        item_tex_model(t_env const *e, GLuint loc);

void            sp_update_uniforms(t_env const *e, int prid, GLuint prog);

/*
** ERRORS
*/
void				sp_enomem(void);
# define PERR_H qprintf("Error l%d: ", __LINE__)
# define PERRNO_ENDL qprintf(", (%s)\n", strerror(errno))

# define ERRORF(...) PERR_H, qprintf(__VA_ARGS__), ft_putchar_fd('\n', 2)
# define ERROR(ARG) ERRORF("%s", (ARG))

# define ERRORNOF(...) PERR_H, qprintf(__VA_ARGS__), PERRNO_ENDL
# define ERRORNO(ARG) ERRORNOF("%s", (ARG))

#endif
