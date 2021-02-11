//
// Places binaries in the right place.
//
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>

#include <filesystem>
namespace fs = std::filesystem;

// A place entry.
struct PlaceEntry {
	std::string baseName;
	std::string outName;
};

std::vector<PlaceEntry> place_entries;
char* ToolDir;
char* SysRoot;
std::string FileName;
std::string BaseName;
	
void InitPlaceEntries() {
	std::string PlaceName = std::string(ToolDir) + "/place.txt";
	std::ifstream ifs(PlaceName);
	
	std::string line;
	
	if(!ifs) {
		std::printf("Could not open place.txt. Try running place in a Dazzle shell.\n");
		std::exit(1);
	}
	
	while(std::getline(ifs, line)) {
		if(line[0] == '#')
			continue;
		
		PlaceEntry entry;
		auto sep_index = line.find_first_of(' ');
		
		if(sep_index == std::string::npos)
			continue;
		
		entry.baseName = line.substr(0, sep_index);
		entry.outName = line.substr(sep_index+1);
		
		place_entries.push_back(entry);
	}
	
}

std::string GetBaseName(const std::string& path) { 
	auto ind = path.find_last_of('/');
	if(ind == std::string::npos)
		return path;
	
	return path.substr(ind+1);
}

std::string GetDirName(const std::string& path) { 
	auto ind = path.find_last_of('/');
	if(ind == std::string::npos)
		return path;
	
	return path.substr(0, ind+1);
}

int main(int argc, char** argv) {
	if(argc < 2) {
		std::printf("ree\n");
		return 1;
	}
	
	ToolDir = getenv("ToolsDir");
	SysRoot = getenv("DAZZLE_SYSROOT");
	
	if(!ToolDir || !SysRoot) {
		std::printf("This tool needs to run in a Dazzle shell.\n");
		return 1;
	}
		
	InitPlaceEntries();
	FileName = std::string(argv[1]);
	BaseName = GetBaseName(argv[1]);
	
	
	for(auto& place : place_entries) {
		if(place.baseName == BaseName) {
			auto dirname = GetDirName(place.outName);
			
			if(!fs::exists(fs::path(std::string(SysRoot)) / dirname))
				fs::create_directories(fs::path(std::string(SysRoot) + "/" + dirname));
			
			std::error_code ec;
			fs::copy(FileName, fs::path(std::string(SysRoot) + place.outName), fs::copy_options::update_existing, ec);
		}
	}
}