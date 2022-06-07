/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_offset_f64.c
 * Description:  Floating-point vector offset
 *
 * $Date:        13 September 2021
 * $Revision:    V1.10.0
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
 @addtogroup BasicOffset
 @{
 */

/**
 @brief         Adds a constant offset to a floating-point vector.
 @param[in]     pSrc       points to the input vector
 @param[in]     offset     is the offset to be added
 @param[out]    pDst       points to the output vector
 @param[in]     blockSize  number of samples in each vector
 @return        none
 */
#if defined(ARM_MATH_NEON)
void arm_offset_f64(
                    const float64_t * pSrc,
                    float64_t offset,
                    float64_t * pDst,
                    uint32_t blockSize)
{
    uint32_t blkCnt;                               /* Loop counter */
    float64x2x2_t pDstV ;
    float64x2_t pSrcV;
    float64x2_t offsetV;
    offsetV = vsetq_lane_f64(offset, offsetV, 0);
    offsetV = vsetq_lane_f64(offset, offsetV, 1);
    
    
    
    /* Initialize blkCnt with number of samples */
    blkCnt = blockSize >> 2U;
    
    while (blkCnt > 0U)
    {
        /* C = A + offset */
        
        /* Add offset and store result in destination buffer. */
        for(int i = 0 ; i<2 ; i++)
        {
            pSrcV=vld1q_f64(pSrc+2*i);
            pDstV.val[i] = vaddq_f64(pSrcV, offsetV);
            
        }
        
        /* Decrement loop counter */
        vst1q_f64(pDst, pDstV.val[0]);
        vst1q_f64(pDst+2, pDstV.val[1]);
        pDst += 4 ;
        pSrc += 4 ;
        blkCnt--;
    }
    
    blkCnt = blockSize & 3;
    
    while (blkCnt > 0U)
    {
        /* C = A + offset */
        
        /* Add offset and store result in destination buffer. */
        *pDst++ = (*pSrc++) + offset;
        
        /* Decrement loop counter */
        blkCnt--;
    }
    
}
#else
void arm_offset_f64(
                    const float64_t * pSrc,
                    float64_t offset,
                    float64_t * pDst,
                    uint32_t blockSize)
{
    uint32_t blkCnt;                               /* Loop counter */
    
    /* Initialize blkCnt with number of samples */
    blkCnt = blockSize;
    
    while (blkCnt > 0U)
    {
        /* C = A + offset */
        
        /* Add offset and store result in destination buffer. */
        *pDst++ = (*pSrc++) + offset;
        
        /* Decrement loop counter */
        blkCnt--;
    }
    
}
#endif

/**
 @} end of BasicOffset group
 */
