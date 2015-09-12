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
uniform float				mixval;

in Co
{
	vec3					col;
}							fs_in;

out vec4					color;

#define GAMMA 2.2f

void main()
{
	color = vec4(fs_in.col, 1.0f);
	// color = vec4(sunColor, 1.0f);
	return ;
} 
