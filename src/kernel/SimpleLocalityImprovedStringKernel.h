/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 1999-2008 Gunnar Raetsch
 * Copyright (C) 1999-2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#ifndef _SIMPLELOCALITYIMPROVEDSTRINGKERNEL_H___
#define _SIMPLELOCALITYIMPROVEDSTRINGKERNEL_H___

#include "lib/common.h"
#include "kernel/StringKernel.h"

/** kernel SimpleLocalityImprovedString */
class CSimpleLocalityImprovedStringKernel: public CStringKernel<CHAR>
{
	public:
		/** constructor
		 *
		 * @param size cache size
		 * @param length length
		 * @param inner_degree inner degree
		 * @param outer_degree outer degree
		 */
		CSimpleLocalityImprovedStringKernel(int size, INT length,
			INT inner_degree, INT outer_degree);

		/** constructor
		 *
		 * @param l features of left-hand side
		 * @param r features of right-hand side
		 * @param length length
		 * @param inner_degree inner degree
		 * @param outer_degree outer degree
		 */
		CSimpleLocalityImprovedStringKernel(
			CStringFeatures<CHAR>* l, CStringFeatures<CHAR>* r,
			INT length, INT inner_degree, INT outer_degree);

		virtual ~CSimpleLocalityImprovedStringKernel();

		/** initialize kernel
		 *
		 * @param l features of left-hand side
		 * @param r features of right-hand side
		 * @return if initializing was successful
		 */
		virtual bool init(CFeatures *l, CFeatures *r);

		/** clean up kernel */
		virtual void cleanup();

		/** load kernel init_data
		 *
		 * @param src file to load from
		 * @return if loading was successful
		 */
		bool load_init(FILE *src);

		/** save kernel init_data
		 *
		 * @param dest file to save to
		 * @return if saving was successful
		 */
		bool save_init(FILE *dest);

		/** return what type of kernel we are
		 *
		 * @return kernel type SIMPLELOCALITYIMPROVED
		 */
		virtual EKernelType get_kernel_type()
		{
			return K_SIMPLELOCALITYIMPROVED;
		}

		/** return the kernel's name
		 *
		 * @return name SimpleLocalityImproved
		 */
		virtual const CHAR *get_name()
		{
			return "SimpleLocalityImproved";
		}

	private:
		/** dot pyr
		 *
		 * @param x1 x1
		 * @param x2 x2
		 * @param NOF_NTS NOF NTS
		 * @param NTWIDTH NT width
		 * @param DEGREE1 degree 1
		 * @param DEGREE2 degree 2
		 * @param stage1 stage 1
		 * @param pyra pyramid
		 * @return dot product of pyramid (?)
		 */
		DREAL dot_pyr (const CHAR* const x1, const CHAR* const x2,
				const INT NOF_NTS, const INT NTWIDTH,
				const INT DEGREE1, const INT DEGREE2, CHAR *stage1,
				DREAL *pyra);

	protected:
		/** compute kernel function for features a and b
		 * idx_{a,b} denote the index of the feature vectors
		 * in the corresponding feature object
		 *
		 * @param idx_a index a
		 * @param idx_b index b
		 * @return computed kernel function at indices a,b
		 */
		DREAL compute(INT idx_a, INT idx_b);

	protected:
		/** length */
		INT length;
		/** inner degree */
		INT inner_degree;
		/** outer degree */
		INT outer_degree;
		/** match */
		CHAR* match;
		/** pyramid weights */
		DREAL *pyramid_weights;
};

#endif /* _SIMPLELOCALITYIMPROVEDSTRINGKERNEL_H___ */
