// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   couvno_blendli.frag                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/30 10:07:14 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/27 17:07:02 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

/*
** CONFIG MACROES
*/
#define AMBIENT_STRENGTH 0.02f
#define DIFFUSE_STRENGTH 2.0f
#define SPECULAR_STRENGTH 2.f
#define SPECULAR_POWER 32.f
#define GAMMA 2.2f

#define NSAMPLESI 20
#define BIAS 0.05f
#define DECAY 1.5f
#define NUM_SAMPLING_LOOPS 3
#define INITIAL_RADIUS (4.5f * 15.f / (1024.f * 4.5345679f))
//default radius is 4.534567884

/*
** CALCULATED MACROES
** GN			->	Gold Number
** V0			->	Base value for a normalized dodecahedron
*/
#define NSAMPLESF float(NSAMPLESI)
#define GN ((1.f + sqrt(5.f)) / 2.f)
#define V0 GN
#define V1 (V0 * V0)
#define V2 (V0 * V0 * V0)

vec3						SAMPLES[NSAMPLESI] = vec3[](
	vec3(-V1, -V1, V1),	vec3(V2, V0, 0),	vec3(V2, -V0, 0),
	vec3(-V2, V0, 0),	vec3(-V2, -V0, 0),	vec3(0, V2, V0),
	vec3(0, V2, -V0),	vec3(V0, 0, -V2),	vec3(-V0, 0, -V2),
	vec3(0, -V2, -V0),	vec3(0, -V2, V0),	vec3(V0, 0, V2),
	vec3(-V0, 0, V2),	vec3(V1, V1, -V1),	vec3(V1, V1, V1),
	vec3(-V1, V1, -V1),	vec3(-V1, V1, V1),	vec3(V1, -V1, -V1),
	vec3(V1, -V1, V1),	vec3(-V1, -V1, -V1)
);

/*
** IN / UNIFORMS
*/
in PoCoUvNo
{
	vec3					pos;
	vec3					col;
	vec2					tex;
	vec3					nor;
}							fs_in;
uniform samplerCube			depthMap;
uniform sampler2D			ourTexture;
uniform float				far;
uniform vec3				viewPos;
uniform float				mixval;
uniform struct Light {
	vec3					pos;

	vec3					a;
	vec3					d;
	vec3					s;

	float					linear;
	float					quadratic;
}							l;

/*
** OUT
*/
out vec4					color;

float					sample_shadows(
	float dFraLi, vec3 vLiToFra, float weight, float radius)
{
	float	shadow;
	
	shadow = 0.f;
	for (int i = 0; i < NSAMPLESI; ++i)
	{
		if (dFraLi - BIAS
			> texture(depthMap, vLiToFra + SAMPLES[i] * radius).r * far)
		{
			shadow += weight;
		}
	}
	return (shadow);
}

float					compute_shadows(
	float dnFraLi, float dFraLi, vec3 vLiToFra)
{
	float	shadow;
	float	samples;
	float	weight;
	float	radius;

	shadow = 0.f;
	samples = 0.f;
	weight = 1.f;
	radius = INITIAL_RADIUS * sqrt(dnFraLi);
	for (int i = 0; i < NUM_SAMPLING_LOOPS; i++)
	{
		shadow += sample_shadows(dFraLi, vLiToFra, weight, radius);
		samples += NSAMPLESF * weight;
		weight /= DECAY * DECAY;
		radius *= DECAY;
	}
	return (shadow / samples);
}

void					main()
{
	vec3	vLiToFra = fs_in.pos - l.pos;
	vec3	vFraToLi = -vLiToFra;
	vec3	vnFraToLi = normalize(vFraToLi);
	vec3	vFraToCam = viewPos - fs_in.pos;
	vec3	vnFraToCam = normalize(vFraToCam);
	vec3	vnFraNormal = normalize(fs_in.nor);
	float	dFraLi = length(vLiToFra);
	float	dnFraLi = dFraLi / far;
	float	dFraCam = length(vFraToCam);
	float   attenuation = 1.f
		- (dFraLi / far)
		;
	vec3	ambient = AMBIENT_STRENGTH * l.a;
	vec3	diffuse = max(dot(vnFraNormal, vnFraToLi), 0.f)
		* DIFFUSE_STRENGTH * l.d;

	vec3	vnLiCamHalfway = normalize(vnFraToLi + vnFraToCam);
	vec3	specular =
		pow(max(dot(vnFraNormal, vnLiCamHalfway), 0.0), SPECULAR_POWER)
			* SPECULAR_STRENGTH * l.s;
	
	float	shadow = compute_shadows(dnFraLi, dFraLi, vLiToFra);

	color = mix(vec4(fs_in.col, 1.f), texture(ourTexture, fs_in.tex), mixval);
	color.rgb = pow(color.rgb, vec3(GAMMA));
	// color = vec4(fs_in.col, 1.f);
	// color = vec4(0.7, 0.7, 0.7, 1.);
	color = vec4(
		(ambient
		 + (diffuse + specular)
		 * (1.f - shadow) * attenuation)
		* color.xyz
		, color.w);
	color.rgb = pow(color.rgb, vec3(1.f / GAMMA));
}
