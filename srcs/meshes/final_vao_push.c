/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_vao_push.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 15:34:57 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/03 15:38:03 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	push_buffers(t_mesh *me, t_ftvector const vbo_final[1]
						 , t_ftvector const ebo_final[1])
{
	if (!me->buff_generated)
		glGenBuffers(1, me->handles + 1);
	glBindBuffer(GL_ARRAY_BUFFER, me->handles[1]);
	glBufferData(GL_ARRAY_BUFFER, vbo_final->size * vbo_final->chunk_size
				 , vbo_final->data, me->usage);
	if (!me->buff_generated)
		glGenBuffers(1, me->handles + 2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, me->handles[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ebo_final->size * ebo_final->chunk_size
				 , ebo_final->data, me->usage);
}

void		sp_push_vao(t_mesh *me, t_vshader const *vs
						, t_ftvector const vbo_final[1]
						, t_ftvector const ebo_final[1])
{
	if (!me->buff_generated)
		glGenVertexArrays(1, me->handles + 0);
	glBindVertexArray(me->handles[0]);
	push_buffers(me, vbo_final, ebo_final);
	push_attributes(vs);
	glBindVertexArray(0);
	return ;
}
