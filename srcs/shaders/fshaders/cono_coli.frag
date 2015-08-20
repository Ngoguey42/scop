// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cono_coli.frag                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/27 18:24:49 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/20 14:16:39 by ngoguey          ###   ########.fr       //
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
float ShadowCalculation()
{
	// Get vector between fragment position and light position
	vec3 fragToLight = fs_in.pos - l.pos;
	// Use the fragment to light vector to sample from the depth map
	float closestDepth = texture(depthMap, fragToLight).r;
	// It is currently in linear range between [0,1]. Let's re-transform it back to original depth value
	closestDepth *= far;
	// Now get current linear depth as the length between the fragment and light position
	float currentDepth = length(fragToLight);
	// Now test for shadows
	float bias = 0.05; // We use a much larger bias since depth is now in [near_plane, far] range
	float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
	// color = vec4(vec3(currentDepth / far), 1.0); //debug
	// color = vec4(vec3(closestDepth / far), 1.0); //debug
	// color = vec4(vec3(currentDepth / closestDepth), 1.0); //debug
	return shadow;
}

void main()
{
	float distance    = length(l.pos - fs_in.pos);
	float attenuation = 1.0f / (1.0f + l.linear * distance +
								l.quadratic * (distance * distance));
	color = vec4(fs_in.col, 1.f);
	// color = vec4(0.7, 0.7, 0.7, 1.);
	// Ambient
	float ambientStrength = 0.6f;
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
	vec3 result = (ambient + (diffuse + specular) * (1.f - ShadowCalculation()))
		* color.xyz;
	color = vec4(result, color.w);
}
