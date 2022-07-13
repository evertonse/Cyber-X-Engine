from dataclasses import dataclass
import os
import subprocess


@dataclass
class Project():
	name = "CyberXEngine"
	kind = "StaticLib" 	# ignored for now
	language = "C++"  	# ignored for now
	version = "c++17"
	staticruntime = "off"


	pchheader = "hzpch.h" 			# ignored for now
	pchsource  = "src/hzpch.cpp"	# ignored for now

	srcfiles = [
		"src/math/**",
		"src/graphics/App.cpp",
		"src/graphics/Window.cpp",
		"src/graphics/Shader.cpp",
		"vendor/glad/src/**",
		"src/entry.cpp",
	]

	# -D
	defines = [
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	]
	
	# -I
	includedirs = [
		"vendor/glad/include",
		"vendor/SDL/include",
	]

	# -L
	libdirs = [
		"vendor/SDL/lib/",
	]

	# -l
	libfiles = [
		"SDL2main",
		"SDL2",
		#"mingw32",
	]
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
						self.srcfiles.append(os.path.join(srcdir, file))
				
				self.srcfiles.remove(srcfile)



# cdir = os.getcwd() # it will return current working directory
# print("Previous_dir",cdir)

# # Previous_dir C:\Users\..\Desktop\python
# os.chdir('./..') #chdir used for change direcotry
# print("Current_dir",cdir)

import sys

__filename__ =  __file__[__file__.rindex('\\')+1:]

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
		cmd += f' ./{file} '
		
 
	for folder in project.includedirs:
		cmd += f' -I{folder} '

	for folder in project.libdirs:
		cmd += f' -L{folder} '

	for warning in warnings:
		cmd += f' -W{warning} '
	
	for define in project.defines:
		cmd += f' -D{define} '

	for file in project.libfiles:
		cmd += f' -l{file} '
		
	
	cmd += (" -O3 " if optimized else "-O0 ")
	
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
	
	code = subprocess.run(cmd)
	debug(f"\n\nCommand Generated: {cmd}\n\n")
	if code.returncode == 0:
		debug(f'[INFO]: {GREEN("Compilation Succeded")} return code was zero, usually means success')
		subprocess.run(project.name)
	else:
		debug(f'[ERROR]: {RED("Compilation Failed")} return code was {RED("non-zero")}, usually means bad things')

if __name__ == '__main__':
	__main__()