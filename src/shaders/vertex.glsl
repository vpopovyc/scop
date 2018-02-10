#version 410 core

layout (location = 0) in vec3 pos;

uniform float rot_y;
uniform vec3  rot_vec;

out vec3 _color;

mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

void    main()
{
    gl_Position = vec4(pos.x / 4, pos.y / 4, pos.z/ 4, 1.0) * rotationMatrix(rot_vec, rot_y);
    _color = vec3(pos.x < 0.0f ? pos.x + 0.9 : pos.x, pos.y < 0.0f ? pos.y + 0.7 : pos.y, pos.z < 0.0f ? pos.z + 0.6 : pos.z);
}

