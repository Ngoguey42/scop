/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unif_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/21 09:01:30 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/12 10:11:29 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			sp_unif_model(t_env const *e, t_ob const *ob)
{
	t_program const	*p = POFOB(e, ob);

	UNIF(p, mMatrix4fv, "model", 1, GL_TRUE, (float*)&ob->mat);
	return ;
}

void			sp_unif_model_mix(t_env const *e, t_ob const *ob)
{
	t_program const	*p = POFOB(e, ob);

	UNIF(p, mMatrix4fv, "model", 1, GL_TRUE, (float*)&ob->mat);
	UNIF(p, m1f, "mixval", ob->valf[0]);
	return ;
}

void			sp_unif_viewproj2(t_env const *e, t_program const *p)
{
	UNIF(p, mMatrix4fv, "view", 1, GL_TRUE, (float*)&e->view);
	UNIF(p, mMatrix4fv, "projection", 1, GL_TRUE, (float*)&e->projection);
	return ;
}

void			sp_unif_viewproj(t_env const *e, t_program const *p)
{
	UNIF(p, mMatrix4fv, "viewproj", 1, GL_TRUE, (float*)&e->viewproj);
	return ;
}

void			sp_unif_sunfrag(t_env const *e, t_program const *p)
{
	UNIF(p, m3f, "sunColor", e->sunka.x, e->sunka.y, e->sunka.z);
	return ;
}

void			sp_unif_tesc(t_env const *e, t_program const *p)
{
	UNIF(p, m3fv, "cpos", 1, (float*)&e->cpos);
	return ;
}
