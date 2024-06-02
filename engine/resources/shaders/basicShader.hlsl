#shader vertexShader
#version 460 core

layout(location = 0) in vec3 a_pos;

out vec4 o_color;

void main()
{
    gl_Position = vec4(a_pos, 1.0);
	o_color = vec4(a_pos, 1.0);
}

#shader fragmentShader
#version 460 core

in vec4 o_color;

out vec4 fragColor;

void main()
{
	fragColor = o_color;
}