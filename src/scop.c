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

int main(int ac, char *av[])
{
    t_model_data scop_model;

    ft_memset(&scop_model, 0, sizeof(t_model_data));
    if (ac == 2)
    {
        init();
        parse_obj(av[1], &scop_model);
        compile_shaders();
        loader(&scop_model);
        handle_command();
        deinit();
    }
    return (0);
}
