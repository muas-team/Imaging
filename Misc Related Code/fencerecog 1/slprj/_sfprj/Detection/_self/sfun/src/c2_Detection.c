/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Detection_sfun.h"
#include "c2_Detection.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Detection_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c2_debug_family_names[37] = { "numImgRows", "numImgCols",
  "numTmpRows", "numTmpCols", "numTemplates", "numBBox", "feature", "idx",
  "bestSimilarity", "stepRows", "stepCols", "startColList", "endColList",
  "startRowList", "endRowList", "startCol", "endCol", "ratioCols", "startRow",
  "endRow", "ratioRows", "colSrcFlt", "col", "colSrc", "rowSrcFlt", "row",
  "rowSrc", "iTmp", "similarity", "nargin", "nargout", "T", "minSimilarity", "I",
  "bbox", "Label", "BBox" };

/* Function Declarations */
static void initialize_c2_Detection(SFc2_DetectionInstanceStruct *chartInstance);
static void initialize_params_c2_Detection(SFc2_DetectionInstanceStruct
  *chartInstance);
static void enable_c2_Detection(SFc2_DetectionInstanceStruct *chartInstance);
static void disable_c2_Detection(SFc2_DetectionInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_Detection(SFc2_DetectionInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_Detection(SFc2_DetectionInstanceStruct
  *chartInstance);
static void set_sim_state_c2_Detection(SFc2_DetectionInstanceStruct
  *chartInstance, const mxArray *c2_st);
static void finalize_c2_Detection(SFc2_DetectionInstanceStruct *chartInstance);
static void sf_gateway_c2_Detection(SFc2_DetectionInstanceStruct *chartInstance);
static void mdl_start_c2_Detection(SFc2_DetectionInstanceStruct *chartInstance);
static void c2_chartstep_c2_Detection(SFc2_DetectionInstanceStruct
  *chartInstance);
static void initSimStructsc2_Detection(SFc2_DetectionInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, real32_T
  c2_inData_data[], int32_T c2_inData_sizes[2]);
static void c2_emlrt_marshallIn(SFc2_DetectionInstanceStruct *chartInstance,
  const mxArray *c2_BBox, const char_T *c2_identifier, real32_T c2_y_data[],
  int32_T c2_y_sizes[2]);
static void c2_b_emlrt_marshallIn(SFc2_DetectionInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real32_T
  c2_y_data[], int32_T c2_y_sizes[2]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, real32_T c2_outData_data[],
  int32_T c2_outData_sizes[2]);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_b_inData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, int32_T
  c2_inData_data[], int32_T c2_inData_sizes[2]);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_b_inData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_b_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_DetectionInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_b_inData);
static real32_T c2_d_emlrt_marshallIn(SFc2_DetectionInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_b_inData);
static void c2_e_emlrt_marshallIn(SFc2_DetectionInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real32_T c2_y[3]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_b_inData);
static void c2_f_emlrt_marshallIn(SFc2_DetectionInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real32_T c2_y[7488]);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(const mxArray **c2_info);
static const mxArray *c2_emlrt_marshallOut(const char * c2_u);
static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_u);
static real32_T c2_floor(SFc2_DetectionInstanceStruct *chartInstance, real32_T
  c2_x);
static void c2_eml_scalar_eg(SFc2_DetectionInstanceStruct *chartInstance);
static void c2_b_eml_scalar_eg(SFc2_DetectionInstanceStruct *chartInstance);
static real32_T c2_mean(SFc2_DetectionInstanceStruct *chartInstance, real32_T
  c2_x[7488]);
static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_b_inData);
static int32_T c2_g_emlrt_marshallIn(SFc2_DetectionInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_h_emlrt_marshallIn(SFc2_DetectionInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_Detection, const char_T *c2_identifier);
static uint8_T c2_i_emlrt_marshallIn(SFc2_DetectionInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_floor(SFc2_DetectionInstanceStruct *chartInstance, real32_T
  *c2_x);
static void init_dsm_address_info(SFc2_DetectionInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc2_DetectionInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_Detection(SFc2_DetectionInstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_is_active_c2_Detection = 0U;
}

static void initialize_params_c2_Detection(SFc2_DetectionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_Detection(SFc2_DetectionInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_Detection(SFc2_DetectionInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_Detection(SFc2_DetectionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_Detection(SFc2_DetectionInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_u_sizes[2];
  int32_T c2_u;
  int32_T c2_b_u;
  int32_T c2_loop_ub;
  int32_T c2_i0;
  real32_T c2_u_data[4];
  const mxArray *c2_b_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_c_u;
  const mxArray *c2_c_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(2, 1), false);
  c2_u_sizes[0] = 1;
  c2_u_sizes[1] = (*chartInstance->c2_BBox_sizes)[1];
  c2_u = c2_u_sizes[0];
  c2_b_u = c2_u_sizes[1];
  c2_loop_ub = (*chartInstance->c2_BBox_sizes)[0] *
    (*chartInstance->c2_BBox_sizes)[1] - 1;
  for (c2_i0 = 0; c2_i0 <= c2_loop_ub; c2_i0++) {
    c2_u_data[c2_i0] = (*chartInstance->c2_BBox_data)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u_data, 1, 0U, 1U, 0U, 2,
    c2_u_sizes[0], c2_u_sizes[1]), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_Detection;
  c2_c_u = c2_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_c_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_Detection(SFc2_DetectionInstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  int32_T c2_tmp_sizes[2];
  real32_T c2_tmp_data[4];
  int32_T c2_i1;
  int32_T c2_i2;
  int32_T c2_loop_ub;
  int32_T c2_i3;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)), "BBox",
                      c2_tmp_data, c2_tmp_sizes);
  ssSetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1, 0, 1);
  ssSetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1, 1, c2_tmp_sizes
    [1]);
  c2_i1 = (*chartInstance->c2_BBox_sizes)[0];
  c2_i2 = (*chartInstance->c2_BBox_sizes)[1];
  c2_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
  for (c2_i3 = 0; c2_i3 <= c2_loop_ub; c2_i3++) {
    (*chartInstance->c2_BBox_data)[c2_i3] = c2_tmp_data[c2_i3];
  }

  chartInstance->c2_is_active_c2_Detection = c2_h_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 1)), "is_active_c2_Detection");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_Detection(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_Detection(SFc2_DetectionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_Detection(SFc2_DetectionInstanceStruct *chartInstance)
{
  int32_T c2_i4;
  int32_T c2_loop_ub;
  int32_T c2_i5;
  int32_T c2_b_loop_ub;
  int32_T c2_i6;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i4 = 0; c2_i4 < 44928; c2_i4++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c2_b_T)[c2_i4], 0U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_Detection(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_DetectionMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  c2_loop_ub = (*chartInstance->c2_BBox_sizes)[0] *
    (*chartInstance->c2_BBox_sizes)[1] - 1;
  for (c2_i5 = 0; c2_i5 <= c2_loop_ub; c2_i5++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c2_BBox_data)[c2_i5], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_minSimilarity, 2U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_I, 3U);
  c2_b_loop_ub = (*chartInstance->c2_bbox_sizes)[0] *
    (*chartInstance->c2_bbox_sizes)[1] - 1;
  for (c2_i6 = 0; c2_i6 <= c2_b_loop_ub; c2_i6++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c2_bbox_data)[c2_i6], 4U);
  }

  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c2_Label, 5U);
}

