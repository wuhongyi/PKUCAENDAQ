.. UserDPP.rst --- 
.. 
.. Description: 
.. Author: Hongyi Wu(吴鸿毅)
.. Email: wuhongyi@qq.com 
.. Created: 二 10月  1 23:38:02 2024 (+0800)
.. Last-Updated: 六 1月 10 22:56:39 2026 (+0800)
..           By: Hongyi Wu(吴鸿毅)
..     Update #: 5
.. URL: http://wuhongyi.cn 

##################################################
UserDPP Firmware
##################################################

**Firmware developed by Hongyi Wu(wuhongyi@qq.com / wuhongyi@pku.edu.cn), focusing on the implementation of special algorithms.**

Currently supports firmware customization for models 2740/2745/2730/2751. Teachers with special firmware requirements are welcome to contact us.

For the 2730 firmware, the FPGA operates at a clock frequency of 125 MHz. Four sampling points per clock cycle are summed and processed as one sampling point. For the 2751 firmware, the FPGA operates at a clock frequency of 125 MHz, with eight sampling points per clock cycle summed and processed as one sampling point.

============================================================
PHA
============================================================


----------------------------------------------------------------------
Input Signal
----------------------------------------------------------------------

.. image:: /_static/img/userdpp_basic_input.png


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: ChEnable
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Independently sets whether each channel is enabled for use. If a channel is not enabled, it does not provide any data, and its self-triggering is also disabled.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: DCOffset
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

When the input signal is of positive polarity, DCOffset 0% corresponds to channel address 0; when the input signal is of negative polarity, DCOffset 100% corresponds to channel address 0.


----------------------------------------------------------------------
UserDPP
----------------------------------------------------------------------

.. image:: /_static/img/userdpp_basic_userdpp.png


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


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: Pre-trigger
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

The length recorded before the trigger when capturing waveforms.

- For 2740/2745: Maximum configurable value is 4095, unit is sampling points.
- For 2730: Maximum configurable value is 4095, unit is 4 sampling points.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: Wave Length
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

When the parameter value is greater than 0, waveform recording is enabled.

- For 2740/2745: Maximum configurable value is 4095, unit is 4 sampling points.
- For 2730: Maximum configurable value is 4095, unit is 4 sampling points.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: BL
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Length of two consecutive integration segments in the baseline evaluation strategy.

**Maximum configurable values: 1023 for 2740/2745; 2047 for 2730/2751.**


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: XIAoffset
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

This parameter represents the sampling points before the trigger. Used to determine the precise integration intervals for the three segments of the trapezoidal filter.

Unit is 8 ns.
Maximum configurable value for 2740/2745 is 255.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: SL
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Rise time length parameter for the trapezoidal filter.

Unit is 8 ns.
Maximum configurable value is 1023.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: SG
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Flat top length parameter for the trapezoidal filter.

Unit is 8 ns.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: TAU
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Signal decay time constant.

This parameter is used for calculation during online monitoring. It must be input into the decoding file during data decoding.

Unit is ns.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Logic Parameter
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

validtriggerdelay 256 for 2740/2745/2730/2751.

============================================================
PHA+PSD
============================================================


----------------------------------------------------------------------
UserDPP
----------------------------------------------------------------------


.. image:: /_static/img/userdpp_basic_userdpp.png


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: Qoffset
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Trigger delay for QDC integration. Unit is 8 ns.

Maximum configurable value for 2740/2745 is 127.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: Qshort
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Short gate for QDC integration. Unit is 8 ns.

Maximum configurable value for 2740/2745 is 8191.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: Qlong
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Long gate for QDC integration. Unit is 8 ns.

Maximum configurable value for 2740/2745 is 8191.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: COS offset
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Integration start offset for the Cosine Similarity Discrimination algorithm. Unit is 8 ns.

Maximum configurable value for 2740/2745 is 127.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: COS gate
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Integration gate for the Cosine Similarity Discrimination algorithm. Unit is 8 ns.

Maximum configurable value for 2740/2745 is 1023.

============================================================
PHA+CFD
============================================================


----------------------------------------------------------------------
UserDPP
----------------------------------------------------------------------


.. image:: /_static/img/userdpp_basic_userdpp.png


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: CFD DELAY
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Delay parameter for the CFD algorithm. Unit is 8 ns.

Maximum configurable value is 127.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Parameter: CFD FRAC
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

CFD fraction parameter, configurable range 0-7. Corresponds to compression factors of 8/8, 7/8, 6/8, 5/8, 4/8, 3/8, 2/8, 1/8.

   
.. 
.. UserDPP.rst ends here
