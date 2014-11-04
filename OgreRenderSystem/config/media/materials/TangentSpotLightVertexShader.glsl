varying vec3 light_direction;
varying vec3 light_central_ray;
varying vec4 texture_coordinates;

attribute vec3 tangent;
attribute vec4 uv0;

uniform vec3 light_position;
uniform vec3 light_direction_object_space;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
	vec3 binormal = cross(tangent, gl_Normal);
	
	mat3 tbn = transpose( mat3(tangent, binormal, gl_Normal) );	
	
	vec3 temp_light_direction = normalize(light_position - vec3(gl_Vertex.x, gl_Vertex.y, gl_Vertex.z));

	texture_coordinates = uv0;
	light_central_ray = tbn * light_direction_object_space;
	light_direction =  tbn * temp_light_direction;

}