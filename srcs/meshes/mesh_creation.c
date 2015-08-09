/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/28 11:02:28 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/09 14:10:25 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

char const		*g_locations_str[] = {
	"pos",
	"col",
	"tex",
	"nor"
};

static size_t	mesh_width(t_vshader const *vs)
{
	size_t	i;
	size_t	tot;

	i = 0;
	tot = 0;
	while (i < vs->n_locations)
	{
		tot += vs->locations[i].size;
		i++;
	}
	return (tot);
}

static int		gen_attribs(t_vshader const *vs, size_t vert_width)
{
	size_t	i;
	GLvoid	*delta;

	i = 0;
	delta = NULL;
	lprintf("    Defining locations: ");
	while (i < vs->n_locations)
	{
		lprintf("    ->%-8s i=%02u; sz=%02u; wid=%02u, dt=%02u",
				g_locations_str[vs->locations[i].type],
			i, vs->locations[i].size, vert_width, delta);
		glVertexAttribPointer(i, vs->locations[i].size, GL_FLOAT, GL_FALSE
								, vert_width, delta);
		glEnableVertexAttribArray(i);
		delta += vs->locations[i].size * sizeof(GLfloat);
		i++;
	}
	return (0);
}

static void		handle_buffers(t_env const *e, t_mesh *me,
								size_t const widths[2])
{
	qprintf("    Sending VBO... ");
	glGenBuffers(1, me->handles + 1);
	glBindBuffer(GL_ARRAY_BUFFER, me->handles[1]);
	glBufferData(GL_ARRAY_BUFFER, me->vertices.size * widths[0],
					me->vertices.data, me->usage);
	qprintf("    Sending EAB... ");
	glGenBuffers(1, me->handles + 2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, me->handles[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, me->faces.size * widths[1],
					me->faces.data, me->usage);
	return ;
	(void)e;
}

int				op_new_mesh(t_env const *e, t_mesh *me)
{
	t_program const		*p = &e->programs[me->program];
	size_t const		vert_width = mesh_width(VSOFP(e, p)) * sizeof(float);
	size_t const		elem_width = 3 * sizeof(t_ui);
	t_vbo_basic			raw_vbo[1];

	bzero(raw_vbo, sizeof(t_vbo_basic));
	lprintf("\033[32mGenerating mesh...\033[0m");
	lprintf("    vert_width(%u), elem_width(%u) :", vert_width, elem_width);
	if (ftv_init_instance(&me->vertices, vert_width))
		sp_enomem();
	if (ftv_init_instance(&me->faces, elem_width))
		sp_enomem();
	lprintf("    \033[33mFilling mesh...\033[0m");
	if (me->fill(e, me))
		return (ERROR("me->fill(e, me)"), 1);
	lprintf("    \033[33m...done:  %u vertices, %u faces\033[0m",
			me->vertices.size, me->faces.size);
	glGenVertexArrays(1, me->handles + 0);
	glBindVertexArray(me->handles[0]);
	handle_buffers(e, me, (size_t const[]){vert_width, elem_width});
	lprintf("    Handles: [VAO->%u VBO->%u EBO->%u]",
		me->handles[0], me->handles[1], me->handles[2]);
	gen_attribs(VSOFP(e, p), vert_width);
	glBindVertexArray(0);
	lprintf("\033[32m...done\033[0m");
	return (0);
}
