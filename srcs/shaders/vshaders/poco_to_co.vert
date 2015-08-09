// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   poco_to_co.vert                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/31 12:58:51 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/09 13:28:41 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;

out vec3 ourColor;
uniform mat4 viewproj;

#define FRACTION 5.f

void main()
{
	ourColor = col;
	gl_Position = viewproj * vec4(pos, 1.f);
}
