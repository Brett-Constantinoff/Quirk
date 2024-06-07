##shader vertexShader
#version 460 core
layout (location = 0) in vec3 aPos;

out vec3 oFragPosition;

void main()
{
   gl_Position = vec4(aPos, 1.0);
}

#shader fragmentShader
#version 460 core

out vec4 fragColor;

void main()
{
   fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}