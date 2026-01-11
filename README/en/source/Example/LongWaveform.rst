.. LongWaveform.rst --- 
.. 
.. Description: 
.. Author: Hongyi Wu(吴鸿毅)
.. Email: wuhongyi@qq.com 
.. Created: 六 1月 10 22:39:15 2026 (+0800)
.. Last-Updated: 六 1月 10 22:42:23 2026 (+0800)
..           By: Hongyi Wu(吴鸿毅)
..     Update #: 1
.. URL: http://wuhongyi.cn 

##################################################
Ultra-Long Waveform Acquisition
##################################################

In fusion research devices, some related diagnostic detectors experience extremely high instantaneous counting rates and severe pulse pile-up, requiring continuous waveform recording for durations exceeding 1 second. The scope firmware can help you achieve this goal.

============================================================
Acquisition Mode
============================================================

When using the ultra-long waveform acquisition mode, only Channel 0 can be used. All other channels must be disabled, as the system allocates all available memory to Channel 0.

Taking the recording of a 2-second continuous waveform as an example, the setup involves configuring a single pulse record length of 10 ms, using an external trigger, and sending 200 consecutive triggers at 10 ms intervals.

In practice, it is necessary to account for timing discrepancies between the external clock and the acquisition module's clock. Therefore, the recorded waveform length should be set slightly longer than the configured trigger interval. Enabling waveform overlap is recommended to ensure continuous acquisition without data loss.

When using Gigabit Ethernet for data readout, tests on the 2730 model have achieved continuous acquisition for up to 5.7 seconds. Using the 10G UDP mode enables recording of even longer waveforms.

To avoid data transfer delays to disk during acquisition, the acquisition software is equipped with a specialized data writing mode. Users can adjust the allocated memory size. Data is written to disk in blocks only when the accumulated data in memory reaches the specified size.

============================================================
Clearing Computer Cache
============================================================

In Linux systems, buff/cache typically refers to buffers and caches used to accelerate disk and file access. Clearing this memory is usually done to free up space for other applications, but it is not a common operation as the kernel manages this memory automatically. However, when recording ultra-long waveforms, the program may require several GiB of memory. After running the program multiple times, the buff/cache may not be released promptly.

If you need to clear the buff/cache, you can execute the `sync` command to ensure all data from buffers and caches is written to disk. Then, you can use the `echo` command to write to `/proc/sys/vm/drop_caches` to clear the buffers and caches.

.. code-block:: bash
  
  # Synchronize disk data
  sudo sync
  # Clear page cache
  sudo bash -c "echo 1 > /proc/sys/vm/drop_caches"
  # Clear dentries and inodes
  sudo bash -c "echo 2 > /proc/sys/vm/drop_caches"
  # Clear page cache, dentries, and inodes
  sudo bash -c "echo 3 > /proc/sys/vm/drop_caches"
   
.. 
.. LongWaveform.rst ends here
