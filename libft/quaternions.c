/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 11:52:43 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/02/11 11:52:44 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector_types.h>
#include <math.h>

/*
 ** Creates quaternion using 3d vector and rotation angle
 */

t_float4    quat(const float x, const float y, const float z, const float w)
{
    float angle;

    angle = sin(w * HPI180);
    return ((t_float4){x * angle, y * angle, z * angle, cos(w * HPI180)});
}

/*
 ** Quaternion mul block calculates the product for 2 given quaternions
 ** ** qi' = aw * bi + ai * bw + aj * bk - ak * bj
 ** ** qj' = aw * bj - ai * bk + aj * bw + ak * bi
 ** ** qk' = aw * bk + ai * bj - aj * bi + ak * bw
 ** ** qw' = aw * bw - ai * bi - aj * bj - ak * bk
 */

t_float4    qmul(const t_float4 a, const t_float4 b)
{
    return ((t_float4){
        a[3] * b[0] + a[0] * b[3] + a[1] * b[2] - a[2] * b[1],
        a[3] * b[1] - a[0] * b[2] + a[1] * b[3] + a[2] * b[0],
        a[3] * b[2] + a[0] * b[1] - a[1] * b[0] + a[2] * b[3],
        a[3] * b[3] - a[0] * b[0] - a[1] * b[1] - a[2] * b[2]});
}

/*
 ** Norm of quaternion
 ** ** n = xx + yy + zz + ww
 */

float        qnorm(t_float4 x)
{
    x *= x;
    return (x[0] + x[1] + x[2] + x[3]);
}

t_float4    qinv(const t_float4 x)
{
    t_float4 c;
    double   n;

    c = quat(-x[0], -x[1], -x[2], x[3]);
    n = qnorm(x);
    return ((t_float4){c[0] / n, c[1] / n, c[2] / n, c[3] / n});
}

t_float4    qrot(const t_float4 x, const t_float4 n)
{
    return (qnormalise(qmul(qmul(n, x), qinv(n))));
}
