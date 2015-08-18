// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   depth01.frag                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/08/18 15:54:08 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/18 15:55:47 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

in vec4			pos;

uniform vec3	lpos;
uniform float	far;

void main()
{
	gl_FragDepth = length(pos.xyz - lpos) / far;
} 
