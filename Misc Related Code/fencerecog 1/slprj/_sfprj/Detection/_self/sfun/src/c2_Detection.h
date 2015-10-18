#ifndef __c2_Detection_h__
#define __c2_Detection_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc2_DetectionInstanceStruct
#define typedef_SFc2_DetectionInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_Detection;
  real32_T c2_inData[44928];
  real32_T c2_T[44928];
  real32_T (*c2_b_T)[44928];
  real32_T (*c2_BBox_data)[4];
  int32_T (*c2_BBox_sizes)[2];
  real_T *c2_minSimilarity;
  real_T *c2_I;
  int32_T (*c2_bbox_data)[1020];
  int32_T (*c2_bbox_sizes)[2];
  uint8_T *c2_Label;
} SFc2_DetectionInstanceStruct;

#endif                                 /*typedef_SFc2_DetectionInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_Detection_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_Detection_get_check_sum(mxArray *plhs[]);
extern void c2_Detection_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
