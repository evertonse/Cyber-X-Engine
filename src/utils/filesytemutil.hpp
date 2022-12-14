#include <filesystem>
#include <iostream>

auto change_working_directory(const std::string& wd) -> void {
	auto path = std::filesystem::current_path(); //getting path
	std::cout << "Current working directory: Before " << path << std::endl;
	auto new_path = std::filesystem::path(wd); 
	auto path_string = path.string(); 
	std::filesystem::current_path(new_path); 
	std::cout << "Current working directory: After" << new_path << std::endl;
}