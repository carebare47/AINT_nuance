tasklist /FI "IMAGENAME eq cmd.exe" 2>NUL | find /I /N "cmd.exe">NUL
if "%ERRORLEVEL%"=="0" echo Command windows detected, killing all naunce systems...
if "%ERRORLEVEL%"=="0" taskkill /im cmd.exe