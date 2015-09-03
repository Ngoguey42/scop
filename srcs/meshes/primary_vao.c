/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_vao.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 15:05:12 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/03 16:23:05 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static inline void	split_vbo(t_mesh const *me, t_vao_basic *vao)
{
	if (me->set_groups != NULL)
	{
		me->set_groups(vao);
		sp_rebuild_vbo_from_groups(vao);
	}
}

int					sp_build_vao_primary(t_mesh const *me, t_vao_basic *vao
										 , t_vshader const *vs)
{
	t_byte const	nnor_req = vs->locations[sp_nor_loc].size;
	t_byte const	ntex_req = vs->locations[sp_tex_loc].size;

	if (ftv_init_instance(&vao->vbo.vertices, sizeof(t_vertex_basic))
		|| ftv_init_instance(&vao->ebo.faces, sizeof(t_face_basic)))
		ft_enomem();
	if (me->fill == NULL || me->fill(me, vao))
		return (ERROR("vao->fill(vao, me->filename)"), 1);
	if (me->recenter_positions)
		sp_recenter_positions(&vao->vbo);
	if (nnor_req != vao->vbo.nnor)
	{
		sp_build_ebo_normals(vao);
		if (me->vertices_normals_before_split)
			sp_build_vbo_normals(vao);
	}
	split_vbo(me, vao);
	if (nnor_req != vao->vbo.nnor)
		sp_build_vbo_normals(vao);
	if (ntex_req != vao->vbo.ntex && me->set_textures != NULL)
		me->set_textures(vao);
	return (0);
}
