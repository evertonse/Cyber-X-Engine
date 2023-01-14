set toml=CyberXEngine.msvc.toml
rem set toml=CyberXEngine.toml

cls
cargs.py --clangd %toml%
cls
cargs.py %toml% 
