#include "dense_latency_ap_fixed_ap_fixed_78_40_5_3_0_config5_0_0_0.h"
#include "AESL_pkg.h"

using namespace std;

namespace ap_rtl {

void dense_latency_ap_fixed_ap_fixed_78_40_5_3_0_config5_0_0_0::thread_ap_clk_no_reset_() {
    if ( ap_rst.read() == ap_const_logic_1) {
        ap_CS_fsm = ap_ST_fsm_pp0_stage0;
    } else {
        ap_CS_fsm = ap_NS_fsm.read();
    }
    if ( ap_rst.read() == ap_const_logic_1) {
        ap_done_reg = ap_const_logic_0;
    } else {
        if (esl_seteq<1,1,1>(ap_const_logic_1, ap_continue.read())) {
            ap_done_reg = ap_const_logic_0;
        } else if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp0_stage0.read()) && 
                    esl_seteq<1,1,1>(ap_block_pp0_stage0_11001.read(), ap_const_boolean_0) && 
                    esl_seteq<1,1,1>(ap_const_logic_1, ap_enable_reg_pp0_iter1.read()))) {
            ap_done_reg = ap_const_logic_1;
        }
    }
    if ( ap_rst.read() == ap_const_logic_1) {
        ap_enable_reg_pp0_iter1 = ap_const_logic_0;
    } else {
        if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp0_stage0.read()) && 
             esl_seteq<1,1,1>(ap_block_pp0_stage0_subdone.read(), ap_const_boolean_0))) {
            ap_enable_reg_pp0_iter1 = ap_start.read();
        }
    }
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_pp0_stage0.read()) && esl_seteq<1,1,1>(ap_block_pp0_stage0_11001.read(), ap_const_boolean_0))) {
        add_ln703_100_reg_391324 = add_ln703_100_fu_388627_p2.read();
        add_ln703_101_reg_391329 = add_ln703_101_fu_388633_p2.read();
        add_ln703_107_reg_391334 = add_ln703_107_fu_388639_p2.read();
        add_ln703_108_reg_391339 = add_ln703_108_fu_388645_p2.read();
        add_ln703_112_reg_391344 = add_ln703_112_fu_388657_p2.read();
        add_ln703_114_reg_391349 = add_ln703_114_fu_388669_p2.read();
        add_ln703_117_reg_391354 = add_ln703_117_fu_388675_p2.read();
        add_ln703_118_reg_391359 = add_ln703_118_fu_388681_p2.read();
        add_ln703_121_reg_391364 = add_ln703_121_fu_388687_p2.read();
        add_ln703_123_reg_391369 = add_ln703_123_fu_388693_p2.read();
        add_ln703_128_reg_391374 = add_ln703_128_fu_388699_p2.read();
        add_ln703_129_reg_391379 = add_ln703_129_fu_388705_p2.read();
        add_ln703_133_reg_391384 = add_ln703_133_fu_388717_p2.read();
        add_ln703_135_reg_391389 = add_ln703_135_fu_388729_p2.read();
        add_ln703_139_reg_391394 = add_ln703_139_fu_388741_p2.read();
        add_ln703_140_reg_391399 = add_ln703_140_fu_388747_p2.read();
        add_ln703_144_reg_391404 = add_ln703_144_fu_388759_p2.read();
        add_ln703_145_reg_391409 = add_ln703_145_fu_388765_p2.read();
        add_ln703_152_reg_391414 = add_ln703_152_fu_388771_p2.read();
        add_ln703_153_reg_391419 = add_ln703_153_fu_388777_p2.read();
        add_ln703_157_reg_391424 = add_ln703_157_fu_388789_p2.read();
        add_ln703_159_reg_391429 = add_ln703_159_fu_388801_p2.read();
        add_ln703_162_reg_391434 = add_ln703_162_fu_388807_p2.read();
        add_ln703_163_reg_391439 = add_ln703_163_fu_388813_p2.read();
        add_ln703_166_reg_391444 = add_ln703_166_fu_388819_p2.read();
        add_ln703_168_reg_391449 = add_ln703_168_fu_388825_p2.read();
        add_ln703_175_reg_391454 = add_ln703_175_fu_388837_p2.read();
        add_ln703_178_reg_391459 = add_ln703_178_fu_388849_p2.read();
        add_ln703_179_reg_391464 = add_ln703_179_fu_388855_p2.read();
        add_ln703_184_reg_391469 = add_ln703_184_fu_388867_p2.read();
        add_ln703_185_reg_391474 = add_ln703_185_fu_388873_p2.read();
        add_ln703_189_reg_391479 = add_ln703_189_fu_388885_p2.read();
        add_ln703_191_reg_391484 = add_ln703_191_fu_388897_p2.read();
        add_ln703_196_reg_391489 = add_ln703_196_fu_388903_p2.read();
        add_ln703_197_reg_391494 = add_ln703_197_fu_388909_p2.read();
        add_ln703_201_reg_391499 = add_ln703_201_fu_388921_p2.read();
        add_ln703_202_reg_391504 = add_ln703_202_fu_388927_p2.read();
        add_ln703_206_reg_391509 = add_ln703_206_fu_388933_p2.read();
        add_ln703_207_reg_391514 = add_ln703_207_fu_388939_p2.read();
        add_ln703_210_reg_391519 = add_ln703_210_fu_388945_p2.read();
        add_ln703_212_reg_391524 = add_ln703_212_fu_388951_p2.read();
        add_ln703_217_reg_391529 = add_ln703_217_fu_388957_p2.read();
        add_ln703_218_reg_391534 = add_ln703_218_fu_388963_p2.read();
        add_ln703_222_reg_391539 = add_ln703_222_fu_388975_p2.read();
        add_ln703_224_reg_391544 = add_ln703_224_fu_388987_p2.read();
        add_ln703_228_reg_391549 = add_ln703_228_fu_388999_p2.read();
        add_ln703_229_reg_391554 = add_ln703_229_fu_389005_p2.read();
        add_ln703_233_reg_391559 = add_ln703_233_fu_389021_p2.read();
        add_ln703_235_reg_391564 = add_ln703_235_fu_389037_p2.read();
        add_ln703_242_reg_391569 = add_ln703_242_fu_389043_p2.read();
        add_ln703_243_reg_391574 = add_ln703_243_fu_389049_p2.read();
        add_ln703_247_reg_391579 = add_ln703_247_fu_389061_p2.read();
        add_ln703_249_reg_391584 = add_ln703_249_fu_389073_p2.read();
        add_ln703_252_reg_391589 = add_ln703_252_fu_389079_p2.read();
        add_ln703_253_reg_391594 = add_ln703_253_fu_389085_p2.read();
        add_ln703_257_reg_391599 = add_ln703_257_fu_389097_p2.read();
        add_ln703_258_reg_391604 = add_ln703_258_fu_389103_p2.read();
        add_ln703_263_reg_391609 = add_ln703_263_fu_389109_p2.read();
        add_ln703_264_reg_391614 = add_ln703_264_fu_389115_p2.read();
        add_ln703_268_reg_391619 = add_ln703_268_fu_389127_p2.read();
        add_ln703_269_reg_391624 = add_ln703_269_fu_389133_p2.read();
        add_ln703_274_reg_391629 = add_ln703_274_fu_389145_p2.read();
        add_ln703_275_reg_391634 = add_ln703_275_fu_389151_p2.read();
        add_ln703_279_reg_391639 = add_ln703_279_fu_389163_p2.read();
        add_ln703_281_reg_391644 = add_ln703_281_fu_389175_p2.read();
        add_ln703_286_reg_391649 = add_ln703_286_fu_389181_p2.read();
        add_ln703_287_reg_391654 = add_ln703_287_fu_389187_p2.read();
        add_ln703_290_reg_391659 = add_ln703_290_fu_389193_p2.read();
        add_ln703_293_reg_391664 = add_ln703_293_fu_389205_p2.read();
        add_ln703_296_reg_391669 = add_ln703_296_fu_389211_p2.read();
        add_ln703_297_reg_391674 = add_ln703_297_fu_389217_p2.read();
        add_ln703_301_reg_391679 = add_ln703_301_fu_389229_p2.read();
        add_ln703_302_reg_391684 = add_ln703_302_fu_389235_p2.read();
        add_ln703_307_reg_391689 = add_ln703_307_fu_389241_p2.read();
        add_ln703_308_reg_391694 = add_ln703_308_fu_389247_p2.read();
        add_ln703_311_reg_391699 = add_ln703_311_fu_389253_p2.read();
        add_ln703_313_reg_391704 = add_ln703_313_fu_389259_p2.read();
        add_ln703_318_reg_391709 = add_ln703_318_fu_389271_p2.read();
        add_ln703_319_reg_391714 = add_ln703_319_fu_389277_p2.read();
        add_ln703_323_reg_391719 = add_ln703_323_fu_389289_p2.read();
        add_ln703_324_reg_391724 = add_ln703_324_fu_389295_p2.read();
        add_ln703_331_reg_391729 = add_ln703_331_fu_389301_p2.read();
        add_ln703_332_reg_391734 = add_ln703_332_fu_389307_p2.read();
        add_ln703_336_reg_391739 = add_ln703_336_fu_389319_p2.read();
        add_ln703_338_reg_391744 = add_ln703_338_fu_389331_p2.read();
        add_ln703_341_reg_391749 = add_ln703_341_fu_389337_p2.read();
        add_ln703_342_reg_391754 = add_ln703_342_fu_389343_p2.read();
        add_ln703_346_reg_391759 = add_ln703_346_fu_389355_p2.read();
        add_ln703_347_reg_391764 = add_ln703_347_fu_389361_p2.read();
        add_ln703_353_reg_391769 = add_ln703_353_fu_389367_p2.read();
        add_ln703_357_reg_391774 = add_ln703_357_fu_389379_p2.read();
        add_ln703_359_reg_391779 = add_ln703_359_fu_389391_p2.read();
        add_ln703_363_reg_391784 = add_ln703_363_fu_389403_p2.read();
        add_ln703_364_reg_391789 = add_ln703_364_fu_389409_p2.read();
        add_ln703_368_reg_391794 = add_ln703_368_fu_389421_p2.read();
        add_ln703_369_reg_391799 = add_ln703_369_fu_389427_p2.read();
        add_ln703_375_reg_391804 = add_ln703_375_fu_389433_p2.read();
        add_ln703_376_reg_391809 = add_ln703_376_fu_389439_p2.read();
        add_ln703_380_reg_391814 = add_ln703_380_fu_389451_p2.read();
        add_ln703_381_reg_391819 = add_ln703_381_fu_389457_p2.read();
        add_ln703_385_reg_391824 = add_ln703_385_fu_389463_p2.read();
        add_ln703_386_reg_391829 = add_ln703_386_fu_389469_p2.read();
        add_ln703_390_reg_391834 = add_ln703_390_fu_389481_p2.read();
        add_ln703_391_reg_391839 = add_ln703_391_fu_389487_p2.read();
        add_ln703_396_reg_391844 = add_ln703_396_fu_389493_p2.read();
        add_ln703_398_reg_391849 = add_ln703_398_fu_389505_p2.read();
        add_ln703_401_reg_391854 = add_ln703_401_fu_389517_p2.read();
        add_ln703_403_reg_391859 = add_ln703_403_fu_389529_p2.read();
        add_ln703_407_reg_391864 = add_ln703_407_fu_389541_p2.read();
        add_ln703_409_reg_391869 = add_ln703_409_fu_389553_p2.read();
        add_ln703_415_reg_391874 = add_ln703_415_fu_389595_p2.read();
        add_ln703_64_reg_391259 = add_ln703_64_fu_388503_p2.read();
        add_ln703_68_reg_391264 = add_ln703_68_fu_388515_p2.read();
        add_ln703_70_reg_391269 = add_ln703_70_fu_388527_p2.read();
        add_ln703_73_reg_391274 = add_ln703_73_fu_388533_p2.read();
        add_ln703_75_reg_391279 = add_ln703_75_fu_388545_p2.read();
        add_ln703_77_reg_391284 = add_ln703_77_fu_388551_p2.read();
        add_ln703_79_reg_391289 = add_ln703_79_fu_388557_p2.read();
        add_ln703_84_reg_391294 = add_ln703_84_fu_388563_p2.read();
        add_ln703_85_reg_391299 = add_ln703_85_fu_388569_p2.read();
        add_ln703_89_reg_391304 = add_ln703_89_fu_388585_p2.read();
        add_ln703_91_reg_391309 = add_ln703_91_fu_388597_p2.read();
        add_ln703_95_reg_391314 = add_ln703_95_fu_388609_p2.read();
        add_ln703_96_reg_391319 = add_ln703_96_fu_388615_p2.read();
        add_ln703_reg_391254 = add_ln703_fu_388497_p2.read();
        mult_102_V_reg_391049 = mult_102_V_fu_382362_p1.read();
        tmp_116_reg_391209 = add_ln1118_15_fu_386866_p2.read().range(40, 28);
        tmp_21_reg_390999 = mul_ln1118_28_fu_2104_p2.read().range(40, 28);
        tmp_87_reg_391174 = mul_ln1118_174_fu_1952_p2.read().range(41, 28);
        trunc_ln708_101_reg_391099 = mul_ln1118_120_fu_1936_p2.read().range(42, 28);
        trunc_ln708_103_reg_391104 = mul_ln1118_124_fu_2159_p2.read().range(41, 28);
        trunc_ln708_112_reg_391109 = mul_ln1118_132_fu_2211_p2.read().range(41, 28);
        trunc_ln708_115_reg_391114 = mul_ln1118_135_fu_2205_p2.read().range(42, 28);
        trunc_ln708_120_reg_391119 = mul_ln1118_142_fu_1940_p2.read().range(41, 28);
        trunc_ln708_123_reg_391124 = mul_ln1118_145_fu_2087_p2.read().range(42, 28);
        trunc_ln708_137_reg_391129 = sub_ln1118_45_fu_384765_p2.read().range(38, 28);
        trunc_ln708_139_reg_391134 = mul_ln1118_161_fu_2151_p2.read().range(42, 28);
        trunc_ln708_142_reg_391139 = mul_ln1118_163_fu_2163_p2.read().range(42, 28);
        trunc_ln708_143_reg_391144 = mul_ln1118_167_fu_2227_p2.read().range(41, 28);
        trunc_ln708_144_reg_391149 = sub_ln1118_48_fu_385150_p2.read().range(40, 28);
        trunc_ln708_149_reg_391154 = mul_ln1118_170_fu_2240_p2.read().range(42, 28);
        trunc_ln708_151_reg_391159 = sub_ln1118_52_fu_385366_p2.read().range(38, 28);
        trunc_ln708_152_reg_391164 = mul_ln1118_171_fu_2273_p2.read().range(42, 28);
        trunc_ln708_153_reg_391169 = sub_ln1118_53_fu_385435_p2.read().range(41, 28);
        trunc_ln708_154_reg_391179 = mul_ln1118_179_fu_1991_p2.read().range(42, 28);
        trunc_ln708_159_reg_391184 = sub_ln1118_64_fu_386121_p2.read().range(39, 28);
        trunc_ln708_162_reg_391189 = mul_ln1118_188_fu_2006_p2.read().range(41, 28);
        trunc_ln708_169_reg_391194 = mul_ln1118_200_fu_2247_p2.read().range(42, 28);
        trunc_ln708_173_reg_391199 = mul_ln1118_206_fu_2270_p2.read().range(42, 28);
        trunc_ln708_174_reg_391204 = sub_ln1118_66_fu_386625_p2.read().range(40, 28);
        trunc_ln708_17_reg_390989 = sub_ln1118_7_fu_380616_p2.read().range(35, 28);
        trunc_ln708_183_reg_391214 = sub_ln1118_69_fu_386927_p2.read().range(35, 28);
        trunc_ln708_186_reg_391219 = mul_ln1118_221_fu_2170_p2.read().range(41, 28);
        trunc_ln708_188_reg_391224 = sub_ln1118_73_fu_387195_p2.read().range(41, 28);
        trunc_ln708_191_reg_391229 = mul_ln1118_225_fu_2261_p2.read().range(41, 28);
        trunc_ln708_195_reg_391234 = add_ln1118_17_fu_387384_p2.read().range(41, 28);
        trunc_ln708_198_reg_391239 = mul_ln1118_233_fu_2244_p2.read().range(40, 28);
        trunc_ln708_19_reg_390994 = mul_ln1118_23_fu_2212_p2.read().range(42, 28);
        trunc_ln708_1_reg_390979 = mul_ln1118_4_fu_2263_p2.read().range(42, 28);
        trunc_ln708_202_reg_391244 = mul_ln1118_238_fu_2046_p2.read().range(42, 28);
        trunc_ln708_213_reg_391249 = mul_ln1118_254_fu_2181_p2.read().range(42, 28);
        trunc_ln708_22_reg_391004 = mul_ln1118_30_fu_2213_p2.read().range(42, 28);
        trunc_ln708_26_reg_391009 = mul_ln1118_35_fu_1969_p2.read().range(41, 28);
        trunc_ln708_28_reg_391014 = mul_ln1118_37_fu_2035_p2.read().range(40, 28);
        trunc_ln708_2_reg_390984 = mul_ln1118_5_fu_2066_p2.read().range(42, 28);
        trunc_ln708_36_reg_391019 = mul_ln1118_46_fu_2141_p2.read().range(41, 28);
        trunc_ln708_38_reg_391024 = sub_ln1118_20_fu_381713_p2.read().range(41, 28);
        trunc_ln708_40_reg_391029 = mul_ln1118_54_fu_1956_p2.read().range(39, 28);
        trunc_ln708_49_reg_391034 = mul_ln1118_62_fu_2143_p2.read().range(42, 28);
        trunc_ln708_54_reg_391039 = mul_ln1118_69_fu_2236_p2.read().range(42, 28);
        trunc_ln708_56_reg_391044 = mul_ln1118_72_fu_2037_p2.read().range(42, 28);
        trunc_ln708_69_reg_391054 = mul_ln1118_86_fu_2052_p2.read().range(42, 28);
        trunc_ln708_72_reg_391059 = mul_ln1118_88_fu_2267_p2.read().range(42, 28);
        trunc_ln708_75_reg_391064 = mul_ln1118_91_fu_2214_p2.read().range(42, 28);
        trunc_ln708_77_reg_391069 = mul_ln1118_96_fu_2065_p2.read().range(42, 28);
        trunc_ln708_78_reg_391074 = mul_ln1118_99_fu_2157_p2.read().range(41, 28);
        trunc_ln708_82_reg_391079 = mul_ln1118_103_fu_2009_p2.read().range(42, 28);
        trunc_ln708_84_reg_391084 = mul_ln1118_104_fu_2012_p2.read().range(42, 28);
        trunc_ln708_89_reg_391089 = mul_ln1118_107_fu_2278_p2.read().range(41, 28);
        trunc_ln708_93_reg_391094 = mul_ln1118_112_fu_2001_p2.read().range(42, 28);
    }
}

void dense_latency_ap_fixed_ap_fixed_78_40_5_3_0_config5_0_0_0::thread_ap_NS_fsm() {
    switch (ap_CS_fsm.read().to_uint64()) {
        case 1 : 
            ap_NS_fsm = ap_ST_fsm_pp0_stage0;
break;
        default : 
            ap_NS_fsm = "X";
            break;
    }
}

}

