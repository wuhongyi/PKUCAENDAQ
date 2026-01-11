.. UserScope.rst --- 
.. 
.. Description: 
.. Author: Hongyi Wu(吴鸿毅)
.. Email: wuhongyi@qq.com 
.. Created: 六 1月 10 22:23:07 2026 (+0800)
.. Last-Updated: 六 1月 10 22:28:42 2026 (+0800)
..           By: Hongyi Wu(吴鸿毅)
..     Update #: 1
.. URL: http://wuhongyi.cn 

##################################################
UserScope Firmware
##################################################

**Firmware developed by Hongyi Wu(wuhongyi@qq.com/wuhongyi@pku.edu.cn). This firmware focuses on recording ultra-long waveforms.**

Currently supports firmware customization for models 2740/2745/2730/2751. Teachers with special firmware requirements are welcome to contact us.

============================================================
Basic Parameter Configuration
============================================================


----------------------------------------------------------------------
Input Signal
----------------------------------------------------------------------

.. image:: /_static/img/userscope_basic_input.png


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: ChEnable
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Independently sets whether each channel is enabled for use. If a channel is not enabled, it does not provide any data, and its self-triggering is also disabled.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: DCOffset
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

When the input signal is of positive polarity, DCOffset 0% corresponds to channel address 0; when the input signal is of negative polarity, DCOffset 100% corresponds to channel address 0.


----------------------------------------------------------------------
UserScope
----------------------------------------------------------------------


.. image:: /_static/img/userscope_basic_userscope.png


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: Polarity
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Set to 1 when the input signal is of positive polarity, and to 0 when it is of negative polarity.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: FL
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Parameter for XIA fast filter (fast trapezoidal filter parameter).

The unit for FL is 8 ns. Configurable range is 1-127.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: FL+FG
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Fast trapezoidal filter parameter.

The unit for FL+FG is 8 ns. This parameter must be greater than or equal to FL. Configurable range is 1-127.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: Threshold
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Trigger threshold for the fast trapezoidal filter.
   
.. 
.. UserScope.rst ends here
