/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 12:23:45 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/02 13:50:27 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>
#include <string.h>

/*
** 'sp_init_objs'	init the #(e->models.size) models.
**						'm->filename' must already be allocated
** *
** 'sp_register_obj'	registers a new uninitialized model.
*/

int			sp_init_objs(t_env *e)
{
	t_objmodel		*const models = e->models.data;
	t_objmodel		*m;
	size_t			i;

	i = 0;
	while (i < e->models.size)
	{
		m = models + i;
		if (ftv_init_instance(&m->vertices, sizeof(float) * 3))
			sp_enomem();
		if (ftv_init_instance(&m->faces, sizeof(unsigned int) * 3))
			sp_enomem();
		if (sp_parse_obj(m))
			return (DEBUGF("Error in sp_parse_obj(%s)", m->filepath), 1);
		i++;
	}
	return (0);
}

void		sp_clean_models(void *modelptr)
{
	t_objmodel		*const m = modelptr;

	free(m->filepath);
	ftv_release(&m->vertices, NULL);
	ftv_release(&m->faces, NULL);
	return ;
}

void		sp_register_obj(t_env *e, char const *filepath)
{
	t_objmodel		m;

	m.filepath = strdup(filepath);
	if (m.filepath == NULL)
		sp_enomem();
	if (ftv_push_back(&e->models, &m))
		sp_enomem();
	return ;
}
