/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_add_f64.c
 * Description:  Floating-point vector addition
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
  @addtogroup BasicAdd
  @{
 */

/**
  @brief         Floating-point vector addition.
  @param[in]     pSrcA      points to first input vector
  @param[in]     pSrcB      points to second input vector
  @param[out]    pDst       points to output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
#if defined(ARM_MATH_NEON)
void arm_add_f64(
  const float64_t * pSrcA,
  const float64_t * pSrcB,
        float64_t * pDst,
        uint32_t blockSize)
{
    uint32_t blkCnt;                               /* Loop counter */
    float64x2_t pSrcAV;
    float64x2_t pSrcBV;
    float64x2x2_t pDestV;

  /* Initialize blkCnt with number of samples */
    blkCnt = blockSize >> 2U;
    
    while (blkCnt > 0U)
    {
        /* C = A + B */

        for(int i = 0 ; i< 2 ; i++)
        {
          /* Load source value in Neon buffer */
            pSrcAV = vld1q_f64(pSrcA+2*i);
            pSrcBV = vld1q_f64(pSrcB+2*i);
            
            /* Sum value with Neon method */
            pDestV.val[i] = vaddq_f64(pSrcAV, pSrcBV);
        }
        
        /* Store result in dst */
        vst1q_f64(pDst,pDestV.val[0]);
        vst1q_f64(pDst+2, pDestV.val[1]);
        
        /* Increment Source and destination */
        pSrcA+=4;
        pSrcB+=4;
        pDst+=4;

        /* Decrement loop counter */
        blkCnt--;
        
    }
    /* Tail */
    blkCnt = blockSize & 3;
    
    while( blkCnt > 0U)
    {
        /* Add and store result in destination buffer. */
        *pDst++ = (*pSrcA++) + (*pSrcB++);

        /* Decrement loop counter */
        blkCnt--;
    }

}

#else
void arm_add_f64(
  const float64_t * pSrcA,
  const float64_t * pSrcB,
        float64_t * pDst,
        uint32_t blockSize)
{
  uint32_t blkCnt;                               /* Loop counter */

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

  while (blkCnt > 0U)
  {
    /* C = A + B */

    /* Add and store result in destination buffer. */
    *pDst++ = (*pSrcA++) + (*pSrcB++);

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif
/**
  @} end of BasicAdd group
 */
