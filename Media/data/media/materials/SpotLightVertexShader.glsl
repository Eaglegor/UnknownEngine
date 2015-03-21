varying vec3 normal;
varying vec3 light_direction;

uniform vec3 light_position;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	light_direction = normalize(light_position - vec3(gl_Vertex.x, gl_Vertex.y, gl_Vertex.z));
	normal = normalize(gl_Normal);
}