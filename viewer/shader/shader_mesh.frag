#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec3 Color;
in float Depth;

uniform vec3 light_pos;
uniform vec4 light_amb;
uniform vec4 light_diff;
uniform vec4 light_spec;
uniform float spec_power;

uniform float alpha;
uniform bool is_single_color;

out vec4 out_color;

void main(){
   vec4 my_color = vec4(Color.xyz, 1.0);
   if(Normal == vec3(0.0, 0.0, 0.0)){
       out_color = my_color;
       return;
   }
   vec3 L = light_pos - FragPos;
   vec3 V = -FragPos; // Assume view direction is vector starting from (0, 0, 0) to vertex position
   vec3 N = normalize(Normal);
   L = normalize(L);
   V = normalize(V);
   vec3 R = reflect(-L, N);

   float dot_prod = dot(N, L);
   vec4 ambient = my_color * light_amb;
   vec4 diffuse = abs(dot_prod) * light_diff * my_color;
//    vec4 specular = pow(max(dot(R, V), 0.0), spec_power) * light_spec;
//    vec4 ret_color = vec4(ambient.xyz + diffuse.xyz + specular.xyz, 1);
   vec4 ret_color = vec4(ambient.xyz + diffuse.xyz, 1);
   // vec4 ret_color = vec4(ambient.xyz, 1);
   if(is_single_color){
      out_color = vec4(0.0, 0.0, 0.0, Depth);
   }else{
      out_color = vec4(ret_color.xyz, alpha);
   }
      // out_color = vec4(Color.xyz, alpha);
}