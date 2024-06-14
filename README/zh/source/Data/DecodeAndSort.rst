.. DecodeAndSort.rst --- 
.. 
.. Description: 
.. Author: Hongyi Wu(吴鸿毅)
.. Email: wuhongyi@qq.com 
.. Created: 五 6月 14 17:55:18 2024 (+0800)
.. Last-Updated: 五 6月 14 18:24:27 2024 (+0800)
..           By: Hongyi Wu(吴鸿毅)
..     Update #: 2
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

   
.. 
.. DecodeAndSort.rst ends here
