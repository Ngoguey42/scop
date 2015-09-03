/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_vao.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 15:05:12 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/03 15:24:11 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#incude "scop.h"

static inline void	split_vbo(t_vao_basic *vao)
{
	if (vao->set_groups != NULL)
	{
		vao->set_groups(vao);
		sp_rebuild_vbo_from_groups(vao);
	}
}

int					sp_build_vao_primary(t_vao_basic *vao, t_vshader const *vs)
{
	t_byte	constnnor_req = vs->locations[sp_nor_loc].size;
	t_byte	constntex_req = vs->locations[sp_tex_loc].size;

	if (ftv_init_instance(&vao->vbo.vertices, sizeof(t_vertex_basic))
		|| ftv_init_instance(&vao->ebo.facess, sizeof(t_face_basic)))
		ft_enomem();
	if (vao->fill == NULL || vao->fill(me, vao))
		return (ERROR("vao->fill(vao, me->filename)"), 1);
	if (vao->recenter_positions)
		sp_recenter_positions(&vao->vbo);
	if (nnor_req != vao->vbo.nnor)
	{
		sp_build_ebo_normals(vao);
		if (vao->vertices_normal_before_split)
			sp_build_vbo_normals(vao);
	}
	split_vbo(vao);
	if (nnor_req != vao->vbo.nnor)
		sp_build_vbo_normals(vao);
	if (ntex_req != vao->vbo.ntex && vao->set_tex != NULL)
		vao->set_tex(vao);
	return (0);
}
