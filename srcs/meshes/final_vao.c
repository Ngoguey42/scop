/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_vao.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 15:26:07 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/03 15:31:16 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		fill_vbo_final(t_ftvector vbo_final[1], t_vbo_basic const vbo[1]
						   , t_vertex_basic const vert[1])
{
	(void)vbo_final;
	(void)vbo;
	(void)vertex;
	return ;
}

void		fill_ebo_final(t_ftvector ebo_final[1], t_face_basic const face[1])
{
	(void)ebo_final;
	(void)face;
	return ;
}

void		sp_build_vao_final(t_ftvector vbo_final[1], t_ftvector ebo_final[1]
							   , t_vao_basic const vao[1])
{
	t_byte const	vbo_width = calc_vbo_width(&vao->vbo);

	if (ftv_init_instance(vbo_final, vbo_width)
		|| ftv_reserve(vbo_final, vao->vbo.vertices.size)
		|| ftv_init_instance(ebo_final, 3 * sizeof(t_ui))
		|| ftv_reserve(ebo_final, vao->ebo.faces.size))
		ft_enomem();
	ftv_foreach2(&vao->vbo.vertices, &fill_vbo_final, vbo_final, &vao->vbo);
	ftv_foreach(&vao->ebo.faces, &fill_ebo_final, ebo_final);
	return ;
}
