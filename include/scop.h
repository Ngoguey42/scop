/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 12:07:31 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/17 17:03:36 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

# include "libft.h"
# include "ft_timeval.h"

# include "ftmath.h"
# include "scop_conf.h"
# include "scop_types.h"
# include "cog_meshfill.h"
# include "fterror.h"
# include "objmodel.h"

# define sp_enomem ft_enomem	// to fix at home

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
void		sp_toggle_mouse_state(t_env *e);
void		sp_keystate(t_env *e, int a, t_keystate newstate);
void        sp_keyevent(t_env *e, int a, t_keystate keystate);
void        sp_keymodrelease(t_env *e, t_keystate keystate);
void		sp_update_states(t_env *e);
void		sp_update_movements(t_env *e, t_bool force);
void		sp_update_sun(t_env *e, t_bool force);
void		sp_updatepos_mainob(t_env *e);

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
int			sp_new_mesh(t_env const *e, t_mesh *me);
int			sp_refresh_vbo(t_env const *e, t_mesh const *me);
int			sp_fill_mesh(t_env const *e, t_mesh *me);

void		sp_calc_normals(t_env const *e, t_mesh const *me
							, t_vbo_basic *vbo);
void		sp_calc_uv(t_env const *e, t_vbo_basic *vbo, float d[2]
							, t_uvwrapping_type t);
void		sp_recenter_positions(t_vbo_basic *vbo);
void		sp_shrink_vbo(t_ftvector *const dst, t_vbo_basic const *const vbo);
int         sp_meshfillbumb_objmodel(t_env const *e, t_mesh *me
									 , t_vbo_basic *vbo
									 , char const *filename);

/*
** MAIN OB HANDLING
*/
void		sp_mainob_model_remapuv(t_env *e, t_uvwrapping_type t);
void        sp_mainob_changemodel(t_env *e, t_model_index moi);

/*
** LAND GENERATION
*/
void		sp_fill_landgrid(t_ftvector *lines);
void		sp_fill_landvertices(t_ftvector const *lines, t_vbo_basic *vbo,
	float bounds[2]);
void		sp_fill_landfaces(t_ftvector const *lines, t_ftvector *vertices);
void		sp_fill_landrgb(t_vbo_basic *vbo, float const bounds[2]);

/*
** UNIFORMS
*/
void		sp_unif_model(t_env const *e, t_ob const *ob);
void		sp_unif_model_mix(t_env const *e, t_ob const *ob);
void		sp_unif_land(t_env const *e, t_ob const *ob);
void		sp_unif_viewproj(t_env const *e, t_program const *p);
void		sp_unif_viewproj2(t_env const *e, t_program const *p);
void		sp_unif_light(t_env const *e, t_program const *p);
void		sp_unif_lightstruct(t_env const *e, t_program const *p);
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
void		sp_obupdate_mainob(t_env const *e, t_ob *ob);
void		sp_obupdate_plane(t_env const *e, t_ob *ob);
t_bool		sp_ob_getnot_hidden(t_env const *e, t_ob const *ob);
t_bool		sp_ob_get_moved(t_env const *e, t_ob const *ob);
t_ob		sp_default_ob(t_model_index moi);
#endif
