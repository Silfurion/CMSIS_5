/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_negate_f64.c
 * Description:  Negates floating-point vectors
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
  @addtogroup BasicNegate
  @{
 */

/**
  @brief         Negates the elements of a floating-point vector.
  @param[in]     pSrc       points to input vector.
  @param[out]    pDst       points to output vector.
  @param[in]     blockSize  number of samples in each vector.
  @return        none
 */
/*#if defined(ARM_MATH_NEON)
void arm_negate_f64(
  const float64_t * pSrc,
        float64_t * pDst,
        uint32_t blockSize)
{
  uint32_t blkCnt;

    float64x2_t pSrcV ;
    float64x2x4_t pDestV;
  blkCnt = blockSize >> 3U;

  while (blkCnt > 0U)
  {
      for(int i = 0 ; i<4 ; i++){
          pSrcV = vld1q_f64(pSrc+2*i);
          pDestV.val[i] = vnegq_f64(pSrcV);
      }
      vst1q_f64(pDst, pDestV.val[0]);
      vst1q_f64(pDst+2, pDestV.val[1]);
      vst1q_f64(pDst+4, pDestV.val[2]);
      vst1q_f64(pDst+6, pDestV.val[3]);
      pDst+=8;
      pSrc+=8;

    blkCnt--;
  }
    
    blkCnt = blockSize & 7;

    while (blkCnt > 0U)
    {

      *pDst++ = -*pSrc++;

      blkCnt--;
    }
    

}
#else
 */
void arm_negate_f64(
  const float64_t * pSrc,
        float64_t * pDst,
        uint32_t blockSize)
{
  uint32_t blkCnt;                               /* Loop counter */

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

  while (blkCnt > 0U)
  {
    /* C = -A */

    /* Negate and store result in destination buffer. */
    *pDst++ = -*pSrc++;

    /* Decrement loop counter */
    blkCnt--;
  }

}
//#endif

/**
  @} end of BasicNegate group
 */
