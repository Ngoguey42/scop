// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cono_coli.frag                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/27 18:24:49 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/25 12:39:38 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

in PoCoNo
{
	vec3					pos;
	vec3					col;
	vec3					nor;
}							fs_in;

uniform vec3                viewPos;
uniform samplerCube			depthMap;
uniform float				far;
uniform struct Light
{
	vec3					pos;

	vec3					a;
	vec3					d;
	vec3					s;

	float					linear;
	float					quadratic;
}							l;

out vec4					color;

#define NSAMPLES 20
#define GN ((1 + sqrt(5.f)) / 2.f)
#define GN2 (GN * GN)
#define GN3 (GN2 * GN)

vec3						gridSamplingDisk[NSAMPLES] = vec3[](
	vec3(-GN2, -GN2, GN2), vec3(GN3, GN, 0), vec3(GN3, -GN, 0),
	vec3(-GN3, GN, 0), vec3(-GN3, -GN, 0), vec3(0, GN3, GN),
	vec3(0, GN3, -GN), vec3(GN, 0, -GN3), vec3(-GN, 0, -GN3),
	vec3(0, -GN3, -GN), vec3(0, -GN3, GN), vec3(GN, 0, GN3),
	vec3(-GN, 0, GN3), vec3(GN2, GN2, -GN2), vec3(GN2, GN2, GN2),
	vec3(-GN2, GN2, -GN2), vec3(-GN2, GN2, GN2), vec3(GN2, -GN2, -GN2),
	vec3(GN2, -GN2, GN2), vec3(-GN2, -GN2, -GN2)
);

float					ShadowCalculation()
{
	vec3 light_to_frag = fs_in.pos - l.pos;
	float currentDepth = length(light_to_frag);
	float shadow = 0.0;
	float bias = 0.05;
	int samples = NSAMPLES;
	float viewDistance = length(viewPos - fs_in.pos);

	float diskRadius = 20.f / 1024.f;
	for (int i = 0; i < samples; ++i)
	{
		float closestDepth =
			texture(depthMap, light_to_frag + gridSamplingDisk[i] * diskRadius).r;
		closestDepth *= far;
		if (currentDepth - bias > closestDepth)
			shadow += 1.f;
	}
	shadow = shadow / float(samples);
	return (shadow);
}

#define AMBIENT_STRENGTH 0.05f
#define SPECULAR_STRENGTH 0.5f

void					main()
{
	vec3		v_LiToFra = fs_in.pos - l.pos;
	vec3		v_FraToLi = -v_LiToFra;
	vec3		vn_FraToLi = normalize(v_FraToLi);
	float		d_FraLi = length(v_LiToFra);
	float		attenuation = 1.f / (1.f
									 + l.linear * d_FraLi
									 + l.quadratic * (d_FraLi * d_FraLi));
	
	color = vec4(fs_in.col, 1.f);
	// color = vec4(0.7, 0.7, 0.7, 1.);
	// Ambient
	vec3		ambient = AMBIENT_STRENGTH * l.a;

	// Diffuse
	vec3		vn_FraNormal = normalize(fs_in.nor);
	vec3		diffuse = max(dot(vn_FraNormal, vn_FraToLi), 0.f) * l.d;

	// Specular
	vec3		vn_FraToCam = normalize(viewPos - fs_in.pos);
	vec3 reflectDir = reflect(-vn_FraToLi, vn_FraNormal);
	float spec = pow(max(dot(vn_FraToCam, reflectDir), 0.0), 32);
	vec3 specular = SPECULAR_STRENGTH * spec * l.s;
	// vec3 specular = SPECULAR_STRENGTH * spec * vec3(1.f, 0.f, 0.f);

	// attenuation
	vec3 result = (ambient + (diffuse + specular)
				   * (1.f - ShadowCalculation()) * attenuation)
		* color.xyz;
	color = vec4(result, color.w);
}
