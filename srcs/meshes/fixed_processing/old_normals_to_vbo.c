
#include "scop.h"

void		sp_vbo_normals_restore(t_ftvector *dst, t_ftvector const *src)
{
	t_vertex_basic				*vert_dst;
	t_vertex_basic const		*vert_src = src->data;
	t_vertex_basic const *const	vert_src_end = ftv_end(src);

	vert_dst = dst->data;
	T;
	ftv_summarize(dst);
	ftv_summarize(src);
	while (vert_src != vert_src_end)
	{
		*(t_vec3*)&vert_dst->nor = *(t_vec3*)&vert_src->nor;
		vert_src++;
		vert_dst++;
	}
	return ;
}
