#version 410 core

out vec4 color;

in vec3 _color;

void    main()
{
    color = vec4(_color, 1.0f);
}

