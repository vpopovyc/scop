#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

// out vec3 _color;
out vec2 tex_coord;

uniform mat4 rotation_matrix;
uniform mat4 scale_matrix;
uniform mat4 translate_matrix;


const mat4 proj_matrix = mat4(
	1.79259f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.79259f, 0.0f, 0.0f, 
	0.0f, 0.0f, -1.002f, -1.0f,
	0.0f, 0.0f, -0.2002f, 0.0
);

void    main()
{
    gl_Position = proj_matrix * (translate_matrix * rotation_matrix * scale_matrix * vec4(pos.x, pos.y, pos.z, 1.0f));
    // _color = vec3(pos.x < 0.0f ? pos.x + 0.9 : pos.x, pos.y < 0.0f ? pos.y + 0.7 : pos.y, pos.z < 0.0f ? pos.z + 0.6 : pos.z);
    tex_coord = vec2(uv.x, 1.0f - uv.y);
}

