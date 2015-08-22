/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unif_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/21 09:01:30 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/22 18:38:50 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#define LOC(N)	glGetUniformLocation(p->handle, N)
#define PREFIX(T) glUniform ## T
#define U(T, N, ...) PREFIX(T)(LOC(N), __VA_ARGS__)

void			sp_unif_model(t_env const *e, t_ob const *ob)
{
	t_program const	*p = POFOB(e, ob);

	U(Matrix4fv, "model", 1, GL_TRUE, (float*)&ob->mat);
	U(1f, "mixval", 1.f);//debug
	return ;
}

void			sp_unif_model_mix(t_env const *e, t_ob const *ob)
{
	t_program const	*p = POFOB(e, ob);

	U(Matrix4fv, "model", 1, GL_TRUE, (float*)&ob->mat);
	U(1f, "mixval", ob->valf[0]);
	return ;
}

void			sp_unif_viewproj2(t_env const *e, t_program const *p)
{
	U(Matrix4fv, "view", 1, GL_TRUE, (float*)&e->view);
	U(Matrix4fv, "projection", 1, GL_TRUE, (float*)&e->projection);
	return ;
}

void			sp_unif_viewproj(t_env const *e, t_program const *p)
{
	U(Matrix4fv, "viewproj", 1, GL_TRUE, (float*)&e->viewproj);
	return ;
}

void			sp_unif_light(t_env const *e, t_program const *p)
{
	U(3f, "lightPos", e->sunpos_cartesian.x
	  , e->sunpos_cartesian.y, e->sunpos_cartesian.z);
	U(3f, "viewPos", e->cpos.x, e->cpos.y, e->cpos.z);
	U(3f, "lightColor", e->sunka.x, e->sunka.y, e->sunka.z);
	return ;
}

void			sp_unif_lightstruct(t_env const *e, t_program const *p)
{
	U(3fv, "l.pos", 1, (float*)&e->sunpos_cartesian);
	U(3fv, "l.a", 1, (float*)&e->sunka);
	U(3fv, "l.d", 1, (float*)&e->sunkd);
	U(3fv, "l.s", 1, (float*)&e->sunks);
	U(1f, "l.linear", e->sundat[0]);
	U(1f, "l.quadratic", e->sundat[1]);
	U(3fv, "viewPos", 1, (float*)&e->cpos);
	U(1f, "far", e->sbox_resolution);
	return ;
}

void			sp_unif_suncolor(t_env const *e, t_program const *p)
{
	U(3f, "sunColor", e->sunka.x, e->sunka.y, e->sunka.z);
	return ;
}

void			sp_unif_lightdepth(t_env const *e, t_program const *p)
{
	(void)e;
	(void)p;	
	return ;
}

void			sp_unif_shadowmat6(t_env const *e, t_program const *p)
{
	(void)e;
	(void)p;
	return ;
}
