/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 12:23:45 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/13 09:48:52 by ngoguey          ###   ########.fr       */
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
	t_objmodel		*models;
	t_objmodel		*m;
	size_t			i;

	models = e->models.data;
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
	t_objmodel		*m;

	m = modelptr;
	free(m->filepath);
	if (m->mtllib)
		free(m->mtllib);
	if (m->name)
		free(m->name);
	if (m->usemtl)
		free(m->usemtl);
	ftv_release(&m->vertices, NULL);
	ftv_release(&m->faces, NULL);
	return ;
}

void		sp_register_obj(t_env *e, char const *filepath)
{
	t_objmodel		m;

	bzero(&m, sizeof(m));
	m.filepath = strdup(filepath);
	m.smooth = undefined;
	if (m.filepath == NULL)
		sp_enomem();
	if (ftv_push_back(&e->models, &m))
		sp_enomem();
	return ;
}
