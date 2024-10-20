* Compile cps2linux and place the binary in your ~/bin folder.

* If you're using RetroDebugger, make sure it's in your path.  You can do this by adding a symbolic link to it in your user bin path.
  
      ln -s /path/to/wherever_retrobugger_exist ~/bin/retrodebugger
  
* In CBM Prg Studio, open Tools | Options and configure the following:
   * Emulator Control
       * Emulator and path:  Z:\home\your_user_name\bin\cps2linux.

           [NOTE: That period at the end of the path is not a typo, add it!]
         
       * Emulator parameters:  c2l_x64 %prg
         
           Note that you would replace the "x64" portion with the name of another emulator if configuring for systems other than the commodore 64.

  * Debugger
      Switch from Use CBM prg Studio Debugger to either Use VICE Debugger or Use C64 Debugger.

      * Use C64 Debugger
          * Parameters:  Add "-c2l_retrodebugger" to parameters (without the quotes).
          * Location: Z:\home\your_user_name\bin\cps2linux.
