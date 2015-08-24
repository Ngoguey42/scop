/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unif_update_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/24 15:46:01 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/24 15:49:05 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			sp_unif_light(t_env const *e, t_program const *p)
{
	UNIF(p, m3fv, "lightPos", 1, (float*)&e->sunpos_cartesian);
	UNIF(p, m3fv, "viewPos", 1, (float*)&e->cpos);
	UNIF(p, m3fv, "lightColor", 1, (float*)&e->sunka);
	return ;
}

void			sp_unif_lightstruct(t_env const *e, t_program const *p)
{
	UNIF(p, m3fv, "l.pos", 1, (float*)&e->sunpos_cartesian);
	UNIF(p, m3fv, "l.a", 1, (float*)&e->sunka);
	UNIF(p, m3fv, "l.d", 1, (float*)&e->sunkd);
	UNIF(p, m3fv, "l.s", 1, (float*)&e->sunks);
	UNIF(p, m1f, "l.linear", e->sundat[0]);
	UNIF(p, m1f, "l.quadratic", e->sundat[1]);
	UNIF(p, m3fv, "viewPos", 1, (float*)&e->cpos);
	UNIF(p, m1f, "far", e->sbox_farplane);
	return ;
}
