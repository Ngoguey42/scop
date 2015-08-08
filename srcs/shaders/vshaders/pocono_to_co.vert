// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   pocono_to_co.vert                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/27 18:22:28 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/27 18:54:24 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3	position;
layout (location = 1) in vec3	color;
layout (location = 2) in vec3	normal;

out vec3						ourColor;
out vec3						Normal;
out vec3						fragPos;

uniform mat4					model;
uniform mat4					viewproj;

void main()
{
	Normal = mat3(transpose(inverse(model))) * normal;
	ourColor = color;
	gl_Position = model * vec4(position, 1.f);
	fragPos = vec3(gl_Position);	
	gl_Position = viewproj * gl_Position;
}