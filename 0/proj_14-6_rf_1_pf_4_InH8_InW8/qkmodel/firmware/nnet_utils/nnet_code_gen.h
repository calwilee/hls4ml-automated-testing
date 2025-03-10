#ifndef NNET_INSTR_GEN_H_
#define NNET_INSTR_GEN_H_

#include "nnet_conv1d_latency.h"
#include "nnet_helpers.h"

#include "hls_stream.h"
#include "nnet_common.h"
#include "nnet_function_stubs.h"
#include "nnet_mult.h"

namespace nnet {

template <class data_T, class res_T, typename CONFIG_T> class PointwiseConv1D {
  public:
    static void pointwise_conv(data_T data[CONFIG_T::in_width * CONFIG_T::n_chan],
                               res_T res[CONFIG_T::out_width * CONFIG_T::n_filt],
                               typename CONFIG_T::weight_t weights[CONFIG_T::n_chan * CONFIG_T::n_filt],
                               typename CONFIG_T::bias_t biases[CONFIG_T::n_filt]) {
        // To be implemented in subclasses
    }
};

// hls4ml insert code
template<class data_T, typename CONFIG_T>
class fill_buffer_7 : public FillConv2DBuffer<data_T, CONFIG_T> {
    public:
    static void fill_buffer(
        data_T data[CONFIG_T::in_height * CONFIG_T::in_width * CONFIG_T::n_chan],
        data_T buffer[CONFIG_T::n_pixels][CONFIG_T::filt_height * CONFIG_T::filt_width * CONFIG_T::n_chan],
        const unsigned partition
    ) {
        if (partition ==   0) {
            buffer[0][0] =    data[0]; buffer[0][1] =    data[1]; buffer[0][2] =    data[2]; buffer[0][3] =    data[3]; buffer[0][4] =    data[4]; buffer[0][5] =    data[5]; buffer[0][6] =   data[16]; buffer[0][7] =   data[17]; buffer[0][8] =   data[18]; buffer[0][9] =   data[19]; buffer[0][10] =   data[20]; buffer[0][11] =   data[21]; buffer[0][12] =   data[32]; buffer[0][13] =   data[33]; buffer[0][14] =   data[34]; buffer[0][15] =   data[35]; buffer[0][16] =   data[36]; buffer[0][17] =   data[37];
            buffer[1][0] =    data[2]; buffer[1][1] =    data[3]; buffer[1][2] =    data[4]; buffer[1][3] =    data[5]; buffer[1][4] =    data[6]; buffer[1][5] =    data[7]; buffer[1][6] =   data[18]; buffer[1][7] =   data[19]; buffer[1][8] =   data[20]; buffer[1][9] =   data[21]; buffer[1][10] =   data[22]; buffer[1][11] =   data[23]; buffer[1][12] =   data[34]; buffer[1][13] =   data[35]; buffer[1][14] =   data[36]; buffer[1][15] =   data[37]; buffer[1][16] =   data[38]; buffer[1][17] =   data[39];
            buffer[2][0] =    data[4]; buffer[2][1] =    data[5]; buffer[2][2] =    data[6]; buffer[2][3] =    data[7]; buffer[2][4] =    data[8]; buffer[2][5] =    data[9]; buffer[2][6] =   data[20]; buffer[2][7] =   data[21]; buffer[2][8] =   data[22]; buffer[2][9] =   data[23]; buffer[2][10] =   data[24]; buffer[2][11] =   data[25]; buffer[2][12] =   data[36]; buffer[2][13] =   data[37]; buffer[2][14] =   data[38]; buffer[2][15] =   data[39]; buffer[2][16] =   data[40]; buffer[2][17] =   data[41];
            buffer[3][0] =    data[6]; buffer[3][1] =    data[7]; buffer[3][2] =    data[8]; buffer[3][3] =    data[9]; buffer[3][4] =   data[10]; buffer[3][5] =   data[11]; buffer[3][6] =   data[22]; buffer[3][7] =   data[23]; buffer[3][8] =   data[24]; buffer[3][9] =   data[25]; buffer[3][10] =   data[26]; buffer[3][11] =   data[27]; buffer[3][12] =   data[38]; buffer[3][13] =   data[39]; buffer[3][14] =   data[40]; buffer[3][15] =   data[41]; buffer[3][16] =   data[42]; buffer[3][17] =   data[43];

        }
        if (partition ==   1) {
            buffer[0][0] =    data[8]; buffer[0][1] =    data[9]; buffer[0][2] =   data[10]; buffer[0][3] =   data[11]; buffer[0][4] =   data[12]; buffer[0][5] =   data[13]; buffer[0][6] =   data[24]; buffer[0][7] =   data[25]; buffer[0][8] =   data[26]; buffer[0][9] =   data[27]; buffer[0][10] =   data[28]; buffer[0][11] =   data[29]; buffer[0][12] =   data[40]; buffer[0][13] =   data[41]; buffer[0][14] =   data[42]; buffer[0][15] =   data[43]; buffer[0][16] =   data[44]; buffer[0][17] =   data[45];
            buffer[1][0] =   data[10]; buffer[1][1] =   data[11]; buffer[1][2] =   data[12]; buffer[1][3] =   data[13]; buffer[1][4] =   data[14]; buffer[1][5] =   data[15]; buffer[1][6] =   data[26]; buffer[1][7] =   data[27]; buffer[1][8] =   data[28]; buffer[1][9] =   data[29]; buffer[1][10] =   data[30]; buffer[1][11] =   data[31]; buffer[1][12] =   data[42]; buffer[1][13] =   data[43]; buffer[1][14] =   data[44]; buffer[1][15] =   data[45]; buffer[1][16] =   data[46]; buffer[1][17] =   data[47];
            buffer[2][0] =   data[16]; buffer[2][1] =   data[17]; buffer[2][2] =   data[18]; buffer[2][3] =   data[19]; buffer[2][4] =   data[20]; buffer[2][5] =   data[21]; buffer[2][6] =   data[32]; buffer[2][7] =   data[33]; buffer[2][8] =   data[34]; buffer[2][9] =   data[35]; buffer[2][10] =   data[36]; buffer[2][11] =   data[37]; buffer[2][12] =   data[48]; buffer[2][13] =   data[49]; buffer[2][14] =   data[50]; buffer[2][15] =   data[51]; buffer[2][16] =   data[52]; buffer[2][17] =   data[53];
            buffer[3][0] =   data[18]; buffer[3][1] =   data[19]; buffer[3][2] =   data[20]; buffer[3][3] =   data[21]; buffer[3][4] =   data[22]; buffer[3][5] =   data[23]; buffer[3][6] =   data[34]; buffer[3][7] =   data[35]; buffer[3][8] =   data[36]; buffer[3][9] =   data[37]; buffer[3][10] =   data[38]; buffer[3][11] =   data[39]; buffer[3][12] =   data[50]; buffer[3][13] =   data[51]; buffer[3][14] =   data[52]; buffer[3][15] =   data[53]; buffer[3][16] =   data[54]; buffer[3][17] =   data[55];

        }
        if (partition ==   2) {
            buffer[0][0] =   data[20]; buffer[0][1] =   data[21]; buffer[0][2] =   data[22]; buffer[0][3] =   data[23]; buffer[0][4] =   data[24]; buffer[0][5] =   data[25]; buffer[0][6] =   data[36]; buffer[0][7] =   data[37]; buffer[0][8] =   data[38]; buffer[0][9] =   data[39]; buffer[0][10] =   data[40]; buffer[0][11] =   data[41]; buffer[0][12] =   data[52]; buffer[0][13] =   data[53]; buffer[0][14] =   data[54]; buffer[0][15] =   data[55]; buffer[0][16] =   data[56]; buffer[0][17] =   data[57];
            buffer[1][0] =   data[22]; buffer[1][1] =   data[23]; buffer[1][2] =   data[24]; buffer[1][3] =   data[25]; buffer[1][4] =   data[26]; buffer[1][5] =   data[27]; buffer[1][6] =   data[38]; buffer[1][7] =   data[39]; buffer[1][8] =   data[40]; buffer[1][9] =   data[41]; buffer[1][10] =   data[42]; buffer[1][11] =   data[43]; buffer[1][12] =   data[54]; buffer[1][13] =   data[55]; buffer[1][14] =   data[56]; buffer[1][15] =   data[57]; buffer[1][16] =   data[58]; buffer[1][17] =   data[59];
            buffer[2][0] =   data[24]; buffer[2][1] =   data[25]; buffer[2][2] =   data[26]; buffer[2][3] =   data[27]; buffer[2][4] =   data[28]; buffer[2][5] =   data[29]; buffer[2][6] =   data[40]; buffer[2][7] =   data[41]; buffer[2][8] =   data[42]; buffer[2][9] =   data[43]; buffer[2][10] =   data[44]; buffer[2][11] =   data[45]; buffer[2][12] =   data[56]; buffer[2][13] =   data[57]; buffer[2][14] =   data[58]; buffer[2][15] =   data[59]; buffer[2][16] =   data[60]; buffer[2][17] =   data[61];
            buffer[3][0] =   data[26]; buffer[3][1] =   data[27]; buffer[3][2] =   data[28]; buffer[3][3] =   data[29]; buffer[3][4] =   data[30]; buffer[3][5] =   data[31]; buffer[3][6] =   data[42]; buffer[3][7] =   data[43]; buffer[3][8] =   data[44]; buffer[3][9] =   data[45]; buffer[3][10] =   data[46]; buffer[3][11] =   data[47]; buffer[3][12] =   data[58]; buffer[3][13] =   data[59]; buffer[3][14] =   data[60]; buffer[3][15] =   data[61]; buffer[3][16] =   data[62]; buffer[3][17] =   data[63];

        }
        if (partition ==   3) {
            buffer[0][0] =   data[32]; buffer[0][1] =   data[33]; buffer[0][2] =   data[34]; buffer[0][3] =   data[35]; buffer[0][4] =   data[36]; buffer[0][5] =   data[37]; buffer[0][6] =   data[48]; buffer[0][7] =   data[49]; buffer[0][8] =   data[50]; buffer[0][9] =   data[51]; buffer[0][10] =   data[52]; buffer[0][11] =   data[53]; buffer[0][12] =   data[64]; buffer[0][13] =   data[65]; buffer[0][14] =   data[66]; buffer[0][15] =   data[67]; buffer[0][16] =   data[68]; buffer[0][17] =   data[69];
            buffer[1][0] =   data[34]; buffer[1][1] =   data[35]; buffer[1][2] =   data[36]; buffer[1][3] =   data[37]; buffer[1][4] =   data[38]; buffer[1][5] =   data[39]; buffer[1][6] =   data[50]; buffer[1][7] =   data[51]; buffer[1][8] =   data[52]; buffer[1][9] =   data[53]; buffer[1][10] =   data[54]; buffer[1][11] =   data[55]; buffer[1][12] =   data[66]; buffer[1][13] =   data[67]; buffer[1][14] =   data[68]; buffer[1][15] =   data[69]; buffer[1][16] =   data[70]; buffer[1][17] =   data[71];
            buffer[2][0] =   data[36]; buffer[2][1] =   data[37]; buffer[2][2] =   data[38]; buffer[2][3] =   data[39]; buffer[2][4] =   data[40]; buffer[2][5] =   data[41]; buffer[2][6] =   data[52]; buffer[2][7] =   data[53]; buffer[2][8] =   data[54]; buffer[2][9] =   data[55]; buffer[2][10] =   data[56]; buffer[2][11] =   data[57]; buffer[2][12] =   data[68]; buffer[2][13] =   data[69]; buffer[2][14] =   data[70]; buffer[2][15] =   data[71]; buffer[2][16] =   data[72]; buffer[2][17] =   data[73];
            buffer[3][0] =   data[38]; buffer[3][1] =   data[39]; buffer[3][2] =   data[40]; buffer[3][3] =   data[41]; buffer[3][4] =   data[42]; buffer[3][5] =   data[43]; buffer[3][6] =   data[54]; buffer[3][7] =   data[55]; buffer[3][8] =   data[56]; buffer[3][9] =   data[57]; buffer[3][10] =   data[58]; buffer[3][11] =   data[59]; buffer[3][12] =   data[70]; buffer[3][13] =   data[71]; buffer[3][14] =   data[72]; buffer[3][15] =   data[73]; buffer[3][16] =   data[74]; buffer[3][17] =   data[75];

        }
        if (partition ==   4) {
            buffer[0][0] =   data[40]; buffer[0][1] =   data[41]; buffer[0][2] =   data[42]; buffer[0][3] =   data[43]; buffer[0][4] =   data[44]; buffer[0][5] =   data[45]; buffer[0][6] =   data[56]; buffer[0][7] =   data[57]; buffer[0][8] =   data[58]; buffer[0][9] =   data[59]; buffer[0][10] =   data[60]; buffer[0][11] =   data[61]; buffer[0][12] =   data[72]; buffer[0][13] =   data[73]; buffer[0][14] =   data[74]; buffer[0][15] =   data[75]; buffer[0][16] =   data[76]; buffer[0][17] =   data[77];
            buffer[1][0] =   data[42]; buffer[1][1] =   data[43]; buffer[1][2] =   data[44]; buffer[1][3] =   data[45]; buffer[1][4] =   data[46]; buffer[1][5] =   data[47]; buffer[1][6] =   data[58]; buffer[1][7] =   data[59]; buffer[1][8] =   data[60]; buffer[1][9] =   data[61]; buffer[1][10] =   data[62]; buffer[1][11] =   data[63]; buffer[1][12] =   data[74]; buffer[1][13] =   data[75]; buffer[1][14] =   data[76]; buffer[1][15] =   data[77]; buffer[1][16] =   data[78]; buffer[1][17] =   data[79];
            buffer[2][0] =   data[48]; buffer[2][1] =   data[49]; buffer[2][2] =   data[50]; buffer[2][3] =   data[51]; buffer[2][4] =   data[52]; buffer[2][5] =   data[53]; buffer[2][6] =   data[64]; buffer[2][7] =   data[65]; buffer[2][8] =   data[66]; buffer[2][9] =   data[67]; buffer[2][10] =   data[68]; buffer[2][11] =   data[69]; buffer[2][12] =   data[80]; buffer[2][13] =   data[81]; buffer[2][14] =   data[82]; buffer[2][15] =   data[83]; buffer[2][16] =   data[84]; buffer[2][17] =   data[85];
            buffer[3][0] =   data[50]; buffer[3][1] =   data[51]; buffer[3][2] =   data[52]; buffer[3][3] =   data[53]; buffer[3][4] =   data[54]; buffer[3][5] =   data[55]; buffer[3][6] =   data[66]; buffer[3][7] =   data[67]; buffer[3][8] =   data[68]; buffer[3][9] =   data[69]; buffer[3][10] =   data[70]; buffer[3][11] =   data[71]; buffer[3][12] =   data[82]; buffer[3][13] =   data[83]; buffer[3][14] =   data[84]; buffer[3][15] =   data[85]; buffer[3][16] =   data[86]; buffer[3][17] =   data[87];

        }
        if (partition ==   5) {
            buffer[0][0] =   data[52]; buffer[0][1] =   data[53]; buffer[0][2] =   data[54]; buffer[0][3] =   data[55]; buffer[0][4] =   data[56]; buffer[0][5] =   data[57]; buffer[0][6] =   data[68]; buffer[0][7] =   data[69]; buffer[0][8] =   data[70]; buffer[0][9] =   data[71]; buffer[0][10] =   data[72]; buffer[0][11] =   data[73]; buffer[0][12] =   data[84]; buffer[0][13] =   data[85]; buffer[0][14] =   data[86]; buffer[0][15] =   data[87]; buffer[0][16] =   data[88]; buffer[0][17] =   data[89];
            buffer[1][0] =   data[54]; buffer[1][1] =   data[55]; buffer[1][2] =   data[56]; buffer[1][3] =   data[57]; buffer[1][4] =   data[58]; buffer[1][5] =   data[59]; buffer[1][6] =   data[70]; buffer[1][7] =   data[71]; buffer[1][8] =   data[72]; buffer[1][9] =   data[73]; buffer[1][10] =   data[74]; buffer[1][11] =   data[75]; buffer[1][12] =   data[86]; buffer[1][13] =   data[87]; buffer[1][14] =   data[88]; buffer[1][15] =   data[89]; buffer[1][16] =   data[90]; buffer[1][17] =   data[91];
            buffer[2][0] =   data[56]; buffer[2][1] =   data[57]; buffer[2][2] =   data[58]; buffer[2][3] =   data[59]; buffer[2][4] =   data[60]; buffer[2][5] =   data[61]; buffer[2][6] =   data[72]; buffer[2][7] =   data[73]; buffer[2][8] =   data[74]; buffer[2][9] =   data[75]; buffer[2][10] =   data[76]; buffer[2][11] =   data[77]; buffer[2][12] =   data[88]; buffer[2][13] =   data[89]; buffer[2][14] =   data[90]; buffer[2][15] =   data[91]; buffer[2][16] =   data[92]; buffer[2][17] =   data[93];
            buffer[3][0] =   data[58]; buffer[3][1] =   data[59]; buffer[3][2] =   data[60]; buffer[3][3] =   data[61]; buffer[3][4] =   data[62]; buffer[3][5] =   data[63]; buffer[3][6] =   data[74]; buffer[3][7] =   data[75]; buffer[3][8] =   data[76]; buffer[3][9] =   data[77]; buffer[3][10] =   data[78]; buffer[3][11] =   data[79]; buffer[3][12] =   data[90]; buffer[3][13] =   data[91]; buffer[3][14] =   data[92]; buffer[3][15] =   data[93]; buffer[3][16] =   data[94]; buffer[3][17] =   data[95];

        }
        if (partition ==   6) {
            buffer[0][0] =   data[64]; buffer[0][1] =   data[65]; buffer[0][2] =   data[66]; buffer[0][3] =   data[67]; buffer[0][4] =   data[68]; buffer[0][5] =   data[69]; buffer[0][6] =   data[80]; buffer[0][7] =   data[81]; buffer[0][8] =   data[82]; buffer[0][9] =   data[83]; buffer[0][10] =   data[84]; buffer[0][11] =   data[85]; buffer[0][12] =   data[96]; buffer[0][13] =   data[97]; buffer[0][14] =   data[98]; buffer[0][15] =   data[99]; buffer[0][16] =  data[100]; buffer[0][17] =  data[101];
            buffer[1][0] =   data[66]; buffer[1][1] =   data[67]; buffer[1][2] =   data[68]; buffer[1][3] =   data[69]; buffer[1][4] =   data[70]; buffer[1][5] =   data[71]; buffer[1][6] =   data[82]; buffer[1][7] =   data[83]; buffer[1][8] =   data[84]; buffer[1][9] =   data[85]; buffer[1][10] =   data[86]; buffer[1][11] =   data[87]; buffer[1][12] =   data[98]; buffer[1][13] =   data[99]; buffer[1][14] =  data[100]; buffer[1][15] =  data[101]; buffer[1][16] =  data[102]; buffer[1][17] =  data[103];
            buffer[2][0] =   data[68]; buffer[2][1] =   data[69]; buffer[2][2] =   data[70]; buffer[2][3] =   data[71]; buffer[2][4] =   data[72]; buffer[2][5] =   data[73]; buffer[2][6] =   data[84]; buffer[2][7] =   data[85]; buffer[2][8] =   data[86]; buffer[2][9] =   data[87]; buffer[2][10] =   data[88]; buffer[2][11] =   data[89]; buffer[2][12] =  data[100]; buffer[2][13] =  data[101]; buffer[2][14] =  data[102]; buffer[2][15] =  data[103]; buffer[2][16] =  data[104]; buffer[2][17] =  data[105];
            buffer[3][0] =   data[70]; buffer[3][1] =   data[71]; buffer[3][2] =   data[72]; buffer[3][3] =   data[73]; buffer[3][4] =   data[74]; buffer[3][5] =   data[75]; buffer[3][6] =   data[86]; buffer[3][7] =   data[87]; buffer[3][8] =   data[88]; buffer[3][9] =   data[89]; buffer[3][10] =   data[90]; buffer[3][11] =   data[91]; buffer[3][12] =  data[102]; buffer[3][13] =  data[103]; buffer[3][14] =  data[104]; buffer[3][15] =  data[105]; buffer[3][16] =  data[106]; buffer[3][17] =  data[107];

        }
        if (partition ==   7) {
            buffer[0][0] =   data[72]; buffer[0][1] =   data[73]; buffer[0][2] =   data[74]; buffer[0][3] =   data[75]; buffer[0][4] =   data[76]; buffer[0][5] =   data[77]; buffer[0][6] =   data[88]; buffer[0][7] =   data[89]; buffer[0][8] =   data[90]; buffer[0][9] =   data[91]; buffer[0][10] =   data[92]; buffer[0][11] =   data[93]; buffer[0][12] =  data[104]; buffer[0][13] =  data[105]; buffer[0][14] =  data[106]; buffer[0][15] =  data[107]; buffer[0][16] =  data[108]; buffer[0][17] =  data[109];
            buffer[1][0] =   data[74]; buffer[1][1] =   data[75]; buffer[1][2] =   data[76]; buffer[1][3] =   data[77]; buffer[1][4] =   data[78]; buffer[1][5] =   data[79]; buffer[1][6] =   data[90]; buffer[1][7] =   data[91]; buffer[1][8] =   data[92]; buffer[1][9] =   data[93]; buffer[1][10] =   data[94]; buffer[1][11] =   data[95]; buffer[1][12] =  data[106]; buffer[1][13] =  data[107]; buffer[1][14] =  data[108]; buffer[1][15] =  data[109]; buffer[1][16] =  data[110]; buffer[1][17] =  data[111];
            buffer[2][0] =   data[80]; buffer[2][1] =   data[81]; buffer[2][2] =   data[82]; buffer[2][3] =   data[83]; buffer[2][4] =   data[84]; buffer[2][5] =   data[85]; buffer[2][6] =   data[96]; buffer[2][7] =   data[97]; buffer[2][8] =   data[98]; buffer[2][9] =   data[99]; buffer[2][10] =  data[100]; buffer[2][11] =  data[101]; buffer[2][12] =  data[112]; buffer[2][13] =  data[113]; buffer[2][14] =  data[114]; buffer[2][15] =  data[115]; buffer[2][16] =  data[116]; buffer[2][17] =  data[117];
            buffer[3][0] =   data[82]; buffer[3][1] =   data[83]; buffer[3][2] =   data[84]; buffer[3][3] =   data[85]; buffer[3][4] =   data[86]; buffer[3][5] =   data[87]; buffer[3][6] =   data[98]; buffer[3][7] =   data[99]; buffer[3][8] =  data[100]; buffer[3][9] =  data[101]; buffer[3][10] =  data[102]; buffer[3][11] =  data[103]; buffer[3][12] =  data[114]; buffer[3][13] =  data[115]; buffer[3][14] =  data[116]; buffer[3][15] =  data[117]; buffer[3][16] =  data[118]; buffer[3][17] =  data[119];

        }
        if (partition ==   8) {
            buffer[0][0] =   data[84]; buffer[0][1] =   data[85]; buffer[0][2] =   data[86]; buffer[0][3] =   data[87]; buffer[0][4] =   data[88]; buffer[0][5] =   data[89]; buffer[0][6] =  data[100]; buffer[0][7] =  data[101]; buffer[0][8] =  data[102]; buffer[0][9] =  data[103]; buffer[0][10] =  data[104]; buffer[0][11] =  data[105]; buffer[0][12] =  data[116]; buffer[0][13] =  data[117]; buffer[0][14] =  data[118]; buffer[0][15] =  data[119]; buffer[0][16] =  data[120]; buffer[0][17] =  data[121];
            buffer[1][0] =   data[86]; buffer[1][1] =   data[87]; buffer[1][2] =   data[88]; buffer[1][3] =   data[89]; buffer[1][4] =   data[90]; buffer[1][5] =   data[91]; buffer[1][6] =  data[102]; buffer[1][7] =  data[103]; buffer[1][8] =  data[104]; buffer[1][9] =  data[105]; buffer[1][10] =  data[106]; buffer[1][11] =  data[107]; buffer[1][12] =  data[118]; buffer[1][13] =  data[119]; buffer[1][14] =  data[120]; buffer[1][15] =  data[121]; buffer[1][16] =  data[122]; buffer[1][17] =  data[123];
            buffer[2][0] =   data[88]; buffer[2][1] =   data[89]; buffer[2][2] =   data[90]; buffer[2][3] =   data[91]; buffer[2][4] =   data[92]; buffer[2][5] =   data[93]; buffer[2][6] =  data[104]; buffer[2][7] =  data[105]; buffer[2][8] =  data[106]; buffer[2][9] =  data[107]; buffer[2][10] =  data[108]; buffer[2][11] =  data[109]; buffer[2][12] =  data[120]; buffer[2][13] =  data[121]; buffer[2][14] =  data[122]; buffer[2][15] =  data[123]; buffer[2][16] =  data[124]; buffer[2][17] =  data[125];
            buffer[3][0] =   data[90]; buffer[3][1] =   data[91]; buffer[3][2] =   data[92]; buffer[3][3] =   data[93]; buffer[3][4] =   data[94]; buffer[3][5] =   data[95]; buffer[3][6] =  data[106]; buffer[3][7] =  data[107]; buffer[3][8] =  data[108]; buffer[3][9] =  data[109]; buffer[3][10] =  data[110]; buffer[3][11] =  data[111]; buffer[3][12] =  data[122]; buffer[3][13] =  data[123]; buffer[3][14] =  data[124]; buffer[3][15] =  data[125]; buffer[3][16] =  data[126]; buffer[3][17] =  data[127];

        }
    }
};
template<class data_T, typename CONFIG_T>
class fill_buffer_9 : public FillConv2DBuffer<data_T, CONFIG_T> {
    public:
    static void fill_buffer(
        data_T data[CONFIG_T::in_height * CONFIG_T::in_width * CONFIG_T::n_chan],
        data_T buffer[CONFIG_T::n_pixels][CONFIG_T::filt_height * CONFIG_T::filt_width * CONFIG_T::n_chan],
        const unsigned partition
    ) {
        if (partition ==   0) {
            buffer[0][0] =    data[0]; buffer[0][1] =    data[1];
            buffer[1][0] =    data[2]; buffer[1][1] =    data[3];
            buffer[2][0] =    data[4]; buffer[2][1] =    data[5];
            buffer[3][0] =    data[6]; buffer[3][1] =    data[7];

        }
        if (partition ==   1) {
            buffer[0][0] =    data[8]; buffer[0][1] =    data[9];
            buffer[1][0] =   data[10]; buffer[1][1] =   data[11];
            buffer[2][0] =   data[12]; buffer[2][1] =   data[13];
            buffer[3][0] =   data[14]; buffer[3][1] =   data[15];

        }
        if (partition ==   2) {
            buffer[0][0] =   data[16]; buffer[0][1] =   data[17];
            buffer[1][0] =   data[18]; buffer[1][1] =   data[19];
            buffer[2][0] =   data[20]; buffer[2][1] =   data[21];
            buffer[3][0] =   data[22]; buffer[3][1] =   data[23];

        }
        if (partition ==   3) {
            buffer[0][0] =   data[24]; buffer[0][1] =   data[25];
            buffer[1][0] =   data[26]; buffer[1][1] =   data[27];
            buffer[2][0] =   data[28]; buffer[2][1] =   data[29];
            buffer[3][0] =   data[30]; buffer[3][1] =   data[31];

        }
        if (partition ==   4) {
            buffer[0][0] =   data[32]; buffer[0][1] =   data[33];
            buffer[1][0] =   data[34]; buffer[1][1] =   data[35];
            buffer[2][0] =   data[36]; buffer[2][1] =   data[37];
            buffer[3][0] =   data[38]; buffer[3][1] =   data[39];

        }
        if (partition ==   5) {
            buffer[0][0] =   data[40]; buffer[0][1] =   data[41];
            buffer[1][0] =   data[42]; buffer[1][1] =   data[43];
            buffer[2][0] =   data[44]; buffer[2][1] =   data[45];
            buffer[3][0] =   data[46]; buffer[3][1] =   data[47];

        }
        if (partition ==   6) {
            buffer[0][0] =   data[48]; buffer[0][1] =   data[49];
            buffer[1][0] =   data[50]; buffer[1][1] =   data[51];
            buffer[2][0] =   data[52]; buffer[2][1] =   data[53];
            buffer[3][0] =   data[54]; buffer[3][1] =   data[55];

        }
        if (partition ==   7) {
            buffer[0][0] =   data[56]; buffer[0][1] =   data[57];
            buffer[1][0] =   data[58]; buffer[1][1] =   data[59];
            buffer[2][0] =   data[60]; buffer[2][1] =   data[61];
            buffer[3][0] =   data[62]; buffer[3][1] =   data[63];

        }
        if (partition ==   8) {
            buffer[0][0] =   data[64]; buffer[0][1] =   data[65];
            buffer[1][0] =   data[66]; buffer[1][1] =   data[67];
            buffer[2][0] =   data[68]; buffer[2][1] =   data[69];
            buffer[3][0] =   data[70]; buffer[3][1] =   data[71];

        }
    }
};

} // namespace nnet

#endif
