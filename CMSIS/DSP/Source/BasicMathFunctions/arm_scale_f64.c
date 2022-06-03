/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_scale_f64.c
 * Description:  Multiplies a floating-point vector by a scalar
 *
 * $Date:        03 June 2022
 * $Revision:    V1.10.1
 *
 * Target Processor: Cortex-M and Cortex-A cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2021 ARM Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "dsp/basic_math_functions.h"

/**
  @ingroup groupMath
 */

/**
  @addtogroup BasicScale
  @{
 */

/**
  @brief         Multiplies a floating-point vector by a scalar.
  @param[in]     pSrc       points to the input vector
  @param[in]     scale      scale factor to be applied
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
#if defined(ARM_MATH_NEON)
void arm_scale_f64(
  const float64_t *pSrc,
        float64_t scale,
        float64_t *pDst,
        uint32_t blockSize)
{
    uint32_t blkCnt;                               /* Loop counter */
    float64x2x2_t pDstVect ;
    float64x2_t pSrcVect ;

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = A * scale */
      for (int i = 0 ; i < 2 ; i++){
          /*Load source value in Neon buffer*/
          pSrcVect = vld1q_f64(pSrc+2*i);
          
          /* Multiplication by scale */
          pDstVect.val[i] = vmulq_n_f64(pSrcVect, scale);
      }
      
      /* Store the result in destination */
      vst1q_f64(pDst, pDstVect.val[0]);
      vst1q_f64(pDst+2, pDstVect.val[1]);
      

      /* Update source and destination*/
      pSrc += 4;
      pDst += 4;
      /* Decrement loop counter */
      blkCnt--;
  }
    
  /* Tail */
  blkCnt = blockSize & 0x3;
  while (blkCnt > 0U)
    {
      /* C = A * scale */

      /* Scale input and store result in destination buffer. */
      *pDst++ = (*pSrc++) * scale;

      /* Decrement loop counter */
      blkCnt--;
    }


}


#else
void arm_scale_f64(
  const float64_t *pSrc,
        float64_t scale,
        float64_t *pDst,
        uint32_t blockSize)
{
  uint32_t blkCnt;                               /* Loop counter */

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

  while (blkCnt > 0U)
  {
    /* C = A * scale */

    /* Scale input and store result in destination buffer. */
    *pDst++ = (*pSrc++) * scale;

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif

/**
  @} end of BasicScale group
 */
