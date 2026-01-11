.. FIRMWARE.rst --- 
.. 
.. Description: 
.. Author: Hongyi Wu(吴鸿毅)
.. Email: wuhongyi@qq.com 
.. Created: 日 9月  8 21:25:48 2024 (+0800)
.. Last-Updated: 日 1月 11 16:40:52 2026 (+0800)
..           By: Hongyi Wu(吴鸿毅)
..     Update #: 24
.. URL: http://wuhongyi.cn 

=================================
Firmware
=================================

---------------------------------
Latest Firmware
---------------------------------

- 2745
    - V2745-scope-1G-2025102000.cup
    - V2745-dpp-pha-1G-2025102402.cup
    - V2745-dpp-psd-1G-2025052200.cup
    - V2745-dpp-zle-1G-2025093000.cup
    - V2745-OpenDPP-2026011100.cup PHA+PSD 
    - V2745-OpenDPP-2026011101.cup PHA+CFD
    - V2745-OpenScope-2026011004.cup
- 2740
    - V2740-scope-1G-2025102000.cup
    - V2740-dpp-pha-1G-2025102402.cup
    - V2740-dpp-psd-1G-2025052200.cup
    - V2740-dpp-zle-1G-2025093000.cup
    - V2740-OpenDPP-2026011008.cup PHA+PSD 
    - V2740-OpenDPP-2026011007.cup PHA+CFD
    - V2740-OpenScope-2026011002.cup
- 2730
    - V2730-scope-1G-2025102002.cup
    - V2730-dpp-pha-1G-2025102401.cup
    - V2730-dpp-psd-1G-2025121611.cup
    - V2730-OpenDPP-2026011006.cup PHA+PSD
    - V2730-OpenDPP-2026011005.cup PHA+CFD
- 2751
    - V2751-scope-1G-2025102001.cup
    - V2751-dpp-psd-1G-2025121612.cup
    - V2751-OpenDPP-2026011102.cup  PHA+PSD



 To facilitate experimental diagnosis and debugging, we have proposed that CAEN add/modify the following features in the DPP firmware:

- External signal timestamp reset: The timestamp can be reset via SIN/GPIO input signals (Completed).
- Option to reset the timestamp when acquiring start (Not completed).
- Addition of monitoring parameters similar to SelfTriggerRate to monitor coincidence/anti-coincidence count rates and actual output count rates (Not completed).
- Addition of coincidence and anti-coincidence monitoring signals in WaveDigitalProbe (Completed).
- Addition of input signal delay for 2730 (Not completed).

  

---------------------------------
Firmware Update
---------------------------------

Access the module configuration page via USB (CAENDGTZ-USB-{PIDNUMBER}) or IP. There is a "Firmware" option in the left menu bar. Click to enter the page, as shown below:


.. image:: /_static/img/firmwareupdate.png

Check whether the Scope/PHA/PSD/ZLE firmware versions on this page are consistent with those in the firmware folder of the obtained package. If they are not, upload new firmware through "Upload new firmware". Each firmware on the webpage has a blue down triangle button on the right side. By clicking the button, you can switch to the currently used firmware, set the default firmware loaded at startup, etc. In addition, promptly delete old versions of firmware.

	   
   
.. 
.. FIRMWARE.rst ends here
