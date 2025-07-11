/**
	Sisteme de programe pentru retele de calculatoare

	Copyright (C) 2008 Ciprian Dobre & Florin Pop
	Univerity Politehnica of Bucharest, Romania

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 */

#include <stdio.h>
#include <time.h>
#include <rpc/rpc.h>

#include "load.h"

double *
add_sum_1_svc(numbers *argp, struct svc_req *rqstp)
{
	static double  result;

	/*
	 * insert server code here
	 */

	result = argp->a + argp->b;

	return &result;
}

