/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_normals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:39:11 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/22 17:39:13 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

t_vector	normal_sphere(t_point position_on_the_surface, void *obj)
{
	t_sphere	*sp;
	t_vector	normal;

	sp = (t_sphere *)obj;
	normal = sub_vec(position_on_the_surface, sp->centre);
	normal = unit_vec(normal, length_vec(normal));
	//  There are two design decisions to make for normals. The first is
	//  whether these normals are unit length. That is convenient for shading
	//  so I will say yes, but I won’t enforce that in the code. This could
	//  allow subtle bugs, so be aware this is personal preference as are most
	//  design decisions like that.
	//
	//  second : We can set things up so that normals always point “outward”
	//  from the surface, or always point against the incident ray. This
	//  decision is determined by whether you want to determine the side of the
	//  surface at the time of geometry intersection or at the time of
	//  coloring. In this book we have more material types than we have
	//  geometry types, so we'll go for less work and put the determination at
	//  geometry time. This is simply a matter of preference, and you'll see
	//  both implementations in the literature.
	return (normal);
}

t_vector	normal_plane(t_point position, void *obj)
{
	(void)position;
	return (((t_plane *)obj)->normal);
}
