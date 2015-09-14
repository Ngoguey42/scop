// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   co_sun.frag                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/30 13:42:20 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/12 08:30:24 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

uniform vec3				sunColor;
uniform int					colorUsing;

#define USE_SUN_COLOR 1
#define USE_PATCH_COLOR 2
#define USE_TRIANGLE_COLOR 3
#define GAMMA 2.2f

in Co
{
	vec3					col;
}							fs_in;

out vec4					color;

void main()
{
	if (colorUsing == USE_SUN_COLOR)
		color = vec4(sunColor, 1.0f);
	else
		color = vec4(fs_in.col, 1.0f);
	return ;
} 
