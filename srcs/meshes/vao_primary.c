
#include "scop.h"

int			sp_vao_primary_build(t_mesh const *me, t_vao_basic *vao)
{
	if (me->primary_fill == NULL)
		return (ERROR("missing vao->primary_fill"), 1);
	if (ftv_init_instance(&vao->vbo.vertices, sizeof(t_vertex_basic))
		|| ftv_init_instance(&vao->ebo.faces, sizeof(t_face_basic)))
		ft_enomem();
	if (me->primary_fill(me, vao))
		return (ERROR("vao->primary_fill(vao, me->filename)"), 1);
	return (0);
}
