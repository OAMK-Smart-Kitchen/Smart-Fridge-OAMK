<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.3">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
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
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="con-power c">
<description>&lt;b&gt;SHALLIN Electronics Co., Ltd.&lt;/b&gt;&lt;p&gt;
NO. 45, LANE 135, SEC. 3, HAI AN RD. TAININ, TAIWAN&lt;br&gt;
http://www.shallin.com&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="K375M">
<description>&lt;b&gt;K375M - DC POWER JACK 2.5mm/CENTRAL PIN&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="http://www.shallin.com/productview.aspx?itemnumber=K375M"&gt; Data sheet &lt;/a&gt;</description>
<wire x1="1.35" y1="6.9" x2="1.35" y2="0.9" width="0.2032" layer="21"/>
<wire x1="1.35" y1="0.9" x2="-1.35" y2="0.9" width="0.2032" layer="21"/>
<wire x1="-1.35" y1="0.9" x2="-1.35" y2="6.9" width="0.2032" layer="21"/>
<wire x1="0" y1="2.5" x2="0" y2="6" width="2" layer="21"/>
<text x="-6" y="-0.5" size="1.27" layer="25" ratio="5" rot="R90">&gt;NAME</text>
<text x="-4" y="8" size="1.27" layer="27" ratio="5">&gt;VALUE</text>
<rectangle x1="-1" y1="1" x2="1" y2="2.5" layer="21" rot="R180"/>
<wire x1="4.5" y1="7" x2="-4.5" y2="7" width="0.127" layer="21"/>
<wire x1="1.5" y1="7" x2="1" y2="7" width="0.127" layer="21"/>
<wire x1="-1.5" y1="7" x2="-1" y2="7" width="0.127" layer="21"/>
<rectangle x1="-1" y1="4.5" x2="1" y2="6" layer="21" rot="R180"/>
<hole x="0" y="3.5" drill="2.1"/>
<pad name="P$1" x="5" y="3" drill="1" diameter="1.9304" shape="long" rot="R90"/>
<pad name="P$6" x="-5" y="-4.5" drill="1" diameter="1.9304" shape="long" rot="R270"/>
<hole x="-4.953" y="-3.429" drill="1"/>
<hole x="-4.953" y="-3.683" drill="1"/>
<hole x="-4.953" y="-3.937" drill="1"/>
<hole x="-4.953" y="-4.191" drill="1"/>
<hole x="-4.953" y="-4.445" drill="1"/>
<hole x="-4.953" y="-4.699" drill="1"/>
<hole x="-4.953" y="-4.953" drill="1"/>
<hole x="-4.953" y="-5.207" drill="1"/>
<hole x="-4.953" y="-5.461" drill="1"/>
<pad name="P$7" x="0.0042" y="-7.0066" drill="1" diameter="1.9304" shape="long"/>
<hole x="-1.0668" y="-6.9596" drill="1"/>
<hole x="-0.8128" y="-6.9596" drill="1"/>
<hole x="-0.5588" y="-6.9596" drill="1"/>
<hole x="-0.3048" y="-6.9596" drill="1"/>
<hole x="-0.0508" y="-6.9596" drill="1"/>
<hole x="0.2032" y="-6.9596" drill="1"/>
<hole x="0.4572" y="-6.9596" drill="1"/>
<hole x="0.7112" y="-6.9596" drill="1"/>
<hole x="0.9652" y="-6.9596" drill="1"/>
<hole x="5.0546" y="4.064" drill="1"/>
<hole x="5.0546" y="3.81" drill="1"/>
<hole x="5.0546" y="3.556" drill="1"/>
<hole x="5.0546" y="3.302" drill="1"/>
<hole x="5.0546" y="3.048" drill="1"/>
<hole x="5.0546" y="2.794" drill="1"/>
<hole x="5.0546" y="2.54" drill="1"/>
<hole x="5.0546" y="2.286" drill="1"/>
<hole x="5.0546" y="2.032" drill="1"/>
<wire x1="4.5" y1="7" x2="4.5" y2="-7" width="0.127" layer="21"/>
<wire x1="4.5" y1="-7" x2="-4.5" y2="-7" width="0.127" layer="21"/>
<wire x1="-4.5" y1="-7" x2="-4.5" y2="7" width="0.127" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="K375M">
<wire x1="-2.54" y1="2.54" x2="2.54" y2="2.54" width="0.762" layer="94"/>
<wire x1="-2.54" y1="0" x2="0" y2="0" width="0.1524" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="-2.54" x2="0.762" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0.762" y1="-2.54" x2="1.651" y2="-1.651" width="0.1524" layer="94"/>
<wire x1="1.651" y1="-1.651" x2="2.54" y2="-2.54" width="0.1524" layer="94"/>
<text x="-2.54" y="6.35" size="1.778" layer="95" ratio="5">&gt;NAME</text>
<text x="-2.54" y="-7.62" size="1.778" layer="96" ratio="5">&gt;VALUE</text>
<pin name="1" x="-5.08" y="2.54" visible="off" length="short" direction="pas"/>
<pin name="2" x="-5.08" y="-2.54" visible="off" length="short" direction="pas"/>
<pin name="3" x="-5.08" y="0" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="K375M" prefix="X">
<description>&lt;b&gt;K375M - DC POWER JACK 2.5mm/CENTRAL PIN&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="http://www.shallin.com/productview.aspx?itemnumber=K375M"&gt; Data sheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="K375M" x="0" y="0"/>
</gates>
<devices>
<device name="" package="K375M">
<connects>
<connect gate="G$1" pin="1" pad="P$7"/>
<connect gate="G$1" pin="2" pad="P$1"/>
<connect gate="G$1" pin="3" pad="P$6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-lstb">
<description>&lt;b&gt;Pin Headers&lt;/b&gt;&lt;p&gt;
Naming:&lt;p&gt;
MA = male&lt;p&gt;
# contacts - # rows&lt;p&gt;
W = angled&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="MA03-1">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-3.175" y1="1.27" x2="-1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="0.635" x2="-3.81" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-3.81" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="-0.635" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.27" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="0.635" x2="3.81" y2="-0.635" width="0.1524" layer="21"/>
<pad name="1" x="-2.54" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="0" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="2.54" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-3.81" y="1.651" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-0.635" size="1.27" layer="21" ratio="10">1</text>
<text x="-3.81" y="-2.921" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
<rectangle x1="-2.794" y1="-0.254" x2="-2.286" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="MA03-1">
<wire x1="3.81" y1="-5.08" x2="-1.27" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="1.27" y1="2.54" x2="2.54" y2="2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="0" x2="2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="2.54" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="5.08" x2="-1.27" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-5.08" x2="3.81" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-1.27" y1="5.08" x2="3.81" y2="5.08" width="0.4064" layer="94"/>
<text x="-1.27" y="-7.62" size="1.778" layer="96">&gt;VALUE</text>
<text x="-1.27" y="5.842" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MA03-1" prefix="SV" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="MA03-1" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MA03-1">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
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
<part name="X1" library="con-power c" deviceset="K375M" device=""/>
<part name="SV1" library="con-lstb" deviceset="MA03-1" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="X1" gate="G$1" x="53.34" y="50.8"/>
<instance part="SV1" gate="G$1" x="25.4" y="50.8"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="X1" gate="G$1" pin="1"/>
<wire x1="48.26" y1="53.34" x2="33.02" y2="53.34" width="0.1524" layer="91"/>
<pinref part="SV1" gate="G$1" pin="3"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="X1" gate="G$1" pin="3"/>
<pinref part="SV1" gate="G$1" pin="2"/>
<wire x1="48.26" y1="50.8" x2="33.02" y2="50.8" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="1"/>
<pinref part="X1" gate="G$1" pin="2"/>
<wire x1="33.02" y1="48.26" x2="48.26" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
