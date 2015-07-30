/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/30 13:49:29 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/30 13:54:18 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <math.h>

void		sp_obupdate_sun(t_env const *e, t_ob *ob)
{
	qprintf("updating ob->mat for sun\n");
	ob->mat = m4_translate_nonuniform(e->sunpos);
	return ;
}
