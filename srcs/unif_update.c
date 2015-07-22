/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unif_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/21 09:01:30 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/22 14:50:05 by ngoguey          ###   ########.fr       */
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
	t_program const	*p = POFOB(e, ob);
	/* GLuint const	mloc = glGetUniformLocation(p->handle, "model"); */
	GLuint const	lloc = glGetUniformLocation(p->handle, "landrange");
	float const		tmp = LAND_RANGEF;

	/* glUniformMatrix4fv(mloc, 1, GL_TRUE, (float*)&ob->mat); */
	glUniform1f(lloc, tmp);
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
