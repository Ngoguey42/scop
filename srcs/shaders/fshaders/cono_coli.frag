// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cono_coli.frag                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/27 18:24:49 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/23 16:11:58 by ngoguey          ###   ########.fr       //
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

// float ShadowCalculation()
// {
// 	vec3 fragToLight = fs_in.pos - l.pos;
// 	float closestDepth = texture(depthMap, fragToLight).r;
// 	closestDepth *= far;
// 	float currentDepth = length(fragToLight);
// 	float bias = 0.05f;
// 	float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
// 	return shadow;
// }

#define NSAMPLES 20

vec3					gridSamplingDisk[NSAMPLES] = vec3[](
	// vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1),
	// vec3(1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
	// vec3(1, 1, 0), vec3(1, -1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
	// vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(-1, 0, -1),
	// vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1)
	vec3(-0.57735, -0.57735, 0.57735),
	vec3(0.934172, 0.356822, 0),
	vec3(0.934172, -0.356822, 0),
	vec3(-0.934172, 0.356822, 0),
	vec3(-0.934172, -0.356822, 0),
	vec3(0, 0.934172, 0.356822),
	vec3(0, 0.934172, -0.356822),
	vec3(0.356822, 0, -0.934172),
	vec3(-0.356822, 0, -0.934172),
	vec3(0, -0.934172, -0.356822),
	vec3(0, -0.934172, 0.356822),
	vec3(0.356822, 0, 0.934172),
	vec3(-0.356822, 0, 0.934172),
	vec3(0.57735, 0.57735, -0.57735),
	vec3(0.57735, 0.57735, 0.57735),
	vec3(-0.57735, 0.57735, -0.57735),
	vec3(-0.57735, 0.57735, 0.57735),
	vec3(0.57735, -0.57735, -0.57735),
	vec3(0.57735, -0.57735, 0.57735),
	vec3(-0.57735, -0.57735, -0.57735)
	);

float					ShadowCalculation()
{
	vec3 fragToLight = fs_in.pos - l.pos;
	float currentDepth = length(fragToLight);
	float shadow = 0.0;
	float bias = 0.15;
	int samples = NSAMPLES;
	float viewDistance = length(viewPos - fs_in.pos);
	
	float diskRadius = (1.0 + (viewDistance / far)) / 25.f;
	for (int i = 0; i < samples; ++i)
	{
		float closestDepth =
			texture(depthMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
		closestDepth *= far;
		if (currentDepth - bias > closestDepth)
			shadow += 1.0;
	}
	shadow = shadow / float(samples);
	return (shadow);
}

void					main()
{
	float distance    = length(l.pos - fs_in.pos);
	float attenuation = 1.0f / (1.0f + l.linear * distance +
								l.quadratic * (distance * distance));
	color = vec4(fs_in.col, 1.f);
	// color = vec4(0.7, 0.7, 0.7, 1.);
	// Ambient
	float ambientStrength = 0.4f;
	vec3 ambient = ambientStrength * l.a;

	// Diffuse
	vec3 norm = normalize(fs_in.nor);
	vec3 lightDir = normalize(l.pos - fs_in.pos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * l.d;

	// Specular
	float specularStrength = 0.25f;
	vec3 viewDir = normalize(viewPos - fs_in.pos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * l.s;

	// attenuation
	vec3 result =
		// (ambientStrength * (1.f - ShadowCalculation()))
		(ambient + (diffuse + specular)
		 * (1.f - ShadowCalculation()) * attenuation)
		* color.xyz;
	color = vec4(result, color.w);
}
