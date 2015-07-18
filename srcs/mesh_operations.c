/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/18 12:01:22 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/18 13:21:16 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int		gen_buffer(GLuint *desc, GLenum trg, GLvoid *data, GLuint size)
{
	glGenBuffers(1, desc);
	glBindBuffer(trg, *desc);
	glBufferData(trg, size, data, GL_STATIC_DRAW);
	return (0);
}

static int		gen_attribs(t_meshattribs att)
{
	size_t	i;
	GLuint	v_size;
	GLvoid	*delta;

	i = 0;
	v_size = 0;
	while (i < att.size)
		v_size += att.data[i++];
	v_size *= sizeof(GLfloat);
	i = 0;
	delta = NULL;
	qprintf("v_size %d\n", v_size);
	while (i < att.size)
	{
		glVertexAttribPointer(i, att.data[i],
							  GL_FLOAT, GL_FALSE, v_size, delta);
		glEnableVertexAttribArray(i);		
		qprintf("attrib[%d] size %u\n", i, att.data[i]);
		delta += att.data[i] * sizeof(GLfloat);
		i++;
	}
	return (0);
}

int				ps_build_mesh(t_mesh *me, t_meshattribs att)
{
	glGenVertexArrays(1, me->desc + 0);
	glBindVertexArray(me->desc[0]);
	gen_buffer(me->desc + 1, GL_ARRAY_BUFFER, (GLvoid*)me->floats,
			   me->n_floats * sizeof(*me->floats));
	if (att.has_indices)
		gen_buffer(me->desc + 2, GL_ELEMENT_ARRAY_BUFFER, (GLvoid*)me->indices,
				   me->n_indices * sizeof(*me->indices));
	gen_attribs(att);
	glBindVertexArray(0);
	return (0);
}

