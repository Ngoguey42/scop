/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 15:57:45 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 16:18:06 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "objmodel.h"

int				sp_meshfill_item(t_env const *e, t_mesh *me)
{
	// t_objmodel	m[1];

	// op_init_instance(m, "res/teapot2.obj");
	// if (op_parse_obj(m))
		// return (ERROR("op_parse_obj(m)"), 1);
	// op_swap_vectors(m, &me->vertices, &me->faces);
	(void)e;
	(void)me;
	return (0);
}

int				sp_meshfill_square(t_env const *e, t_mesh *me)
{
	(void)e;
	(void)me;
	return (0);
}
