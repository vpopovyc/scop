/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:11:29 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/27 15:11:31 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scop.h"

void preinit(t_gl *gl, t_model_data *scop_model)
{
    ft_memset(gl, 0, sizeof(t_gl));
    ft_memset(scop_model, 0, sizeof(t_model_data));
}

int main(int ac, char *av[])
{
    t_gl         gl;
    t_model_data scop_model;

    preinit(&gl, &scop_model);
    if (ac == 2)
    {
        init(&gl);
        parse_obj(av[1], &scop_model);
        compile_shaders(&gl);
        loader(&gl, &scop_model);
        handle_command(&gl);
        deinit(&gl);
    }
    return (0);
}
