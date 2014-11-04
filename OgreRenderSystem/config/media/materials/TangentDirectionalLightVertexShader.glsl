varying vec3 light_direction;
varying vec4 texture_coordinates;

attribute vec3 tangent;
attribute vec4 uv0;

uniform vec3 light_position;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
	vec3 binormal = cross(tangent, gl_Normal);
	
	mat3 tbn = transpose( mat3(tangent, binormal, gl_Normal) );	
	
	texture_coordinates = uv0;
	light_direction = tbn * light_position;

}