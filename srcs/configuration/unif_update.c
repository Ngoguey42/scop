/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unif_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/21 09:01:30 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/15 14:41:12 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#define LOC(N)	glGetUniformLocation(p->handle, N)
#define PREFIX(T) glUniform ## T
#define U(T, N, ...) PREFIX(T)(LOC(N), __VA_ARGS__)

void			sp_unif_model(t_env const *e, t_ob const *ob)
{
	t_program const	*p = POFOB(e, ob);
	GLuint const	loc = glGetUniformLocation(p->handle, "model");

	glUniformMatrix4fv(loc, 1, GL_TRUE, (float*)&ob->mat);
	return ;
}

void			sp_unif_viewproj2(t_env const *e, t_program const *p)
{
	GLuint const	vloc = glGetUniformLocation(p->handle, "view");
	GLuint const	ploc = glGetUniformLocation(p->handle, "projection");

	glUniformMatrix4fv(vloc, 1, GL_TRUE, (float*)&e->view);
	glUniformMatrix4fv(ploc, 1, GL_TRUE, (float*)&e->projection);
	return ;
}

void			sp_unif_viewproj(t_env const *e, t_program const *p)
{
	GLuint const	loc = glGetUniformLocation(p->handle, "viewproj");

	glUniformMatrix4fv(loc, 1, GL_TRUE, (float*)&e->viewproj);
	return ;
}

void			sp_unif_light(t_env const *e, t_program const *p)
{
	GLuint const	lploc = glGetUniformLocation(p->handle, "lightPos");
	GLuint const	vpoloc = glGetUniformLocation(p->handle, "viewPos");
	GLuint const	lcloc = glGetUniformLocation(p->handle, "lightColor");

	glUniform3f(lploc, e->sunpos_cartesian.x
				, e->sunpos_cartesian.y, e->sunpos_cartesian.z);
	glUniform3f(vpoloc, e->cpos.x, e->cpos.y, e->cpos.z);
	glUniform3f(lcloc, e->suncolor.x, e->suncolor.y, e->suncolor.z);
	return ;
}

void			sp_unif_lightstruct(t_env const *e, t_program const *p)
{
	U(3fv, "l.pos", 1, (float*)&e->sunpos_cartesian);
	U(3fv, "l.a", 1, (float*)&e->suncolor);
	U(3fv, "l.d", 1, (float*)&e->suncolor);
	U(3fv, "l.s", 1, (float*)&e->suncolor);
	U(3fv, "viewPos", 1, (float*)&e->cpos);
	return ;
}

void			sp_unif_suncolor(t_env const *e, t_program const *p)
{
	GLuint const	loc = glGetUniformLocation(p->handle, "sunColor");

	glUniform3f(loc, e->suncolor.x, e->suncolor.y, e->suncolor.z);
	return ;
}
