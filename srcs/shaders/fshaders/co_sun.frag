// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   co_sun.frag                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/30 13:42:20 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/12 06:51:09 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

uniform vec3		sunColor;

out vec4 color;

#define GAMMA 2.2f

void main()
{
	color = vec4(sunColor, 1.0f);
//	color.rgb = pow(color.rgb, vec3(1.f / GAMMA));
	// color = vec4(233.f / 255.f, 189.f / 255.f, 21.f / 255.f, 1.0f);
} 
