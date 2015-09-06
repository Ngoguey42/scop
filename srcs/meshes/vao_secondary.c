
#include "scop.h"

void		sp_vao_secondary_build(t_mesh const *me, t_vao_basic *vao
									, t_vshader const *vs)
{
	t_byte const	nnor_req = sp_location_size(vs, sp_nor_loc);
	t_byte const	ntex_req = sp_location_size(vs, sp_tex_loc);

	if (me->recenter_positions)
		sp_recenter_positions(&vao->vbo);
	if (nnor_req != vao->vbo.nnor)
	{
		sp_normals_to_ebo(vao);
		if (me->vertices_normals_before_split)
			sp_normals_to_vbo(vao);
	}
	if (0 && me->groups_to_ebo != NULL)
	{
		me->groups_to_ebo(vao);
		sp_rebuild_vbo_from_groups(vao);
	}
	if (nnor_req != vao->vbo.nnor)
		sp_normals_to_vbo(vao);
	if (ntex_req != vao->vbo.ntex && me->texs_to_vbo != NULL)
		ftv_foreach(&vao->vbo.vertices, me->texs_to_vbo, (void*)me);
//		me->texs_to_vbo(me, vao);
	return ;
}
