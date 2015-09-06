/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbo_rebuilding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 16:27:03 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/03 16:27:19 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void    sp_rebuild_vbo_from_groups(t_vao_basic *vao)
{
	t_transp_ebo	tebo[1];

	sp_transpose_ebo(tebo, vao);
	
	ftv_release(&tebo->tvertices, NULL);
	free(tebo->field);
	return ;
}
