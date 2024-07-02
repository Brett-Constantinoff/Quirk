#shader vertexShader
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 oFragPos;
out vec3 oNormal;

uniform mat4 uTransform;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    oFragPos = vec3(uTransform * vec4(aPos, 1.0));
    oNormal = mat3(transpose(inverse(uTransform))) * aNormal;  
    
    gl_Position = uProjection * uView * vec4(oFragPos, 1.0);
}

#shader fragmentShader
#version 460 core

in vec3 oFragPos;
in vec3 oNormal;

uniform vec3 uDiffuse;

out vec4 oFragColor;

void main()
{
    vec3 uLightPos = vec3(1.2f, 1.0f, 2.0f);
    vec3 uLightColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 viewPos = vec3(0.0f, 0.0f, -3.0f);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * uLightColor;
  	
    // diffuse 
    vec3 norm = normalize(oNormal);
    vec3 lightDir = normalize(uLightPos - oFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * uLightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - oFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * uLightColor;  
        
    vec3 result = (ambient + diffuse) * uDiffuse;
    oFragColor = vec4(result, 1.0);
}
