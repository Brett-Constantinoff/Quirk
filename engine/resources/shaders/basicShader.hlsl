##shader vertexShader
#version 460 core
layout (location = 0) in vec3 aPos;

uniform mat4 uTransform;
uniform mat4 uProjection;
uniform mat4 uView;

out vec3 oFragPosition;

void main()
{
   gl_Position = uProjection * uView * uTransform * vec4(aPos, 1.0);
}

#shader fragmentShader
#version 460 core

uniform vec3 uDiffuse;

out vec4 fragColor;

void main()
{
   fragColor = vec4(uDiffuse, 1.0f);
}