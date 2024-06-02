##shader vertexShader
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 oFragPosition;
out vec3 oColor;

void main()
{
   gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
   oFragPosition = (uModel * vec4(aPos, 1.0)).xyz;
   oColor = aColor;
}

#shader fragmentShader
#version 460 core

in vec3 oFragPosition;
in vec3 oColor;

out vec4 fragColor;

void main()
{
   fragColor = vec4(oColor, 1.0);
}