static void mdl_start_c2_Detection(SFc2_DetectionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_chartstep_c2_Detection(SFc2_DetectionInstanceStruct
  *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_b_hoistedGlobal;
  uint8_T c2_c_hoistedGlobal;
  int32_T c2_i7;
  real_T c2_b_minSimilarity;
  real_T c2_b_I;
  int32_T c2_b_bbox_sizes[2];
  int32_T c2_bbox;
  int32_T c2_b_bbox;
  int32_T c2_loop_ub;
  int32_T c2_i8;
  int32_T c2_b_bbox_data[1020];
  uint8_T c2_b_Label;
  uint32_T c2_debug_family_var_map[37];
  real32_T c2_numImgRows;
  real32_T c2_numImgCols;
  real32_T c2_numTmpRows;
  real32_T c2_numTmpCols;
  real32_T c2_numTemplates;
  real32_T c2_numBBox;
  real32_T c2_feature[7488];
  real32_T c2_idx;
  real32_T c2_bestSimilarity;
  real32_T c2_stepRows;
  real32_T c2_stepCols;
  real32_T c2_startColList[3];
  real32_T c2_endColList[3];
  real32_T c2_startRowList[3];
  real32_T c2_endRowList[3];
  real32_T c2_startCol;
  real32_T c2_endCol;
  real32_T c2_ratioCols;
  real32_T c2_startRow;
  real32_T c2_endRow;
  real32_T c2_ratioRows;
  real32_T c2_colSrcFlt;
  real32_T c2_col;
  real32_T c2_colSrc;
  real32_T c2_rowSrcFlt;
  real32_T c2_row;
  real32_T c2_rowSrc;
  real32_T c2_iTmp;
  real32_T c2_similarity;
  real_T c2_nargin = 5.0;
  real_T c2_nargout = 1.0;
  int32_T c2_b_BBox_sizes[2];
  real32_T c2_b_BBox_data[4];
  int32_T c2_i9;
  int32_T c2_b_numBBox[2];
  int32_T c2_tmp_sizes[2];
  int32_T c2_i10;
  int32_T c2_i11;
  int32_T c2_b_loop_ub;
  int32_T c2_i12;
  real32_T c2_tmp_data[1020];
  int32_T c2_BBox;
  int32_T c2_b_BBox;
  int32_T c2_c_loop_ub;
  int32_T c2_i13;
  real32_T c2_c_numBBox;
  int32_T c2_i14;
  int32_T c2_b_idx;
  real_T c2_d0;
  real_T c2_d1;
  real32_T c2_A;
  real32_T c2_x;
  real32_T c2_b_x;
  real32_T c2_c_x;
  real32_T c2_y;
  real32_T c2_f0;
  real32_T c2_b_A;
  real32_T c2_d_x;
  real32_T c2_e_x;
  real32_T c2_f_x;
  real32_T c2_b_y;
  real32_T c2_f1;
  int32_T c2_i15;
  real32_T c2_varargin_2;
  real32_T c2_varargin_3;
  real32_T c2_c_y;
  real32_T c2_d_y;
  real32_T c2_yk;
  real32_T c2_e_y;
  real32_T c2_b;
  boolean_T c2_p;
  real32_T c2_maxval;
  real32_T c2_b_varargin_2;
  real32_T c2_b_varargin_3;
  real32_T c2_f_y;
  real32_T c2_g_y;
  real32_T c2_b_yk;
  real32_T c2_h_y;
  real32_T c2_minval;
  int32_T c2_i16;
  int64_T c2_i17;
  int64_T c2_i18;
  real32_T c2_c_varargin_2;
  real32_T c2_c_varargin_3;
  real32_T c2_i_y;
  real32_T c2_j_y;
  real32_T c2_c_yk;
  real32_T c2_k_y;
  real32_T c2_b_b;
  boolean_T c2_b_p;
  real32_T c2_b_maxval;
  real32_T c2_d_varargin_2;
  real32_T c2_d_varargin_3;
  real32_T c2_l_y;
  real32_T c2_m_y;
  real32_T c2_d_yk;
  real32_T c2_n_y;
  real32_T c2_b_minval;
  int32_T c2_i19;
  real32_T c2_e_varargin_2;
  real32_T c2_e_varargin_3;
  real32_T c2_o_y;
  real32_T c2_p_y;
  real32_T c2_e_yk;
  real32_T c2_q_y;
  real32_T c2_c_b;
  boolean_T c2_c_p;
  real32_T c2_c_maxval;
  real32_T c2_f_varargin_2;
  real32_T c2_f_varargin_3;
  real32_T c2_r_y;
  real32_T c2_s_y;
  real32_T c2_f_yk;
  real32_T c2_t_y;
  real32_T c2_c_minval;
  int32_T c2_i20;
  int64_T c2_i21;
  int64_T c2_i22;
  real32_T c2_g_varargin_2;
  real32_T c2_g_varargin_3;
  real32_T c2_u_y;
  real32_T c2_v_y;
  real32_T c2_g_yk;
  real32_T c2_w_y;
  real32_T c2_d_b;
  boolean_T c2_d_p;
  real32_T c2_d_maxval;
  real32_T c2_h_varargin_2;
  real32_T c2_h_varargin_3;
  real32_T c2_x_y;
  real32_T c2_y_y;
  real32_T c2_h_yk;
  real32_T c2_ab_y;
  real32_T c2_d_minval;
  int32_T c2_i23;
  real32_T c2_b_startColList[3];
  int32_T c2_b_startCol;
  int32_T c2_i24;
  real32_T c2_b_endColList[3];
  int32_T c2_b_endCol;
  real32_T c2_c_A;
  real32_T c2_g_x;
  real32_T c2_h_x;
  real32_T c2_i_x;
  int32_T c2_i25;
  real32_T c2_b_startRowList[3];
  int32_T c2_b_startRow;
  int32_T c2_i26;
  real32_T c2_b_endRowList[3];
  int32_T c2_b_endRow;
  real32_T c2_d_A;
  real32_T c2_j_x;
  real32_T c2_k_x;
  real32_T c2_l_x;
  int32_T c2_b_col;
  real32_T c2_f2;
  int32_T c2_b_row;
  real32_T c2_f3;
  int32_T c2_i27;
  real32_T c2_b_feature[7488];
  real32_T c2_f4;
  int32_T c2_i28;
  int32_T c2_b_iTmp;
  int32_T c2_c_col;
  int32_T c2_c_row;
  int32_T c2_i29;
  int32_T c2_i30;
  int32_T c2_d_loop_ub;
  int32_T c2_i31;
  boolean_T guard1 = false;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *chartInstance->c2_minSimilarity;
  c2_b_hoistedGlobal = *chartInstance->c2_I;
  c2_c_hoistedGlobal = *chartInstance->c2_Label;
  for (c2_i7 = 0; c2_i7 < 44928; c2_i7++) {
    chartInstance->c2_T[c2_i7] = (*chartInstance->c2_b_T)[c2_i7];
  }

  c2_b_minSimilarity = c2_hoistedGlobal;
  c2_b_I = c2_b_hoistedGlobal;
  c2_b_bbox_sizes[0] = (*chartInstance->c2_bbox_sizes)[0];
  c2_b_bbox_sizes[1] = (*chartInstance->c2_bbox_sizes)[1];
  c2_bbox = c2_b_bbox_sizes[0];
  c2_b_bbox = c2_b_bbox_sizes[1];
  c2_loop_ub = (*chartInstance->c2_bbox_sizes)[0] *
    (*chartInstance->c2_bbox_sizes)[1] - 1;
  for (c2_i8 = 0; c2_i8 <= c2_loop_ub; c2_i8++) {
    c2_b_bbox_data[c2_i8] = (*chartInstance->c2_bbox_data)[c2_i8];
  }

  c2_b_Label = c2_c_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 37U, 37U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_numImgRows, 0U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_numImgCols, 1U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_numTmpRows, 2U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_numTmpCols, 3U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_numTemplates, 4U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_numBBox, 5U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_feature, 6U, c2_h_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_idx, 7U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_bestSimilarity, 8U,
    c2_f_sf_marshallOut, c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_stepRows, 9U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_stepCols, 10U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_startColList, 11U, c2_g_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_endColList, 12U, c2_g_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_startRowList, 13U, c2_g_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_endRowList, 14U, c2_g_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_startCol, 15U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_endCol, 16U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_ratioCols, 17U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_startRow, 18U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_endRow, 19U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_ratioRows, 20U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_colSrcFlt, 21U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_col, 22U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_colSrc, 23U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_rowSrcFlt, 24U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_row, 25U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_rowSrc, 26U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_iTmp, 27U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_similarity, 28U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 29U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 30U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(chartInstance->c2_T, 31U, c2_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_minSimilarity, 32U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_I, 33U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN(c2_b_bbox_data, (const int32_T *)
    &c2_b_bbox_sizes, NULL, 1, 34, (void *)c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_Label, 35U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c2_b_BBox_data, (const int32_T *)
    &c2_b_BBox_sizes, NULL, 0, 36, (void *)c2_sf_marshallOut, (void *)
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 27);
  c2_numImgRows = 1.0F;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
  c2_numImgCols = 1.0F;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 29);
  c2_numTmpRows = 72.0F;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 30);
  c2_numTmpCols = 104.0F;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 31);
  c2_numTemplates = 6.0F;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 32);
  c2_numBBox = (real32_T)c2_b_bbox_sizes[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 33);
  for (c2_i9 = 0; c2_i9 < 7488; c2_i9++) {
    c2_feature[c2_i9] = 0.0F;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 34);
  c2_b_numBBox[0] = (int32_T)c2_numBBox;
  c2_b_numBBox[1] = 4;
  c2_tmp_sizes[0] = c2_b_numBBox[0];
  c2_tmp_sizes[1] = 4;
  c2_i10 = c2_tmp_sizes[0];
  c2_i11 = c2_tmp_sizes[1];
  c2_b_loop_ub = ((int32_T)c2_numBBox << 2) - 1;
  for (c2_i12 = 0; c2_i12 <= c2_b_loop_ub; c2_i12++) {
    c2_tmp_data[c2_i12] = 0.0F;
  }

  _SFD_DIM_SIZE_EQ_CHECK(1, c2_tmp_sizes[0], 1);
  c2_b_BBox_sizes[0] = c2_tmp_sizes[0];
  c2_b_BBox_sizes[1] = 4;
  c2_BBox = c2_b_BBox_sizes[0];
  c2_b_BBox = c2_b_BBox_sizes[1];
  c2_c_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
  for (c2_i13 = 0; c2_i13 <= c2_c_loop_ub; c2_i13++) {
    c2_b_BBox_data[c2_i13] = c2_tmp_data[c2_i13];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 37);
  c2_c_numBBox = c2_numBBox;
  c2_i14 = (int32_T)c2_c_numBBox - 1;
  c2_idx = 1.0F;
  c2_b_idx = 0;
  while (c2_b_idx <= c2_i14) {
    c2_idx = 1.0F + (real32_T)c2_b_idx;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 38);
    c2_bestSimilarity = 0.0F;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 40);
    (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", 4, 1, c2_b_bbox_sizes[1], 2, 0);
    c2_d0 = (real_T)c2_b_bbox_data[((int32_T)(real32_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK("bbox", (int32_T)c2_idx, 1, c2_b_bbox_sizes[0],
      1, 0) + c2_b_bbox_sizes[0] * 3) - 1];
    guard1 = false;
    if (CV_EML_COND(0, 1, 0, CV_RELATIONAL_EVAL(4U, 0U, 0, c2_d0, 72.0, -1, 5U,
          c2_d0 >= 72.0))) {
      (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", 3, 1, c2_b_bbox_sizes[1], 2, 0);
      c2_d1 = (real_T)c2_b_bbox_data[((int32_T)(real32_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("bbox", (int32_T)c2_idx, 1, c2_b_bbox_sizes
        [0], 1, 0) + (c2_b_bbox_sizes[0] << 1)) - 1];
      if (CV_EML_COND(0, 1, 1, CV_RELATIONAL_EVAL(4U, 0U, 1, c2_d1, 104.0, -1,
            5U, c2_d1 >= 104.0))) {
        CV_EML_MCDC(0, 1, 0, true);
        CV_EML_IF(0, 1, 0, true);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 42);
        (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", 4, 1, c2_b_bbox_sizes[1], 2,
          0);
        c2_A = (real32_T)c2_b_bbox_data[((int32_T)(real32_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("bbox", (int32_T)c2_idx, 1,
          c2_b_bbox_sizes[0], 1, 0) + c2_b_bbox_sizes[0] * 3) - 1];
        c2_x = c2_A;
        c2_b_x = c2_x;
        c2_c_x = c2_b_x;
        c2_y = c2_c_x / 72.0F;
        c2_f0 = c2_y;
        c2_b_floor(chartInstance, &c2_f0);
        c2_stepRows = c2_f0;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
        (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", 3, 1, c2_b_bbox_sizes[1], 2,
          0);
        c2_b_A = (real32_T)c2_b_bbox_data[((int32_T)(real32_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("bbox", (int32_T)c2_idx, 1,
          c2_b_bbox_sizes[0], 1, 0) + (c2_b_bbox_sizes[0] << 1)) - 1];
        c2_d_x = c2_b_A;
        c2_e_x = c2_d_x;
        c2_f_x = c2_e_x;
        c2_b_y = c2_f_x / 104.0F;
        c2_f1 = c2_b_y;
        c2_b_floor(chartInstance, &c2_f1);
        c2_stepCols = c2_f1;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 47);
        for (c2_i15 = 0; c2_i15 < 3; c2_i15++) {
          c2_startColList[c2_i15] = 0.0F;
        }

        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 48);
        (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", 1, 1, c2_b_bbox_sizes[1], 2,
          0);
        c2_startColList[1] = (real32_T)c2_b_bbox_data[(int32_T)(real32_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("bbox", (int32_T)c2_idx, 1,
          c2_b_bbox_sizes[0], 1, 0) - 1];
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 49);
        c2_varargin_2 = c2_startColList[1] - c2_stepCols;
        c2_varargin_3 = c2_varargin_2;
        c2_c_y = c2_varargin_3;
        c2_d_y = c2_c_y;
        c2_eml_scalar_eg(chartInstance);
        c2_yk = c2_d_y;
        c2_e_y = c2_yk;
        c2_eml_scalar_eg(chartInstance);
        c2_b = c2_e_y;
        c2_p = (1.0F < c2_b);
        if (c2_p) {
          c2_maxval = c2_e_y;
        } else {
          c2_maxval = 1.0F;
        }

        c2_startColList[0] = c2_maxval;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 50);
        c2_b_varargin_2 = c2_startColList[1] + c2_stepCols;
        c2_b_varargin_3 = c2_b_varargin_2;
        c2_f_y = c2_b_varargin_3;
        c2_g_y = c2_f_y;
        c2_b_eml_scalar_eg(chartInstance);
        c2_b_yk = c2_g_y;
        c2_h_y = c2_b_yk;
        c2_b_eml_scalar_eg(chartInstance);
        c2_minval = muSingleScalarMin(1.0F, c2_h_y);
        c2_startColList[2] = c2_minval;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 52);
        for (c2_i16 = 0; c2_i16 < 3; c2_i16++) {
          c2_endColList[c2_i16] = 0.0F;
        }

        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 53);
        (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", 1, 1, c2_b_bbox_sizes[1], 2,
          0);
        (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", 3, 1, c2_b_bbox_sizes[1], 2,
          0);
        c2_i17 = (int64_T)c2_b_bbox_data[(int32_T)(real32_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("bbox", (int32_T)c2_idx, 1,
          c2_b_bbox_sizes[0], 1, 0) - 1] + (int64_T)c2_b_bbox_data[((int32_T)
          (real32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", (int32_T)c2_idx, 1,
          c2_b_bbox_sizes[0], 1, 0) + (c2_b_bbox_sizes[0] << 1)) - 1];
        if (c2_i17 > 2147483647L) {
          CV_SATURATION_EVAL(4, 0, 0, 0, 1);
          c2_i17 = 2147483647L;
        } else {
          if (CV_SATURATION_EVAL(4, 0, 0, 0, c2_i17 < -2147483648L)) {
            c2_i17 = -2147483648L;
          }
        }

        c2_i18 = (int64_T)(int32_T)c2_i17 - 1L;
        if (c2_i18 > 2147483647L) {
          CV_SATURATION_EVAL(4, 0, 1, 0, 1);
          c2_i18 = 2147483647L;
        } else {
          if (CV_SATURATION_EVAL(4, 0, 1, 0, c2_i18 < -2147483648L)) {
            c2_i18 = -2147483648L;
          }
        }

        c2_endColList[1] = (real32_T)(int32_T)c2_i18;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 54);
        c2_c_varargin_2 = c2_endColList[1] - c2_stepCols;
        c2_c_varargin_3 = c2_c_varargin_2;
        c2_i_y = c2_c_varargin_3;
        c2_j_y = c2_i_y;
        c2_eml_scalar_eg(chartInstance);
        c2_c_yk = c2_j_y;
        c2_k_y = c2_c_yk;
        c2_eml_scalar_eg(chartInstance);
        c2_b_b = c2_k_y;
        c2_b_p = (1.0F < c2_b_b);
        if (c2_b_p) {
          c2_b_maxval = c2_k_y;
        } else {
          c2_b_maxval = 1.0F;
        }

        c2_endColList[0] = c2_b_maxval;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 55);
        c2_d_varargin_2 = c2_endColList[1] + c2_stepCols;
        c2_d_varargin_3 = c2_d_varargin_2;
        c2_l_y = c2_d_varargin_3;
        c2_m_y = c2_l_y;
        c2_b_eml_scalar_eg(chartInstance);
        c2_d_yk = c2_m_y;
        c2_n_y = c2_d_yk;
        c2_b_eml_scalar_eg(chartInstance);
        c2_b_minval = muSingleScalarMin(1.0F, c2_n_y);
        c2_endColList[2] = c2_b_minval;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 57);
        for (c2_i19 = 0; c2_i19 < 3; c2_i19++) {
          c2_startRowList[c2_i19] = 0.0F;
        }

        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 58);
        (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", 2, 1, c2_b_bbox_sizes[1], 2,
          0);
        c2_startRowList[1] = (real32_T)c2_b_bbox_data[((int32_T)(real32_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("bbox", (int32_T)c2_idx, 1,
          c2_b_bbox_sizes[0], 1, 0) + c2_b_bbox_sizes[0]) - 1];
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 59);
        c2_e_varargin_2 = c2_startRowList[1] - c2_stepRows;
        c2_e_varargin_3 = c2_e_varargin_2;
        c2_o_y = c2_e_varargin_3;
        c2_p_y = c2_o_y;
        c2_eml_scalar_eg(chartInstance);
        c2_e_yk = c2_p_y;
        c2_q_y = c2_e_yk;
        c2_eml_scalar_eg(chartInstance);
        c2_c_b = c2_q_y;
        c2_c_p = (1.0F < c2_c_b);
        if (c2_c_p) {
          c2_c_maxval = c2_q_y;
        } else {
          c2_c_maxval = 1.0F;
        }

        c2_startRowList[0] = c2_c_maxval;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 60);
        c2_f_varargin_2 = c2_startRowList[1] + c2_stepRows;
        c2_f_varargin_3 = c2_f_varargin_2;
        c2_r_y = c2_f_varargin_3;
        c2_s_y = c2_r_y;
        c2_b_eml_scalar_eg(chartInstance);
        c2_f_yk = c2_s_y;
        c2_t_y = c2_f_yk;
        c2_b_eml_scalar_eg(chartInstance);
        c2_c_minval = muSingleScalarMin(1.0F, c2_t_y);
        c2_startRowList[2] = c2_c_minval;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 62);
        for (c2_i20 = 0; c2_i20 < 3; c2_i20++) {
          c2_endRowList[c2_i20] = 0.0F;
        }

        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 63);
        (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", 2, 1, c2_b_bbox_sizes[1], 2,
          0);
        (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", 4, 1, c2_b_bbox_sizes[1], 2,
          0);
        c2_i21 = (int64_T)c2_b_bbox_data[((int32_T)(real32_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("bbox", (int32_T)c2_idx, 1,
          c2_b_bbox_sizes[0], 1, 0) + c2_b_bbox_sizes[0]) - 1] + (int64_T)
          c2_b_bbox_data[((int32_T)(real32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox",
                           (int32_T)c2_idx, 1, c2_b_bbox_sizes[0], 1, 0) +
                          c2_b_bbox_sizes[0] * 3) - 1];
        if (c2_i21 > 2147483647L) {
          CV_SATURATION_EVAL(4, 0, 2, 0, 1);
          c2_i21 = 2147483647L;
        } else {
          if (CV_SATURATION_EVAL(4, 0, 2, 0, c2_i21 < -2147483648L)) {
            c2_i21 = -2147483648L;
          }
        }

        c2_i22 = (int64_T)(int32_T)c2_i21 - 1L;
        if (c2_i22 > 2147483647L) {
          CV_SATURATION_EVAL(4, 0, 3, 0, 1);
          c2_i22 = 2147483647L;
        } else {
          if (CV_SATURATION_EVAL(4, 0, 3, 0, c2_i22 < -2147483648L)) {
            c2_i22 = -2147483648L;
          }
        }

        c2_endRowList[1] = (real32_T)(int32_T)c2_i22;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 64);
        c2_g_varargin_2 = c2_endRowList[1] - c2_stepRows;
        c2_g_varargin_3 = c2_g_varargin_2;
        c2_u_y = c2_g_varargin_3;
        c2_v_y = c2_u_y;
        c2_eml_scalar_eg(chartInstance);
        c2_g_yk = c2_v_y;
        c2_w_y = c2_g_yk;
        c2_eml_scalar_eg(chartInstance);
        c2_d_b = c2_w_y;
        c2_d_p = (1.0F < c2_d_b);
        if (c2_d_p) {
          c2_d_maxval = c2_w_y;
        } else {
          c2_d_maxval = 1.0F;
        }

        c2_endRowList[0] = c2_d_maxval;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 65);
        c2_h_varargin_2 = c2_endRowList[1] + c2_stepRows;
        c2_h_varargin_3 = c2_h_varargin_2;
        c2_x_y = c2_h_varargin_3;
        c2_y_y = c2_x_y;
        c2_b_eml_scalar_eg(chartInstance);
        c2_h_yk = c2_y_y;
        c2_ab_y = c2_h_yk;
        c2_b_eml_scalar_eg(chartInstance);
        c2_d_minval = muSingleScalarMin(1.0F, c2_ab_y);
        c2_endRowList[2] = c2_d_minval;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 68);
        for (c2_i23 = 0; c2_i23 < 3; c2_i23++) {
          c2_b_startColList[c2_i23] = c2_startColList[c2_i23];
        }

        c2_startCol = c2_b_startColList[0];
        c2_b_startCol = 0;
        while (c2_b_startCol < 3) {
          c2_startCol = c2_b_startColList[c2_b_startCol];
          CV_EML_FOR(0, 1, 1, 1);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 69);
          for (c2_i24 = 0; c2_i24 < 3; c2_i24++) {
            c2_b_endColList[c2_i24] = c2_endColList[c2_i24];
          }

          c2_endCol = c2_b_endColList[0];
          c2_b_endCol = 0;
          while (c2_b_endCol < 3) {
            c2_endCol = c2_b_endColList[c2_b_endCol];
            CV_EML_FOR(0, 1, 2, 1);
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 70);
            c2_c_A = c2_endCol - c2_startCol;
            c2_g_x = c2_c_A;
            c2_h_x = c2_g_x;
            c2_i_x = c2_h_x;
            c2_ratioCols = c2_i_x / 104.0F;
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 71);
            for (c2_i25 = 0; c2_i25 < 3; c2_i25++) {
              c2_b_startRowList[c2_i25] = c2_startRowList[c2_i25];
            }

            c2_startRow = c2_b_startRowList[0];
            c2_b_startRow = 0;
            while (c2_b_startRow < 3) {
              c2_startRow = c2_b_startRowList[c2_b_startRow];
              CV_EML_FOR(0, 1, 3, 1);
              _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 72);
              for (c2_i26 = 0; c2_i26 < 3; c2_i26++) {
                c2_b_endRowList[c2_i26] = c2_endRowList[c2_i26];
              }

              c2_endRow = c2_b_endRowList[0];
              c2_b_endRow = 0;
              while (c2_b_endRow < 3) {
                c2_endRow = c2_b_endRowList[c2_b_endRow];
                CV_EML_FOR(0, 1, 4, 1);
                _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 73);
                c2_d_A = c2_endRow - c2_startRow;
                c2_j_x = c2_d_A;
                c2_k_x = c2_j_x;
                c2_l_x = c2_k_x;
                c2_ratioRows = c2_l_x / 72.0F;
                _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 76);
                c2_colSrcFlt = c2_startCol;
                _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 77);
                c2_col = 1.0F;
                c2_b_col = 0;
                while (c2_b_col < 104) {
                  c2_col = 1.0F + (real32_T)c2_b_col;
                  CV_EML_FOR(0, 1, 5, 1);
                  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 78);
                  c2_f2 = c2_colSrcFlt;
                  c2_b_floor(chartInstance, &c2_f2);
                  c2_colSrc = c2_f2;
                  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 79);
                  c2_rowSrcFlt = c2_startRow;
                  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 80);
                  c2_row = 1.0F;
                  c2_b_row = 0;
                  while (c2_b_row < 72) {
                    c2_row = 1.0F + (real32_T)c2_b_row;
                    CV_EML_FOR(0, 1, 6, 1);
                    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 81);
                    c2_f3 = c2_rowSrcFlt;
                    c2_b_floor(chartInstance, &c2_f3);
                    c2_rowSrc = c2_f3;
                    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 82);
                    (real32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("I", (int32_T)
                      c2_rowSrc, 1, 1, 1, 0);
                    (real32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("I", (int32_T)
                      c2_colSrc, 1, 1, 2, 0);
                    c2_feature[((int32_T)c2_row + 72 * ((int32_T)c2_col - 1)) -
                      1] = (real32_T)c2_b_I;
                    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 83);
                    c2_rowSrcFlt += c2_ratioRows;
                    c2_b_row++;
                    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
                  }

                  CV_EML_FOR(0, 1, 6, 0);
                  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 85);
                  c2_colSrcFlt += c2_ratioCols;
                  c2_b_col++;
                  _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
                }

                CV_EML_FOR(0, 1, 5, 0);
                _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 89);
                for (c2_i27 = 0; c2_i27 < 7488; c2_i27++) {
                  c2_b_feature[c2_i27] = c2_feature[c2_i27];
                }

                c2_f4 = c2_mean(chartInstance, c2_b_feature);
                for (c2_i28 = 0; c2_i28 < 7488; c2_i28++) {
                  c2_feature[c2_i28] -= c2_f4;
                }

                _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 92);
                c2_iTmp = 1.0F;
                c2_b_iTmp = 0;
                while (c2_b_iTmp < 6) {
                  c2_iTmp = 1.0F + (real32_T)c2_b_iTmp;
                  CV_EML_FOR(0, 1, 7, 1);
                  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 93);
                  c2_similarity = 0.0F;
                  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 95);
                  c2_col = 1.0F;
                  c2_c_col = 0;
                  while (c2_c_col < 104) {
                    c2_col = 1.0F + (real32_T)c2_c_col;
                    CV_EML_FOR(0, 1, 8, 1);
                    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 96);
                    c2_row = 1.0F;
                    c2_c_row = 0;
                    while (c2_c_row < 72) {
                      c2_row = 1.0F + (real32_T)c2_c_row;
                      CV_EML_FOR(0, 1, 9, 1);
                      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 97);
                      c2_similarity += chartInstance->c2_T[(((int32_T)c2_row +
                        72 * ((int32_T)c2_col - 1)) + 7488 * ((int32_T)c2_iTmp -
                        1)) - 1] * c2_feature[((int32_T)c2_row + 72 * ((int32_T)
                        c2_col - 1)) - 1];
                      c2_c_row++;
                      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
                    }

                    CV_EML_FOR(0, 1, 9, 0);
                    c2_c_col++;
                    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
                  }

                  CV_EML_FOR(0, 1, 8, 0);
                  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 101);
                  if (CV_EML_IF(0, 1, 1, CV_RELATIONAL_EVAL(4U, 0U, 2, (real_T)
                        c2_similarity, (real_T)c2_bestSimilarity, -3, 4U,
                        c2_similarity > c2_bestSimilarity))) {
                    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 102);
                    c2_bestSimilarity = c2_similarity;
                  }

                  c2_b_iTmp++;
                  _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
                }

                CV_EML_FOR(0, 1, 7, 0);
                c2_b_endRow++;
                _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
              }

              CV_EML_FOR(0, 1, 4, 0);
              c2_b_startRow++;
              _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
            }

            CV_EML_FOR(0, 1, 3, 0);
            c2_b_endCol++;
            _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
          }

          CV_EML_FOR(0, 1, 2, 0);
          c2_b_startCol++;
          _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
        }

        CV_EML_FOR(0, 1, 1, 0);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 111);
        if (CV_EML_IF(0, 1, 2, CV_RELATIONAL_EVAL(4U, 0U, 3, (real_T)
              c2_bestSimilarity, c2_b_minSimilarity, -1, 5U, (real_T)
              c2_bestSimilarity >= c2_b_minSimilarity))) {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 112);
          (real32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("BBox", (int32_T)c2_idx, 1, 1, 1,
            0);
          (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", 1, 1, c2_b_bbox_sizes[1],
            2, 0);
          c2_b_BBox_data[0] = (real32_T)c2_b_bbox_data[(int32_T)(real32_T)
            _SFD_EML_ARRAY_BOUNDS_CHECK("bbox", (int32_T)c2_idx, 1,
            c2_b_bbox_sizes[0], 1, 0) - 1];
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 113);
          (real32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", (int32_T)c2_idx, 1,
            c2_b_bbox_sizes[0], 1, 0);
          (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", 2, 1, c2_b_bbox_sizes[1],
            2, 0);
          c2_b_BBox_data[c2_b_BBox_sizes[0]] = (real32_T)
            c2_b_bbox_data[c2_b_bbox_sizes[0]];
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 114);
          (real32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", (int32_T)c2_idx, 1,
            c2_b_bbox_sizes[0], 1, 0);
          (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", 3, 1, c2_b_bbox_sizes[1],
            2, 0);
          c2_b_BBox_data[c2_b_BBox_sizes[0] << 1] = (real32_T)
            c2_b_bbox_data[c2_b_bbox_sizes[0] << 1];
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 115);
          (real32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", (int32_T)c2_idx, 1,
            c2_b_bbox_sizes[0], 1, 0);
          (real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("bbox", 4, 1, c2_b_bbox_sizes[1],
            2, 0);
          c2_b_BBox_data[c2_b_BBox_sizes[0] * 3] = (real32_T)
            c2_b_bbox_data[c2_b_bbox_sizes[0] * 3];
        }
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1 == true) {
      CV_EML_MCDC(0, 1, 0, false);
      CV_EML_IF(0, 1, 0, false);
    }

    c2_b_idx++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -115);
  _SFD_SYMBOL_SCOPE_POP();
  ssSetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1, 0, 1);
  ssSetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1, 1,
    c2_b_BBox_sizes[1]);
  c2_i29 = (*chartInstance->c2_BBox_sizes)[0];
  c2_i30 = (*chartInstance->c2_BBox_sizes)[1];
  c2_d_loop_ub = c2_b_BBox_sizes[0] * c2_b_BBox_sizes[1] - 1;
  for (c2_i31 = 0; c2_i31 <= c2_d_loop_ub; c2_i31++) {
    (*chartInstance->c2_BBox_data)[c2_i31] = c2_b_BBox_data[c2_i31];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_Detection(SFc2_DetectionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  (void)c2_chartNumber;
  (void)c2_instanceNumber;
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, real32_T
  c2_inData_data[], int32_T c2_inData_sizes[2])
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u_sizes[2];
  int32_T c2_u;
  int32_T c2_b_u;
  int32_T c2_b_inData;
  int32_T c2_c_inData;
  int32_T c2_b_inData_sizes;
  int32_T c2_loop_ub;
  int32_T c2_i32;
  real32_T c2_b_inData_data[4];
  int32_T c2_b_loop_ub;
  int32_T c2_i33;
  real32_T c2_u_data[4];
  const mxArray *c2_y = NULL;
  SFc2_DetectionInstanceStruct *chartInstance;
  chartInstance = (SFc2_DetectionInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u_sizes[0] = 1;
  c2_u_sizes[1] = c2_inData_sizes[1];
  c2_u = c2_u_sizes[0];
  c2_b_u = c2_u_sizes[1];
  c2_b_inData = c2_inData_sizes[0];
  c2_c_inData = c2_inData_sizes[1];
  c2_b_inData_sizes = c2_b_inData * c2_c_inData;
  c2_loop_ub = c2_b_inData * c2_c_inData - 1;
  for (c2_i32 = 0; c2_i32 <= c2_loop_ub; c2_i32++) {
    c2_b_inData_data[c2_i32] = c2_inData_data[c2_i32];
  }

  c2_b_loop_ub = c2_b_inData_sizes - 1;
  for (c2_i33 = 0; c2_i33 <= c2_b_loop_ub; c2_i33++) {
    c2_u_data[c2_i33] = c2_b_inData_data[c2_i33];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u_data, 1, 0U, 1U, 0U, 2,
    c2_u_sizes[0], c2_u_sizes[1]), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_DetectionInstanceStruct *chartInstance,
  const mxArray *c2_BBox, const char_T *c2_identifier, real32_T c2_y_data[],
  int32_T c2_y_sizes[2])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_BBox), &c2_thisId,
                        c2_y_data, c2_y_sizes);
  sf_mex_destroy(&c2_BBox);
}

