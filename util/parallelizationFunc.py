import hls4ml
import hls4ml.utils
import hls4ml.converters
import hls4ml.model.profiling
import time
import matplotlib.pyplot as plt
import numpy as np

def loop_parallelization(config, specsDict, test, outdir, kmodel, x_train):

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

    print("Testing Parallelization\n")

    prec = []; rF = []; pF = []; h = []; w = []; chans = []; fh = []; fw = []; fs = []; stime = []; memAddress = [];
    ctime = []; bram = []; dsp = []; ff = []; lut = []; blat = []; wlat = []; interMin = []; interMax = []; 

    config['LayerName']['input_1']['Precision']['result'] = 'fixed<{},{}>'.format(FXD_W, FXD_I)

    i=0
    for rf, pf in zip(reuseFactor, parallelFactor):
        #if i > 2:
            #print("\n DONE \n") 
            #break

        config['LayerName']['separable_conv2d']['ReuseFactor'] = rf
        config['LayerName']['separable_conv2d']['ParallelizationFactor'] = pf
        
        hls_kmodel = 0
        report = 0
        outdir = 0
        
        output_dir= f'{outdir}/proj_{FXD_W}-{FXD_I}_rf_{rf}_pf_{pf}_InH{H}_InW{W}/qkmodel'

        rF.append(rf)
        pF.append(pf)
        
        if TRACE: #Activate Layer tracing
            for layer in config['LayerName'].keys():
                #print('Enable tracing for layer:', layer)
                config['LayerName'][layer]['Trace'] = True

        hls_kmodel = hls4ml.converters.convert_from_keras_model(
            kmodel, 
            hls_config=config, 
            output_dir=output_dir, 
            part='xcu250-figd2104-2L-e',
            backend=BACKEND,
            io_type=IO_TYPE
        )
        #Time the compilation step
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
            plt.xlabel('hls4ml {}, fixed<{},{}>'.format(LAYER,FXD_W, FXD_I))
            #plt.xlabel('hls4ml {}'.format(LAYER))
            plt.ylabel('Keras {}'.format(LAYER))
            print("/n Traces saved to: " + output_dir + "\n")
            plt.savefig(output_dir + "/traces.png")

        #Time the synthesis step
        start_syn = time.time()
        report = hls_kmodel.build(csim=False)
        end_syn = time.time()

        syn_time = end_syn - start_syn

        #Access report items 
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
        print("---------------------------------")
        print(" \n Reading report from " + outdir + "\n" )
        print("Accessing memory at: ", id(report))
        memAddress.append(id(report))
        print("---------------------------------")
        print(hls4ml.report.read_vivado_report(outdir))
        i += 1

    details = { "MemAdress": memAddress, "Precision": "FXD<{},{}>".format(FXD_W,FXD_I), "rf": rF, "pf": pF, "Input_Height": H, "Input_Width": H,
                "Channels": Din, "Filter_Height": Fh, "Filter_Width": Fw, "Filters": Dout, 
                "Synthesis_Time": stime, "Compilation_time": ctime, "BRAM": bram, "DSP": dsp, "FF": ff,
                "LUT": lut, "BestLatency": blat, "WorstLatency": wlat, "IntervalMin": interMin, 
                "IntervalMax": interMax           
    }
    
    return details