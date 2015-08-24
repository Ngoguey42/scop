/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_vbo_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/15 11:25:49 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/24 12:16:22 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

#define NORM_AT_42_IS_WTF(E, ME, RVBO) (ME)->fill((E), (ME), (RVBO))

t_byte const		g_vbo_offsets[4][2] = {
	{offsetof(t_vertex_basic, pos), offsetof(t_vbo_basic, npos)},
	{offsetof(t_vertex_basic, col), offsetof(t_vbo_basic, ncol)},
	{offsetof(t_vertex_basic, tex), offsetof(t_vbo_basic, ntex)},
	{offsetof(t_vertex_basic, nor), offsetof(t_vbo_basic, nnor)}
};

extern char const	*g_locations_str[];

static t_byte	get_num_elt_vs(t_vshader const *const vs
								, enum e_location_type type)
{
	t_location const		*loc;
	t_location const *const	end = vs->locations + vs->n_locations;

	loc = vs->locations;
	while (loc < end)
	{
		if (type == loc->type)
			return (loc->size);
		loc++;
	}
	return (0);
}

int				sp_validate_vbo(t_vbo_basic const *const vbo
								, t_vshader const *const vs)
{
	size_t					i;
	int						error;
	t_byte					num_elt_vbo;
	t_byte					num_elt_vs;

	error = 0;
	i = 0;
	while (i < SIZE_ARRAY(g_vbo_offsets))
	{
		num_elt_vbo = *REACH_OFFSET(t_byte, vbo, g_vbo_offsets[i][1]);
		num_elt_vs = get_num_elt_vs(vs, i);
		if (num_elt_vbo != num_elt_vs)
		{
			ERRORF("%s(%hhu/%hhu)"
			, g_locations_str[i], num_elt_vbo, num_elt_vs);
			error = 1;
		}
		i++;
	}
	return (error);
}

static void		build_vertex(float tmp[], t_vbo_basic const *const vbo
								, t_vertex_basic const *const vert)
{
	t_byte const			*offsets;
	t_byte const *const		end = END_ARRAY(g_vbo_offsets);
	float					*tmpptr;
	t_byte					num_elt;

	offsets = (const t_byte*)g_vbo_offsets;
	tmpptr = tmp;
	while (offsets < end)
	{
		num_elt = *REACH_OFFSET(t_byte, vbo, offsets[1]);
		if (num_elt > 0)
		{
			memcpy(tmpptr, REACH_OFFSET(void, vert, offsets[0])
						, num_elt * sizeof(float));
			tmpptr += num_elt;
		}
		offsets = (void*)offsets + STRIDE_ARRAY(g_vbo_offsets);
	}
	return ;
}

void			sp_shrink_vbo(t_ftvector *const dst
								, t_vbo_basic const *const vbo)
{
	t_ftvector const *const			srcv = &vbo->vertices;
	t_vertex_basic const			*src;
	t_vertex_basic const *const		end = ftv_end(srcv);
	float							tmp[dst->chunk_size / sizeof(float)];

	src = srcv->data;
	if (ftv_reserve(dst, srcv->size))
		sp_enomem();
	while (src < end)
	{
		build_vertex(tmp, vbo, src);
		ftv_push_back_unsafe(dst, tmp);
		src++;
	}
	return ;
}

int				sp_fill_mesh(t_env const *e, t_mesh *me)
{
	bzero(&me->vbo, sizeof(t_vbo_basic));
	if (ftv_init_instance(&me->vbo.vertices, sizeof(t_vertex_basic)))
		ft_enomem();
	if (NORM_AT_42_IS_WTF(e, me, &me->vbo))
		return (ERROR("me->fill(e, me)"), 1);
	if (sp_validate_vbo(&me->vbo, VSOFME(e, me)))
		return (ERROR("validate_vbo(...)"), 1);
	sp_shrink_vbo(&me->vertices, &me->vbo);
	if (me->usage == GL_STATIC_DRAW)
		ftv_release(&me->vbo.vertices, NULL);
	return (0);
}
