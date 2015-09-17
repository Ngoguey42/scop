// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   debug_print_sampler.frag                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/17 16:07:08 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/17 16:44:37 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

uniform sampler2D			tex;
uniform vec2				viewport;

out vec4                    color;

void	main()
{
	vec2	tex_size = textureSize(tex, 0);

	if (gl_FragCoord.x > tex_size.x || gl_FragCoord.y > tex_size.y)
		discard;
	color = texture(tex, vec2(
						(gl_FragCoord.x / viewport.x) / (tex_size.x / viewport.x)
						, (gl_FragCoord.y / viewport.y) / (tex_size.y / viewport.y)
							 // (gl_FragCoord.x / viewport.x) / tex_size.x
							 // , (gl_FragCoord.y / viewport.y) / tex_size.y
						));
	return ;
}
