// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   uvno_uvli.frag                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/27 14:26:39 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/27 14:50:14 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

in vec2				texUV;
in vec3				Normal;
in vec3				fragPos;

out vec4			color;

uniform sampler2D	ourTexture;
uniform vec3		lightPos;
uniform vec3		viewPos;
uniform vec3		lightColor; 

void main()
{
	color = texture(ourTexture, texUV);
	// Ambient
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// Specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;
	
	vec3 result = (ambient + diffuse + specular) * color.xyz;
	color = vec4(result, color.w);
} 
