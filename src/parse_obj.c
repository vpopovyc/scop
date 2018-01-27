/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 17:43:18 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/27 17:43:40 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scop.h"
#include "../parse_obj.h"

int flush(void *buffer)
{
    memset(buffer, 0, 512);
    return (1);
}

void process_mtl_lib(void)
{
    perror("Not implemented");
    assert(0);
}

void process_face(void)
{
    perror("Not implemented");
    assert(0);
}

void process_vertex(void)
{
    // TODO: Process vertices array creation, appending
    perror("Not implemented");
    assert(0);
}

void parse_obj(const char *file_path)
{
    FILE    *fp;
    char    type;
    char    buffer[512];

    assert(fp = fopen(file_path, "r"));
    while (flush(buffer) && fscanf(fp, "%511[^\n]\n", buffer) != EOF)
    {
        sscanf(buffer, "%1c", &type);
        if (type == comment)
        {
            printf(">%s\n", buffer + 1);
        }
        else if (type == object_name)
        {
            printf("> Object: %s\n", buffer + 2);
        }
        else if (type == mtllib)
        {
            process_mtl_lib();
        }
        else if (type == face)
        {
            process_face();
        }
        else if (type == vertex)
        {
            process_vertex();
        }
        else
        {
            perror("Unexpected type, skipping it\n");
        }
    }
    fclose(fp);
}
