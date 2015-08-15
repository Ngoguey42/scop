/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_refresh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/15 10:49:57 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/15 12:00:22 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int				sp_refresh_vbo(t_env const *e, t_mesh const *me)
{
	glBindVertexArray(me->handles[0]);
	glBindBuffer(GL_ARRAY_BUFFER, me->handles[1]);
	glBufferSubData(GL_ARRAY_BUFFER, 0
					, me->vertices.size * me->vertices.chunk_size,
					me->vertices.data);
	glBindVertexArray(0);
	(void)e;
	return (0);
}
