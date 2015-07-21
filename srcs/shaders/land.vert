// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   scop.vert                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/30 17:43:59 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/21 17:29:42 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3 position;

#define CTOF(V) ((V) / 256.f)
#define HIGH vec3(CTOF(109.f), CTOF(61.f), CTOF(39.f))
#define MEDIUM vec3(CTOF(34.f), CTOF(156.f), CTOF(13.f))
#define LOW vec3(CTOF(94.f), CTOF(97.f), CTOF(186.f))

out vec3 ourColor;

uniform float landrange;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

#define FRACTION 5.f

void main()
{
	float ratio = (position.y + landrange / 2.f) / landrange;

	if (ratio > (4.f / FRACTION))
	{
		ratio = (ratio - (4.f / FRACTION)) * FRACTION;
		ourColor = MEDIUM * ratio + HIGH * (1.f - ratio);
		// ourColor = HIGH * ratio + MEDIUM * (1.f - ratio);
	}
	else if (ratio > (3.f / FRACTION))
	{
		ratio = (ratio - (3.f / FRACTION)) * FRACTION;
		ourColor = HIGH * ratio + MEDIUM * (1.f - ratio);
		// ourColor = MEDIUM * ratio + HIGH * (1.f - ratio);
	}
	else if (ratio > (2.f / FRACTION))
	{
		ratio = (ratio - (2.f / FRACTION)) * FRACTION;
		ourColor = MEDIUM * ratio + LOW * (1.f - ratio);
	}
	else if (ratio > (1.f / FRACTION))
	{
		ratio = (ratio - (1.f / FRACTION)) * FRACTION;
		ourColor = LOW * ratio + MEDIUM * (1.f - ratio);
	}
	else
	{
		ratio = ratio * FRACTION;
		ourColor = LOW;
	}		
	gl_Position = projection * view * model * vec4(position, 1.f);
}
