varying vec3 normal;
varying vec3 light_direction;

uniform vec3 spotlight_central_ray;
uniform vec4 diffuse_color;
uniform vec4 light_color;
uniform vec4 spotlight_params;

float spotEffect(vec3 light_direction, vec3 light_central_ray)
{
	float current_effect = dot(-normalize(light_direction), normalize(light_central_ray));
	return smoothstep(spotlight_params.y, spotlight_params.x, current_effect);
}

void main()
{
	float LDonN = clamp(dot(normal, light_direction), 0.0, 1.0);
	float spot_effect = spotEffect(light_direction, spotlight_central_ray);
	gl_FragColor = diffuse_color * LDonN * light_color * spot_effect;
}