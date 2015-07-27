/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unif_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/21 09:01:30 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/27 15:29:47 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			sp_unif_model(t_env const *e, t_ob const *ob)
{
	t_program const	*p = POFOB(e, ob);
	GLuint const	loc = glGetUniformLocation(p->handle, "model");

	glUniformMatrix4fv(loc, 1, GL_TRUE, (float*)&ob->mat);
	return ;
}

void			sp_unif_land(t_env const *e, t_ob const *ob)
{
	(void)e;
	(void)ob;
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

	glUniform3f(lploc, 10.f, 30.f, 0.f);
	glUniform3f(vpoloc, e->cpos.x, e->cpos.y, e->cpos.z);
	glUniform3f(lcloc, 1.0f, 1.0f, 1.0f);
	/* glUniform3f(lcloc, 64.f / 255.f, 156.f / 255.f, 255.f / 255.f); */
	return ;
}
