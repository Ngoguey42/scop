/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawables_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/18 13:59:15 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/18 15:55:41 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>
#include <stdlib.h>

#ifndef NARG
# define NARG_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,N,...) N
# define NARG(...) NARG_(__VA_ARGS__,11,10,9,8,7,6,5,4,3,2,1)
#endif

#define CONV(...) (t_meshattribs){__VA_ARGS__}
#define ATT_(...) (GLuint[]){__VA_ARGS__}
#define ATT(tex, ...) CONV(NARG(__VA_ARGS__), ATT_(__VA_ARGS__), tex)

#define FLOATTAB(...) (GLfloat[]){__VA_ARGS__}
#define UINTTAB(...) (GLuint[]){__VA_ARGS__}

static int		create_item(t_env *e)
{
	t_drawable		d[1];

	bzero(d, sizeof(t_drawable));
	d->prog = sc_item_program;
	d->n_textures = 0;
	d->mesh.n_floats = ((t_objmodel*)e->models.data)->vertices.size * 5;
	d->mesh.floats = ((t_objmodel*)e->models.data)->vertices.data;
	d->mesh.n_indices = ((t_objmodel*)e->models.data)->faces.size * 3;
	d->mesh.indices = ((t_objmodel*)e->models.data)->faces.data;
	ps_build_mesh(&d->mesh, ATT(true, 3, 2));
	ftv_push_back(&e->drawables, d);
	return (0);
}

static int		create_square(t_env *e)
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
	d->mesh.floats = FLOATTAB(
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	d->mesh.n_indices = 2 * 3;
	d->mesh.indices = UINTTAB(
		0, 1, 3,
		1, 2, 3);
	ps_build_mesh(&d->mesh, ATT(true, 3, 3, 2));
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
	t_drawable	*d;

	d = ptr;
	if (d->textures != NULL)
		free(d->textures);
	return ;
}