static void c2_b_emlrt_marshallIn(SFc2_DetectionInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real32_T
  c2_y_data[], int32_T c2_y_sizes[2])
{
  int32_T c2_i34;
  uint32_T c2_uv0[2];
  int32_T c2_i35;
  static boolean_T c2_bv0[2] = { false, true };

  boolean_T c2_bv1[2];
  int32_T c2_tmp_sizes[2];
  real32_T c2_tmp_data[4];
  int32_T c2_y;
  int32_T c2_b_y;
  int32_T c2_loop_ub;
  int32_T c2_i36;
  (void)chartInstance;
  for (c2_i34 = 0; c2_i34 < 2; c2_i34++) {
    c2_uv0[c2_i34] = 1U + 3U * (uint32_T)c2_i34;
  }

  for (c2_i35 = 0; c2_i35 < 2; c2_i35++) {
    c2_bv1[c2_i35] = c2_bv0[c2_i35];
  }

  sf_mex_import_vs(c2_parentId, sf_mex_dup(c2_u), c2_tmp_data, 1, 1, 0U, 1, 0U,
                   2, c2_bv1, c2_uv0, c2_tmp_sizes);
  c2_y_sizes[0] = 1;
  c2_y_sizes[1] = c2_tmp_sizes[1];
  c2_y = c2_y_sizes[0];
  c2_b_y = c2_y_sizes[1];
  c2_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
  for (c2_i36 = 0; c2_i36 <= c2_loop_ub; c2_i36++) {
    c2_y_data[c2_i36] = c2_tmp_data[c2_i36];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, real32_T c2_outData_data[],
  int32_T c2_outData_sizes[2])
{
  const mxArray *c2_BBox;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y_sizes[2];
  real32_T c2_y_data[4];
  int32_T c2_loop_ub;
  int32_T c2_i37;
  SFc2_DetectionInstanceStruct *chartInstance;
  chartInstance = (SFc2_DetectionInstanceStruct *)chartInstanceVoid;
  c2_BBox = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_BBox), &c2_thisId,
                        c2_y_data, c2_y_sizes);
  sf_mex_destroy(&c2_BBox);
  c2_outData_sizes[0] = 1;
  c2_outData_sizes[1] = c2_y_sizes[1];
  c2_loop_ub = c2_y_sizes[1] - 1;
  for (c2_i37 = 0; c2_i37 <= c2_loop_ub; c2_i37++) {
    c2_outData_data[c2_outData_sizes[0] * c2_i37] = c2_y_data[c2_y_sizes[0] *
      c2_i37];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_b_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_DetectionInstanceStruct *chartInstance;
  chartInstance = (SFc2_DetectionInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(uint8_T *)c2_b_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, int32_T
  c2_inData_data[], int32_T c2_inData_sizes[2])
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u_sizes[2];
  int32_T c2_u;
  int32_T c2_b_u;
  int32_T c2_b_inData;
  int32_T c2_c_inData;
  int32_T c2_b_inData_sizes;
  int32_T c2_loop_ub;
  int32_T c2_i38;
  int32_T c2_b_inData_data[1020];
  int32_T c2_b_loop_ub;
  int32_T c2_i39;
  int32_T c2_u_data[1020];
  const mxArray *c2_y = NULL;
  SFc2_DetectionInstanceStruct *chartInstance;
  chartInstance = (SFc2_DetectionInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u_sizes[0] = c2_inData_sizes[0];
  c2_u_sizes[1] = c2_inData_sizes[1];
  c2_u = c2_u_sizes[0];
  c2_b_u = c2_u_sizes[1];
  c2_b_inData = c2_inData_sizes[0];
  c2_c_inData = c2_inData_sizes[1];
  c2_b_inData_sizes = c2_b_inData * c2_c_inData;
  c2_loop_ub = c2_b_inData * c2_c_inData - 1;
  for (c2_i38 = 0; c2_i38 <= c2_loop_ub; c2_i38++) {
    c2_b_inData_data[c2_i38] = c2_inData_data[c2_i38];
  }

  c2_b_loop_ub = c2_b_inData_sizes - 1;
  for (c2_i39 = 0; c2_i39 <= c2_b_loop_ub; c2_i39++) {
    c2_u_data[c2_i39] = c2_b_inData_data[c2_i39];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u_data, 6, 0U, 1U, 0U, 2,
    c2_u_sizes[0], c2_u_sizes[1]), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_b_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_DetectionInstanceStruct *chartInstance;
  chartInstance = (SFc2_DetectionInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_b_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_b_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i40;
  int32_T c2_i41;
  int32_T c2_i42;
  int32_T c2_i43;
  int32_T c2_i44;
  int32_T c2_i45;
  int32_T c2_i46;
  int32_T c2_i47;
  int32_T c2_i48;
  int32_T c2_i49;
  real32_T c2_u[44928];
  const mxArray *c2_y = NULL;
  SFc2_DetectionInstanceStruct *chartInstance;
  chartInstance = (SFc2_DetectionInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i40 = 0;
  for (c2_i41 = 0; c2_i41 < 6; c2_i41++) {
    c2_i42 = 0;
    for (c2_i43 = 0; c2_i43 < 104; c2_i43++) {
      for (c2_i44 = 0; c2_i44 < 72; c2_i44++) {
        chartInstance->c2_inData[(c2_i44 + c2_i42) + c2_i40] = (*(real32_T (*)
          [44928])c2_b_inData)[(c2_i44 + c2_i42) + c2_i40];
      }

      c2_i42 += 72;
    }

    c2_i40 += 7488;
  }

  c2_i45 = 0;
  for (c2_i46 = 0; c2_i46 < 6; c2_i46++) {
    c2_i47 = 0;
    for (c2_i48 = 0; c2_i48 < 104; c2_i48++) {
      for (c2_i49 = 0; c2_i49 < 72; c2_i49++) {
        c2_u[(c2_i49 + c2_i47) + c2_i45] = chartInstance->c2_inData[(c2_i49 +
          c2_i47) + c2_i45];
      }

      c2_i47 += 72;
    }

    c2_i45 += 7488;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 1, 0U, 1U, 0U, 3, 72, 104, 6),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_DetectionInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d2;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d2, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d2;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_DetectionInstanceStruct *chartInstance;
  chartInstance = (SFc2_DetectionInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_b_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_DetectionInstanceStruct *chartInstance;
  chartInstance = (SFc2_DetectionInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real32_T *)c2_b_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real32_T c2_d_emlrt_marshallIn(SFc2_DetectionInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real32_T c2_y;
  real32_T c2_f5;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_f5, 1, 1, 0U, 0, 0U, 0);
  c2_y = c2_f5;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_similarity;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real32_T c2_y;
  SFc2_DetectionInstanceStruct *chartInstance;
  chartInstance = (SFc2_DetectionInstanceStruct *)chartInstanceVoid;
  c2_similarity = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_similarity),
    &c2_thisId);
  sf_mex_destroy(&c2_similarity);
  *(real32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_b_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i50;
  real32_T c2_c_inData[3];
  int32_T c2_i51;
  real32_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_DetectionInstanceStruct *chartInstance;
  chartInstance = (SFc2_DetectionInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i50 = 0; c2_i50 < 3; c2_i50++) {
    c2_c_inData[c2_i50] = (*(real32_T (*)[3])c2_b_inData)[c2_i50];
  }

  for (c2_i51 = 0; c2_i51 < 3; c2_i51++) {
    c2_u[c2_i51] = c2_c_inData[c2_i51];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 1, 0U, 1U, 0U, 2, 1, 3), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_e_emlrt_marshallIn(SFc2_DetectionInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real32_T c2_y[3])
{
  real32_T c2_fv0[3];
  int32_T c2_i52;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_fv0, 1, 1, 0U, 1, 0U, 2, 1, 3);
  for (c2_i52 = 0; c2_i52 < 3; c2_i52++) {
    c2_y[c2_i52] = c2_fv0[c2_i52];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_endRowList;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real32_T c2_y[3];
  int32_T c2_i53;
  SFc2_DetectionInstanceStruct *chartInstance;
  chartInstance = (SFc2_DetectionInstanceStruct *)chartInstanceVoid;
  c2_endRowList = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_endRowList), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_endRowList);
  for (c2_i53 = 0; c2_i53 < 3; c2_i53++) {
    (*(real32_T (*)[3])c2_outData)[c2_i53] = c2_y[c2_i53];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_b_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i54;
  int32_T c2_i55;
  int32_T c2_i56;
  real32_T c2_c_inData[7488];
  int32_T c2_i57;
  int32_T c2_i58;
  int32_T c2_i59;
  real32_T c2_u[7488];
  const mxArray *c2_y = NULL;
  SFc2_DetectionInstanceStruct *chartInstance;
  chartInstance = (SFc2_DetectionInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i54 = 0;
  for (c2_i55 = 0; c2_i55 < 104; c2_i55++) {
    for (c2_i56 = 0; c2_i56 < 72; c2_i56++) {
      c2_c_inData[c2_i56 + c2_i54] = (*(real32_T (*)[7488])c2_b_inData)[c2_i56 +
        c2_i54];
    }

    c2_i54 += 72;
  }

  c2_i57 = 0;
  for (c2_i58 = 0; c2_i58 < 104; c2_i58++) {
    for (c2_i59 = 0; c2_i59 < 72; c2_i59++) {
      c2_u[c2_i59 + c2_i57] = c2_c_inData[c2_i59 + c2_i57];
    }

    c2_i57 += 72;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 1, 0U, 1U, 0U, 2, 72, 104),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_f_emlrt_marshallIn(SFc2_DetectionInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real32_T c2_y[7488])
{
  real32_T c2_fv1[7488];
  int32_T c2_i60;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_fv1, 1, 1, 0U, 1, 0U, 2, 72,
                104);
  for (c2_i60 = 0; c2_i60 < 7488; c2_i60++) {
    c2_y[c2_i60] = c2_fv1[c2_i60];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_feature;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real32_T c2_y[7488];
  int32_T c2_i61;
  int32_T c2_i62;
  int32_T c2_i63;
  SFc2_DetectionInstanceStruct *chartInstance;
  chartInstance = (SFc2_DetectionInstanceStruct *)chartInstanceVoid;
  c2_feature = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_feature), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_feature);
  c2_i61 = 0;
  for (c2_i62 = 0; c2_i62 < 104; c2_i62++) {
    for (c2_i63 = 0; c2_i63 < 72; c2_i63++) {
      (*(real32_T (*)[7488])c2_outData)[c2_i63 + c2_i61] = c2_y[c2_i63 + c2_i61];
    }

    c2_i61 += 72;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_Detection_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_createstruct("structure", 2, 48, 1),
                false);
  c2_info_helper(&c2_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs0 = NULL;
  const mxArray *c2_lhs0 = NULL;
  const mxArray *c2_rhs1 = NULL;
  const mxArray *c2_lhs1 = NULL;
  const mxArray *c2_rhs2 = NULL;
  const mxArray *c2_lhs2 = NULL;
  const mxArray *c2_rhs3 = NULL;
  const mxArray *c2_lhs3 = NULL;
  const mxArray *c2_rhs4 = NULL;
  const mxArray *c2_lhs4 = NULL;
  const mxArray *c2_rhs5 = NULL;
  const mxArray *c2_lhs5 = NULL;
  const mxArray *c2_rhs6 = NULL;
  const mxArray *c2_lhs6 = NULL;
  const mxArray *c2_rhs7 = NULL;
  const mxArray *c2_lhs7 = NULL;
  const mxArray *c2_rhs8 = NULL;
  const mxArray *c2_lhs8 = NULL;
  const mxArray *c2_rhs9 = NULL;
  const mxArray *c2_lhs9 = NULL;
  const mxArray *c2_rhs10 = NULL;
  const mxArray *c2_lhs10 = NULL;
  const mxArray *c2_rhs11 = NULL;
  const mxArray *c2_lhs11 = NULL;
  const mxArray *c2_rhs12 = NULL;
  const mxArray *c2_lhs12 = NULL;
  const mxArray *c2_rhs13 = NULL;
  const mxArray *c2_lhs13 = NULL;
  const mxArray *c2_rhs14 = NULL;
  const mxArray *c2_lhs14 = NULL;
  const mxArray *c2_rhs15 = NULL;
  const mxArray *c2_lhs15 = NULL;
  const mxArray *c2_rhs16 = NULL;
  const mxArray *c2_lhs16 = NULL;
  const mxArray *c2_rhs17 = NULL;
  const mxArray *c2_lhs17 = NULL;
  const mxArray *c2_rhs18 = NULL;
  const mxArray *c2_lhs18 = NULL;
  const mxArray *c2_rhs19 = NULL;
  const mxArray *c2_lhs19 = NULL;
  const mxArray *c2_rhs20 = NULL;
  const mxArray *c2_lhs20 = NULL;
  const mxArray *c2_rhs21 = NULL;
  const mxArray *c2_lhs21 = NULL;
  const mxArray *c2_rhs22 = NULL;
  const mxArray *c2_lhs22 = NULL;
  const mxArray *c2_rhs23 = NULL;
  const mxArray *c2_lhs23 = NULL;
  const mxArray *c2_rhs24 = NULL;
  const mxArray *c2_lhs24 = NULL;
  const mxArray *c2_rhs25 = NULL;
  const mxArray *c2_lhs25 = NULL;
  const mxArray *c2_rhs26 = NULL;
  const mxArray *c2_lhs26 = NULL;
  const mxArray *c2_rhs27 = NULL;
  const mxArray *c2_lhs27 = NULL;
  const mxArray *c2_rhs28 = NULL;
  const mxArray *c2_lhs28 = NULL;
  const mxArray *c2_rhs29 = NULL;
  const mxArray *c2_lhs29 = NULL;
  const mxArray *c2_rhs30 = NULL;
  const mxArray *c2_lhs30 = NULL;
  const mxArray *c2_rhs31 = NULL;
  const mxArray *c2_lhs31 = NULL;
  const mxArray *c2_rhs32 = NULL;
  const mxArray *c2_lhs32 = NULL;
  const mxArray *c2_rhs33 = NULL;
  const mxArray *c2_lhs33 = NULL;
  const mxArray *c2_rhs34 = NULL;
  const mxArray *c2_lhs34 = NULL;
  const mxArray *c2_rhs35 = NULL;
  const mxArray *c2_lhs35 = NULL;
  const mxArray *c2_rhs36 = NULL;
  const mxArray *c2_lhs36 = NULL;
  const mxArray *c2_rhs37 = NULL;
  const mxArray *c2_lhs37 = NULL;
  const mxArray *c2_rhs38 = NULL;
  const mxArray *c2_lhs38 = NULL;
  const mxArray *c2_rhs39 = NULL;
  const mxArray *c2_lhs39 = NULL;
  const mxArray *c2_rhs40 = NULL;
  const mxArray *c2_lhs40 = NULL;
  const mxArray *c2_rhs41 = NULL;
  const mxArray *c2_lhs41 = NULL;
  const mxArray *c2_rhs42 = NULL;
  const mxArray *c2_lhs42 = NULL;
  const mxArray *c2_rhs43 = NULL;
  const mxArray *c2_lhs43 = NULL;
  const mxArray *c2_rhs44 = NULL;
  const mxArray *c2_lhs44 = NULL;
  const mxArray *c2_rhs45 = NULL;
  const mxArray *c2_lhs45 = NULL;
  const mxArray *c2_rhs46 = NULL;
  const mxArray *c2_lhs46 = NULL;
  const mxArray *c2_rhs47 = NULL;
  const mxArray *c2_lhs47 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mrdivide"), "name", "name", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410829248U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1370031486U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c2_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389739374U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c2_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("rdivide"), "name", "name", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363731880U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c2_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395949856U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c2_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840396U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c2_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_div"), "name", "name", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1386445552U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c2_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410829370U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c2_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("floor"), "name", "name", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363731854U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c2_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395949856U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c2_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840326U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c2_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("max"), "name", "name", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m"), "resolved",
                  "resolved", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1311276916U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c2_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m"), "context",
                  "context", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_min_or_max"), "name",
                  "name", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378317584U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c2_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1376002288U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c2_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410829370U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c2_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1376002288U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c2_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410829370U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c2_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323192178U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c2_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1376002288U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c2_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_relop"), "name", "name",
                  18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("function_handle"),
                  "dominantType", "dominantType", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_relop.m"), "resolved",
                  "resolved", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1342472782U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c2_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnan"), "name", "name", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363731858U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c2_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "context",
                  "context", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395949856U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c2_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("min"), "name", "name", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1311276918U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c2_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "context",
                  "context", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_min_or_max"), "name",
                  "name", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m"),
                  "resolved", "resolved", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378317584U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c2_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395949856U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c2_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mean"), "name", "name", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/mean.m"), "resolved",
                  "resolved", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1397279022U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c2_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/mean.m"), "context",
                  "context", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389739374U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c2_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/mean.m"), "context",
                  "context", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395949856U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c2_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/mean.m"), "context",
                  "context", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("process_sumprod_inputs"),
                  "name", "name", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXPE]$matlabroot$/toolbox/eml/lib/matlab/datafun/private/process_sumprod_inputs.m"),
                  "resolved", "resolved", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395948302U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c2_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXPE]$matlabroot$/toolbox/eml/lib/matlab/datafun/private/process_sumprod_inputs.m"),
                  "context", "context", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.narginchk"),
                  "name", "name", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/narginchk.m"),
                  "resolved", "resolved", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363732558U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c2_rhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/narginchk.m"),
                  "context", "context", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("floor"), "name", "name", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363731854U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c2_rhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395949856U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c2_rhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840326U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c2_rhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/narginchk.m"),
                  "context", "context", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389739374U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c2_rhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXPE]$matlabroot$/toolbox/eml/lib/matlab/datafun/private/process_sumprod_inputs.m"),
                  "context", "context", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.constNonSingletonDim"), "name", "name", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/constNonSingletonDim.m"),
                  "resolved", "resolved", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372604760U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c2_rhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXPE]$matlabroot$/toolbox/eml/lib/matlab/datafun/private/process_sumprod_inputs.m"),
                  "context", "context", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389739374U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c2_rhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs34), "lhs", "lhs",
                  34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXPE]$matlabroot$/toolbox/eml/lib/matlab/datafun/private/process_sumprod_inputs.m"),
                  "context", "context", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1376002288U), "fileTimeLo",
                  "fileTimeLo", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 35);
  sf_mex_assign(&c2_rhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs35), "rhs", "rhs",
                  35);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs35), "lhs", "lhs",
                  35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/mean.m"), "context",
                  "context", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isequal"), "name", "name", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "resolved",
                  "resolved", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840358U), "fileTimeLo",
                  "fileTimeLo", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 36);
  sf_mex_assign(&c2_rhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs36), "rhs", "rhs",
                  36);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs36), "lhs", "lhs",
                  36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "context",
                  "context", 37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_isequal_core"), "name",
                  "name", 37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m"),
                  "resolved", "resolved", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840386U), "fileTimeLo",
                  "fileTimeLo", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 37);
  sf_mex_assign(&c2_rhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs37), "rhs", "rhs",
                  37);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs37), "lhs", "lhs",
                  37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/mean.m"), "context",
                  "context", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("combine_vector_elements"),
                  "name", "name", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("function_handle"),
                  "dominantType", "dominantType", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXPE]$matlabroot$/toolbox/eml/lib/matlab/datafun/private/combine_vector_elements.m"),
                  "resolved", "resolved", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395948302U), "fileTimeLo",
                  "fileTimeLo", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 38);
  sf_mex_assign(&c2_rhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs38), "rhs", "rhs",
                  38);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs38), "lhs", "lhs",
                  38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXPE]$matlabroot$/toolbox/eml/lib/matlab/datafun/private/combine_vector_elements.m"),
                  "context", "context", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1397279022U), "fileTimeLo",
                  "fileTimeLo", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 39);
  sf_mex_assign(&c2_rhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs39), "rhs", "rhs",
                  39);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs39), "lhs", "lhs",
                  39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 40);
  sf_mex_assign(&c2_rhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs40), "rhs", "rhs",
                  40);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs40), "lhs", "lhs",
                  40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "context",
                  "context", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1398897198U), "fileTimeLo",
                  "fileTimeLo", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 41);
  sf_mex_assign(&c2_rhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs41), "rhs", "rhs",
                  41);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs41), "lhs", "lhs",
                  41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362283482U), "fileTimeLo",
                  "fileTimeLo", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 42);
  sf_mex_assign(&c2_rhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs42), "rhs", "rhs",
                  42);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs42), "lhs", "lhs",
                  42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "context",
                  "context", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1393352458U), "fileTimeLo",
                  "fileTimeLo", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 43);
  sf_mex_assign(&c2_rhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs43), "rhs", "rhs",
                  43);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs43), "lhs", "lhs",
                  43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmin"), "name", "name", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362283482U), "fileTimeLo",
                  "fileTimeLo", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 44);
  sf_mex_assign(&c2_rhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs44), "rhs", "rhs",
                  44);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs44), "lhs", "lhs",
                  44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "context",
                  "context", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1393352458U), "fileTimeLo",
                  "fileTimeLo", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 45);
  sf_mex_assign(&c2_rhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs45), "rhs", "rhs",
                  45);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs45), "lhs", "lhs",
                  45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/mean.m"), "context",
                  "context", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("rdivide"), "name", "name", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363731880U), "fileTimeLo",
                  "fileTimeLo", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 46);
  sf_mex_assign(&c2_rhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs46), "rhs", "rhs",
                  46);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs46), "lhs", "lhs",
                  46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395949856U), "fileTimeLo",
                  "fileTimeLo", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 47);
  sf_mex_assign(&c2_rhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs47), "rhs", "rhs",
                  47);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs47), "lhs", "lhs",
                  47);
  sf_mex_destroy(&c2_rhs0);
  sf_mex_destroy(&c2_lhs0);
  sf_mex_destroy(&c2_rhs1);
  sf_mex_destroy(&c2_lhs1);
  sf_mex_destroy(&c2_rhs2);
  sf_mex_destroy(&c2_lhs2);
  sf_mex_destroy(&c2_rhs3);
  sf_mex_destroy(&c2_lhs3);
  sf_mex_destroy(&c2_rhs4);
  sf_mex_destroy(&c2_lhs4);
  sf_mex_destroy(&c2_rhs5);
  sf_mex_destroy(&c2_lhs5);
  sf_mex_destroy(&c2_rhs6);
  sf_mex_destroy(&c2_lhs6);
  sf_mex_destroy(&c2_rhs7);
  sf_mex_destroy(&c2_lhs7);
  sf_mex_destroy(&c2_rhs8);
  sf_mex_destroy(&c2_lhs8);
  sf_mex_destroy(&c2_rhs9);
  sf_mex_destroy(&c2_lhs9);
  sf_mex_destroy(&c2_rhs10);
  sf_mex_destroy(&c2_lhs10);
  sf_mex_destroy(&c2_rhs11);
  sf_mex_destroy(&c2_lhs11);
  sf_mex_destroy(&c2_rhs12);
  sf_mex_destroy(&c2_lhs12);
  sf_mex_destroy(&c2_rhs13);
  sf_mex_destroy(&c2_lhs13);
  sf_mex_destroy(&c2_rhs14);
  sf_mex_destroy(&c2_lhs14);
  sf_mex_destroy(&c2_rhs15);
  sf_mex_destroy(&c2_lhs15);
  sf_mex_destroy(&c2_rhs16);
  sf_mex_destroy(&c2_lhs16);
  sf_mex_destroy(&c2_rhs17);
  sf_mex_destroy(&c2_lhs17);
  sf_mex_destroy(&c2_rhs18);
  sf_mex_destroy(&c2_lhs18);
  sf_mex_destroy(&c2_rhs19);
  sf_mex_destroy(&c2_lhs19);
  sf_mex_destroy(&c2_rhs20);
  sf_mex_destroy(&c2_lhs20);
  sf_mex_destroy(&c2_rhs21);
  sf_mex_destroy(&c2_lhs21);
  sf_mex_destroy(&c2_rhs22);
  sf_mex_destroy(&c2_lhs22);
  sf_mex_destroy(&c2_rhs23);
  sf_mex_destroy(&c2_lhs23);
  sf_mex_destroy(&c2_rhs24);
  sf_mex_destroy(&c2_lhs24);
  sf_mex_destroy(&c2_rhs25);
  sf_mex_destroy(&c2_lhs25);
  sf_mex_destroy(&c2_rhs26);
  sf_mex_destroy(&c2_lhs26);
  sf_mex_destroy(&c2_rhs27);
  sf_mex_destroy(&c2_lhs27);
  sf_mex_destroy(&c2_rhs28);
  sf_mex_destroy(&c2_lhs28);
  sf_mex_destroy(&c2_rhs29);
  sf_mex_destroy(&c2_lhs29);
  sf_mex_destroy(&c2_rhs30);
  sf_mex_destroy(&c2_lhs30);
  sf_mex_destroy(&c2_rhs31);
  sf_mex_destroy(&c2_lhs31);
  sf_mex_destroy(&c2_rhs32);
  sf_mex_destroy(&c2_lhs32);
  sf_mex_destroy(&c2_rhs33);
  sf_mex_destroy(&c2_lhs33);
  sf_mex_destroy(&c2_rhs34);
  sf_mex_destroy(&c2_lhs34);
  sf_mex_destroy(&c2_rhs35);
  sf_mex_destroy(&c2_lhs35);
  sf_mex_destroy(&c2_rhs36);
  sf_mex_destroy(&c2_lhs36);
  sf_mex_destroy(&c2_rhs37);
  sf_mex_destroy(&c2_lhs37);
  sf_mex_destroy(&c2_rhs38);
  sf_mex_destroy(&c2_lhs38);
  sf_mex_destroy(&c2_rhs39);
  sf_mex_destroy(&c2_lhs39);
  sf_mex_destroy(&c2_rhs40);
  sf_mex_destroy(&c2_lhs40);
  sf_mex_destroy(&c2_rhs41);
  sf_mex_destroy(&c2_lhs41);
  sf_mex_destroy(&c2_rhs42);
  sf_mex_destroy(&c2_lhs42);
  sf_mex_destroy(&c2_rhs43);
  sf_mex_destroy(&c2_lhs43);
  sf_mex_destroy(&c2_rhs44);
  sf_mex_destroy(&c2_lhs44);
  sf_mex_destroy(&c2_rhs45);
  sf_mex_destroy(&c2_lhs45);
  sf_mex_destroy(&c2_rhs46);
  sf_mex_destroy(&c2_lhs46);
  sf_mex_destroy(&c2_rhs47);
  sf_mex_destroy(&c2_lhs47);
}

