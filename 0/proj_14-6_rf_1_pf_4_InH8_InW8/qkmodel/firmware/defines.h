#ifndef DEFINES_H_
#define DEFINES_H_

#include "ap_fixed.h"
#include "ap_int.h"
#include "nnet_utils/nnet_types.h"
#include <cstddef>
#include <cstdio>

// hls-fpga-machine-learning insert numbers
#define N_INPUT_1_1 8
#define N_INPUT_2_1 8
#define N_INPUT_3_1 2
#define OUT_HEIGHT_7 6
#define OUT_WIDTH_7 6
#define N_CHAN_7 2
#define OUT_HEIGHT_8 6
#define OUT_WIDTH_8 6
#define N_FILT_8 5
#define N_SIZE_0_4 180
#define N_LAYER_5 2


// hls-fpga-machine-learning insert layer-precision
typedef ap_fixed<14,6> input_t;
typedef ap_fixed<16,6> model_default_t;
typedef ap_fixed<35,17> separable_conv2d_depthwise_result_t;
typedef ap_fixed<16,6> separable_conv2d_depthwise_weight_t;
typedef ap_uint<1> bias7_t;
typedef ap_fixed<53,25> separable_conv2d_pointwise_result_t;
typedef ap_fixed<16,6> separable_conv2d_pointwise_weight_t;
typedef ap_uint<1> bias8_t;
typedef ap_fixed<78,40> result_t;
typedef ap_fixed<16,6> dense_weight_t;
typedef ap_fixed<16,6> dense_bias_t;
typedef ap_uint<1> layer5_index;


#endif
