// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   landgen_notrel.frag                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/16 11:32:06 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/17 15:42:40 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

uniform int					level_stride;
uniform int					phase_startoffset[2];
uniform vec2				random_seeds;

out vec4					color;

float	rand(vec2 co)
{
	return fract(sin(dot(co.xy, vec2(12.9898f, 78.233f))) * 43758.5453f);
}

void	main()
{
	if ((int(gl_FragCoord.x) - phase_startoffset[0]) % level_stride != 0
		|| (int(gl_FragCoord.y) - phase_startoffset[1]) % level_stride != 0)
		discard;
	color = vec4(1.f, 0.f, 0.f, 1.f);
	// color = vec4(rand(gl_FragCoord.xy + random_seeds), 0.f, 0.f, 1.f);
	return ;
}
