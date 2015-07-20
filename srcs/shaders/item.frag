// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   item.frag                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/18 14:36:31 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/18 15:21:36 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

in vec3 ourColor;
in vec2 texUV;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
	// color = vec4(ourColor, 1.0f);
	// color = texture(ourTexture, texUV) / 2 + vec4(ourColor, 1.f) / 2;
	color = texture(ourTexture, texUV);
} 
