#Script that automates modelTest.ipynb #################

import matplotlib.pyplot as plt
import numpy as np
import argparse
import yaml
import tensorflow as tf
from tensorflow.keras import datasets, layers, models
from tensorflow import keras
from tensorflow.keras.layers import Input, Flatten
from tensorflow.keras.models import Sequential
from qkeras import *
import os

import json


def main(args):

    # Parsing yaml into a dictionary
    print("\n Reading conversion specs from ", args.testConfigs, "\n")

    def parse_yaml(file_path):
        with open(file_path, 'r') as file:
            return yaml.safe_load(file)
    
    specs = parse_yaml(args.testConfigs)

    
    #Use dictionary to set arguments

    LAYER = specs['LAYER'] # uses both depthwise and pointwise
    RUN_HLS = specs['RUN_HLS']
    IO_TYPE = specs['IO_TYPE']
    STRATEGY = specs['STRATEGY']
    BACKEND = specs['BACKEND']
    TRACE = specs['TRACE']

    H = specs['Height']  # Input height
    W = specs['Width']  # Input width
    FXD_W = specs['Bitwidth'] # Fixed-point precision, word bit width
    FXD_I = specs['Int_Width'] # Fixed-point precision, integer-part bit width
    reuseFactor = specs['reuseFactor']
    parallelFactor = specs['parallelFactor']


    Din = specs["Channels"]  # Input # of channels    
    Fh = specs["Filter_Height"]   # Kernel height   
    Fw = specs["Filter_Width"]  # Kernel width  
    Dout = specs['Filters'] # Kernel # of filters 


    os.environ['PATH'] = f'/data/software/xilinx/{BACKEND}/{VERSION}/bin:' + os.environ['PATH'] #Mulder

#Define a keras model 

    def CreateKerasModel(layer, input_shape, kernel_size, filters):
    
        x_in = Input(input_shape, name='input_1')
        if layer == 'depthwise_conv2d':
            x = DepthwiseConv2D(
                kernel_size=kernel_size,
                use_bias=False,
                depthwise_initializer=tf.keras.initializers.Ones(), # makes debugging easy
                bias_initializer=tf.keras.initializers.Zeros(), # makes debugging easy
                name='depthwise_conv2d'
            )(x_in)
        elif layer == 'pointwise_conv2d':
            x_out = Conv2D(
                filters=filters,
                kernel_size=(1,1),
                use_bias=False,
                kernel_initializer=tf.keras.initializers.Ones(), # makes debugging easy
                bias_initializer=tf.keras.initializers.Zeros(), # makes debugging easy
                name='pointwise_conv2d'
            )(x_in)
        else:
            x= SeparableConv2D(
                filters=filters,
                kernel_size=kernel_size,
                use_bias=False,
                depthwise_initializer=tf.keras.initializers.Ones(), # makes debugging easy
                pointwise_initializer=tf.keras.initializers.Ones(), # makes debugging easy
                name = 'separable_conv2d'
        )(x_in)
        x = Flatten()(x)
        x_out = Dense(2)(x)
        kmodel = Model(inputs=x_in, outputs=x_out)
        return kmodel
    
    kmodel = CreateKerasModel(LAYER, input_shape=(H,W,Din), kernel_size=(Fh, Fw), filters=Dout)

#Define random dataset
    X_train = np.random.rand(10,H,W,Din)  
    y_train = np.random.randint(2, size=(10,))

