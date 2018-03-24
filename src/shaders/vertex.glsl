#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

// out vec4 _color;
out vec2 tex_coord;

uniform mat4 rm;
uniform mat4 sm;
uniform mat4 tm;


const mat4 proj_matrix = mat4(
	1.79259f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.79259f, 0.0f, 0.0f, 
	0.0f, 0.0f, -1.002f, -1.0f,
	0.0f, 0.0f, -0.2002f, 0.0
);

void    main()
{
    gl_Position = proj_matrix * (tm * rm * sm * vec4(pos.x, pos.y, pos.z, 1.0f));
    tex_coord = uv;
}

