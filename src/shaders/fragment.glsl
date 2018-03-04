#version 410 core

out vec4 color;

// in vec3 _color;
in vec2 tex_coord;

uniform sampler2D texture_data;

void    main()
{
    color = texture(texture_data, tex_coord);
}
