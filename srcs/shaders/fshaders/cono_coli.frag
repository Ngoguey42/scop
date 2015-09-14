// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cono_coli.frag                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/12 08:25:34 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/12 08:30:04 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

/*
** CONFIG MACROES
** INITIAL_RADIUS		-> Initial sampling radius at max distance.
*/
#define AMBIENT_STRENGTH 0.05f
#define DIFFUSE_STRENGTH 2.f
#define SPECULAR_STRENGTH 0.99f
#define SPECULAR_POWER 32.f
#define GAMMA 2.2f

#define NSAMPLESI 20
#define BIAS 0.05f
#define DECAY 1.5f
#define NUM_SAMPLING_LOOPS 3
#define SBOX_RESOLUTIONF 1024.f
#define INITIAL_RADIUS (200.f / SBOX_RESOLUTIONF)

/*
** CALCULATED MACROES
** GN           ->  Gold Number
** V0           ->  Base value for a normalized dodecahedron
*/
#define NSAMPLESF float(NSAMPLESI)
#define GN ((1.f + sqrt(5.f)) / 2.f)
#define GN2 (GN * GN)
#define GN3 (GN2 * GN)
#define NORMALIZE_FACT (1 / sqrt(GN2 * GN2 * 3))
#define V0 (GN * NORMALIZE_FACT)
#define V1 (GN2 * NORMALIZE_FACT)
#define V2 (GN3 * NORMALIZE_FACT)

vec3                        SAMPLES[NSAMPLESI] = vec3[](
	vec3(-V1, -V1, V1), vec3(V2, V0, 0),    vec3(V2, -V0, 0),
	vec3(-V2, V0, 0),   vec3(-V2, -V0, 0),  vec3(0, V2, V0),
	vec3(0, V2, -V0),   vec3(V0, 0, -V2),   vec3(-V0, 0, -V2),
	vec3(0, -V2, -V0),  vec3(0, -V2, V0),   vec3(V0, 0, V2),
	vec3(-V0, 0, V2),   vec3(V1, V1, -V1),  vec3(V1, V1, V1),
	vec3(-V1, V1, -V1), vec3(-V1, V1, V1),  vec3(V1, -V1, -V1),
	vec3(V1, -V1, V1),  vec3(-V1, -V1, -V1)
);

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
	vec3 col;
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
	color = vec4(fs_in.col, 1.f);
	color.rgb = pow(color.rgb, vec3(GAMMA)); //to sRGB space
	vec3	cLight = l.col;
	cLight = pow(cLight, vec3(GAMMA)); //to sRGB space

	vec3	vLiToFra = fs_in.pos - l.pos;
	vec3	vFraToLi = -vLiToFra;
	vec3	vnFraToLi = normalize(vFraToLi);
	vec3	vFraToCam = viewPos - fs_in.pos;
	vec3	vnFraToCam = normalize(vFraToCam);
	vec3	vnFraNormal = normalize(fs_in.nor);
	float	dFraLi = length(vLiToFra);
	float	dnFraLi = dFraLi / far;
	float	dFraCam = length(vFraToCam);
	float	attenuation = 1.f - (dFraLi / far);
	float	ambient = AMBIENT_STRENGTH;
	float	diffuse = max(dot(vnFraNormal, vnFraToLi), 0.f)
		* DIFFUSE_STRENGTH;
	vec3    vnLiCamHalfway = normalize(vnFraToLi + vnFraToCam);
	float	specular =
		pow(max(dot(vnFraNormal, vnLiCamHalfway), 0.0), SPECULAR_POWER)
		* SPECULAR_STRENGTH;
	float	shadow = compute_shadows(dnFraLi, dFraLi, vLiToFra);

	color = vec4(
		(ambient + (diffuse + specular) * (1.f - shadow) * attenuation)
		* cLight * color.xyz
		, color.w);
	color.rgb = pow(color.rgb, vec3(1.f / GAMMA)); //to linear space
}
