varying vec3 normal;

uniform vec4 light_direction;
uniform vec4 diffuse_color;
uniform vec4 light_color;

void main()
{
	float LDonN = clamp(dot(normalize(normal), normalize(vec3(light_direction.x, light_direction.y, light_direction.z))), 0.0, 1.0);
	gl_FragColor = diffuse_color * LDonN * light_color;
}