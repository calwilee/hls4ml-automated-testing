#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/users/calwinlee/hls4ml-automated-testing/0/proj_14-6_rf_1_pf_4_InH8_InW8/qkmodel/myproject_prj/solution1/.autopilot/db/a.g.bc ${1+"$@"}
