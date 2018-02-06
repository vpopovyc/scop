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
    if (ac == 2)
    {
        init();
        parse_obj(av[1]);
        // TODO: Create VAO
        load_vertices_to_VBO();
        // TODO: Compile shaders
        // TODO: Draw first cube
        handle_command();
        deinit();
    }
    return (0);
}
