#version 410 core

layout (location = 0) in vec3 pos;

out vec3 _color;

uniform mat4 rotation_matrix;
uniform mat4 scale_matrix;
uniform mat4 translate_matrix;

void    main()
{
    gl_Position = translate_matrix * rotation_matrix * scale_matrix * vec4(pos.x, pos.y, pos.z, 1.0f);
    _color = vec3(pos.x < 0.0f ? pos.x + 0.9 : pos.x, pos.y < 0.0f ? pos.y + 0.7 : pos.y, pos.z < 0.0f ? pos.z + 0.6 : pos.z);
}

