.. FIRMWARE.rst --- 
.. 
.. Description: 
.. Author: Hongyi Wu(吴鸿毅)
.. Email: wuhongyi@qq.com 
.. Created: 六 2月  3 20:59:00 2024 (+0800)
.. Last-Updated: 四 12月 18 20:42:40 2025 (+0800)
..           By: Hongyi Wu(吴鸿毅)
..     Update #: 29
.. URL: http://wuhongyi.cn 

=================================
固件
=================================

---------------------------------
最新固件
---------------------------------


- 2745
    - V2745-scope-1G-2025102000.cup
    - V2745-dpp-pha-1G-2025102402.cup
    - V2745-dpp-psd-1G-2025052200.cup
    - V2745-dpp-zle-1G-2025093000.cup
    - V2745-OpenDPP-2025121701.cup
    - V2745-OpenScope-2025051100.cup
- 2740
    - V2740-scope-1G-2025102000.cup
    - V2740-dpp-pha-1G-2025102402.cup
    - V2740-dpp-psd-1G-2025052200.cup
    - V2740-dpp-zle-1G-2025093000.cup
    - V2740-OpenDPP-2025121700.cup
    - V2740-OpenScope-2025051102.cup
- 2730
    - V2730-scope-1G-2025102002.cup
    - V2730-dpp-pha-1G-2025102401.cup
    - V2730-dpp-psd-1G-2025121611.cup
    - V2730-OpenDPP-2025121703.cup
- 2751
    - V2751-scope-1G-2025102001.cup
    - V2751-dpp-psd-1G-2025121612.cup
    - V2751-OpenDPP-2025121702.cup


      
为了方便实验的诊断和调试，我们建议 CAEN 在 DPP 固件中添加/修改了以下功能:

- 外部信号重置时间戳，可通过 SIN/GPIO 输入信号来重置时间戳（已完成）
- 获取 start 时可选是否重置时间戳（未完成）
- 添加类似 SelfTriggerRate 的监视参数，监视符合/反符合的计数率，监视实际的输出计数率（未完成）
- WaveDigitalProbe 中添加符合、反符合监视信号（已完成）
- 2730 添加输入信号延迟（未完成）


      
---------------------------------
固件更新
---------------------------------

通过 USB （CAENDGTZ-USB-{PIDNUMBER}）或者 IP 方式访问模块配置页面，在左侧菜单栏有个 Fireware，点击进入该页面，如下： 

.. image:: /_static/img/firmwareupdate.png

检查该页面的 Scope/PHA/PSD/ZLE 固件版本与获取程序包中， firmware 文件夹内的是否一致，如果不一致，通过 “Upload new firmware” 上传新固件。 网页中每个固件右端均有一个蓝色下三角按钮，通过点击该按钮，可以进行当前使用的固件进行切换，设置开机默认加载的固件等。另外，及时删除老版本的固件。


.. 
.. FIRMWARE.rst ends here
