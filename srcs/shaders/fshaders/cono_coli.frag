// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   couvno_blendli.frag                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/30 10:07:14 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/25 15:13:13 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

/*
** CONFIG MACROES
*/
#define AMBIENT_STRENGTH 0.35f
#define SPECULAR_STRENGTH 0.10f
#define SPECULAR_POWER 32.f

#define NSAMPLESI 20
#define BIAS 0.05f
#define DECAY 1.5f
#define NUM_SAMPLING_LOOPS 3
#define INITIAL_RADIUS (300.f / 1024.f)

/*
** CALCULATED MACROES
*/
#define NSAMPLESF float(NSAMPLESI)
#define GN ((1 + sqrt(5.f)) / 2.f)
#define GN2 (GN * GN)
#define GN3 (GN2 * GN)

/*
** IN / UNIFORMS
*/
in PoCoNo
{
	vec3					pos;
	vec3					col;
	vec3					nor;
}							fs_in;
uniform samplerCube			depthMap;
uniform float				far;
uniform vec3				viewPos;
uniform struct Light {
	vec3 pos;

	vec3 a;
	vec3 d;
	vec3 s;

	float linear;
	float quadratic;
}							l;

/*
** OUT
*/
out vec4					color;

vec3						SAMPLES[NSAMPLESI] = vec3[](
	vec3(-GN2, -GN2, GN2),	vec3(GN3, GN, 0),		vec3(GN3, -GN, 0),
	vec3(-GN3, GN, 0),		vec3(-GN3, -GN, 0),		vec3(0, GN3, GN),
	vec3(0, GN3, -GN),		vec3(GN, 0, -GN3),		vec3(-GN, 0, -GN3),
	vec3(0, -GN3, -GN),		vec3(0, -GN3, GN),		vec3(GN, 0, GN3),
	vec3(-GN, 0, GN3),		vec3(GN2, GN2, -GN2),	vec3(GN2, GN2, GN2),
	vec3(-GN2, GN2, -GN2),	vec3(-GN2, GN2, GN2),	vec3(GN2, -GN2, -GN2),
	vec3(GN2, -GN2, GN2),	vec3(-GN2, -GN2, -GN2)
);

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
	float	attenuation = 1.f / (1.f
								 + l.linear * dFraLi
								 + l.quadratic * (dFraLi * dFraLi));
	vec3	ambient = AMBIENT_STRENGTH * l.a;
	vec3	diffuse = max(dot(vnFraNormal, vnFraToLi), 0.f) * l.d;
	vec3	specular =
		pow(max(dot(vnFraToCam, reflect(-vnFraToLi, vnFraNormal)), 0.0)
			, SPECULAR_POWER)
		* SPECULAR_STRENGTH * l.s;
	float	shadow = compute_shadows(dnFraLi, dFraLi, vLiToFra);

	color = vec4(fs_in.col, 1.f);
	// color = vec4(0.7, 0.7, 0.7, 1.);
	color = vec4(
		(ambient
		 + (diffuse + specular)
		 * (1.f - shadow) * attenuation)
		* color.xyz
		, color.w);
}
