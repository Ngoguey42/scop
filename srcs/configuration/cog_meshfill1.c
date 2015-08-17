/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_fill1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/08 12:49:25 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/12 14:58:17 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "objmodel.h"
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

int			sp_meshfill_teapot1(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	return (sp_meshfillbumb_objmodel(e, me, vbo, "res/teapot.obj"));
}

int			sp_meshfill_teapot2(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	return (sp_meshfillbumb_objmodel(e, me, vbo, "res/teapot2.obj"));
}

int			sp_meshfill_ft(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	return (sp_meshfillbumb_objmodel(e, me, vbo, "res/42.obj"));
}

int			sp_meshfill_csie(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	return (sp_meshfillbumb_objmodel(e, me, vbo, "res/new_csie_b1.obj"));
}

int			sp_meshfill_ptn(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	return (sp_meshfillbumb_objmodel(e, me, vbo, "res/alfa147.obj"));
}

/*
**  [[[end]]]
*/
