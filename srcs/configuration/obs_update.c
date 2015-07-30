/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/30 13:49:29 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/30 15:47:23 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <math.h>

void		sp_obupdate_sun(t_env const *e, t_ob *ob)
{
	ob->mat = m4_translate_nonuniform(e->sunpos_cartesian);
	return ;
}
