/*************************************************************
 * BatSpy: Teensy 4.1 based recording device for bat sounds  *
 * ***********************************************************
 * Copyright (C) 2021 Christian Mueller                      *
 *                    chrmue44(AT)gmail{DOT}com              *
 * License: GNU GPLv3.0                                      *
 * ***********************************************************

 * ***********************************************************/
#ifndef _IMRXT_HW_H
#define _IMRXT_HW_H

extern int CCM_CS1CDR;
#define CCM_CS1CDR_SAI1_CLK_PRED_MASK 22
#define CCM_CS1CDR_SAI1_CLK_PODF_MASK 33
#define CCM_CS1CDR_SAI1_CLK_PRED(x) (x)
#define CCM_CS1CDR_SAI1_CLK_PODF(x) (x)

#define CCM_CS1CDR_SAI3_CLK_PRED_MASK 22
#define CCM_CS1CDR_SAI3_CLK_PODF_MASK 33
#define CCM_CS1CDR_SAI3_CLK_PRED(x) (x)
#define CCM_CS1CDR_SAI3_CLK_PODF(x) (x)
#endif //#ifndef _IMRXT_HW_H
