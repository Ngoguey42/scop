/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/18 12:01:22 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/10 13:48:44 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <sys/time.h>

static struct timeval	diff(struct timeval x, struct timeval y)
{
	int		nsec;

	if (x.tv_usec < y.tv_usec)
	{
		nsec = (y.tv_usec - x.tv_usec) / 1000000 + 1;
		y.tv_usec -= 1000000 * nsec;
		y.tv_sec += nsec;
	}
	if (x.tv_usec - y.tv_usec > 1000000)
	{
		nsec = (x.tv_usec - y.tv_usec) / 1000000;
		y.tv_usec += 1000000 * nsec;
		y.tv_sec -= nsec;
	}
	return ((struct timeval){x.tv_sec - y.tv_sec, x.tv_usec - y.tv_usec});
}

static double			tosec(struct timeval t)
{
	return ((double)t.tv_usec / 1000000.f + (double)t.tv_sec);
}

void					sp_delete_meshes(t_env *e)
{
	t_mesh			*me;
	t_mesh const	*end = ITEND_MESHES(e);

	me = e->meshes;
	while (me < end)
	{
		ftv_release(&me->vertices, NULL);
		ftv_release(&me->faces, NULL);
		glDeleteBuffers(1, me->handles + 1);
		glDeleteBuffers(1, me->handles + 2);
		glDeleteVertexArrays(1, me->handles + 3);
		me++;
	}
	return ;
}

int						sp_init_meshes(t_env *e)
{
	t_mesh			*me;
	t_mesh const	*end = ITEND_MESHES(e);
	struct timeval	start;
	struct timeval	stop;

	me = e->meshes;
	while (me < end)
	{
		gettimeofday(&start, NULL);
		lprintf("\033[32mGenerating mesh...\033[0m");
		if (sp_new_mesh(e, me))
			return (1);
		gettimeofday(&stop, NULL);
		lprintf("\033[32m...done in %.6fs\033[0m"
				, tosec(diff(stop, start)));
		me++;
	}
	return (0);
}
