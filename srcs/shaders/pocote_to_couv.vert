// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   pocote_to_couv.vert                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/27 14:20:47 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/27 14:20:48 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 ourColor;
out vec2 texUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	ourColor = color;
	texUV = texCoord;
	gl_Position = projection * view *model * vec4(position, 1.0);
}
