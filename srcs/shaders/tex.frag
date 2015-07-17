// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   scop.frag                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/30 17:44:08 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/17 15:01:45 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

// #version 410 core
// in vec3 ourColor;
// in vec2 texCoord;

// out vec4 color;

// // Texture samplers

// void main()
// {
// }


#version 410 core

in vec3 ourColor;
in vec2 texUV;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
	color = texture(ourTexture, texUV);
	// color = vec4(ourColor, 1.0f);
	// color = mix(vec4(ourColor, 1.0f), ourTexture, 0.5);
	// color = vec4(1.f, 0.f, 0.f, 0.f);
	// color = vec4(texUV, 0.f, 0.f);
} 
