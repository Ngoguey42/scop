/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_cogconf_meshfill.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/08 12:43:22 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/08 12:44:24 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_COGCONF_MESHFILL_H
# define SCOP_COGCONF_MESHFILL_H

/*
**  [[[cog
**  import cog
**  cog.outl("*" "/")
**  from scop_confloader import output_meshfill_prototypes
**  output_meshfill_prototypes()
**  cog.out("/" "*")
**  ]]]
*/
int							sp_meshfill_plane(t_env const *e, t_mesh *me, t_vbo_basic *vbo);
int							sp_meshfill_land(t_env const *e, t_mesh *me, t_vbo_basic *vbo);
int							sp_meshfill_ptn(t_env const *e, t_mesh *me, t_vbo_basic *vbo);
int							sp_meshfill_sun(t_env const *e, t_mesh *me, t_vbo_basic *vbo);
/*
**  [[[end]]]
*/

#endif
