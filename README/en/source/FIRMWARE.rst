.. FIRMWARE.rst --- 
.. 
.. Description: 
.. Author: Hongyi Wu(吴鸿毅)
.. Email: wuhongyi@qq.com 
.. Created: 日 9月  8 21:25:48 2024 (+0800)
.. Last-Updated: 二 10月  1 18:17:40 2024 (+0800)
..           By: Hongyi Wu(吴鸿毅)
..     Update #: 2
.. URL: http://wuhongyi.cn 

=================================
Firmware
=================================

---------------------------------
Latest Firmware
---------------------------------


- 2745
    - V2745-scope-1G-2024051505.cup
    - V2745-dpp-pha-1G-2024091704.cup
    - V2745-dpp-psd-1G-2023091901.cup  
    - V2745-dpp-zle-1G-2023091902.cup
    - V2745-OpenDPP-2024091700.cup  
- 2740
    - V2740-scope-1G-2024051505.cup
    - V2740-dpp-pha-1G-2023112703.cup  
    - V2740-dpp-psd-1G-2023091901.cup
    - V2740-dpp-zle-1G-2023091902.cup
    - V2740-OpenDPP-2024091701.cup  
- 2730
    - V2730-scope-1G-2024062500.cup
    - V2730-dpp-psd-1G-2024092000.cup
    - V2730-OpenDPP-2024091804.cup

  

---------------------------------
Firmware Update
---------------------------------

Access the module configuration page via USB （CAENDGTZ-USB-{PIDNUMBER}） or IP. There is a "Fireware" option in the left menu bar, click to enter the page, as follows:

.. image:: /_static/img/firmwareupdate.png

Check if the Scope/PHA/PSD/ZLE firmware version on this page matches the **firmware** folder in thepackage. If not, upload the new firmware through 'Upload new firmware'. There is a blue bottom triangle button on the right end of each firmware in the webpage. By clicking this button, you can switch between the currently used firmware and set the default firmware to load when booting up. Additionally, promptly remove outdated firmware versions.
	   
   
.. 
.. FIRMWARE.rst ends here