static const mxArray *c2_emlrt_marshallOut(const char * c2_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c2_u)), false);
  return c2_y;
}

static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 7, 0U, 0U, 0U, 0), false);
  return c2_y;
}

static real32_T c2_floor(SFc2_DetectionInstanceStruct *chartInstance, real32_T
  c2_x)
{
  real32_T c2_b_x;
  c2_b_x = c2_x;
  c2_b_floor(chartInstance, &c2_b_x);
  return c2_b_x;
}

static void c2_eml_scalar_eg(SFc2_DetectionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_b_eml_scalar_eg(SFc2_DetectionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static real32_T c2_mean(SFc2_DetectionInstanceStruct *chartInstance, real32_T
  c2_x[7488])
{
  real32_T c2_b_y;
  int32_T c2_k;
  int32_T c2_b_k;
  real32_T c2_b_x;
  real32_T c2_c_x;
  real32_T c2_d_x;
  (void)chartInstance;
  c2_b_y = c2_x[0];
  for (c2_k = 2; c2_k < 7489; c2_k++) {
    c2_b_k = c2_k - 1;
    c2_b_y += c2_x[c2_b_k];
  }

  c2_b_x = c2_b_y;
  c2_c_x = c2_b_x;
  c2_d_x = c2_c_x;
  return c2_d_x / 7488.0F;
}

static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_b_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_DetectionInstanceStruct *chartInstance;
  chartInstance = (SFc2_DetectionInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_b_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_g_emlrt_marshallIn(SFc2_DetectionInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i64;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i64, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i64;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_DetectionInstanceStruct *chartInstance;
  chartInstance = (SFc2_DetectionInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_h_emlrt_marshallIn(SFc2_DetectionInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_Detection, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_Detection), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_Detection);
  return c2_y;
}

static uint8_T c2_i_emlrt_marshallIn(SFc2_DetectionInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_floor(SFc2_DetectionInstanceStruct *chartInstance, real32_T
  *c2_x)
{
  (void)chartInstance;
  *c2_x = muSingleScalarFloor(*c2_x);
}

static void init_dsm_address_info(SFc2_DetectionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc2_DetectionInstanceStruct *chartInstance)
{
  chartInstance->c2_b_T = (real32_T (*)[44928])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c2_BBox_data = (real32_T (*)[4])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_BBox_sizes = (int32_T (*)[2])
    ssGetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1);
  chartInstance->c2_minSimilarity = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_I = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    2);
  chartInstance->c2_bbox_data = (int32_T (*)[1020])ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c2_bbox_sizes = (int32_T (*)[2])
    ssGetCurrentInputPortDimensions_wrapper(chartInstance->S, 3);
  chartInstance->c2_Label = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_Detection_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(285528201U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2619917546U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(773201372U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(236569642U);
}

mxArray* sf_c2_Detection_get_post_codegen_info(void);
mxArray *sf_c2_Detection_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("qjdMwzYPEQVeSRp1W7DnnG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,3,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(72);
      pr[1] = (double)(104);
      pr[2] = (double)(6);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(255);
      pr[1] = (double)(4);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(8));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(4);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c2_Detection_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_Detection_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_Detection_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "incompatibleSymbol", };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 3, infoFields);
  mxArray *fallbackReason = mxCreateString("feature_off");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxArray *fallbackType = mxCreateString("early");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_Detection_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_Detection_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c2_Detection(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"BBox\",},{M[8],M[0],T\"is_active_c2_Detection\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_Detection_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_DetectionInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc2_DetectionInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _DetectionMachineNumber_,
           2,
           1,
           1,
           0,
           6,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_DetectionMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_DetectionMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _DetectionMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"T");
          _SFD_SET_DATA_PROPS(1,2,0,1,"BBox");
          _SFD_SET_DATA_PROPS(2,1,1,0,"minSimilarity");
          _SFD_SET_DATA_PROPS(3,1,1,0,"I");
          _SFD_SET_DATA_PROPS(4,1,1,0,"bbox");
          _SFD_SET_DATA_PROPS(5,1,1,0,"Label");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,3,0,4,0,10,0,2,1);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,4717);
        _SFD_CV_INIT_EML_SATURATION(0,1,0,1913,-1,1936);
        _SFD_CV_INIT_EML_SATURATION(0,1,1,1913,-1,1938);
        _SFD_CV_INIT_EML_SATURATION(0,1,2,2357,-1,2380);
        _SFD_CV_INIT_EML_SATURATION(0,1,3,2357,-1,2382);
        _SFD_CV_INIT_EML_IF(0,1,0,1302,1355,-1,4712);
        _SFD_CV_INIT_EML_IF(0,1,1,4228,4258,-1,4351);
        _SFD_CV_INIT_EML_IF(0,1,2,4504,4536,-1,4704);
        _SFD_CV_INIT_EML_FOR(0,1,0,1240,1261,4716);
        _SFD_CV_INIT_EML_FOR(0,1,1,2600,2628,4451);
        _SFD_CV_INIT_EML_FOR(0,1,2,2640,2664,4439);
        _SFD_CV_INIT_EML_FOR(0,1,3,2742,2770,4423);
        _SFD_CV_INIT_EML_FOR(0,1,4,2790,2814,4403);
        _SFD_CV_INIT_EML_FOR(0,1,5,3024,3048,3523);
        _SFD_CV_INIT_EML_FOR(0,1,6,3181,3205,3432);
        _SFD_CV_INIT_EML_FOR(0,1,7,3763,3790,4379);
        _SFD_CV_INIT_EML_FOR(0,1,8,3912,3936,4199);
        _SFD_CV_INIT_EML_FOR(0,1,9,3968,3992,4167);

        {
          static int condStart[] = { 1305, 1332 };

          static int condEnd[] = { 1328, 1355 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,1305,1355,2,0,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,1305,1328,-1,5);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,1,1332,1355,-1,5);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,2,4231,4258,-3,4);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,3,4507,4536,-1,5);

        {
          unsigned int dimVector[3];
          dimVector[0]= 72;
          dimVector[1]= 104;
          dimVector[2]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_SINGLE,3,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_SINGLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 255;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_INT32,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_VALUE_PTR(0U, *chartInstance->c2_b_T);
        _SFD_SET_DATA_VALUE_PTR_VAR_DIM(1U, *chartInstance->c2_BBox_data, (void *)
          chartInstance->c2_BBox_sizes);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c2_minSimilarity);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c2_I);
        _SFD_SET_DATA_VALUE_PTR_VAR_DIM(4U, *chartInstance->c2_bbox_data, (void *)
          chartInstance->c2_bbox_sizes);
        _SFD_SET_DATA_VALUE_PTR(5U, chartInstance->c2_Label);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _DetectionMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "AUrc9B6qgh0gMLT7OXqTSB";
}

