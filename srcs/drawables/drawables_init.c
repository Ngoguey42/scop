/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawables_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/18 13:59:15 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/18 14:30:36 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>
#include <stdlib.h>

static int		create_item(t_env *e)
{
	t_drawable		d[1];
	
	bzero(d, sizeof(t_drawable));
	d->prog = sc_basic_program;
	d->n_textures = 0;
	d->mesh.n_floats = ((t_objmodel*)e->models.data)->vertices.size * 3;
	d->mesh.floats = ((t_objmodel*)e->models.data)->vertices.data;
	d->mesh.n_indices = ((t_objmodel*)e->models.data)->faces.size * 3;
	d->mesh.indices = ((t_objmodel*)e->models.data)->faces.data;
	ps_build_mesh(&d->mesh, (t_meshattribs){1, (GLuint[1]){3}, true});
	ftv_push_back(&e->drawables, d);
	return (0);
}

static int					create_square(t_env *e)
{
	t_drawable		d[1];
	GLuint const	textures[] = {e->tex};

	bzero(d, sizeof(t_drawable));
	d->prog = sc_tex_program;
	d->n_textures = 1;
	d->textures = ft_memdup((void*)textures, sizeof(textures));
	if (d->textures == NULL)
		sp_enomem();

	d->mesh.n_floats = 4 * 8;
	d->mesh.floats = (GLfloat[]){
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f
	};
	d->mesh.n_indices = 2 * 3;
	d->mesh.indices = (GLuint[]){
		0, 1, 3,
		1, 2, 3
	};
	ps_build_mesh(&d->mesh, (t_meshattribs)
				  {3, (GLuint[3]){3, 3, 2}, true});
	
	ftv_push_back(&e->drawables, d);	
	return (0);
}

int				sp_create_drawables(t_env *e)
{
	if (create_item(e))
		return (1);
	if (create_square(e))
		return (1);
	return (0);
}

void			sp_release_drawable(void *ptr)
{
	t_drawable	*d = ptr;

	if (d->textures != NULL)
		free(d->textures);
	return ;
}
