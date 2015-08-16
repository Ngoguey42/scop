// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   pocono_to_co.vert                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/27 18:22:28 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/16 15:08:55 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3	pos;
layout (location = 1) in vec3	col;
layout (location = 2) in vec3	nor;

uniform mat4					model;
uniform mat4					viewproj;

out PoCoNo
{
	vec3                        pos;
	vec3						col;
	vec3                        nor;
}                               vs_out;

void main()
{
	vs_out.nor = mat3(transpose(inverse(model))) * nor;
	vs_out.col = col;
	gl_Position = model * vec4(pos, 1.f);
	vs_out.pos = vec3(gl_Position);	
	gl_Position = viewproj * gl_Position;
}
