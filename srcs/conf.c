/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 12:53:00 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 13:02:17 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

int				sp_loadconf_shaders(t_env *e)
{
	int					i;
	t_shader const		tmp[sp_num_shaders] = {

	{strdup(SHADER_PATH("scop.vert")), GL_VERTEX_SHADER, NULL, 0},
	{strdup(SHADER_PATH("scop.frag")), GL_VERTEX_SHADER, NULL, 0},
	{strdup(SHADER_PATH("tex.vert")), GL_VERTEX_SHADER, NULL, 0},
	{strdup(SHADER_PATH("tex.frag")), GL_VERTEX_SHADER, NULL, 0},
	{strdup(SHADER_PATH("item.vert")), GL_VERTEX_SHADER, NULL, 0},
	{strdup(SHADER_PATH("item.frag")), GL_VERTEX_SHADER, NULL, 0},
	};
	i = 0;
	while (i < sp_num_shaders)
	{
		if (tmp[i].filepath == NULL)
			sp_enomem();
		i++;
	}
	memcpy(&e->shaders, &tmp, sizeof(tmp));
	return (0);
}
