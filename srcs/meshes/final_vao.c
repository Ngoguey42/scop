/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_vao.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 15:26:07 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/03 17:00:58 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

extern t_byte const			g_vbo_offsets[4][2];

static int	calc_vbo_width(t_vbo_basic const vbo[1])
{
	return (vbo->npos + vbo->ncol + vbo->ntex + vbo->nnor);
}

static void	build_vertex(float tmp[], t_vbo_basic const vbo[1]
						 , t_vertex_basic const vert[1])
{
	t_byte const		*offsets;
	t_byte const *const	end = END_ARRAY(g_vbo_offsets);
	float				*tmpptr;
	t_byte				num_elt;

	offsets = (t_byte const*)g_vbo_offsets;
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

static void	fill_vbo_final(t_ftvector vbo_final[1], t_vbo_basic const vbo[1]
						   , t_vertex_basic const vert[1])
{
	t_byte		buf[vbo_final->chunk_size];

	build_vertex((float*)buf, vbo, vert);
	ftv_push_back_unsafe(vbo_final, &buf);
	return ;
}

static void	fill_ebo_final(t_ftvector ebo_final[1], t_face_basic const face[1])
{
	ftv_push_back_unsafe(ebo_final, &face->indices);
	return ;
}

void		sp_build_vao_final(t_ftvector vbo_final[1], t_ftvector ebo_final[1]
							   , t_vao_basic const vao[1])
{
	if (ftv_init_instance(vbo_final, calc_vbo_width(&vao->vbo))
		|| ftv_reserve(vbo_final, vao->vbo.vertices.size)
		|| ftv_init_instance(ebo_final, 3 * sizeof(t_ui))
		|| ftv_reserve(ebo_final, vao->ebo.faces.size))
		ft_enomem();
	ftv_foreach2(&vao->vbo.vertices, &fill_vbo_final, vbo_final
				 , (void*)&vao->vbo);
	ftv_foreach(&vao->ebo.faces, &fill_ebo_final, ebo_final);
	return ;
}
