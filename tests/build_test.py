from dataclasses import dataclass
import os
import subprocess
__filename__ =  __file__[__file__.rindex('\\')+1:]

@dataclass
class Project():
	name = "CyberXEngine"
	kind = "StaticLib" 	# ignored for now
	language = "C++"  	# ignored for now
	version = "C++17"
	staticruntime = "off"


	pchheader = "hzpch.h"
	pchsource  = "src/hzpch.cpp"

	srcfiles = {
		"src/math/**",
		"tests/test_vec.cpp",
		"vendor/glad/src/**",
	}

	# -D
	defines = {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}
	
	# -I
	includedirs = {
		"src",
		"vendor/glad/include",
		"vendor/SDL/include",
	}

	# -L
	libdirs = {
		"vendor/SDL/lib/x64",
	}

	# -l
	libfiles = {
		"mingw32",
		"SDL2main.lib",
		"SDL2.lib",
	}
	#-O
	optimize = "on"
	
	
	def __init__(self) -> None:
		self.add_src_files()
	def add_src_files(self):
		for srcfile in list(self.srcfiles):
			if srcfile.endswith("**"):
				
				srcdir = srcfile[:len(srcfile)-2]
				for file in os.listdir(srcdir):
					if file.endswith(".cpp") or file.endswith(".c"):
						self.srcfiles.add(os.path.join(srcdir, file))
				
				self.srcfiles.remove(srcfile)



class bcolors:
	HEADER 	 = '\033[95m'
	OKBLUE 	 = '\033[94m'
	OKCYAN 	 = '\033[96m'
	OKGREEN 	 = '\033[92m'
	WARNING 	 = '\033[93m'
	FAIL 		 = '\033[91m'
	ENDC 		 = '\033[0m'
	BOLD 		 = '\033[1m'
	UNDERLINE = '\033[4m'

def RED(msg:str) -> str:
	return f"{bcolors.FAIL}{msg}{bcolors.ENDC}"

def GREEN(msg:str) -> str:
	return f"{bcolors.OKGREEN}{msg}{bcolors.ENDC}"

def debug(*args,**kwargs):
	print(f'[{ __filename__}]',*args,**kwargs)


			

def create_cmd(
	compiler:str,
	warnings:str, 
	project:Project) -> str:
	
	version  :str  = project.version.lower() if project.version else "c++17"
	optimized :bool = True if project.optimize == "on" else False

	cmd = f'{compiler} -std={version}'

	for file in project.srcfiles:
		cmd += f' {file} '

	for warning in warnings:
		cmd += f' -W{warning} '
 
	for folder in project.includedirs:
		cmd += f' -I{folder} '

	for folder in project.libdirs:
		cmd += f' -L{folder} '

	for file in project.libfiles:
		cmd += f' -l{file} '

	for define in project.defines:
		cmd += f' -D{define} '
		
	cmd = cmd + ("-O3 " if optimized else "-O0 ")

	cmd += f'-o{project.name}'
	
	return cmd

def __main__():
	config = {
		"compiler" : 'g++', 
		"warnings" : ['all'],
	}
	project = Project()

	cmd = create_cmd(
		compiler=config['compiler'],
		warnings=config['warnings'],
		project =project
	)
	
	debug(cmd)
	code = subprocess.run(cmd)
	if code.returncode == 0:
		debug(f'[INFO]: {GREEN("Compiled")} return code was zero, usually means success')
		subprocess.run(project.name)
	else:
		debug(f'[ERROR]: return code was {RED("non-zero")}, usually means bad things')

if __name__ == '__main__':
	__main__()