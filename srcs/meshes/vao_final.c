
#include "scop.h"
#include <string.h>

extern t_location_info const	g_locinfo[sp_num_locs];

static void	build_vertex(float tmp[], t_vbo_basic const vbo[1]
						 , t_vertex_basic const vert[1])
{
	t_location_info const	*loc;
	t_byte const *const		end = END_ARRAY(g_locinfo);
	float					*tmpptr;
	t_byte					num_elt;

	loc = g_locinfo;
	tmpptr = tmp;
	while (loc < end)
	{
		num_elt = *REACH_OFFSET(t_byte, vbo, loc->vbo_basic_offset);
		if (num_elt > 0)
		{
			memcpy(tmpptr, REACH_OFFSET(void, vert, loc->vertex_basic_offset)
				   , num_elt * sizeof(float));
			tmpptr += num_elt;
		}
		loc++;
	}
	return ;
}

static void	vbo_final_build(t_ftvector vbo_final[1], t_vbo_basic const vbo[1]
						   , t_vertex_basic const vert[1])
{
	t_byte		buf[vbo_final->chunk_size];

	build_vertex((float*)buf, vbo, vert);
	ftv_push_back_unsafe(vbo_final, &buf);
	return ;
}

static void	ebo_final_build(t_ftvector ebo_final[1], t_face_basic const face[1])
{
	ftv_push_back_unsafe(ebo_final, &face->indices);
	return ;
}

void		sp_vao_final_build(t_ftvector vbo_final[1], t_ftvector ebo_final[1]
							   , t_vao_basic const vao[1])
{
	size_t const	vbo_width = vbo->npos + vbo->ncol + vbo->ntex + vbo->nnor;

	if (ftv_init_instance(vbo_final, vbo_width)
		|| ftv_reserve(vbo_final, vao->vbo.vertices.size)
		|| ftv_init_instance(ebo_final, 3 * sizeof(t_ui))
		|| ftv_reserve(ebo_final, vao->ebo.faces.size))
		ft_enomem();
	ftv_foreach2(&vao->vbo.vertices, &vbo_final_build, vbo_final
				 , (void*)&vao->vbo);
	ftv_foreach(&vao->ebo.faces, &ebo_final_build, ebo_final);
	return ;
}
