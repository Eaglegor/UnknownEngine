varying vec3 light_direction;
varying vec3 light_central_ray;
varying vec4 texture_coordinates;

uniform vec4 light_color;
uniform vec4 spotlight_params;

uniform sampler2D diffuse_map;
uniform sampler2D normal_map;

float spotEffect(vec3 light_direction, vec3 light_central_ray)
{
	float current_effect = dot(-normalize(light_direction), normalize(light_central_ray));
	return smoothstep(spotlight_params.y, spotlight_params.x, current_effect);
}

void main()
{
	vec4 normal = texture2D(normal_map, texture_coordinates);
	vec4 diffuse = texture2D(diffuse_map, texture_coordinates);
	float LDotN = clamp(dot( normalize(vec3(normal.x, normal.y, normal.z)), normalize(light_direction)), 0.0, 1.0);
	float spot_effect = spotEffect(light_direction, light_central_ray);
	gl_FragColor = diffuse * LDotN * light_color * spot_effect;
}