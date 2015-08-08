/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/18 12:01:22 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/08 14:43:27 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			sp_delete_meshes(t_env *e)
{
	t_mesh			*me;
	t_mesh const	*end = ITEND_MESHES(e);

	me = e->meshes;
	while (me < end)
	{
		ftv_release(&me->vertices, NULL);
		if (me->has_indices)
			ftv_release(&me->faces, NULL);
		glDeleteBuffers(1, me->handles + 1);
		glDeleteBuffers(1, me->handles + 2);
		glDeleteVertexArrays(1, me->handles + 3);
		me++;
	}
	return ;
}

int				sp_init_meshes(t_env *e)
{
	t_mesh			*me;
	t_mesh const	*end = ITEND_MESHES(e);

	me = e->meshes;
	while (me < end)
	{
		if (op_new_mesh(e, me))
			return (1);
		me++;
	}
	return (0);
}
