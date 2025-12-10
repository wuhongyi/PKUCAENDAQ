.. DecodeAndSort.rst --- 
.. 
.. Description: 
.. Author: Hongyi Wu(吴鸿毅)
.. Email: wuhongyi@qq.com 
.. Created: 五 6月 14 17:55:18 2024 (+0800)
.. Last-Updated: 三 12月 10 15:32:47 2025 (+0800)
..           By: Hongyi Wu(吴鸿毅)
..     Update #: 3
.. URL: http://wuhongyi.cn 

##################################################
数据解码
##################################################

**DecodeAndSortAll 程序用来将同一轮数据不同采集卡采集的数据转为一个 ROOT 文件。用户的物理分析以本程序产生的 ROOT 文件为基准。本程序生成的数据已经按照时间戳从小到大排列。**

用户首先需要修改 **UesrDefine.hh** 文件中的定义

.. code:: cpp

  // #define ONLYPHA
  // #define ONLYPSD
  // #define ONLYZLE
  // #define ONLYSCOPE

如果获取中所有的模块只使用一个类型的固件，则开启对应的定义。如果没有单一固件的定义，则输出的数据文件将默认支持所有的类型固件。



.. code:: cpp

  #define ROOTFILEPATH "./"       //要生成ROOT文件的路径
  #define ROOTFILENAME "data"     //要生成ROOT文件的名字
  // 生成 ROOT 文件的路径和文件名


  
.. code:: cpp

  #define RAWFILEPATH "/home/wuhongyi/"      //原始数据的路径
  #define RAWFILENAME "data"                 //原始数据的文件名
  #define MODNUMBER 2                        //机箱中使用的模块数
  const unsigned short SamplingRate[MODNUMBER] = {500, 125};//Specify the sampling rate of each modules separately; 125/500/1000 sampling rates; 0 to skip the module
  const unsigned short Firmware[MODNUMBER] = {2, 0};//DPP_PHA=0 DPP_ZLE=1 DPP_PSD=2 DPP_DAW=3 OPEN=4 Scope=5
  // 指定每个模块的固件类型，如果类型指定错误，解码数据将存在问题



修改之后执行以下命令编译程序：
  
.. code:: bash
	  
  make clean
  make


编译成功之后将生成一个可执行文件 **decodeandsort**，程序运行方式：

.. code:: bash

  ./decodeandsort [RunNnumber] 

其中 *[RunNnumber]* 为想要转换的文件运行编号。

------------------------------------


PHA/PSD 数据结构

**flahshigh**

- bit 0 Pile-Up
   - Identifies pile-up events, ie two events in which the second one occurred before the Peaking Time of the first one. Both are then tagged as pile-up because it's not possible to evaluate their energy. See EnergyFilterPeakingPosition
- bit 1 Pile-up rejector guard event
   - Identifies an event occurred during the pile-up rejector guard window. See EnergyFilterPileUpGuardT, EnergyFilterPileUpGuardS. There are cases in which both such bits can be '1': if an event ccurs in the pile-up rejector guard of the previous one and does not reach the peaking time because another event has occurred, then such event will have both bits at 1. This allows, with the same data and without doing two separate acquisitions, to have two spectra: one corrected for the PUR guard and one not corrected
- bit 2 Event Saturation
   - Identifies an event in which a saturation of the input dynamics occurred
- bit 3 Post saturation event
   - Identifies an event occurred during the ADCVetoWidth time
- bit 4 Trapezoid saturation event
   - Identifies an event in which a saturation of the trapezoid occurred.
- bit 5 SCA selected event
   - Identifies an event falling within the SCA windows (if enabled).


**flahslow**

- bit 0 Event waveform occurred during external inhibit
   - Identifies a saved waveform because occurred when the external inhibit is active (useful in case of Transistor Reset Preamplifier detector use to see what happens during the reset).
- bit 1 Event waveform under-saturation
   - Identifies a saved waveform because under-saturating
- bit 2 Event waveform oversaturation
   - Identifies a saved waveform because over-saturating
- bit 3 External trigger
   - Identifies an event triggered by the external trigger from the TRG-IN connector
- bit 4 Global trigger
   - Identifies an event triggered by a global trigger condition
- bit 5 Software trigger
   - Identifies an event triggered by a software trigger
- bit 6 Self trigger
   - Identifies an event triggered by the single channel self trigger
- bit 7 LVDS trigger
   - Identifies an event triggered by the external trigger from the LVDS connector
- bit 8 64 channel trigger
   - Identifies an event triggered by another (or a combination of other) channels trigger
- bit 9 ITLA trigger
   - Identifies an event triggered by the ITLA logic
- bit 10 ITLB trigger
   - Identifies an event triggered by the ITLB logic


     
.. 
.. DecodeAndSort.rst ends here
