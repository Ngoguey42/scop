// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   item.frag                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/18 14:36:31 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/23 13:19:27 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

in vec2 texUV;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
	color = texture(ourTexture, texUV);
} 
