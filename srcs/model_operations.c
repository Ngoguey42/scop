/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 12:23:45 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/02 12:34:54 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>

/*
** 'sp_init_objs'	init the #(e->models.size) models.
**						'm->filename' must already be allocated
*/

void		sp_clean_models(void *modelptr)
{
	t_objmodel		*const m = modelptr;

	free(m->filename);
	ftv_release(&m->vertices, NULL);
	ftv_release(&m->faces, NULL);
	return ;
}

int			sp_init_objs(t_env *e)
{
	t_objmodel		*const models = e->models.data;
	size_t			i;

	i = 0;
	while (i < e->models.size)
	{
		
	}
	return (0);
}
