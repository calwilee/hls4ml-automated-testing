import hls4ml
import hls4ml.utils
import hls4ml.converters
import hls4ml.model.profiling
import time
import matplotlib.pyplot as plt
import numpy as np

def loop_precision(config, specsDict, test, outdir,  kmodel, x_train):
 
 # Read all of the parameters to be used

    LAYER = specsDict['LAYER'] # uses both depthwise and pointwise
    RUN_HLS = specsDict['RUN_HLS']
    IO_TYPE = specsDict['IO_TYPE']
    STRATEGY = specsDict['STRATEGY']
    BACKEND = specsDict['BACKEND']
    TRACE = specsDict['TRACE']

    H = specsDict['Height']  # Input height
    W = specsDict['Width']  # Input width
    FXD_W = specsDict['Bitwidth'] # Fixed-point precision, word bit width
    FXD_I = specsDict['Int_Width'] # Fixed-point precision, integer-part bit width
    reuseFactor = specsDict['reuseFactor']
    parallelFactor = specsDict['parallelFactor']

    Din = specsDict["Channels"]  # Input # of channels    
    Fh = specsDict["Filter_Height"]   # Kernel height   
    Fw = specsDict["Filter_Width"]  # Kernel width  
    Dout = specsDict['Filters'] # Kernel # of filters
    
    print("Testing Precision\n")
    
    prec = []; rf = []; pf = []; h = []; w = []; chans = []; fh = []; fw = []; fs = []; stime = []; 
    ctime = []; bram = []; dsp = []; ff = []; lut = []; blat = []; wlat = []; interMin = []; interMax = []; memAddress = []; 

    config['LayerName']['separable_conv2d']['ReuseFactor'] = reuseFactor
    config['LayerName']['separable_conv2d']['ParallelizationFactor'] = parallelFactor

    i=0 # dummy variable to break loop below if I need to stop earlier, for example
    for fixed_w, fixed_int in zip(FXD_W, FXD_I):
        if i > 2 : break

        hls_kmodel = 0
        report = 0
        #outdir = 0

        prec.append(f'FXD<{fixed_w},{fixed_int}>')

        output_dir= f'{outdir}/proj_{fixed_w}-{fixed_int}_rf_{reuseFactor}_pf_{parallelFactor}_InH{H}_InW{W}/qkmodel'
    
        config['LayerName']['input_1']['Precision']['result'] = 'fixed<{},{}>'.format(fixed_w, fixed_int)

        if TRACE: #Activate Layer tracing
            for layer in config['LayerName'].keys():
                print('Enable tracing for layer:', layer)
                config['LayerName'][layer]['Trace'] = True

        hls_kmodel = hls4ml.converters.convert_from_keras_model(
            kmodel, 
            hls_config=config, 
            output_dir=output_dir, 
            part='xcu250-figd2104-2L-e',
            backend=BACKEND,
            io_type=IO_TYPE
        )

        start_comp = time.time()
        hls_kmodel.compile()
        end_comp = time.time()

        comp_time =  end_comp - start_comp

        if TRACE: #plotting the traces
            y_hls, hls4ml_trace = hls_kmodel.trace(x_train)
            keras_trace = hls4ml.model.profiling.get_ymodel_keras(kmodel, x_train)

            plt.figure()
            plt.scatter(hls4ml_trace[LAYER].flatten(), keras_trace[LAYER].flatten(), s=0.8)
            min_x = min(np.amin(hls4ml_trace[LAYER]), np.amin(keras_trace[LAYER]))
            max_x = max(np.amax(hls4ml_trace[LAYER]), np.amax(keras_trace[LAYER]))
            plt.plot([min_x, max_x], [min_x, max_x], c='gray')
            plt.xlabel('hls4ml {}, fixed<{},{}>'.format(LAYER, fixed_w, fixed_int))
            #plt.xlabel('hls4ml {}'.format(LAYER))
            plt.ylabel('Keras {}'.format(LAYER))
            #plt.savefig(f"LayerTraces/Traces_Precision_{FXD_W}-{FXD_I}_rf_{reuseFactor}_pf_{parallelFactor}_InH{H}_InW{W}.png")
            print("/n Traces saved to: " + output_dir + "\n")
            plt.savefig(output_dir + "/traces.png")
        
        start_syn = time.time()
        report = hls_kmodel.build(csim=False)
        end_syn = time.time()

        syn_time = end_syn - start_syn

        #Access report items
        memAddress.append(id(report)) 
        hls_results = report['CSynthesisReport']
        
        bram.append(hls_results["BRAM_18K"])
        dsp.append(hls_results["DSP"])
        ff.append(hls_results["FF"])
        lut.append(hls_results["LUT"])
        blat.append(hls_results["BestLatency"])
        wlat.append(hls_results["WorstLatency"])
        interMin.append(hls_results["IntervalMin"])
        interMax.append(hls_results["IntervalMax"])
        ctime.append(comp_time)
        stime.append(syn_time)

        i += 1




    details = { "MemAddress": memAddress, "Precision": prec, "rf": reuseFactor, "pf": parallelFactor, "Input_Height": H, "Input_Width": W,
                    "Channels": Din, "Filter_Height": Fh, "Filter_Width": Fw, "Filters": Dout, 
                    "Synthesis_Time": stime, "Compilation_time": ctime, "BRAM": bram, "DSP": dsp, "FF": ff,
                    "LUT": lut, "BestLatency": blat, "WorstLatency": wlat, "IntervalMin": interMin, 
                    "IntervalMax": interMax           
        }
    
    return details