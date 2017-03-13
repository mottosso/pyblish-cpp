@echo off
if %ERRORLEVEL%==0 python %~dp0src\py\app.py %~dp0build\debug\pyblish-cpp.exe %*