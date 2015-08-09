/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 12:07:31 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/09 14:16:50 by ngoguey          ###   ########.fr       */
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
# include "scop_cogconf_meshfill.h"
# include "fterror.h"
# include "objmodel.h"

/*
** DEBUG
*/
# include "ft_debug.h"
# define DEBUG(ARG) qprintf("%s\n", (ARG))
# define DEBUGF(...) qprintf(__VA_ARGS__), ft_putchar_fd('\n', 2)

/*
** PROTOTYPES
*/
/*
** CONTROLS
*/
void		sp_toggle_mouse_state(GLFWwindow *w, t_env *e);
void		sp_keystate(t_env *e, int a, t_bool newstate);
void		sp_update_states(t_env *e);
void		sp_update_movements(t_env *e);
void		sp_update_sun(t_env *e, t_bool force);

/*
** ENV
*/
void		sp_clean_env(t_env *e);
int			sp_init_env(t_env *e);
t_env		*sp_instance(void);

int			sp_loadconf_vshaders(t_env *e);
int			sp_loadconf_fshaders(t_env *e);
int			sp_loadconf_gshaders(t_env *e);
int			sp_loadconf_programs(t_env *e);
int			sp_loadconf_textures(t_env *e);
int			sp_loadconf_meshes(t_env *e);
int			sp_loadconf_models(t_env *e);

/*
** GLFW
*/
void		sp_disable_glfw(t_env *e);
int			sp_init_glfw(t_env *e);

/*
** SHADERS
*/
void		sp_delete_shaders(t_env *e);
int			sp_init_shaders(t_env *e);

/*
** PROGRAMS
*/
void		sp_delete_programs(t_env *e);
int			sp_init_programs(t_env *e);

/*
** TEXTURES
*/
int			sp_init_textures(t_env *e);
void		sp_delete_textures(t_env *e);
int			parse_tga(char const *filepath, t_ftvector *v, t_ui dim[2]);
/*
** MESHES
*/
int			sp_init_meshes(t_env *e);

void		sp_delete_meshes(t_env *e);
int			op_new_mesh(t_env const *e, t_mesh *me);
int			sp_fill_mesh(t_env const *e, t_mesh *me);

void		sp_inject_normals(t_ftvector *vertices, t_ftvector const *faces);
void		sp_inject_uv_plan_oxy(t_ftvector *v, t_texture const *t,
									float scale, size_t padfloats);

/*
** LAND GENERATION
*/
void		sp_fill_landgrid(t_ftvector *lines);
void		sp_fill_landvertices(t_ftvector const *lines, t_ftvector *faces,
	float bounds[2]);
void		sp_fill_landfaces(t_ftvector const *lines, t_ftvector *vertices);
void		sp_fill_landrgb(t_ftvector *vertices, float const bounds[2]);

/*
** UNIFORMS
*/
void		sp_unif_model(t_env const *e, t_ob const *ob);
void		sp_unif_land(t_env const *e, t_ob const *ob);
void		sp_unif_viewproj(t_env const *e, t_program const *p);
void		sp_unif_viewproj2(t_env const *e, t_program const *p);
void		sp_unif_light(t_env const *e, t_program const *p);
void		sp_unif_suncolor(t_env const *e, t_program const *p);

/*
** OBS (OBJECTS)
*/
int			sp_init_obs(t_env *e);
void		sp_delete_obs(t_env *e);
void		sp_update_obs(t_env *e);
void		sp_render_obs(t_env const *e);
int			sp_fill_obs(t_env *e);
void		sp_obupdate_sun(t_env const *e, t_ob *ob);
t_bool		sp_ob_getnot_hidden(t_env const *e, t_ob const *ob);
t_bool		sp_ob_get_moved(t_env const *e, t_ob const *ob);

#endif
