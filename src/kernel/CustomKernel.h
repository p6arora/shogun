/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 1999-2008 Soeren Sonnenburg
 * Copyright (C) 1999-2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#ifndef _CUSTOMKERNEL_H___
#define _CUSTOMKERNEL_H___

#include "lib/Mathematics.h"
#include "lib/common.h"
#include "kernel/Kernel.h"
#include "features/Features.h"

/** kernel Custom */
class CCustomKernel: public CKernel
{
	public:
		/** default constructor */
		CCustomKernel();

		/** constructor
		 *
		 * @param l features of left-hand side
		 * @param r features of right-hand side
		 */
		CCustomKernel(CFeatures* l, CFeatures* r);

		virtual ~CCustomKernel();

		/** get kernel matrix shortreal
		 *
		 * @param m dimension m of matrix
		 * @param n dimension n of matrix
		 * @param target target for kernel matrix
		 * @return the kernel matrix
		 */
		virtual SHORTREAL* get_kernel_matrix_shortreal(INT &m, INT &n, SHORTREAL* target=NULL);

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
		 * @return kernel type CUSTOM
		 */
		inline virtual EKernelType get_kernel_type() { return K_CUSTOM; }

		/** return feature type the kernel can deal with
		 *
		 * @return feature type ANY
		 */
		inline virtual EFeatureType get_feature_type() { return F_ANY; }

		/** return feature class the kernel can deal with
		 *
		 * @return feature class ANY
		 */
		inline virtual EFeatureClass get_feature_class() { return C_ANY; }

		/** return the kernel's name
		 *
		 * @return name Custom
		 */
		virtual const CHAR* get_name() { return "Custom"; }

		/** set kernel matrix (only elements from upper triangle)
		 * from elements of upper triangle (concat'd), including the
		 * main diagonal
		 *
		 * @param km kernel matrix
		 * @param len denotes the size of the array and should match len=cols*(cols+1)/2
		 * @return if setting was successful
		 */
		bool set_triangle_kernel_matrix_from_triangle(const DREAL* km, INT len);

		/** set kernel matrix (only elements from upper triangle)
		 * from squared matrix
		 *
		 * @param km kernel matrix
		 * @param rows number of rows in matrix
		 * @param cols number of cols in matrix
		 * @return if setting was successful
		 */
		bool set_triangle_kernel_matrix_from_full(const DREAL* km, INT rows, INT cols);

		/** set full kernel matrix from full kernel matrix
		 *
		 * @param km kernel matrix
		 * @param rows number of rows in matrix
		 * @param cols number of cols in matrix
		 * @return if setting was successful
		 */
		bool set_full_kernel_matrix_from_full(const DREAL* km, INT rows, INT cols);

	protected:
		/** compute kernel function
		 *
		 * @param row row
		 * @param col col
		 * @return computed kernel function
		 */
		inline virtual DREAL compute(INT row, INT col)
		{
			ASSERT(row < num_rows);
			ASSERT(col < num_cols);
			ASSERT(kmatrix);

			if (upper_diagonal)
			{
				if (row <= col)
					return kmatrix[row*num_cols - row*(row+1)/2 + col];
				else
					return kmatrix[col*num_cols - col*(col+1)/2 + row];
			}
			else
				return kmatrix[row*num_cols+col];
		}

	protected:
		/** kernel matrix */
		SHORTREAL* kmatrix;
		/** number of rows */
		INT num_rows;
		/** number of columns */
		INT num_cols;
		/** upper diagonal */
		bool upper_diagonal;
};
#endif /* _CUSTOMKERNEL_H__ */
