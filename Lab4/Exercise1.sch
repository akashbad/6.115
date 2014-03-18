<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="53" name="tGND_GNDA" color="7" fill="9" visible="no" active="no"/>
<layer number="54" name="bGND_GNDA" color="1" fill="9" visible="no" active="no"/>
<layer number="56" name="wert" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="100" name="Muster" color="7" fill="1" visible="no" active="no"/>
<layer number="101" name="Patch_Top" color="12" fill="4" visible="yes" active="yes"/>
<layer number="102" name="Vscore" color="7" fill="1" visible="yes" active="yes"/>
<layer number="103" name="tMap" color="7" fill="1" visible="yes" active="yes"/>
<layer number="104" name="Name" color="16" fill="1" visible="yes" active="yes"/>
<layer number="105" name="tPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="106" name="bPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="107" name="Crop" color="7" fill="1" visible="yes" active="yes"/>
<layer number="116" name="Patch_BOT" color="9" fill="4" visible="yes" active="yes"/>
<layer number="121" name="_tsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="122" name="_bsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="125" name="_tNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="144" name="Drill_legend" color="7" fill="1" visible="yes" active="yes"/>
<layer number="151" name="HeatSink" color="7" fill="1" visible="yes" active="yes"/>
<layer number="199" name="Contour" color="7" fill="1" visible="yes" active="yes"/>
<layer number="200" name="200bmp" color="1" fill="10" visible="yes" active="yes"/>
<layer number="201" name="201bmp" color="2" fill="10" visible="yes" active="yes"/>
<layer number="202" name="202bmp" color="3" fill="10" visible="yes" active="yes"/>
<layer number="203" name="203bmp" color="4" fill="10" visible="yes" active="yes"/>
<layer number="204" name="204bmp" color="5" fill="10" visible="yes" active="yes"/>
<layer number="205" name="205bmp" color="6" fill="10" visible="yes" active="yes"/>
<layer number="206" name="206bmp" color="7" fill="10" visible="yes" active="yes"/>
<layer number="207" name="207bmp" color="8" fill="10" visible="yes" active="yes"/>
<layer number="208" name="208bmp" color="9" fill="10" visible="yes" active="yes"/>
<layer number="209" name="209bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="210" name="210bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="211" name="211bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="212" name="212bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="213" name="213bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="214" name="214bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="215" name="215bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="216" name="216bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="217" name="217bmp" color="18" fill="1" visible="no" active="no"/>
<layer number="218" name="218bmp" color="19" fill="1" visible="no" active="no"/>
<layer number="219" name="219bmp" color="20" fill="1" visible="no" active="no"/>
<layer number="220" name="220bmp" color="21" fill="1" visible="no" active="no"/>
<layer number="221" name="221bmp" color="22" fill="1" visible="no" active="no"/>
<layer number="222" name="222bmp" color="23" fill="1" visible="no" active="no"/>
<layer number="223" name="223bmp" color="24" fill="1" visible="no" active="no"/>
<layer number="224" name="224bmp" color="25" fill="1" visible="no" active="no"/>
<layer number="250" name="Descript" color="3" fill="1" visible="no" active="no"/>
<layer number="251" name="SMDround" color="12" fill="11" visible="no" active="no"/>
<layer number="254" name="cooling" color="7" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="micro-intel">
<description>&lt;b&gt;Intel Microcomputer Devices&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="DIL40">
<description>&lt;b&gt;Dual In Line Package&lt;/b&gt;</description>
<wire x1="25.4" y1="6.731" x2="-25.4" y2="6.731" width="0.1524" layer="21"/>
<wire x1="-25.4" y1="-6.731" x2="25.4" y2="-6.731" width="0.1524" layer="21"/>
<wire x1="25.4" y1="6.731" x2="25.4" y2="-6.731" width="0.1524" layer="21"/>
<wire x1="-25.4" y1="6.731" x2="-25.4" y2="0.889" width="0.1524" layer="21"/>
<wire x1="-25.4" y1="-6.731" x2="-25.4" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="-25.4" y1="0.889" x2="-25.4" y2="-1.143" width="0.1524" layer="21" curve="-180"/>
<pad name="1" x="-24.13" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-21.59" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="-8.89" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="-6.35" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="-19.05" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="-16.51" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="-11.43" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="-13.97" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="9" x="-3.81" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="10" x="-1.27" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="11" x="1.27" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="12" x="3.81" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="13" x="6.35" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="14" x="8.89" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="15" x="11.43" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="16" x="13.97" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="17" x="16.51" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="18" x="19.05" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="19" x="21.59" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="20" x="24.13" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="21" x="24.13" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="22" x="21.59" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="23" x="19.05" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="24" x="16.51" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="25" x="13.97" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="26" x="11.43" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="27" x="8.89" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="28" x="6.35" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="29" x="3.81" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="30" x="1.27" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="31" x="-1.27" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="32" x="-3.81" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="33" x="-6.35" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="34" x="-8.89" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="35" x="-11.43" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="36" x="-13.97" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="37" x="-16.51" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="38" x="-19.05" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="39" x="-21.59" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="40" x="-24.13" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<text x="-25.908" y="-6.604" size="1.778" layer="25" rot="R90">&gt;NAME</text>
<text x="-17.145" y="-1.016" size="1.778" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="8255A">
<wire x1="-10.16" y1="-35.56" x2="7.62" y2="-35.56" width="0.4064" layer="94"/>
<wire x1="7.62" y1="-35.56" x2="7.62" y2="33.02" width="0.4064" layer="94"/>
<wire x1="7.62" y1="33.02" x2="-10.16" y2="33.02" width="0.4064" layer="94"/>
<wire x1="-10.16" y1="33.02" x2="-10.16" y2="-35.56" width="0.4064" layer="94"/>
<text x="-10.16" y="33.655" size="1.778" layer="95">&gt;NAME</text>
<text x="-10.16" y="-38.1" size="1.778" layer="96">&gt;VALUE</text>
<pin name="PA3" x="12.7" y="22.86" length="middle" rot="R180"/>
<pin name="PA2" x="12.7" y="25.4" length="middle" rot="R180"/>
<pin name="PA1" x="12.7" y="27.94" length="middle" rot="R180"/>
<pin name="PA0" x="12.7" y="30.48" length="middle" rot="R180"/>
<pin name="RD" x="-15.24" y="7.62" length="middle" direction="in" function="dot"/>
<pin name="CS" x="-15.24" y="-17.78" length="middle" direction="in" function="dot"/>
<pin name="A1" x="-15.24" y="-2.54" length="middle" direction="in"/>
<pin name="A0" x="-15.24" y="-7.62" length="middle" direction="in"/>
<pin name="PC7" x="12.7" y="-33.02" length="middle" rot="R180"/>
<pin name="PC6" x="12.7" y="-30.48" length="middle" rot="R180"/>
<pin name="PC5" x="12.7" y="-27.94" length="middle" rot="R180"/>
<pin name="PC4" x="12.7" y="-25.4" length="middle" rot="R180"/>
<pin name="PC0" x="12.7" y="-15.24" length="middle" rot="R180"/>
<pin name="PC1" x="12.7" y="-17.78" length="middle" rot="R180"/>
<pin name="PC2" x="12.7" y="-20.32" length="middle" rot="R180"/>
<pin name="PC3" x="12.7" y="-22.86" length="middle" rot="R180"/>
<pin name="PB0" x="12.7" y="7.62" length="middle" rot="R180"/>
<pin name="PB1" x="12.7" y="5.08" length="middle" rot="R180"/>
<pin name="PB2" x="12.7" y="2.54" length="middle" rot="R180"/>
<pin name="PB3" x="12.7" y="0" length="middle" rot="R180"/>
<pin name="PB4" x="12.7" y="-2.54" length="middle" rot="R180"/>
<pin name="PB5" x="12.7" y="-5.08" length="middle" rot="R180"/>
<pin name="PB6" x="12.7" y="-7.62" length="middle" rot="R180"/>
<pin name="PB7" x="12.7" y="-10.16" length="middle" rot="R180"/>
<pin name="D7" x="-15.24" y="12.7" length="middle"/>
<pin name="D6" x="-15.24" y="15.24" length="middle"/>
<pin name="D5" x="-15.24" y="17.78" length="middle"/>
<pin name="D4" x="-15.24" y="20.32" length="middle"/>
<pin name="D3" x="-15.24" y="22.86" length="middle"/>
<pin name="D2" x="-15.24" y="25.4" length="middle"/>
<pin name="D1" x="-15.24" y="27.94" length="middle"/>
<pin name="D0" x="-15.24" y="30.48" length="middle"/>
<pin name="RESET" x="-15.24" y="-12.7" length="middle" direction="in"/>
<pin name="WR" x="-15.24" y="2.54" length="middle" direction="in" function="dot"/>
<pin name="PA7" x="12.7" y="12.7" length="middle" rot="R180"/>
<pin name="PA6" x="12.7" y="15.24" length="middle" rot="R180"/>
<pin name="PA5" x="12.7" y="17.78" length="middle" rot="R180"/>
<pin name="PA4" x="12.7" y="20.32" length="middle" rot="R180"/>
</symbol>
<symbol name="PWRN">
<text x="-0.635" y="-0.635" size="1.778" layer="95">&gt;NAME</text>
<text x="1.905" y="-5.842" size="1.27" layer="95" rot="R90">GND</text>
<text x="1.905" y="2.54" size="1.27" layer="95" rot="R90">VCC</text>
<pin name="GND" x="0" y="-7.62" visible="pad" length="middle" direction="pwr" rot="R90"/>
<pin name="VCC" x="0" y="7.62" visible="pad" length="middle" direction="pwr" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="8255A" prefix="IC" uservalue="yes">
<description>&lt;b&gt;MICROCOMPUTER/PERIPHERAL DEVICE&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="8255A" x="0" y="0"/>
<gate name="P" symbol="PWRN" x="-30.48" y="7.62" addlevel="request"/>
</gates>
<devices>
<device name="" package="DIL40">
<connects>
<connect gate="A" pin="A0" pad="9"/>
<connect gate="A" pin="A1" pad="8"/>
<connect gate="A" pin="CS" pad="6"/>
<connect gate="A" pin="D0" pad="34"/>
<connect gate="A" pin="D1" pad="33"/>
<connect gate="A" pin="D2" pad="32"/>
<connect gate="A" pin="D3" pad="31"/>
<connect gate="A" pin="D4" pad="30"/>
<connect gate="A" pin="D5" pad="29"/>
<connect gate="A" pin="D6" pad="28"/>
<connect gate="A" pin="D7" pad="27"/>
<connect gate="A" pin="PA0" pad="4"/>
<connect gate="A" pin="PA1" pad="3"/>
<connect gate="A" pin="PA2" pad="2"/>
<connect gate="A" pin="PA3" pad="1"/>
<connect gate="A" pin="PA4" pad="40"/>
<connect gate="A" pin="PA5" pad="39"/>
<connect gate="A" pin="PA6" pad="38"/>
<connect gate="A" pin="PA7" pad="37"/>
<connect gate="A" pin="PB0" pad="18"/>
<connect gate="A" pin="PB1" pad="19"/>
<connect gate="A" pin="PB2" pad="20"/>
<connect gate="A" pin="PB3" pad="21"/>
<connect gate="A" pin="PB4" pad="22"/>
<connect gate="A" pin="PB5" pad="23"/>
<connect gate="A" pin="PB6" pad="24"/>
<connect gate="A" pin="PB7" pad="25"/>
<connect gate="A" pin="PC0" pad="14"/>
<connect gate="A" pin="PC1" pad="15"/>
<connect gate="A" pin="PC2" pad="16"/>
<connect gate="A" pin="PC3" pad="17"/>
<connect gate="A" pin="PC4" pad="13"/>
<connect gate="A" pin="PC5" pad="12"/>
<connect gate="A" pin="PC6" pad="11"/>
<connect gate="A" pin="PC7" pad="10"/>
<connect gate="A" pin="RD" pad="5"/>
<connect gate="A" pin="RESET" pad="35"/>
<connect gate="A" pin="WR" pad="36"/>
<connect gate="P" pin="GND" pad="7"/>
<connect gate="P" pin="VCC" pad="26"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="st-microelectronics">
<description>&lt;b&gt;ST Microelectronics Devices&lt;/b&gt;&lt;p&gt;
Microcontrollers,  I2C components, linear devices&lt;p&gt;
http://www.st.com&lt;p&gt;
&lt;i&gt;Include st-microelectronics-2.lbr, st-microelectronics-3.lbr.&lt;p&gt;&lt;/i&gt;

