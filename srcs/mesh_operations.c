/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/18 12:01:22 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 15:25:38 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static size_t	mesh_width(t_program const *p)
{
	size_t	i;
	size_t	tot;

	i = 0;
	tot = 0;
	while (i < p->n_locations)
	{
		tot += p->locations[i].size;
		i++;
	}
	return (tot);
}

static int		gen_attribs(t_program const *p, size_t vert_width)
{
	size_t	i;
	GLvoid	*delta;

	i = 0;
	delta = NULL;
	while (i < p->n_locations)
	{
		glVertexAttribPointer(i, p->locations[i].size, GL_FLOAT, GL_FALSE
								, vert_width, delta);
		glEnableVertexAttribArray(i);
		delta += p->locations[i].size * sizeof(GLfloat);
		i++;
	}
	return (0);
}

static int		new_mesh(t_env const *e, t_mesh *me)
{
	t_program const		*p = &e->programs[me->program];
	size_t const		vert_width = mesh_width(p) * sizeof(GLfloat);
	size_t const		elem_width = 3 * sizeof(GLuint);

	if (ftv_init_instance(&me->vertices, vert_width))
		sp_enomem();
	if (me->has_indices && ftv_init_instance(&me->faces, elem_width))
		sp_enomem();
	//fill vectors
	glGenVertexArrays(1, me->handles + 0);
	glBindVertexArray(me->handles[0]);
	glGenBuffers(1, me->handles + 1);
	glBindBuffer(GL_ARRAY_BUFFER, me->handles[1]);
	glBufferData(GL_ARRAY_BUFFER, me->vertices.size * vert_width,
				 me->vertices.data, me->usage);
	if (me->has_indices)
	{
		glGenBuffers(1, me->handles + 2);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, me->handles[2]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, me->faces.size * elem_width,
					 me->faces.data, me->usage);
	}
	gen_attribs(p, vert_width);
	glBindVertexArray(0);
	return (0);
}

void            sp_delete_meshes(t_env *e)
{
	t_mesh           *me;
	t_mesh const     *end = e->meshes + sp_num_meshes;

	me = e->meshes;
	while (me < end)
	{
		ftv_release(&me->vertices, NULL);
		if (me->has_indices)
			ftv_release(&me->faces, NULL);
		me++;
	}
	return ;
}

int             sp_init_meshes(t_env *e)
{
	t_mesh           *me;
	t_mesh const     *end = e->meshes + sp_num_meshes;

	me = e->meshes;
	while (me < end)
	{
		if (new_mesh(e, me))
			return (1);
		qprintf("Mesh handles: = %d %d %d\n",
				me->handles[0], me->handles[1], me->handles[2]);
		
		me++;
	}
	return (0);
}
