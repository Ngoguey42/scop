/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cog_meshfill1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/24 15:53:38 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/03 16:10:26 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "objmodel/objmodel.h"
#include <math.h>
#include <string.h>

/*
**  [[[cog
**  import cog
**  cog.outl("*" "/")
**  from confloader import output_meshfill
**  output_meshfill(0)
**  cog.out("/" "*")
**  ]]]
*/

int			sp_meshfill_main(t_mesh *me, t_vao_basic *vao)
{
	return (sp_meshfillbumb_objmodel(me, vao));
}

int			sp_meshfill_plane(t_mesh *me, t_vao_basic *vao)
{
	return (sp_meshfillbumb_objmodel(me, vao));
}

int			sp_meshfill_sun(t_mesh *me, t_vao_basic *vao)
{
	return (sp_meshfillbumb_objmodel(me, vao));
}

int			sp_meshfill_land(t_mesh *me, t_vao_basic *vao)
{
	t_env const		*e = sp_instance();
	int const		width = (int)pow(2.f, (LAND_NDEPTHLOOPSI + 1 - 2));

	if (ftv_reserve(&vao->vbo.vertices, width * width))
		sp_enomem();
	if (ftv_reserve(&vao->ebo.faces, width * width * 2))
		sp_enomem();
	sp_land_fill_mesh(e, vao);
	return (0);
	(void)me;
}

/*
**  [[[end]]]
*/
