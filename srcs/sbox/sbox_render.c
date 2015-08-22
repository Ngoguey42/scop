/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sbox_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/22 12:21:49 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/22 14:54:47 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <math.h>
extern GLuint depthMapFBO;

#define LOC(N)  glGetUniformLocation(p->handle, N)
#define PREFIX(T) glUniform ## T
#define U(T, N, ...) PREFIX(T)(LOC(N), __VA_ARGS__)

static void	render_ob(t_env const *e, t_ob const *ob)
{
	t_mesh const *const		me = MEOFOB(e, ob);
	t_program const *const	p = e->programs + sp_pointshadow_program;

	U(Matrix4fv, "model", 1, GL_TRUE, (float*)&ob->mat);
	glBindVertexArray(me->handles[0]);
	glDrawElements(GL_TRIANGLES, 3 * me->faces.size, GL_UNSIGNED_INT, 0);
	return ;
}

void		sp_render_sbox(t_env const *e)
{
GLuint SHADOW_WIDTH, SHADOW_HEIGHT;
SHADOW_HEIGHT = SHADOW_WIDTH = 1024 * 1; //sha
	GLfloat far = 250.0f;//s
	t_matrix4   shadowProj = m4_fovprojection(
		M_PI / 2.f, 1.f, 1.f, far); //s

	t_vector3   lightPos = e->sunpos_cartesian;
#define CONV(V) (t_matrix4[]){V}
#define LOOKATPTR(V1, V2) CONV(m4_lookat(lightPos, v3_add(lightPos, (V1)), (V2)))
	t_matrix4   shadowTransforms[6] = {
m4_dotprod(&shadowProj, LOOKATPTR(ATOV3(+1.0, 0.0, 0.0), ATOV3(0.0, -1.0, 0.0))),
m4_dotprod(&shadowProj, LOOKATPTR(ATOV3(-1.0, 0.0, 0.0), ATOV3(0.0, -1.0, 0.0))),
m4_dotprod(&shadowProj, LOOKATPTR(ATOV3(0.0, +1.0, 0.0), ATOV3(0.0, 0.0, +1.0))),
m4_dotprod(&shadowProj, LOOKATPTR(ATOV3(0.0, -1.0, 0.0), ATOV3(0.0, 0.0, -1.0))),
m4_dotprod(&shadowProj, LOOKATPTR(ATOV3(0.0, 0.0, +1.0), ATOV3(0.0, -1.0, 0.0))),
m4_dotprod(&shadowProj, LOOKATPTR(ATOV3(0.0, 0.0, -1.0), ATOV3(0.0, -1.0, 0.0))),
};
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	t_program const *p;
	p = e->programs + sp_pointshadow_program;
	glUseProgram(p->handle);


	int i;
	for (i = 0; i < 6; i++)
	{
		char    truc[32] = "shadowMatrices[6]";

		truc[15] = i + '0';
		U(Matrix4fv, truc, 1, GL_TRUE, (float*)(shadowTransforms + i));
	}
	U(1f, "far", far);
	U(3fv, "lpos", 1, (float*)&lightPos);
	{
		t_program_index     i;

		i = -1;
		while (++i < sp_num_programs)
			ftl_foreach_if(e->obs + i, &render_ob, (void*)e, &sp_ob_get_shadow);
	}
	glBindVertexArray(0);
	return ;
}