&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="SO20">
<description>&lt;b&gt;SMALL OUTLINE INTEGRATED CIRCUIT&lt;/b&gt;&lt;p&gt;
wide body 7.5 mm/JEDEC MS-013AC</description>
<wire x1="6.46" y1="-3.7" x2="-6.46" y2="-3.7" width="0.2032" layer="51"/>
<wire x1="-6.46" y1="-3.7" x2="-6.46" y2="-3.2" width="0.2032" layer="51"/>
<wire x1="-6.46" y1="-3.2" x2="-6.46" y2="3.7" width="0.2032" layer="51"/>
<wire x1="-6.46" y1="3.7" x2="6.46" y2="3.7" width="0.2032" layer="51"/>
<wire x1="6.46" y1="-3.2" x2="-6.46" y2="-3.2" width="0.2032" layer="51"/>
<wire x1="6.46" y1="3.7" x2="6.46" y2="-3.2" width="0.2032" layer="51"/>
<wire x1="6.46" y1="-3.2" x2="6.46" y2="-3.7" width="0.2032" layer="51"/>
<smd name="2" x="-4.445" y="-4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="13" x="3.175" y="4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="1" x="-5.715" y="-4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="3" x="-3.175" y="-4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="4" x="-1.905" y="-4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="14" x="1.905" y="4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="12" x="4.445" y="4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="11" x="5.715" y="4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="6" x="0.635" y="-4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="9" x="4.445" y="-4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="5" x="-0.635" y="-4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="7" x="1.905" y="-4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="10" x="5.715" y="-4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="8" x="3.175" y="-4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="15" x="0.635" y="4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="16" x="-0.635" y="4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="17" x="-1.905" y="4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="18" x="-3.175" y="4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="19" x="-4.445" y="4.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="20" x="-5.715" y="4.6" dx="0.6" dy="2.2" layer="1"/>
<text x="-5.715" y="1.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-5.715" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-5.9601" y1="-5.32" x2="-5.4699" y2="-3.8001" layer="51"/>
<rectangle x1="-4.6901" y1="-5.32" x2="-4.1999" y2="-3.8001" layer="51"/>
<rectangle x1="-3.4201" y1="-5.32" x2="-2.9299" y2="-3.8001" layer="51"/>
<rectangle x1="-2.1501" y1="-5.32" x2="-1.6599" y2="-3.8001" layer="51"/>
<rectangle x1="-0.8801" y1="-5.32" x2="-0.3899" y2="-3.8001" layer="51"/>
<rectangle x1="0.3899" y1="-5.32" x2="0.8801" y2="-3.8001" layer="51"/>
<rectangle x1="1.6599" y1="-5.32" x2="2.1501" y2="-3.8001" layer="51"/>
<rectangle x1="2.9299" y1="-5.32" x2="3.4201" y2="-3.8001" layer="51"/>
<rectangle x1="4.1999" y1="-5.32" x2="4.6901" y2="-3.8001" layer="51"/>
<rectangle x1="5.4699" y1="-5.32" x2="5.9601" y2="-3.8001" layer="51"/>
<rectangle x1="5.4699" y1="3.8001" x2="5.9601" y2="5.32" layer="51"/>
<rectangle x1="4.1999" y1="3.8001" x2="4.6901" y2="5.32" layer="51"/>
<rectangle x1="2.9299" y1="3.8001" x2="3.4201" y2="5.32" layer="51"/>
<rectangle x1="1.6599" y1="3.8001" x2="2.1501" y2="5.32" layer="51"/>
<rectangle x1="0.3899" y1="3.8001" x2="0.8801" y2="5.32" layer="51"/>
<rectangle x1="-0.8801" y1="3.8001" x2="-0.3899" y2="5.32" layer="51"/>
<rectangle x1="-2.1501" y1="3.8001" x2="-1.6599" y2="5.32" layer="51"/>
<rectangle x1="-3.4201" y1="3.8001" x2="-2.9299" y2="5.32" layer="51"/>
<rectangle x1="-4.6901" y1="3.8001" x2="-4.1999" y2="5.32" layer="51"/>
<rectangle x1="-5.9601" y1="3.8001" x2="-5.4699" y2="5.32" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="L293DD">
<wire x1="-10.16" y1="17.78" x2="-10.16" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-20.32" x2="10.16" y2="-20.32" width="0.254" layer="94"/>
<wire x1="10.16" y1="-20.32" x2="10.16" y2="17.78" width="0.254" layer="94"/>
<wire x1="10.16" y1="17.78" x2="-10.16" y2="17.78" width="0.254" layer="94"/>
<wire x1="-3.81" y1="0" x2="-2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="-1.27" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="-1.27" x2="0" y2="0" width="0.1524" layer="94"/>
<wire x1="0" y1="0" x2="-2.54" y2="1.27" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="1.27" x2="-2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="-3.81" y1="-5.08" x2="-2.54" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="-5.08" x2="-2.54" y2="-3.81" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="-3.81" x2="0" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="0" y1="-5.08" x2="-2.54" y2="-6.35" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="-6.35" x2="-2.54" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="-3.302" y1="-2.54" x2="-1.27" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-1.27" y1="-2.54" x2="-1.27" y2="-0.762" width="0.1524" layer="94"/>
<wire x1="-1.27" y1="-2.54" x2="-1.27" y2="-4.318" width="0.1524" layer="94"/>
<wire x1="0" y1="-5.08" x2="1.27" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="0" y1="0" x2="1.27" y2="0" width="0.1524" layer="94"/>
<wire x1="-3.81" y1="10.16" x2="-2.54" y2="10.16" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="10.16" x2="-2.54" y2="8.89" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="8.89" x2="0" y2="10.16" width="0.1524" layer="94"/>
<wire x1="0" y1="10.16" x2="-2.54" y2="11.43" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="11.43" x2="-2.54" y2="10.16" width="0.1524" layer="94"/>
<wire x1="-3.81" y1="5.08" x2="-2.54" y2="5.08" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="6.35" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="6.35" x2="0" y2="5.08" width="0.1524" layer="94"/>
<wire x1="0" y1="5.08" x2="-2.54" y2="3.81" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="3.81" x2="-2.54" y2="5.08" width="0.1524" layer="94"/>
<wire x1="-3.302" y1="7.62" x2="-1.27" y2="7.62" width="0.1524" layer="94"/>
<wire x1="-1.27" y1="7.62" x2="-1.27" y2="9.398" width="0.1524" layer="94"/>
<wire x1="-1.27" y1="7.62" x2="-1.27" y2="5.842" width="0.1524" layer="94"/>
<wire x1="0" y1="5.08" x2="1.27" y2="5.08" width="0.1524" layer="94"/>
<wire x1="0" y1="10.16" x2="1.27" y2="10.16" width="0.1524" layer="94"/>
<text x="-10.16" y="18.796" size="1.778" layer="95">&gt;NAME</text>
<text x="-10.16" y="-22.86" size="1.778" layer="96">&gt;VALUE</text>
<pin name="EN1" x="-12.7" y="7.62" length="short" direction="in"/>
<pin name="IN1" x="-12.7" y="10.16" length="short" direction="in"/>
<pin name="OUT1" x="12.7" y="10.16" length="short" direction="out" rot="R180"/>
<pin name="GND@1" x="-12.7" y="-10.16" length="short" direction="pwr"/>
<pin name="GND@2" x="-12.7" y="-12.7" length="short" direction="pwr"/>
<pin name="OUT2" x="12.7" y="5.08" length="short" direction="out" rot="R180"/>
<pin name="IN2" x="-12.7" y="5.08" length="short" direction="in"/>
<pin name="VSS" x="12.7" y="15.24" length="short" direction="pwr" rot="R180"/>
<pin name="VS" x="-12.7" y="15.24" length="short" direction="pwr"/>
<pin name="IN3" x="-12.7" y="0" length="short" direction="in"/>
<pin name="OUT4" x="12.7" y="-5.08" length="short" direction="out" rot="R180"/>
<pin name="GND@3" x="-12.7" y="-15.24" length="short" direction="pwr"/>
<pin name="GND@4" x="-12.7" y="-17.78" length="short" direction="pwr"/>
<pin name="OUT3" x="12.7" y="0" length="short" direction="out" rot="R180"/>
<pin name="IN4" x="-12.7" y="-5.08" length="short" direction="in"/>
<pin name="EN2" x="-12.7" y="-2.54" length="short" direction="in"/>
<pin name="GND@5" x="12.7" y="-17.78" length="short" direction="pwr" rot="R180"/>
<pin name="GND@6" x="12.7" y="-15.24" length="short" direction="pwr" rot="R180"/>
<pin name="GND@7" x="12.7" y="-12.7" length="short" direction="pwr" rot="R180"/>
<pin name="GND@8" x="12.7" y="-10.16" length="short" direction="pwr" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="L293DD" prefix="IC">
<description>&lt;b&gt;PUSH-PULL FOUR CHANNEL DRIVER WITH DIODES&lt;/b&gt;&lt;p&gt;
Source: http://www.st.com/stonline/books/pdf/docs/1330.pdf</description>
<gates>
<gate name="G$1" symbol="L293DD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SO20">
<connects>
<connect gate="G$1" pin="EN1" pad="1"/>
<connect gate="G$1" pin="EN2" pad="11"/>
<connect gate="G$1" pin="GND@1" pad="4"/>
<connect gate="G$1" pin="GND@2" pad="5"/>
<connect gate="G$1" pin="GND@3" pad="6"/>
<connect gate="G$1" pin="GND@4" pad="7"/>
<connect gate="G$1" pin="GND@5" pad="14"/>
<connect gate="G$1" pin="GND@6" pad="15"/>
<connect gate="G$1" pin="GND@7" pad="16"/>
<connect gate="G$1" pin="GND@8" pad="17"/>
<connect gate="G$1" pin="IN1" pad="2"/>
<connect gate="G$1" pin="IN2" pad="9"/>
<connect gate="G$1" pin="IN3" pad="12"/>
<connect gate="G$1" pin="IN4" pad="19"/>
<connect gate="G$1" pin="OUT1" pad="3"/>
<connect gate="G$1" pin="OUT2" pad="8"/>
<connect gate="G$1" pin="OUT3" pad="13"/>
<connect gate="G$1" pin="OUT4" pad="18"/>
<connect gate="G$1" pin="VS" pad="10"/>
<connect gate="G$1" pin="VSS" pad="20"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun-Aesthetics">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find non-functional items- supply symbols, logos, notations, frame blocks, etc.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; CC v3.0 Share-Alike You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
</packages>
<symbols>
<symbol name="5V">
<wire x1="0.762" y1="1.27" x2="0" y2="2.54" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="-0.762" y2="1.27" width="0.254" layer="94"/>
<text x="-1.016" y="3.556" size="1.778" layer="96">&gt;VALUE</text>
<pin name="5V" x="0" y="0" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="DGND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="5V" prefix="SUPPLY">
<gates>
<gate name="G$1" symbol="5V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="GND" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="DGND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="VDD">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<wire x1="1.27" y1="-1.905" x2="0" y2="1.27" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="VDD" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="VDD" prefix="VDD">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="VDD" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="IC1" library="micro-intel" deviceset="8255A" device=""/>
<part name="IC2" library="st-microelectronics" deviceset="L293DD" device=""/>
<part name="IC3" library="st-microelectronics" deviceset="L293DD" device=""/>
<part name="IC4" library="st-microelectronics" deviceset="L293DD" device=""/>
<part name="SUPPLY1" library="SparkFun-Aesthetics" deviceset="5V" device=""/>
<part name="SUPPLY2" library="SparkFun-Aesthetics" deviceset="5V" device=""/>
<part name="SUPPLY3" library="SparkFun-Aesthetics" deviceset="5V" device=""/>
<part name="GND1" library="SparkFun-Aesthetics" deviceset="GND" device=""/>
<part name="V+" library="supply1" deviceset="VDD" device="" value="V+"/>
<part name="VDD2" library="supply1" deviceset="VDD" device="" value="V+"/>
<part name="VDD3" library="supply1" deviceset="VDD" device="" value="V+"/>
<part name="SUPPLY4" library="SparkFun-Aesthetics" deviceset="5V" device=""/>
<part name="SUPPLY5" library="SparkFun-Aesthetics" deviceset="5V" device=""/>
<part name="VDD1" library="supply1" deviceset="VDD" device="" value="V+"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="IC1" gate="A" x="58.42" y="109.22"/>
<instance part="IC2" gate="G$1" x="33.02" y="38.1"/>
<instance part="IC3" gate="G$1" x="83.82" y="38.1"/>
<instance part="IC4" gate="G$1" x="137.16" y="38.1"/>
<instance part="SUPPLY1" gate="G$1" x="48.26" y="53.34"/>
<instance part="SUPPLY2" gate="G$1" x="99.06" y="53.34"/>
<instance part="SUPPLY3" gate="G$1" x="152.4" y="53.34"/>
<instance part="GND1" gate="1" x="81.28" y="10.16"/>
<instance part="V+" gate="G$1" x="17.78" y="55.88"/>
<instance part="VDD2" gate="G$1" x="68.58" y="55.88"/>
<instance part="VDD3" gate="G$1" x="121.92" y="55.88"/>
<instance part="SUPPLY4" gate="G$1" x="5.08" y="45.72"/>
<instance part="SUPPLY5" gate="G$1" x="58.42" y="45.72"/>
<instance part="VDD1" gate="G$1" x="111.76" y="48.26"/>
</instances>
<busses>
<bus name="TO-8051">
<segment>
<wire x1="43.18" y1="96.52" x2="43.18" y2="142.24" width="0.762" layer="92"/>
<wire x1="43.18" y1="142.24" x2="40.64" y2="144.78" width="0.762" layer="92"/>
<wire x1="40.64" y1="144.78" x2="30.48" y2="144.78" width="0.762" layer="92"/>
<label x="30.48" y="142.24" size="1.778" layer="95"/>
</segment>
</bus>
<bus name="OUTPUT-BUS">
<segment>
<wire x1="55.88" y1="48.26" x2="55.88" y2="7.62" width="0.762" layer="92"/>
<wire x1="55.88" y1="7.62" x2="58.42" y2="5.08" width="0.762" layer="92"/>
<wire x1="58.42" y1="5.08" x2="104.14" y2="5.08" width="0.762" layer="92"/>
<wire x1="104.14" y1="5.08" x2="106.68" y2="7.62" width="0.762" layer="92"/>
<wire x1="106.68" y1="48.26" x2="106.68" y2="7.62" width="0.762" layer="92"/>
<wire x1="106.68" y1="7.62" x2="109.22" y2="5.08" width="0.762" layer="92"/>
<wire x1="109.22" y1="5.08" x2="157.48" y2="5.08" width="0.762" layer="92"/>
<wire x1="157.48" y1="5.08" x2="160.02" y2="7.62" width="0.762" layer="92"/>
<wire x1="160.02" y1="7.62" x2="160.02" y2="48.26" width="0.762" layer="92"/>
<wire x1="58.42" y1="5.08" x2="38.1" y2="5.08" width="0.762" layer="92"/>
<label x="38.1" y="2.54" size="1.778" layer="95"/>
</segment>
</bus>
<bus name="B$1">
<segment>
<wire x1="12.7" y1="33.02" x2="12.7" y2="60.96" width="0.762" layer="92"/>
<wire x1="12.7" y1="60.96" x2="15.24" y2="63.5" width="0.762" layer="92"/>
<wire x1="15.24" y1="63.5" x2="60.96" y2="63.5" width="0.762" layer="92"/>
<wire x1="60.96" y1="63.5" x2="63.5" y2="60.96" width="0.762" layer="92"/>
<wire x1="63.5" y1="60.96" x2="63.5" y2="33.02" width="0.762" layer="92"/>
<wire x1="63.5" y1="60.96" x2="66.04" y2="63.5" width="0.762" layer="92"/>
<wire x1="66.04" y1="63.5" x2="76.2" y2="63.5" width="0.762" layer="92"/>
<wire x1="76.2" y1="63.5" x2="114.3" y2="63.5" width="0.762" layer="92"/>
<wire x1="114.3" y1="63.5" x2="116.84" y2="60.96" width="0.762" layer="92"/>
<wire x1="116.84" y1="60.96" x2="116.84" y2="43.18" width="0.762" layer="92"/>
<wire x1="76.2" y1="63.5" x2="76.2" y2="139.7" width="0.762" layer="92"/>
</segment>
</bus>
</busses>
<nets>
<net name="TO-74138" class="0">
<segment>
<pinref part="IC1" gate="A" pin="CS"/>
<wire x1="43.18" y1="91.44" x2="43.18" y2="86.36" width="0.1524" layer="91"/>
<wire x1="43.18" y1="86.36" x2="30.48" y2="86.36" width="0.1524" layer="91"/>
<label x="30.48" y="86.36" size="1.778" layer="95"/>
</segment>
</net>
<net name="5V" class="0">
<segment>
<pinref part="IC4" gate="G$1" pin="VSS"/>
<pinref part="SUPPLY3" gate="G$1" pin="5V"/>
<wire x1="149.86" y1="53.34" x2="152.4" y2="53.34" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC3" gate="G$1" pin="VSS"/>
<pinref part="SUPPLY2" gate="G$1" pin="5V"/>
<wire x1="96.52" y1="53.34" x2="99.06" y2="53.34" width="0.1524" layer="91"/>
<wire x1="93.98" y1="53.34" x2="96.52" y2="53.34" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="VSS"/>
<pinref part="SUPPLY1" gate="G$1" pin="5V"/>
<wire x1="45.72" y1="53.34" x2="48.26" y2="53.34" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="EN1"/>
<wire x1="20.32" y1="45.72" x2="5.08" y2="45.72" width="0.1524" layer="91"/>
<wire x1="5.08" y1="45.72" x2="5.08" y2="35.56" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="EN2"/>
<wire x1="5.08" y1="35.56" x2="20.32" y2="35.56" width="0.1524" layer="91"/>
<pinref part="SUPPLY4" gate="G$1" pin="5V"/>
<junction x="5.08" y="45.72"/>
</segment>
<segment>
<pinref part="IC3" gate="G$1" pin="EN1"/>
<wire x1="71.12" y1="45.72" x2="58.42" y2="45.72" width="0.1524" layer="91"/>
<wire x1="58.42" y1="45.72" x2="58.42" y2="35.56" width="0.1524" layer="91"/>
<pinref part="IC3" gate="G$1" pin="EN2"/>
<wire x1="58.42" y1="35.56" x2="71.12" y2="35.56" width="0.1524" layer="91"/>
<pinref part="SUPPLY5" gate="G$1" pin="5V"/>
<junction x="58.42" y="45.72"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="GND@1"/>
<wire x1="20.32" y1="27.94" x2="20.32" y2="25.4" width="0.1524" layer="91"/>
<pinref part="IC4" gate="G$1" pin="GND@8"/>
<wire x1="20.32" y1="25.4" x2="20.32" y2="22.86" width="0.1524" layer="91"/>
<wire x1="20.32" y1="22.86" x2="20.32" y2="20.32" width="0.1524" layer="91"/>
<wire x1="20.32" y1="20.32" x2="20.32" y2="12.7" width="0.1524" layer="91"/>
<wire x1="20.32" y1="12.7" x2="45.72" y2="12.7" width="0.1524" layer="91"/>
<wire x1="45.72" y1="12.7" x2="71.12" y2="12.7" width="0.1524" layer="91"/>
<wire x1="71.12" y1="12.7" x2="81.28" y2="12.7" width="0.1524" layer="91"/>
<wire x1="81.28" y1="12.7" x2="96.52" y2="12.7" width="0.1524" layer="91"/>
<wire x1="96.52" y1="12.7" x2="124.46" y2="12.7" width="0.1524" layer="91"/>
<wire x1="124.46" y1="12.7" x2="149.86" y2="12.7" width="0.1524" layer="91"/>
<wire x1="149.86" y1="12.7" x2="149.86" y2="20.32" width="0.1524" layer="91"/>
<pinref part="IC3" gate="G$1" pin="GND@8"/>
<wire x1="149.86" y1="20.32" x2="149.86" y2="22.86" width="0.1524" layer="91"/>
<wire x1="149.86" y1="22.86" x2="149.86" y2="25.4" width="0.1524" layer="91"/>
<wire x1="149.86" y1="25.4" x2="149.86" y2="27.94" width="0.1524" layer="91"/>
<wire x1="96.52" y1="27.94" x2="96.52" y2="25.4" width="0.1524" layer="91"/>
<junction x="96.52" y="12.7"/>
<pinref part="IC4" gate="G$1" pin="GND@1"/>
<wire x1="96.52" y1="25.4" x2="96.52" y2="22.86" width="0.1524" layer="91"/>
<wire x1="96.52" y1="22.86" x2="96.52" y2="20.32" width="0.1524" layer="91"/>
<wire x1="96.52" y1="20.32" x2="96.52" y2="12.7" width="0.1524" layer="91"/>
<wire x1="124.46" y1="27.94" x2="124.46" y2="25.4" width="0.1524" layer="91"/>
<junction x="124.46" y="12.7"/>
<pinref part="IC3" gate="G$1" pin="GND@1"/>
<wire x1="124.46" y1="25.4" x2="124.46" y2="22.86" width="0.1524" layer="91"/>
<wire x1="124.46" y1="22.86" x2="124.46" y2="20.32" width="0.1524" layer="91"/>
<wire x1="124.46" y1="20.32" x2="124.46" y2="12.7" width="0.1524" layer="91"/>
<wire x1="71.12" y1="27.94" x2="71.12" y2="25.4" width="0.1524" layer="91"/>
<junction x="71.12" y="12.7"/>
<pinref part="IC2" gate="G$1" pin="GND@8"/>
<wire x1="71.12" y1="25.4" x2="71.12" y2="22.86" width="0.1524" layer="91"/>
<wire x1="71.12" y1="22.86" x2="71.12" y2="20.32" width="0.1524" layer="91"/>
<wire x1="71.12" y1="20.32" x2="71.12" y2="12.7" width="0.1524" layer="91"/>
<wire x1="45.72" y1="27.94" x2="45.72" y2="25.4" width="0.1524" layer="91"/>
<junction x="45.72" y="12.7"/>
<pinref part="GND1" gate="1" pin="GND"/>
<junction x="81.28" y="12.7"/>
<junction x="20.32" y="27.94"/>
<pinref part="IC2" gate="G$1" pin="GND@2"/>
<junction x="20.32" y="25.4"/>
<pinref part="IC2" gate="G$1" pin="GND@3"/>
<junction x="20.32" y="22.86"/>
<pinref part="IC2" gate="G$1" pin="GND@4"/>
<junction x="20.32" y="20.32"/>
<junction x="45.72" y="27.94"/>
<pinref part="IC2" gate="G$1" pin="GND@7"/>
<junction x="45.72" y="25.4"/>
<wire x1="45.72" y1="25.4" x2="45.72" y2="22.86" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="GND@6"/>
<junction x="45.72" y="22.86"/>
<wire x1="45.72" y1="22.86" x2="45.72" y2="20.32" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="GND@5"/>
<junction x="45.72" y="20.32"/>
<wire x1="45.72" y1="20.32" x2="45.72" y2="12.7" width="0.1524" layer="91"/>
<junction x="71.12" y="27.94"/>
<pinref part="IC3" gate="G$1" pin="GND@2"/>
<junction x="71.12" y="25.4"/>
<pinref part="IC3" gate="G$1" pin="GND@3"/>
<junction x="71.12" y="22.86"/>
<pinref part="IC3" gate="G$1" pin="GND@4"/>
<junction x="71.12" y="20.32"/>
<junction x="96.52" y="27.94"/>
<pinref part="IC3" gate="G$1" pin="GND@7"/>
<junction x="96.52" y="25.4"/>
<pinref part="IC3" gate="G$1" pin="GND@6"/>
<junction x="96.52" y="22.86"/>
<pinref part="IC3" gate="G$1" pin="GND@5"/>
<junction x="96.52" y="20.32"/>
<junction x="124.46" y="27.94"/>
<pinref part="IC4" gate="G$1" pin="GND@2"/>
<junction x="124.46" y="25.4"/>
<pinref part="IC4" gate="G$1" pin="GND@3"/>
<junction x="124.46" y="22.86"/>
<pinref part="IC4" gate="G$1" pin="GND@4"/>
<junction x="124.46" y="20.32"/>
<junction x="149.86" y="27.94"/>
<pinref part="IC4" gate="G$1" pin="GND@7"/>
<junction x="149.86" y="25.4"/>
<pinref part="IC4" gate="G$1" pin="GND@6"/>
<junction x="149.86" y="22.86"/>
<pinref part="IC4" gate="G$1" pin="GND@5"/>
<junction x="149.86" y="20.32"/>
</segment>
</net>
<net name="VDD" class="0">
<segment>
<pinref part="V+" gate="G$1" pin="VDD"/>
<pinref part="IC2" gate="G$1" pin="VS"/>
<wire x1="17.78" y1="53.34" x2="20.32" y2="53.34" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="VDD2" gate="G$1" pin="VDD"/>
<pinref part="IC3" gate="G$1" pin="VS"/>
<wire x1="68.58" y1="53.34" x2="71.12" y2="53.34" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="VDD3" gate="G$1" pin="VDD"/>
<pinref part="IC4" gate="G$1" pin="VS"/>
<wire x1="121.92" y1="53.34" x2="124.46" y2="53.34" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC4" gate="G$1" pin="EN1"/>
<wire x1="124.46" y1="45.72" x2="111.76" y2="45.72" width="0.1524" layer="91"/>
<pinref part="VDD1" gate="G$1" pin="VDD"/>
</segment>
</net>
<net name="OUTA.1" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="OUT1"/>
<label x="45.72" y="48.26" size="1.778" layer="95"/>
<wire x1="45.72" y1="48.26" x2="55.88" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="OUTA.0" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="OUT2"/>
<label x="45.72" y="43.18" size="1.778" layer="95"/>
<wire x1="45.72" y1="43.18" x2="55.88" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="OUTA.7" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="OUT3"/>
<label x="45.72" y="38.1" size="1.778" layer="95"/>
<wire x1="45.72" y1="38.1" x2="55.88" y2="38.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="OUTA.6" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="OUT4"/>
<label x="45.72" y="33.02" size="1.778" layer="95"/>
<wire x1="45.72" y1="33.02" x2="55.88" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="OUTA.2" class="0">
<segment>
<pinref part="IC3" gate="G$1" pin="OUT2"/>
<label x="96.52" y="43.18" size="1.778" layer="95"/>
<wire x1="96.52" y1="43.18" x2="106.68" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="OUTA.5" class="0">
<segment>
<pinref part="IC3" gate="G$1" pin="OUT3"/>
<label x="96.52" y="38.1" size="1.778" layer="95"/>
<wire x1="96.52" y1="38.1" x2="106.68" y2="38.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="OUTA.4" class="0">
<segment>
<pinref part="IC3" gate="G$1" pin="OUT4"/>
<label x="96.52" y="33.02" size="1.778" layer="95"/>
<wire x1="96.52" y1="33.02" x2="106.68" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="OUTC.5" class="0">
<segment>
<pinref part="IC4" gate="G$1" pin="OUT1"/>
<label x="149.86" y="48.26" size="1.778" layer="95"/>
<wire x1="149.86" y1="48.26" x2="160.02" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="OUTA.3" class="0">
<segment>
<pinref part="IC3" gate="G$1" pin="OUT1"/>
<label x="96.52" y="48.26" size="1.778" layer="95"/>
<wire x1="96.52" y1="48.26" x2="106.68" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="OUTC.4" class="0">
<segment>
<pinref part="IC4" gate="G$1" pin="OUT2"/>
<label x="149.86" y="43.18" size="1.778" layer="95"/>
<wire x1="149.86" y1="43.18" x2="160.02" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA3" class="0">
<segment>
<wire x1="71.12" y1="48.26" x2="63.5" y2="48.26" width="0.1524" layer="91"/>
<label x="66.04" y="48.26" size="1.778" layer="95"/>
<pinref part="IC3" gate="G$1" pin="IN1"/>
</segment>
</net>
<net name="PA1" class="0">
<segment>
<wire x1="20.32" y1="48.26" x2="12.7" y2="48.26" width="0.1524" layer="91"/>
<label x="15.24" y="48.26" size="1.778" layer="95"/>
<pinref part="IC2" gate="G$1" pin="IN1"/>
</segment>
</net>
<net name="PA0" class="0">
<segment>
<wire x1="20.32" y1="43.18" x2="12.7" y2="43.18" width="0.1524" layer="91"/>
<label x="15.24" y="43.18" size="1.778" layer="95"/>
<pinref part="IC2" gate="G$1" pin="IN2"/>
</segment>
</net>
<net name="PA6" class="0">
<segment>
<wire x1="20.32" y1="33.02" x2="12.7" y2="33.02" width="0.1524" layer="91"/>
<label x="15.24" y="33.02" size="1.778" layer="95"/>
<pinref part="IC2" gate="G$1" pin="IN4"/>
</segment>
</net>
<net name="PA7" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="IN3"/>
<wire x1="20.32" y1="38.1" x2="12.7" y2="38.1" width="0.1524" layer="91"/>
<label x="15.24" y="38.1" size="1.778" layer="95"/>
</segment>
</net>
<net name="PA2" class="0">
<segment>
<pinref part="IC3" gate="G$1" pin="IN2"/>
<wire x1="71.12" y1="43.18" x2="63.5" y2="43.18" width="0.1524" layer="91"/>
<label x="66.04" y="43.18" size="1.778" layer="95"/>
</segment>
</net>
<net name="PA5" class="0">
<segment>
<pinref part="IC3" gate="G$1" pin="IN3"/>
<wire x1="71.12" y1="38.1" x2="63.5" y2="38.1" width="0.1524" layer="91"/>
<label x="66.04" y="38.1" size="1.778" layer="95"/>
</segment>
</net>
<net name="PA4" class="0">
<segment>
<pinref part="IC3" gate="G$1" pin="IN4"/>
<wire x1="71.12" y1="33.02" x2="63.5" y2="33.02" width="0.1524" layer="91"/>
<label x="66.04" y="33.02" size="1.778" layer="95"/>
</segment>
</net>
<net name="PC5" class="0">
<segment>
<pinref part="IC4" gate="G$1" pin="IN1"/>
<wire x1="124.46" y1="48.26" x2="116.84" y2="48.26" width="0.1524" layer="91"/>
<label x="119.38" y="48.26" size="1.778" layer="95"/>
</segment>
</net>
<net name="PC4" class="0">
<segment>
<pinref part="IC4" gate="G$1" pin="IN2"/>
<wire x1="124.46" y1="43.18" x2="116.84" y2="43.18" width="0.1524" layer="91"/>
<label x="119.38" y="43.18" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="IC1" gate="A" pin="PA0"/>
<wire x1="71.12" y1="139.7" x2="76.2" y2="139.7" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="71.12" y1="137.16" x2="76.2" y2="137.16" width="0.1524" layer="91"/>
<pinref part="IC1" gate="A" pin="PA1"/>
</segment>
<segment>
<wire x1="71.12" y1="134.62" x2="76.2" y2="134.62" width="0.1524" layer="91"/>
<pinref part="IC1" gate="A" pin="PA2"/>
</segment>
<segment>
<wire x1="71.12" y1="132.08" x2="76.2" y2="132.08" width="0.1524" layer="91"/>
<pinref part="IC1" gate="A" pin="PA3"/>
</segment>
<segment>
<wire x1="71.12" y1="129.54" x2="76.2" y2="129.54" width="0.1524" layer="91"/>
<pinref part="IC1" gate="A" pin="PA4"/>
</segment>
<segment>
<wire x1="71.12" y1="127" x2="76.2" y2="127" width="0.1524" layer="91"/>
<pinref part="IC1" gate="A" pin="PA5"/>
</segment>
<segment>
<wire x1="71.12" y1="124.46" x2="76.2" y2="124.46" width="0.1524" layer="91"/>
<pinref part="IC1" gate="A" pin="PA6"/>
</segment>
<segment>
<wire x1="71.12" y1="121.92" x2="76.2" y2="121.92" width="0.1524" layer="91"/>
<pinref part="IC1" gate="A" pin="PA7"/>
</segment>
<segment>
<wire x1="71.12" y1="81.28" x2="76.2" y2="81.28" width="0.1524" layer="91"/>
<pinref part="IC1" gate="A" pin="PC5"/>
</segment>
<segment>
<wire x1="71.12" y1="83.82" x2="76.2" y2="83.82" width="0.1524" layer="91"/>
<pinref part="IC1" gate="A" pin="PC4"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
