.. HPGe.rst --- 
.. 
.. Description: 
.. Author: Hongyi Wu(吴鸿毅)
.. Email: wuhongyi@qq.com 
.. Created: 三 10月  2 15:39:29 2024 (+0800)
.. Last-Updated: 三 10月  2 15:53:29 2024 (+0800)
..           By: Hongyi Wu(吴鸿毅)
..     Update #: 4
.. URL: http://wuhongyi.cn 

=================================
HPGe
=================================

- VGAGain
   - Adjust the gain to achieve a measurement range of 6 MeV
- Thre
   - based on the noise situation
   - about 50
- PoleZero
   - based on pre amp parameter
   - about 50us
- TriggerTriangular
   - 104 ns
- BaselineAvg
   - MediumHigt
- EnergyRiseTIme
   - 5104 ns
- EnergyFlatTop
   - 1200 ns
- PeakingPosition
   - 91%
- PeakingAvg
   - OneShot

.. image:: /_static/img/clover_fastfilter.png
     
.. image:: /_static/img/clover_energyfilter.png


     
x2745 测量结果:
     
- dynamic range : 0-2MeV
   - FWHM: 0.15% @ 1332 keV   TriggerRate ~ 1000/s
- dynamic range : 0-6MeV
   - FWHM: 0.16% @ 1332 keV   TriggerRate ~ 1000/s
   - FWHM: 0.175% @ 1332 keV   TriggerRate ~ 4000/s
   - FWHM: 0.190% @ 1332 keV   TriggerRate ~ 10000/s


.. image:: /_static/img/example_Clover_online.png

   
.. 
.. HPGe.rst ends here
