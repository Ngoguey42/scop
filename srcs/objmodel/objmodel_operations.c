/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objmodel_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 08:26:17 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/22 13:00:27 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "scop.h"
#include "objmodel_parsing.h"

/*
** 'sp_init_objmodels'			Initializes the #(e->models.size) models.
**							'm->filename' must already be allocated.
** *
** 'sp_clean_objmodels'			Releases ressources allocated in register/init
** 							phases.
** *
** 'sp_register_objmodel'		Registers a new uninitialized model
** 							for initialization.
*/
/*
int			sp_init_objmodels(t_env *e)
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
		if (op_parse_obj(m))
			return (ERRORF("op_parse_obj(%s)", m->filepath), 1);
		i++;
	}
	return (0);
}
*/
void		sp_clean_objmodel(t_objmodel *m)
{
	/* free(m->filepath); */
	if (m->mtllib)
		free(m->mtllib);
	if (m->name)
		free(m->name);
	if (m->usemtl)
		free(m->usemtl);
	/* ftv_release(&m->vertices, NULL); */
	/* ftv_release(&m->faces, NULL); */
	return ;
}
/*
void		sp_register_objmodel(t_env *e, char const *filepath)
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
*/
