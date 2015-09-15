// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   global.glsl                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/15 09:28:17 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/15 11:35:51 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

#define G_USE_SUN_COLOR 1
#define G_USE_PATCH_COLOR 2
#define G_USE_TRIANGLE_COLOR 3
#define G_GAMMAF 2.2f
#define G_GAMMAV3 vec3(G_GAMMAF)

#define G_AMBIENT_STRENGTH 0.05f
#define G_DIFFUSE_STRENGTH 2.f
#define G_SPECULAR_STRENGTH 0.99f
#define G_SPECULAR_POWER 32.f

#define G_SBOX_RESOLUTIONF 1024.f
#define G_SHADOW_NSAMPLESI 20
#define G_SHADOW_BIAS 0.05f
#define G_SHADOW_DECAY 1.5f
#define G_SHADOW_NUM_SAMPLING_LOOPS 3
#define G_SHADOW_INITIAL_RADIUS (200.f / SBOX_RESOLUTIONF)

#define G_SHADOW_NSAMPLESF float(NSAMPLESI)
