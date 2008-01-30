/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 1999-2008 Soeren Sonnenburg
 * Copyright (C) 1999-2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#ifndef _SPARSEGAUSSIANKERNEL_H___
#define _SPARSEGAUSSIANKERNEL_H___

#include "lib/common.h"
#include "kernel/SparseKernel.h"
#include "features/SparseFeatures.h"

/** kernel SparseGaussian */
class CSparseGaussianKernel: public CSparseKernel<DREAL>
{
	public:
		/** constructor
		 *
		 * @param size cache size
		 * @param width width
		 */
		CSparseGaussianKernel(INT size, double width);

		/** constructor
		 *
		 * @param l features of left-hand side
		 * @param r features of right-hand side
		 * @param width width
		 */
		CSparseGaussianKernel(
			CSparseFeatures<DREAL>* l, CSparseFeatures<DREAL>* r,
			double width);

		virtual ~CSparseGaussianKernel();

		/** initialize kernel
		 *
		 * @param l features of left-hand side
		 * @param r features of right-hand side
		 * @return if initializing was successful
		 */
		virtual bool init(CFeatures* l, CFeatures* r);

		/** clean up kernel */
		virtual void cleanup();

		/** load kernel init_data
		 *
		 * @param src file to load from
		 * @return if loading was successful
		 */
		virtual bool load_init(FILE* src);

		/** save kernel init_data
		 *
		 * @param dest file to save to
		 * @return if saving was successful
		 */
		virtual bool save_init(FILE* dest);

		/** return what type of kernel we are
		 *
		 * @return kernel type SPARSEGAUSSIAN
		 */
		virtual EKernelType get_kernel_type() { return K_SPARSEGAUSSIAN; }

		/** return feature type the kernel can deal with
		 *
		 * @return feature type DREAL
		 */
		inline virtual EFeatureType get_feature_type() { return F_DREAL; }

		/** return the kernel's name
		 *
		 * @return name SparseGaussian
		 */
		virtual const CHAR* get_name() { return "SparseGaussian" ; } ;

	protected:
		/** compute kernel function for features a and b
		 * idx_{a,b} denote the index of the feature vectors
		 * in the corresponding feature object
		 *
		 * @param idx_a index a
		 * @param idx_b index b
		 * @return computed kernel function at indices a,b
		 */
		virtual DREAL compute(INT idx_a, INT idx_b);

	protected:
		/** width */
		double width;
		/** squared left-hand side */
		DREAL* sq_lhs;
		/** squared right-hand side */
		DREAL* sq_rhs;
};

#endif /* _SPARSEGAUSSIANKERNEL_H__ */
