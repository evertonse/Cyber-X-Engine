@echo off

if exist build/*.sln (
  echo project solution already exists on dir build/
  call devenv
) else (
  if exist build/bin/*.sln (
    echo project solution already exists on dir build/bin/
    call devenv
  ) else (
    call devenv build/bin/CyberXEngine.exe 
  )
)