/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/18 12:01:22 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 15:59:52 by ngoguey          ###   ########.fr       */
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
	lprintf("Defining locations: ");
	while (i < p->n_locations)
	{
		lprintf("    '%s' i=%u; sz=%u; wid=%u, dt=%u", p->locations[i].name, 
			i, p->locations[i].size, vert_width, delta);
		glVertexAttribPointer(i, p->locations[i].size, GL_FLOAT, GL_FALSE
								, vert_width, delta);
		glEnableVertexAttribArray(i);
		delta += p->locations[i].size;
		i++;
	}
	return (0);
}

static int		new_mesh(t_env const *e, t_mesh *me)
{
	t_program const		*p = &e->programs[me->program];
	size_t const		vert_width = mesh_width(p);
	size_t const		elem_width = 3 * sizeof(GLuint);

	lprintf("Generating mesh:");
	lprintf("    vert_width(%u), elem_width(%u) :", vert_width, elem_width);
	if (ftv_init_instance(&me->vertices, vert_width))
		sp_enomem();
	if (me->has_indices && ftv_init_instance(&me->faces, elem_width))
		sp_enomem();
	lprintf("Filling mesh:");
	if (me->fill(e, me))
		return (ERROR("me->fill(e, me)"), 1);
	lprintf("    %u vertices, %u faces:", me->vertices.size, me->faces.size);
	glGenVertexArrays(1, me->handles + 0);
	glBindVertexArray(me->handles[0]);
	lprintf("Sending VBO");
	glGenBuffers(1, me->handles + 1);
	glBindBuffer(GL_ARRAY_BUFFER, me->handles[1]);
	glBufferData(GL_ARRAY_BUFFER, me->vertices.size * vert_width,
				 me->vertices.data, me->usage);
	if (me->has_indices)
	{
		lprintf("Sending EAB");
		glGenBuffers(1, me->handles + 2);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, me->handles[2]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, me->faces.size * elem_width,
					 me->faces.data, me->usage);
	}
	lprintf("Handles: [%u, %u, %u]",
		me->handles[0], me->handles[1], me->handles[2]);
	gen_attribs(p, vert_width);
	glBindVertexArray(0);
	lprintf("");
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

	lprintf("Initializing meshes...");
	me = e->meshes;
	while (me < end)
	{
		if (new_mesh(e, me))
			return (1);
		me++;
	}
	return (0);
}
