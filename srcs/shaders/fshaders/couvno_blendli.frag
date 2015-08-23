// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   couvno_blendli.frag                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/30 10:07:14 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/23 17:17:16 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

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
	vec3 pos;

	vec3 a;
	vec3 d;
	vec3 s;

	float linear;
	float quadratic;
}							l;

out vec4					color;

#define NSAMPLES 20
#define GN ((1 + sqrt(5.f)) / 2.f)
#define GN2 (GN * GN)
#define GN3 (GN2 * GN)

vec3					gridSamplingDisk[NSAMPLES] = vec3[](
	vec3(-GN2, -GN2, GN2), vec3(GN3, GN, 0), vec3(GN3, -GN, 0),
	vec3(-GN3, GN, 0), vec3(-GN3, -GN, 0), vec3(0, GN3, GN),
	vec3(0, GN3, -GN), vec3(GN, 0, -GN3), vec3(-GN, 0, -GN3),
	vec3(0, -GN3, -GN), vec3(0, -GN3, GN), vec3(GN, 0, GN3),
	vec3(-GN, 0, GN3), vec3(GN2, GN2, -GN2), vec3(GN2, GN2, GN2),
	vec3(-GN2, GN2, -GN2), vec3(-GN2, GN2, GN2), vec3(GN2, -GN2, -GN2),
	vec3(GN2, -GN2, GN2), vec3(-GN2, -GN2, -GN2)
);

float                   ShadowCalculation()
{
	vec3 fragToLight = fs_in.pos - l.pos;
	float currentDepth = length(fragToLight);
	float shadow = 0.0;
	float bias = 0.05;
	int samples = NSAMPLES;
	float viewDistance = length(viewPos - fs_in.pos);
	float diskRadius = 10.f / 1024.f;
	for (int i = 0; i < samples; ++i)
	{
		float closestDepth =
			texture(depthMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
		closestDepth *= far;
		if (currentDepth - bias > closestDepth)
			shadow += 1.f;
	}
	shadow = shadow / float(samples);
	return (shadow);
}

void main()
{
	float	distance = length(l.pos - fs_in.pos);
	float	attenuation = 1.0f / (1.0f + l.linear * distance +
								  l.quadratic * (distance * distance));

	// color = vec4(fs_in.col, 1.f);
	color = mix(vec4(fs_in.col, 1.f), texture(ourTexture, fs_in.tex), mixval);
	// color = vec4(0.7, 0.7, 0.7, 1.);
	// color = texture(ourTexture, fs_in.tex);
	// Ambient
	float ambientStrength = 0.25f;
	vec3 ambient = ambientStrength * l.a;

	// Diffuse
	vec3 norm = normalize(fs_in.nor);
	vec3 lightDir = normalize(l.pos - fs_in.pos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * l.d;

	// Specular
	float specularStrength = 0.6f;
	vec3 viewDir = normalize(viewPos - fs_in.pos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * l.s;

	vec3 result = (ambient + (diffuse + specular)
				   * attenuation * (1.f - ShadowCalculation())
		) * color.xyz;
	color = vec4(result, color.w);
} 
