if exist *.exe del *.exe
if exist *.dll del *.dll
cl win-app-lab.cpp kernel32.lib user32.lib gdi32.lib advapi32.lib
cl /LD Info.cpp kernel32.lib user32.lib gdi32.lib advapi32.lib
del *.obj *.lib *.exp