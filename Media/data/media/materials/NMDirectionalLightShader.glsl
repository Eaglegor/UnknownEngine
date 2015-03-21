varying vec3 light_direction;
varying vec4 texture_coordinates;

uniform vec4 light_color;

uniform sampler2D diffuse_map;
uniform sampler2D normal_map;

void main()
{
	vec4 normal = texture2D(normal_map, texture_coordinates);
	vec4 diffuse = texture2D(diffuse_map, texture_coordinates);
	float LDotN = clamp(dot( normalize(vec3(normal.x, normal.y, normal.z)), normalize(light_direction)), 0.0, 1.0);
	gl_FragColor = diffuse * LDotN * light_color;
}