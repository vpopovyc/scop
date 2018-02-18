/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 11:52:25 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/02/11 11:52:27 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_TYPES_H
# define __VECTOR_TYPES_H

typedef float t_float4   __attribute__((vector_size(sizeof(float)*4)));

typedef t_float4 t_axis;

# define HPI180 0.008722222222f

/*
** quaternions.c
*/

float    qnorm(t_float4 x);
t_float4 qmul(const t_float4 a, const t_float4 b);
t_float4 qinv(const t_float4 x);
t_float4 qrot(const t_float4 x, const t_float4 n);
t_float4 quat(const float x, const float y, const float z, const float w);

/*
** quaternions_ext.c
*/

t_float4 quat1f(const float a);
t_float4 qnormalise(const t_float4 q);
t_float4 qscale(const t_float4 q, float s);
t_float4 qmin(const t_float4 q, float s);
t_float4 qdiv(const t_float4 q, float s);
/*
** matrices.c
*/

void identy_m44(float *f);
void scale_m44(float s, float *m);
void translation_m44(t_float4 *d, float *m);
void quat_to_m44(t_float4 *q, float *m);


#endif
