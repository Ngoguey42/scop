// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   poteno_to_uv.vert                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/30 09:09:23 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/30 09:45:32 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3	position;
layout (location = 1) in vec2	texCoord;
layout (location = 2) in vec3	normal;

out UVNOFP
{
	vec2						texUV;
	vec3						Normal;
	vec3						fragPos;
}								vs_out;

out vec2						texUV;
out vec3						Normal;
out vec3						fragPos;

uniform mat4					model;
uniform mat4					viewproj;

void main()
{
	vs_out.texUV = texCoord;
	vs_out.Normal = mat3(transpose(inverse(model))) * normal;
	gl_Position = model * vec4(position, 1.f);
	vs_out.fragPos = vec3(gl_Position);
	gl_Position = viewproj * gl_Position;
}
