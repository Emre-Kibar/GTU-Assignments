#ifndef MYSHELL_H
#define MYSHELL_H

#include "file.h"
#include "directory.h"
#include "regularFile.h"
#include "softLinkedFile.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

namespace myOS{
    class myShell{
		public:
			void startShell();
			directory* getCurrentDirectory()const{ return currentDirectory; }
			directory* getDisk(){ return dynamic_cast<directory*>(disk);}
	
		private:
			file* disk;
			directory* currentDirectory;

			void parseInput(const string& input, string& command, vector<string>& parameters);
			void deleteDiskObjects(file* disk);
			void saveDisk();
			void printDisk(std::ofstream& outputFile, directory* selectedDirectory);
			void loadDisk();
			directory* findDirectory(directory* currentDir, string _path);
			bool isDiskLimitExceed();
			void updateDiskSize(directory* calculatedDirectory);

			void ls(const string& parameter);
			void mkdir(const string& directoryName);
			void rm(const string& fileName);
			void cp(const string& sourcePath, const string& destinationPath);
			void link(const string& sourcePath, const string& destinationPath);
			void cd(const string& directoryName);
			void cat(const string& fileName); 
			void help();
	};
}


#endif //MYSHELL_H