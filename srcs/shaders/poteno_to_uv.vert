// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   item.vert                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/18 15:04:28 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/27 14:46:10 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3	position;
layout (location = 1) in vec2	texCoord;
layout (location = 2) in vec3	normal;

out vec2						texUV;
out vec3						Normal;
out vec3						fragPos;

uniform mat4					model;
uniform mat4					viewproj;

void main()
{
	texUV = texCoord;
	Normal = mat3(transpose(inverse(model))) * normal;
	gl_Position = model * vec4(position, 1.f);
	fragPos = vec3(gl_Position);
	gl_Position = viewproj * gl_Position;
}
