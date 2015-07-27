/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 14:11:32 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 14:29:31 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int		new_texture(char const *filepath, GLuint *desc)
{
	int			dim[2];
	t_ftvector	v;

	glGenTextures(1, desc);
	glBindTexture(GL_TEXTURE_2D, *desc);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (ftv_init_instance(&v, sizeof(t_byte) * 4))
		sp_enomem();
	if (parse_tga(filepath, &v, dim))
		return (ERRORF("parse_tga(%s, &v, dim)", filepath), 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dim[0], dim[1], 0,
				GL_BGRA, GL_UNSIGNED_BYTE, v.data);
	glGenerateMipmap(GL_TEXTURE_2D);
	ftv_release(&v, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
	return (0);
}

void            sp_delete_textures(t_env *e)
{
	t_texture           *t;
	t_texture const     *end = e->textures + sp_num_textures;

	t = e->textures;
	while (t < end)
	{
		glDeleteTextures(1, &t->handle);
		t++;
	}
	return ;
}

int             sp_init_textures(t_env *e)
{
	int     i;

	i = 0;
	while (i < sp_num_textures)
	{
		if (new_texture(e->textures[i].filepath, &e->textures[i].handle))
			return (ERRORF("new_texture(%s, ...)", e->textures[i].filepath), 1);
		i++;
	}
	return (0);
}