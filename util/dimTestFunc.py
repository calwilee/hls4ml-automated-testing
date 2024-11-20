import hls4ml
import hls4ml.utils
import hls4ml.converters
import hls4ml.model.profiling
import time
import matplotlib.pyplot as plt
import numpy as np

def dimTestFunc(config, specsDict, test, outdir, kmodel, X_train):

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
    
    print("Testing Dimensional extent of Synthesis\n")

    prec = []; rf = []; pf = []; h = []; w = []; chans = []; fh = []; fw = []; fs = []; stime = []; 
    ctime = []; bram = []; dsp = []; ff = []; lut = []; blat = []; wlat = []; interMin = []; interMax = []; memAddress = [];
    wCheck = []

    config['LayerName']['separable_conv2d']['ReuseFactor'] = reuseFactor
    config['LayerName']['input_1']['Precision']['result'] = 'fixed<{},{}>'.format(FXD_W, FXD_I)

    i = H
    j = W
    n = 0
    while True: # height loop
        
        j = W # reset the width
        l = W # Extra variable... will not increase later if report is not found and will help
                #  stop loop once report is not found, i.e. synth == "FAILED".

        while True: # width loop

            hls_kmodel = 0
            report = 0 

            w.append(j)
            h.append(i)
            prec.append('fixed<{},{}>'.format(FXD_W, FXD_I))
            fw.append(Fw)
            chans.append(Din)
            fh.append(Fh)
            fs.append(Dout)

            parallelFactor = i*j
            pf.append(parallelFactor)
            config['LayerName']['separable_conv2d']['ParallelizationFactor'] = parallelFactor
            

            outpur_dir =f'{outdir}/proj_{FXD_W}-{FXD_I}_rf_{reuseFactor}_pf_{parallelFactor}_InH{i}_InW{j}/qkmodel'

            if TRACE: #Activate Layer tracing
                for layer in config['LayerName'].keys():
                    #print('Enable tracing for layer:', layer)
                    config['LayerName'][layer]['Trace'] = True

            hls_kmodel = hls4ml.converters.convert_from_keras_model(
            kmodel, 
            hls_config=config, 
            output_dir=outpur_dir, 
            part='xcu250-figd2104-2L-e',
            backend=BACKEND,
            io_type=IO_TYPE
            )

            start_comp = time.time()
            hls_kmodel.compile()
            end_comp = time.time()

            comp_time =  end_comp - start_comp

            if TRACE: #plotting the traces
                y_hls, hls4ml_trace = hls_kmodel.trace(X_train)
                keras_trace = hls4ml.model.profiling.get_ymodel_keras(kmodel, X_train)

                plt.figure()
                plt.scatter(hls4ml_trace[LAYER].flatten(), keras_trace[LAYER].flatten(), s=0.8)
                min_x = min(np.amin(hls4ml_trace[LAYER]), np.amin(keras_trace[LAYER]))
                max_x = max(np.amax(hls4ml_trace[LAYER]), np.amax(keras_trace[LAYER]))
                plt.plot([min_x, max_x], [min_x, max_x], c='gray')
                plt.xlabel('hls4ml {}, fixed<{},{}>'.format(LAYER, FXD_W, FXD_I))
                plt.ylabel('Keras {}'.format(LAYER))
                print("/n Traces saved to: " + outdir + "\n")
                plt.savefig(outdir + "/traces.png")

            start_syn = time.time()
            report = hls_kmodel.build(csim=False)
            end_syn = time.time()

            syn_time = end_syn - start_syn

            try:
                hls_results = report['CSynthesisReport']
                synth = "PASSED"

            except KeyError: #Try the above, except if we get a KeyError. In this case, say synthesis fails

                synth = "FAILED" # sets this string if synthesis fails 

                print("\n -------------------------- \n ")
                print("SYNTHESIS FAILED")
                print("\n -------------------------- \n ")
            
            if synth != "FAILED": #Then 'CSynthesisReport' exists and I can extract the values
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
                rf.append(reuseFactor)
                j += 1
                l += 1

            
            elif synth == "FAILED": # 'CSynthesisReport' does not exist, so set 0's.
                memAddress.append(id(report))
                bram.append(0)
                dsp.append(0)
                ff.append(0)
                lut.append(0)
                blat.append(0)
                wlat.append(0)
                interMin.append(0)
                interMax.append(0)
                ctime.append(comp_time)
                stime.append(syn_time)
                prec.append('fixed<{},{}>'.format(FXD_W, FXD_I))
                rf.append(reuseFactor)
                l += 1
                # Only increase 'l' because I don't wanna increase j, which is my 
                #  width knob
                #break
            wCheck.append(l)
            #if l == j:
            #    i += 1 
            #    break #################### Safety for width loop
                 
            if j != l: # meaning I synthesis report was found and can check a step up
                i += 1 #go up one step in height since we wanna break width loop
                break # Means that report was not found, i.e. synth == "FAILED" 

            if l == W+20:
                i += 1
                break # break if width loop has reached too many

        n += 1  # We went up 1 step in height 
        if n == 20: 
            break #break if heigth loop has reached too many 


    details = { "MemAddress": memAddress, "Precision": prec, "rf": reuseFactor, "pf": pf, "Input_Height": h, "Input_Width": w,
                    "Channels": chans, "Filter_Height": fh, "Filter_Width": fw, "Filters": fs, 
                    "Synthesis_Time": stime, "Compilation_time": ctime, "BRAM": bram, "DSP": dsp, "FF": ff,
                    "LUT": lut, "BestLatency": blat, "WorstLatency": wlat, "IntervalMin": interMin, 
                    "IntervalMax": interMax, "width_check": wCheck   
        }
    
    return details
