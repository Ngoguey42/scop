// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   debug_print_sampler.frag                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/17 16:07:08 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/17 16:53:37 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

uniform sampler2D			tex;
uniform vec2				viewport;

out vec4                    color;

void	main()
{
	vec2	tex_size = textureSize(tex, 0);

//	if (gl_FragCoord.x > tex_size.x || gl_FragCoord.y > tex_size.y)
//		discard;
	color.w = texture(
		tex, vec2(
			(gl_FragCoord.x / viewport.x) / (tex_size.x / viewport.x)
			, (gl_FragCoord.y / viewport.y) / (tex_size.y / viewport.y)));
	color = vec4(color.w, 0.f, 0.f, 1.f);
//	color = vec4(1.f, 0.f, 0.f, 1.f);
	return ;
}
