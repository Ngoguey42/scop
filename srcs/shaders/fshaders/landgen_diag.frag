
uniform int					level_stride;
uniform int					phase_startoffset[2];
uniform vec2				random_seeds;
uniform float               land_average_y;
uniform float				land_range_y;
uniform sampler2D           tex;

layout(location = 0) out float point_y;
layout(location = 1) out vec4   color;
// out float					point_y;
// out vec4                    color;


float	ft_rand0(vec2 co)
{
	return fract(sin(dot(co.xy, vec2(12.9898f, 78.233f))) * 43758.5453f) - 0.5f;
}

void	main()
{
	if ((int(gl_FragCoord.x) - phase_startoffset[0]) % level_stride != 0
		|| (int(gl_FragCoord.y) - phase_startoffset[1]) % level_stride != 0)
	{
		discard;
		//color = vec4(0.f, 1.f, 1.f, 0.f); //debug
//		color = 0.05f;
//		return ; //debug
	}
//	 color = vec4(0.f, 0.f, 0.f, 150.f);
//	color = 1.f;
	vec2    tex_size = textureSize(tex, 0); //c'est un square noob
	

	int		stridehalf = level_stride / 2;
	color = vec4(0.f, 0.f, 1.f, 1.f);

	
	point_y =

		ft_rand0(gl_FragCoord.xy + random_seeds) * land_range_y
		+ texture(tex, vec2((int(gl_FragCoord.x) - stridehalf) / tex_size.x
							, (int(gl_FragCoord.y) - stridehalf) / tex_size.y)).x
		/ 4.f
		+ texture(tex, vec2((int(gl_FragCoord.x) + stridehalf) / tex_size.x
							, (int(gl_FragCoord.y) - stridehalf) / tex_size.y)).x
		/ 4.f
		+ texture(tex, vec2((int(gl_FragCoord.x) + stridehalf) / tex_size.x
							, (int(gl_FragCoord.y) + stridehalf) / tex_size.y)).x
		/ 4.f
		+ texture(tex, vec2((int(gl_FragCoord.x) - stridehalf) / tex_size.x
							, (int(gl_FragCoord.y) + stridehalf) / tex_size.y)).x
		/ 4.f
		;
	return ;
}
