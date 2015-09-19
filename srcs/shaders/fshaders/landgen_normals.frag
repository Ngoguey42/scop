
uniform float				land_width_canonical;
uniform float				land_width_half_canonical;
uniform float				height_factor;
uniform sampler2D			ymap;

out vec3					normap;

vec3	get_vertex_0(float map_width)
{
	return (vec3(
		(gl_FragCoord.x - land_width_half_canonical)
		, float(texture(ymap, vec2(gl_FragCoord.x, gl_FragCoord.y) / map_width)
				* height_factor)
		, gl_FragCoord.y - land_width_half_canonical
	));
}

vec3	get_vertex(float map_width, vec2 offsets)
{
	vec2	frag = vec2(gl_FragCoord.x + offsets.x, gl_FragCoord.y + offsets.y);

	return (vec3(
		frag.x - land_width_half_canonical
		, texture(ymap, vec2(frag.x, frag.y) / map_width).x
		* height_factor
		, frag.y - land_width_half_canonical
				));
}

void	main()
{
	/*
	float			map_width = textureSize(tex, 0).x;
	vec3			center = get_vertex_0(map_width);
	vec3			save1;
	vec3			save2;
	vec3			save3;

	save1 = get_vertex(map_width, vec2(+1.f, +0.f));
	*/
	return ;
}