static void sf_opaque_initialize_c2_Detection(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_DetectionInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c2_Detection((SFc2_DetectionInstanceStruct*)
    chartInstanceVar);
  initialize_c2_Detection((SFc2_DetectionInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_Detection(void *chartInstanceVar)
{
  enable_c2_Detection((SFc2_DetectionInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_Detection(void *chartInstanceVar)
{
  disable_c2_Detection((SFc2_DetectionInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_Detection(void *chartInstanceVar)
{
  sf_gateway_c2_Detection((SFc2_DetectionInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_Detection(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c2_Detection((SFc2_DetectionInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_Detection(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c2_Detection((SFc2_DetectionInstanceStruct*)
    chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c2_Detection(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_DetectionInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Detection_optimization_info();
    }

    finalize_c2_Detection((SFc2_DetectionInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_Detection((SFc2_DetectionInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_Detection(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c2_Detection((SFc2_DetectionInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_Detection(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Detection_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 5; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3814588226U));
  ssSetChecksum1(S,(3818470797U));
  ssSetChecksum2(S,(346703487U));
  ssSetChecksum3(S,(1822294821U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_Detection(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_Detection(SimStruct *S)
{
  SFc2_DetectionInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc2_DetectionInstanceStruct *)utMalloc(sizeof
    (SFc2_DetectionInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_DetectionInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_Detection;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_Detection;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_Detection;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_Detection;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_Detection;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_Detection;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_Detection;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_Detection;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_Detection;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_Detection;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_Detection;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->checksum = SF_RUNTIME_INFO_CHECKSUM;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  crtInfo->compiledInfo = NULL;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_Detection_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_Detection(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_Detection(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_Detection(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_Detection_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
