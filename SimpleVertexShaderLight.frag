#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragmentColor;
in vec3 Pos;
in vec3 Norm;

uniform mat4 ViewMatrix;

vec3 light_position_world  = vec3 (0.0, 0.0, 3.0);
vec3 Ls = vec3 (1.0, 1.0, 1.0); // white specular colour
vec3 Ld = vec3 (0.7, 0.7, 0.7); // dull white diffuse light colour
vec3 La = vec3 (0.2, 0.2, 0.2); // grey ambient colour

// surface reflectance
vec3 Ks = vec3 (0.8, 0.8, 0.8); // fully reflect specular light
vec3 Kd = vec3 (0.7, 0.7, 0.7); // orange diffuse surface reflectance
vec3 Ka = vec3 (0.2, 0.2, 0.2); // fully reflect ambient light
float specular_exponent = 500.0; // specular 'power'

// Ouput data
out vec3 color;

void main(){

   vec3 Ia = La*Ka;     //ambient portion

   vec3 lp_eye = vec3 (ViewMatrix*vec4(light_position_world, 1.0));
   vec3 L = normalize(-lp_eye + Pos);
   vec3 n = normalize(Norm);
   vec3 Id = Ld*Kd*max(dot(L,n),0.0); //Diffuse portion
   
   vec3 V = normalize(Pos);
   vec3 H = normalize(L+V);
   vec3 Is = Ls*Ks*(max(pow((dot(H,n)),specular_exponent),0.0)); //specular portion
 
	// Output color = color specified in the vertex shader, 
	// interpolated between all 3 surrounding vertices
	color = fragmentColor + Id + Ia + Is;

}