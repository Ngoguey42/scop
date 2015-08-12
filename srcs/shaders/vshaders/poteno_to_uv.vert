// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   poteno_to_uv.vert                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/30 09:09:23 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/12 13:08:37 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3	pos;
layout (location = 1) in vec2	tex;
layout (location = 2) in vec3	nor;

out UVNOFP
{
	vec2						texUV;
	vec3						Normal;
	vec3						fragPos;
}								vs_out;

uniform mat4					model;
uniform mat4					viewproj;

void main()
{
	vs_out.texUV = tex;
	vs_out.Normal = mat3(transpose(inverse(model))) * nor;
	gl_Position = model * vec4(pos, 1.f);
	vs_out.fragPos = vec3(gl_Position);
	gl_Position = viewproj * gl_Position;
}
