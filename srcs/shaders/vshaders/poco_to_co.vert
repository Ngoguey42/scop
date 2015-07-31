// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   poco_to_co.vert                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/31 12:58:51 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/31 12:58:52 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 ourColor;
uniform mat4 viewproj;

#define FRACTION 5.f

void main()
{
	ourColor = color;
	gl_Position = viewproj * vec4(position, 1.f);
}
