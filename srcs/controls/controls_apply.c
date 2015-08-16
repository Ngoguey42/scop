/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_apply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 11:35:09 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/16 17:59:42 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include "scop.h"

void			sp_update_states(t_env *e)
{
	sp_update_movements(e, false);//rename
	sp_update_sun(e, false);//rename
	sp_updatepos_mainob(e);
	return ;
}
