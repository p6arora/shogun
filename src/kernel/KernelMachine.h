/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 1999-2008 Soeren Sonnenburg
 * Copyright (C) 1999-2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#ifndef _KERNEL_MACHINE_H__
#define _KERNEL_MACHINE_H__

#include "lib/common.h"
#include "kernel/Kernel.h"
#include "features/Labels.h"
#include "classifier/Classifier.h"

#include <stdio.h>

class CClassifier;

/** class KernelMachine */
class CKernelMachine : public CClassifier
{
	public:
		/** default constructor */
		CKernelMachine();

		virtual ~CKernelMachine();

		/** set kernel
		 *
		 * @param k kernel
		 */
		inline void set_kernel(CKernel* k)
		{
			SG_REF(k);
			kernel=k;
		}

		/** get kernel
		 *
		 * @return kernel
		 */
		inline CKernel* get_kernel()
		{
			SG_REF(kernel);
			return kernel;
		}

		/** set batch computation enabled
		 *
		 * @param enable if batch computation shall be enabled
		 */
		inline void set_batch_computation_enabled(bool enable)
		{
			use_batch_computation=enable;
		}

		/** check if batch computation is enabled
		 *
		 * @return if batch computation is enabled
		 */
		inline bool get_batch_computation_enabled()
		{
			return use_batch_computation;
		}

		/** set linadd enabled
		 *
		 * @param enable if linadd shall be enabled
		 */
		inline void set_linadd_enabled(bool enable)
		{
			use_linadd=enable;
		}

		/** check if linadd is enabled
		 *
		 * @return if linadd is enabled
		 */
		inline bool get_linadd_enabled()
		{
			return use_linadd ;
		}

		/** classify kernel machine
		 *
		 * @param output where resuling labels are stored
		 * @return result labels
		 */
		virtual CLabels* classify(CLabels* output=NULL);

	protected:
		/** kernel */
		CKernel* kernel;
		/** if batch computation is enabled */
		bool use_batch_computation;
		/** if linadd is enabled */
		bool use_linadd;
};

#endif /* _KERNEL_MACHINE_H__ */
