#version 410 core

out vec4 color;

in vec2 tex_coord;
in vec3 world_pos;
in vec3 world_normal;

uniform sampler2D texture_data;

const float material_kd = 0.8f;
const float material_ka = 0.1;
const float gamma = 1/2.2;
const vec3 light_position = vec3(80.0f, 80.0f, 80.0f);

void    main()
{
    vec3 light_ray = normalize(light_position - world_pos);
    float diffuse = max(dot(light_ray, world_normal), 0.0f) * material_kd;
    float ambient = material_ka;
    float gamma_corrected_light = pow((diffuse + ambient), gamma);
    color = texture(texture_data, tex_coord) * gamma_corrected_light;
}
