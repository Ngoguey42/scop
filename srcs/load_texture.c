/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 14:11:32 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/17 15:29:14 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		sp_load_texture(char const *filepath, GLuint *desc)
{
	int			dim[2];
	t_ftvector	v;

	glGenTextures(1, desc);
	glBindTexture(GL_TEXTURE_2D, *desc);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (ftv_init_instance(&v, sizeof(t_byte) * 4))
		sp_enomem();
	if (parse_tga(filepath, &v, dim))
		return (1);
	qprintf("%d pixels in texture, capa=%u\n", v.size, v.capacity);

	int i = 0;
	for (i = 0; i < 10; i++)
	{
	qprintf("pixel %2d: %2hhx %2hhx %2hhx %2hhx\n",
			i,
			((t_byte*)v.data)[0 + i * 4], ((t_byte*)v.data)[1 + i * 4], 
			((t_byte*)v.data)[2 + i * 4], ((t_byte*)v.data)[3 + i * 4]);
	}
	
	qprintf("imgdim : %u %u\n", dim[0], dim[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dim[0], dim[1], 0,
				 GL_BGRA, GL_UNSIGNED_BYTE, v.data);
	glGenerateMipmap(GL_TEXTURE_2D);
	ftv_release(&v, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
	return (0);
}
