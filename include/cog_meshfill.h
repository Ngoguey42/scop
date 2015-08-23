/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cog_meshfill.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 13:03:26 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/10 13:15:56 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COG_MESHFILL_H
# define COG_MESHFILL_H

/*
**  [[[cog
**  import cog
**  cog.outl("*" "/")
**  from confloader import output_meshfill_prototypes
**  output_meshfill_prototypes()
**  cog.out("/" "*")
**  ]]]
*/
int		sp_meshfill_teapot1(t_env const *e, t_mesh *me, t_vbo_basic *vbo);
int		sp_meshfill_teapot2(t_env const *e, t_mesh *me, t_vbo_basic *vbo);
int		sp_meshfill_ft(t_env const *e, t_mesh *me, t_vbo_basic *vbo);
int		sp_meshfill_csie(t_env const *e, t_mesh *me, t_vbo_basic *vbo);
int		sp_meshfill_alpha(t_env const *e, t_mesh *me, t_vbo_basic *vbo);
int		sp_meshfill_plane(t_env const *e, t_mesh *me, t_vbo_basic *vbo);
int		sp_meshfill_square(t_env const *e, t_mesh *me, t_vbo_basic *vbo);
int		sp_meshfill_land(t_env const *e, t_mesh *me, t_vbo_basic *vbo);
int		sp_meshfill_sun(t_env const *e, t_mesh *me, t_vbo_basic *vbo);
/*
**  [[[end]]]
*/

#endif
