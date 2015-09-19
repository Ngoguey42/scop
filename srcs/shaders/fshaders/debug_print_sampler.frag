// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   debug_print_sampler.frag                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/17 16:07:08 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/19 09:25:32 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

uniform sampler2D			tex;
//uniform vec2				viewport;

out vec4                    color;

void	main()
{
	vec2	tex_size = textureSize(tex, 0);

//	if (gl_FragCoord.x > tex_size.x || gl_FragCoord.y > tex_size.y)
//		discard;



	// color = texture(tex, vec2((gl_FragCoord.x) / (tex_size.x)
	// 						  , (gl_FragCoord.y) / (tex_size.y)));


	color.w = texture(
	  tex, vec2(
	  (gl_FragCoord.x) / (tex_size.x)
	  , (gl_FragCoord.y) / (tex_size.y))).x;

	  color = vec4((-color.w - 3.f) / 25.f, 0.f, 0.f, 1.f);


	// color = vec4(texture(tex, vec2((gl_FragCoord.x) / (tex_size.x)
	// 							   , (gl_FragCoord.y) / (tex_size.y))).xyz, 1.f);
	// color.x = abs(color.x) * 5.f;
	// color.y = abs(color.y) / 1.5f;
	// color.z = abs(color.z) * 5.f;
	
	return ;
}
