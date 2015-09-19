// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   global.glsl                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/15 09:28:17 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/19 15:29:17 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

#define G_USE_SUN_COLOR 1
#define G_USE_PATCH_COLOR 2
#define G_USE_TRIANGLE_COLOR 3
#define G_GAMMA 2.2f
#define G_GAMMAV3 vec3(G_GAMMAF)

#define G_AMBIENT_STRENGTH 0.05f
#define G_DIFFUSE_STRENGTH 2.f
#define G_SPECULAR_STRENGTH 0.99f
#define G_SPECULAR_POWER 32.f

#define G_SBOX_RESOLUTIONF 1024.f
#define G_SHADOW_BIAS 0.05f
#define G_SHADOW_DECAY 1.5f
#define G_SHADOW_NUM_SAMPLING_LOOPS 3

#define G_NLANDCOLORSI 8

struct ColType
{
	vec4            color;
	float           center;
	float           halfrange;
};

/*
** CONFIG MACROES
** INITIAL_RADIUS       -> Initial sampling radius at max distance.
*/

#define G_SHADOW_INITIAL_RADIUS (200.f / G_SBOX_RESOLUTIONF)

#define G_SHADOW_NSAMPLESF float(NSAMPLESI)

#define G_COL_TO_SRGB(COL) pow((COL), vec3(G_GAMMA))
#define G_COL_TO_LINEAR(COL) pow((COL), vec3(1.f / G_GAMMA))
