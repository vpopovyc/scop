/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions_ext.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:22:28 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/02/11 12:22:29 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_types.h"

t_float4    quat1f(const float a)
{
    return ((t_float4){a, a, a, 1.0f});
}

t_float4    qnormalise(const t_float4 q)
{
    return (q / quat1f(qnorm(q)));
}

t_float4    qscale(const t_float4 q, float s)
{
    return ((t_float4){q[0] * s, q[1] * s, q[2] * s, q[3]});
}

t_float4	qdiv(const t_float4 q, float s)
{
    return ((t_float4){q[0] / s, q[1] / s, q[2] / s, q[3]});
}

t_float4 	qmin(const t_float4 q, float s)
{
	return ((t_float4){q[0] - s, q[1] - s, q[2] - s, q[3]});	
}
