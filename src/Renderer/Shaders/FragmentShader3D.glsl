#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec4 lightColor;

layout (std140) uniform MaterialProperties3D {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;    
    float shininess;
} material;

void main()
{
    // ambient
    vec4 ambient = lightColor * material.ambient;
      
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = lightColor * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec4 specular = lightColor * (spec * material.specular);  
    
    vec4 result = ambient + diffuse + specular;
    FragColor = vec4(result.rgb, material.diffuse.a);
}