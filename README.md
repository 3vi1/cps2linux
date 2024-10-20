# Cps2Linux
Cps2Linux is a small shim meant to enable Linux users to call native Linux emulators and debuggers while running [CBM Prg Studio x86](https://www.ajordison.co.uk) via WINE.

Cps2linux ingests parameters and does two things:  
1) It rewrites any parameters using WINE's Z:\path format to standard Linux /path format.
2) It looks for -c2l_* parameters and uses the portion denoted here by the wildcard as the actual executable it should call.

Why not just call BASH as the executable and pass a scriptname in the parameters, replacing this with 3 lines of shell?  That works for the "Run" function that starts the emulator, but when VICE is set as the debugger it would fail because the user-defined parameters are not passed before the -moncommands parameter by CBM Prg Studio x86.  This can't be worked around by calling the script directly:  WINE can not call Linux scripts directly because Windows has no idea how to invoke the related shell.

* Compile cps2linux and place the binary in your ~/bin folder.

* If you're using [RetroDebugger](https://github.com/slajerek/RetroDebugger), make sure it's in your path.  You can do this by adding a symbolic link to it in your user bin path.
  
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

<br><br>

# Quick notes about running CBM Prg Studio x86 via WINE:

* You must install .Net 4.6.2 (winetricks makes this easy)
* You _probably_ need to add . to your PATHEXT registry setting for your WINE prefix in order to allow the call to cps2linux as an executable.  You could maybe rename it .exe instead and add .exe to the path in the instructions above, rather than running the commands here.
  
      k='HKLM\System\CurrentControlSet\Control\Session Manager\Environment'
      pathext_orig=$( wine reg query "$k" /v PATHEXT | tr -d '\r' | awk '/^  /{ print $3 }' )
      echo "$pathext_orig" | grep -qE '(^|;)\.(;|$)' | wine reg add "$k" /v PATHEXT /f /d "${pathext_orig};."

    (courtesy of ruvim)
  
* I only tested using a 32-bit prefix
* CBM Prg Studio does have some bugs that show up more readily when run this way.
    * You'll have issues if you try to do things like rename files in the GUI.
    * You may see occasional crashes when doing things like invoking the sprite editor.
* You can configure native Linux tools directly in CBM Prg Studio by using the Z:\path format, but this likely requires the PATHEXT fix mentioned above to work.  I set my apps as follows:
    * Calculator:  Z:\usr\bin\speedcrunch
    * Notepad: Z:\usr\bin\code-insiders
    * Paint: Z:\usr\bin\gimp
* Save frequently.  Have backups.  Use git version control!
