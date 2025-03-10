#include <iostream>

#include "myproject.h"
#include "parameters.h"


void myproject(
    input_t input_1[N_INPUT_1_1*N_INPUT_2_1*N_INPUT_3_1],
    result_t layer5_out[N_LAYER_5]
) {

    // hls-fpga-machine-learning insert IO
    #pragma HLS ARRAY_RESHAPE variable=input_1 complete dim=0
    #pragma HLS ARRAY_PARTITION variable=layer5_out complete dim=0
    #pragma HLS INTERFACE ap_vld port=input_1,layer5_out 
    #pragma HLS DATAFLOW

    // hls-fpga-machine-learning insert load weights
#ifndef __SYNTHESIS__
    static bool loaded_weights = false;
    if (!loaded_weights) {
        nnet::load_weights_from_txt<separable_conv2d_depthwise_weight_t, 18>(w7, "w7.txt");
        nnet::load_weights_from_txt<bias7_t, 2>(b7, "b7.txt");
        nnet::load_weights_from_txt<separable_conv2d_pointwise_weight_t, 10>(w8, "w8.txt");
        nnet::load_weights_from_txt<bias8_t, 5>(b8, "b8.txt");
        nnet::load_weights_from_txt<dense_weight_t, 360>(w5, "w5.txt");
        nnet::load_weights_from_txt<dense_bias_t, 2>(b5, "b5.txt");
        loaded_weights = true;    }
#endif
    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    // hls-fpga-machine-learning insert layers

    separable_conv2d_depthwise_result_t layer7_out[OUT_HEIGHT_7*OUT_WIDTH_7*N_CHAN_7];
    #pragma HLS ARRAY_PARTITION variable=layer7_out complete dim=0
    nnet::depthwise_conv_2d_cl<input_t, separable_conv2d_depthwise_result_t, config7>(input_1, layer7_out, w7, b7); // separable_conv2d_depthwise

    separable_conv2d_pointwise_result_t layer8_out[OUT_HEIGHT_8*OUT_WIDTH_8*N_FILT_8];
    #pragma HLS ARRAY_PARTITION variable=layer8_out complete dim=0
    nnet::pointwise_conv_2d_cl<separable_conv2d_depthwise_result_t, separable_conv2d_pointwise_result_t, config9>(layer7_out, layer8_out, w8, b8); // separable_conv2d_pointwise

    auto& layer4_out = layer8_out;
    nnet::dense<separable_conv2d_pointwise_result_t, result_t, config5>(layer4_out, layer5_out, w5, b5); // dense

}

