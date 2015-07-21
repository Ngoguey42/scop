// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   scop.vert                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/30 17:43:59 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/21 17:15:43 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3 position;

#define CTOF(V) ((V) / 256.f)
#define HIGH vec3(CTOF(89.f), CTOF(34.f), CTOF(8.f))
#define MEDIUM vec3(CTOF(34.f), CTOF(156.f), CTOF(13.f))
#define LOW vec3(CTOF(94.f), CTOF(97.f), CTOF(186.f))

out vec3 ourColor;

uniform float landrange;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	float ratio = (position.y + landrange / 2.f) / landrange;

	if (ratio > (3.f / 4.f))
	{
		ratio = (ratio - (3.f / 4.f)) * 4.f;
		ourColor = MEDIUM * ratio + HIGH * (1.f - ratio);
		// ourColor = HIGH * ratio + MEDIUM * (1.f - ratio);
	}
	else if (ratio > (2.f / 4.f))
	{
		ratio = (ratio - (2.f / 4.f)) * 4.f;
		ourColor = HIGH * ratio + MEDIUM * (1.f - ratio);
		// ourColor = MEDIUM * ratio + HIGH * (1.f - ratio);
	}
	else if (ratio > (1.f / 4.f))
	{
		ratio = (ratio - (1.f / 4.f)) * 4.f;
		ourColor = MEDIUM * ratio + LOW * (1.f - ratio);
	}
	else
	{
		ratio = ratio * 4.f;
		ourColor = LOW * ratio + MEDIUM * (1.f - ratio);
	}		
	gl_Position = projection * view * model * vec4(position, 1.f);
}
