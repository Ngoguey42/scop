// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   landgen_notrel.frag                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/16 11:32:06 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/17 17:07:41 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

uniform int					level_stride;
uniform int					phase_startoffset[2];
uniform vec2				random_seeds;
uniform float				land_average_y;
uniform float				land_range_y;

out float					point_y;
out vec4					color;

float	ft_rand0(vec2 co)
{
	return fract(sin(dot(co.xy, vec2(12.9898f, 78.233f))) * 43758.5453f) - 0.5f;
}

void	main()
{

	if ((int(gl_FragCoord.x) - phase_startoffset[0]) % level_stride != 0
		|| (int(gl_FragCoord.y) - phase_startoffset[1]) % level_stride != 0)
	{
		// discard;
		//color = vec4(0.f, 1.f, 1.f, 0.f); //debug
		color = vec4(0.f, 0.f, 1.f, 1.f);
		point_y = 0.05f;

		return ; //debug
		
	}
//	color = vec4(0.f, 0.f, 0.f, 150.f);
  	point_y =
		ft_rand0(gl_FragCoord.xy + random_seeds) * land_range_y
		+ land_average_y;
	color = vec4(1.f, 1.f, 0.f, 1.f);
//	color = 0.4f;
	return ;
}