#Compile model
    kmodel.compile(loss="binary_crossentropy", optimizer=tf.keras.optimizers.Adam(
        learning_rate=0.001), metrics=["binary_accuracy"])
    
    callback = tf.keras.callbacks.EarlyStopping(monitor="val_loss", verbose=1, patience=100)

    #Train
    history=kmodel.fit(
        X_train,
        y_train,
        epochs=50,
        batch_size=50,
        verbose=2,
        #sample_weight=np.asarray(weights),
        validation_split=0.20,
        callbacks=[callback],
        )
    

    import hls4ml.utils
    import hls4ml.converters
    import hls4ml.model.profiling

    config = hls4ml.utils.config_from_keras_model(kmodel, granularity='name')
    print("----------------------------------- \n")

    # Functions with loops to automate the process
    config['Model']['Strategy'] = STRATEGY

    # def loop_parallelization(items1, items2, test):

    #     print("Testing Parallelization\n")

    #     prec = []; rf = []; pf = []; h = []; w = []; chans = []; fh = []; fw = []; fs = []; stime = []; memAddress = [];
    #     ctime = []; bram = []; dsp = []; ff = []; lut = []; blat = []; wlat = []; interMin = []; interMax = []; 

    #     config['LayerName']['input_1']['Precision']['result'] = 'fixed<{},{}>'.format(FXD_W, FXD_I)

    #     i=0
    #     for item1, item2 in zip(items1, items2):
    #         #if i > 2:
    #          #   print("\n DONE \n") 
    #           #  break

    #         config['LayerName']['separable_conv2d']['ReuseFactor'] = item1
    #         config['LayerName']['separable_conv2d']['ParallelizationFactor'] = item2
            
    #         hls_kmodel = 0
    #         report = 0
    #         outdir = 0
            
    #         outdir= f'/home/users/russelld/VladBranch_SepConv2D/work/SepConv2D_hls4ml/HLS4ML_PROJ_sepConv2D/{test}/proj_{FXD_W}-{FXD_I}_rf_{item1}_pf_{item2}_InH{H}_InW{W}/qkmodel'
            


    #         rf.append(item1)
    #         pf.append(item2)
            
    #         if TRACE: #Activate Layer tracing
    #             for layer in config['LayerName'].keys():
    #                 #print('Enable tracing for layer:', layer)
    #                 config['LayerName'][layer]['Trace'] = True

    #         hls_kmodel = hls4ml.converters.convert_from_keras_model(
    #             kmodel, 
    #             hls_config=config, 
    #             output_dir=outdir, 
    #             part='xcu250-figd2104-2L-e',
    #             backend=BACKEND,
    #             io_type=IO_TYPE
    #         )

    #         start_comp = time.time()
    #         hls_kmodel.compile()
    #         end_comp = time.time()


    #         comp_time =  end_comp - start_comp

    #         if TRACE: #plotting the traces
    #             y_hls, hls4ml_trace = hls_kmodel.trace(X_train)
    #             keras_trace = hls4ml.model.profiling.get_ymodel_keras(kmodel, X_train)

    #             plt.figure()
    #             plt.scatter(hls4ml_trace[LAYER].flatten(), keras_trace[LAYER].flatten(), s=0.8)
    #             min_x = min(np.amin(hls4ml_trace[LAYER]), np.amin(keras_trace[LAYER]))
    #             max_x = max(np.amax(hls4ml_trace[LAYER]), np.amax(keras_trace[LAYER]))
    #             plt.plot([min_x, max_x], [min_x, max_x], c='gray')
    #             plt.xlabel('hls4ml {}, fixed<{},{}>'.format(LAYER,FXD_W, FXD_I))
    #             #plt.xlabel('hls4ml {}'.format(LAYER))
    #             plt.ylabel('Keras {}'.format(LAYER))
    #             plt.savefig(outdir + "/traces.png")

            
    #         start_syn = time.time()
    #         report = hls_kmodel.build(csim=False)
    #         end_syn = time.time()

    #         syn_time = end_syn - start_syn

    #         #Access report items 
    #         hls_results = report['CSynthesisReport']
            
    #         bram.append(hls_results["BRAM_18K"])
    #         dsp.append(hls_results["DSP"])
    #         ff.append(hls_results["FF"])
    #         lut.append(hls_results["LUT"])
    #         blat.append(hls_results["BestLatency"])
    #         wlat.append(hls_results["WorstLatency"])
    #         interMin.append(hls_results["IntervalMin"])
    #         interMax.append(hls_results["IntervalMax"])
    #         ctime.append(comp_time)
    #         stime.append(syn_time)
    #         print("---------------------------------")
    #         print(" \n Reading report from " + outdir + "\n" )
    #         print("Accessing memory at: ", id(report))
    #         memAddress.append(id(report))
    #         print("---------------------------------")
    #         print(hls4ml.report.read_vivado_report(outdir))
    #         i += 1

    #     details = { "MemAdress": memAddress, "Precision": "FXD<{},{}>".format(FXD_W,FXD_I), "rf": rf, "pf": pf, "Input_Height": H, "Input_Width": H,
    #                 "Channels": Din, "Filter_Height": Fh, "Filter_Width": Fw, "Filters": Dout, 
    #                 "Synthesis_Time": stime, "Compilation_time": ctime, "BRAM": bram, "DSP": dsp, "FF": ff,
    #                 "LUT": lut, "BestLatency": blat, "WorstLatency": wlat, "IntervalMin": interMin, 
    #                 "IntervalMax": interMax           
    #     }
        
    #     return details








    # def loop_precision(items1, items2, test):
        
    #     print("Testing Precision\n")
        
    #     prec = []; rf = []; pf = []; h = []; w = []; chans = []; fh = []; fw = []; fs = []; stime = []; 
    #     ctime = []; bram = []; dsp = []; ff = []; lut = []; blat = []; wlat = []; interMin = []; interMax = [], memAddress = []; 

    
    #     config['LayerName']['separable_conv2d']['ReuseFactor'] = reuseFactor
    #     config['LayerName']['separable_conv2d']['ParallelizationFactor'] = parallelFactor
    #     i=0
    #     for item1, item2 in zip(items1, items2):
    #         #if i > 0 : break

    #         hls_kmodel = 0
    #         report = 0
    #         outdir = 0

    #         prec.append(f'FXD<{item1},{item2}>')

    #         outdir= f'/home/users/russelld/VladBranch_SepConv2D/work/SepConv2D_hls4ml/HLS4ML_PROJ_sepConv2D/{test}/proj_{item1}-{item2}_rf_{reuseFactor}_pf_{parallelFactor}_InH{H}_InW{W}/qkmodel'

    #         config['LayerName']['input_1']['Precision']['result'] = 'fixed<{},{}>'.format(item1, item2)

    #         if TRACE: #Activate Layer tracing
    #             for layer in config['LayerName'].keys():
    #                 #print('Enable tracing for layer:', layer)
    #                 config['LayerName'][layer]['Trace'] = True

    #         hls_kmodel = hls4ml.converters.convert_from_keras_model(
    #             kmodel, 
    #             hls_config=config, 
    #             output_dir=outdir, 
    #             part='xcu250-figd2104-2L-e',
    #             backend=BACKEND,
    #             io_type=IO_TYPE
    #         )

    #         start_comp = time.time()
    #         hls_kmodel.compile()
    #         end_comp = time.time()

    #         comp_time =  end_comp - start_comp

    #         if TRACE: #plotting the traces
    #             y_hls, hls4ml_trace = hls_kmodel.trace(X_train)
    #             keras_trace = hls4ml.model.profiling.get_ymodel_keras(kmodel, X_train)

    #             plt.figure()
    #             plt.scatter(hls4ml_trace[LAYER].flatten(), keras_trace[LAYER].flatten(), s=0.8)
    #             min_x = min(np.amin(hls4ml_trace[LAYER]), np.amin(keras_trace[LAYER]))
    #             max_x = max(np.amax(hls4ml_trace[LAYER]), np.amax(keras_trace[LAYER]))
    #             plt.plot([min_x, max_x], [min_x, max_x], c='gray')
    #             plt.xlabel('hls4ml {}, fixed<{},{}>'.format(LAYER, item1, item2))
    #             #plt.xlabel('hls4ml {}'.format(LAYER))
    #             plt.ylabel('Keras {}'.format(LAYER))
    #             #plt.savefig(f"LayerTraces/Traces_Precision_{FXD_W}-{FXD_I}_rf_{reuseFactor}_pf_{parallelFactor}_InH{H}_InW{W}.png")
    #             plt.savefig(outdir + "/traces.png")
            
    #         start_syn = time.time()
    #         report = hls_kmodel.build(csim=False)
    #         end_syn = time.time()

    #         syn_time = end_syn - start_syn

    #         #Access report items
    #         memAddress.append(id(report)) 
    #         hls_results = report['CSynthesisReport']
            
    #         bram.append(hls_results["BRAM_18K"])
    #         dsp.append(hls_results["DSP"])
    #         ff.append(hls_results["FF"])
    #         lut.append(hls_results["LUT"])
    #         blat.append(hls_results["BestLatency"])
    #         wlat.append(hls_results["WorstLatency"])
    #         interMin.append(hls_results["IntervalMin"])
    #         interMax.append(hls_results["IntervalMax"])
    #         ctime.append(comp_time)
    #         stime.append(syn_time)

    #         i += 1




    #     details = { "MemAddress": memAddress, "Precision": prec, "rf": reuseFactor, "pf": parallelFactor, "Input_Height": H, "Input_Width": H,
    #                    "Channels": Din, "Filter_Height": Fh, "Filter_Width": Fw, "Filters": Dout, 
    #                    "Synthesis_Time": stime, "Compilation_time": ctime, "BRAM": bram, "DSP": dsp, "FF": ff,
    #                    "LUT": lut, "BestLatency": blat, "WorstLatency": wlat, "IntervalMin": interMin, 
    #                    "IntervalMax": interMax           
    #         }
        
    #     return details



                 
    #Condition to test the precision of the inputs
    if (type(specs['Bitwidth']) == list): 
        if (len(specs['Bitwidth'])==len(specs['Int_Width'])):
            test = 'precision'

            from util.precisionFunc import loop_precision
            outputDir = f'/home/users/russelld/VladBranch_SepConv2D/work/SepConv2D_hls4ml/HLS4ML_PROJ_sepConv2D/{test}/{BACKEND}_{VERSION}'
            final_report = loop_precision(config, specs, test, outDir, kmodel, X_train)
            outpath = outdir + '/report.json'
            with open(outpath, "w") as outfile: 
                json.dump(final_report, outfile)

        else: print("\n There is a problems with the lengths of bithwidth arrays")

    #Condition to test parallelization:
    if (type(specs["reuseFactor"]) == list):
        if (len(specs["reuseFactor"]) == len(specs["parallelFactor"])):
            test = 'Parallelization'

            from util.parallelizationFunc import loop_parallelization
            outputDir = f'/home/users/russelld/VladBranch_SepConv2D/work/SepConv2D_hls4ml/HLS4ML_PROJ_sepConv2D/{test}/{BACKEND}_{VERSION}'
            final_report = loop_parallelization(config, specs, test, outDir, kmodel, X_train)
            outpath =f'/home/users/russelld/VladBranch_SepConv2D/work/SepConv2D_hls4ml/HLS4ML_PROJ_sepConv2D/{test}/report.json'
            with open(outpath, "w") as outfile: 
                json.dump(final_report, outfile)
        else: 
            print("\n There is a problems with the lengths of bithwidth arrays \n")
            print(f'Reuse factor length: {len(specs["reuseFactor"])} vs. parallel factor length: {len(specs["parallelFactor"])} \n')

    
    # Condition to test dimensions: 
    if ((type(specs["reuseFactor"]) != list) & (type(specs['Bitwidth']) != list)):
        test = "dimensions"

        from util.dimTestFunc import dimTestFunc
        outputDir = f'/home/users/russelld/VladBranch_SepConv2D/work/SepConv2D_hls4ml/HLS4ML_PROJ_sepConv2D/{test}/{BACKEND}_{VERSION}'
        final_report = dimTestFunc(config, specs, test, outputDir kmodel, X_train)
        outpath = outputDir + '/report.json'
        with open(outpath, "w") as outfile: 
            json.dump(final_report, outfile)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Process arguments")

    parser.add_argument("testConfigs", type=str, help="input the signal train file")

    args = parser.parse_args()
    main(args)


