# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\akashbad\Documents\6.115\Lab5\lab2\GoSocedo.cydsn\GoSocedo.cyprj
# Date: Mon, 14 Apr 2014 22:52:04 GMT
#set_units -time ns
create_clock -name {ADC_Ext_CP_Clk(routed)} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dclk_0}]]
create_clock -name {ADCclock(routed)} -period 50000000 -waveform {0 25000000} [list [get_pins {ClockBlock/aclk_1}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_clock -name {ADC_Ext_CP_Clk} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {ADC_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 161 321} -nominal_period 6666.6666666666661 [list [get_pins {ClockBlock/aclk_glb_0}]]
create_clock -name {ADC_theACLK(fixed-function)} -period 6666.6666666666661 -waveform {0 3333.33333333333} -nominal_period 6666.6666666666661 [get_pins {ClockBlock/aclk_glb_ff_0}]
create_generated_clock -name {ADCclock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 1200001 2400001} [list [get_pins {ClockBlock/aclk_glb_1}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]


# Component constraints for C:\Users\akashbad\Documents\6.115\Lab5\lab2\GoSocedo.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\akashbad\Documents\6.115\Lab5\lab2\GoSocedo.cydsn\GoSocedo.cyprj
# Date: Mon, 14 Apr 2014 22:52:00 GMT
