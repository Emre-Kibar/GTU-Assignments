#include "myShell.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
using std::vector;
using std::string;
using std::cout;
using std::endl;

namespace myOS{
	//This templated mySwap function basically swaps two variables.
    template <typename T>
	void mySwap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}

	//ls function calls the ls() or lsRecursive() based on the parameter if it is empty then calls ls() if it is "-R" then calls lsRecursive().
    void myShell::ls(const string& parameter){
		if(parameter == ""){
			currentDirectory->ls();
		}else if(parameter == "-R"){
			currentDirectory->lsRecursive();
		}
	}
	
	//mkdir function calls the currentDirectory's(which is directory*) mkdir function to create new directory.
	void myShell::mkdir(const string& directoryName){
		currentDirectory->mkdir(directoryName);
	}

	//cd function calls	the currentDirectory's(which is directory*) cd function to move through selected directory.
	void myShell::cd(const string& directoryName){
		currentDirectory->cd(currentDirectory, directoryName);
	}

		
	void myShell::rm(const string& fileName) {
		bool isFileThere = false;
		int contentIndexToRemove = -1;  //Track the index of the content to remove

		//Copy the contents of currentDirectory to a temporary vector
		vector<file*> tempContents = currentDirectory->getContents();

		//Find the index of the content to remove
		for (int i = 0; i < tempContents.size(); i++) {
			auto& content = tempContents[i];
			if (content->getName() == fileName) {
				contentIndexToRemove = i;
				isFileThere = true;
				break;
			}
		}

		if (isFileThere) {
			//Move the file to be removed to the end of the vector
			mySwap(tempContents[contentIndexToRemove], tempContents.back());
			//Remove the last element (which is the content to be removed)
			tempContents.back()->rm();
			tempContents.pop_back();
			//Update the original vector with the modified contents
			currentDirectory->setContents(tempContents);
		} else {
			throw std::runtime_error("ERROR!There is no file with the selected name.");
		}
	}

	void myShell::link(const string& sourcePath, const string& destinationPath){
		directory* destinationDir = nullptr;
		bool isDestinationPathCorrect = false;
		//If user enters destinationPath as "Root" then destinationDir is automatically Root directory.
		if(destinationPath == "Root"){
			destinationDir = dynamic_cast<directory*>(disk);
			isDestinationPathCorrect = true;
		}else{
			//If user enters a path,firstly the path is parsed based on "/",then using findDirectory function the directory before the last directory is found.
			size_t firstSlashPos = destinationPath.find("/");
			size_t lastSlashPos = destinationPath.rfind("/");
			string updatedPath = destinationPath.substr(firstSlashPos + 1, lastSlashPos - firstSlashPos);
			destinationDir = findDirectory(dynamic_cast<directory*>(disk), updatedPath);

			//After the directory that is before the last directory is found.For the last directory,the destinationDir content is searched through. 
			if(destinationDir){
				string searchedFileDest = destinationPath.substr(lastSlashPos + 1);
				for(const auto& content : destinationDir->getContents()){
					if(dynamic_cast<directory*>(content) && content->getName() == searchedFileDest ){
						isDestinationPathCorrect = true;
						//The content which is compatible with the lastPart of the destinationPath is destinationDir.
						destinationDir = dynamic_cast<directory*>(content);
						break;
					}
				}
			}else{
				throw std::runtime_error("ERROR!There is not such a destination path.");
			}	
		}

		//The sourcePath is parsed based on "/" characters,then the sourceDir is found using findDirectory function based on extracted first and last part.
		size_t firstSlashPos = sourcePath.find("/");
		size_t lastSlashPos = sourcePath.rfind("/");
		string updatedPath = sourcePath.substr(firstSlashPos + 1, lastSlashPos - firstSlashPos);
		directory* sourceDir = findDirectory(dynamic_cast<directory*>(disk), updatedPath);
		
		//Then the lastPart of the sourcePath(which indicates the the file that will be linked) is find searching through sourceDir contents.
		file* searchedFileP = nullptr;
		bool isSourcePathCorrect = false;
		if(sourceDir){
			string searchedFile = sourcePath.substr(lastSlashPos + 1);
			for(const auto& content : sourceDir->getContents()){
				if(content->getName() == searchedFile ){
					isSourcePathCorrect = true;
					searchedFileP = content;
					break;
				}
			}	
		}else{
			throw std::runtime_error("ERROR!There is not such a source path.");
		}	
		
		if(isDestinationPathCorrect && isSourcePathCorrect){
			//If both destinationPath and sourcePath is correct,then the duplicate situation is searched.
			bool isDuplicateFile = false;
			for(const auto& _content: destinationDir->getContents()){
				if(_content->getName() == "->" + searchedFileP->getName()){
					isDuplicateFile = true;
					break;
				}
			}
			//If the linked file wont be duplicate file then new softLinkedFile is created and sourceFileLinked called to set the link.
			if(!isDuplicateFile){
				softLinkedFile* createdSoftLink = new softLinkedFile("->" + searchedFileP->getName());
				createdSoftLink->setPath(destinationDir->getPath() + "/->" + searchedFileP->getName());
				createdSoftLink->setDate(createdSoftLink->getCurrentDateFormatted());
				createdSoftLink->setSize(searchedFileP->getSize());

				destinationDir->pushBackContent(createdSoftLink);
				createdSoftLink->link(sourcePath);
			}else{
				throw std::runtime_error("ERROR!There is a already a link to source file in the destination directory.Cannot create duplicate link.");
			}
			
		}else{
			if(!isDestinationPathCorrect)
				throw std::runtime_error("ERROR!There isn't such kind of destination.");
			else if(!isSourcePathCorrect)
				throw std::runtime_error("ERROR!There isn't such kind of source.");
		}	
	}
	
	void myShell::cat(const string& fileName){
		bool isFileThere = false;
		//cat function search for selected file through its contents and when file is found call virtual cat function.
		for(const auto& contentOfCurrentDir: currentDirectory->getContents()){
			if(contentOfCurrentDir->getName() == fileName){
				isFileThere = true;
				contentOfCurrentDir->cat(getDisk());
			}
		}
		if(!isFileThere)
			throw std::runtime_error("ERROR!There isnt a file with the entered name.");
	}


	void myShell::cp(const string& sourcePath, const string& destinationPath){
		directory* destinationDir = nullptr;
		bool isDestinationPathCorrect = false;
		if(destinationPath == "Root"){ 		//If the selected destinationPath is Root then the destinationDir is automatically will be Root.
			destinationDir = dynamic_cast<directory*>(disk);
			isDestinationPathCorrect = true;
		}else{
			//If user enters a path,firstly the path is parsed based on "/",then using findDirectory function the directory before the last directory is found.
			size_t firstSlashPos = destinationPath.find("/");
			size_t lastSlashPos = destinationPath.rfind("/");
			string updatedPath = destinationPath.substr(firstSlashPos + 1, lastSlashPos - firstSlashPos);
			destinationDir = findDirectory(dynamic_cast<directory*>(disk), updatedPath);

			//After the directory that is before the last directory is found.For the last directory,the destinationDir content is searched through.
			if(destinationDir){
					string searchedFile = destinationPath.substr(lastSlashPos + 1);
					for(const auto& content : destinationDir->getContents()){
						if(dynamic_cast<directory*>(content) && content->getName() == searchedFile ){
							isDestinationPathCorrect = true;
							destinationDir = dynamic_cast<directory*>(content);
							break;
						}
					}
					if(!isDestinationPathCorrect)
						destinationDir = nullptr;
			}else{
				throw std::runtime_error("ERROR!There is not such a destination path.");
			}
		}

		if(destinationDir){
			//After destination is found correctly,firstly the sourcePath tries for open a file.
			std::ifstream copiedFileOutside(sourcePath);
			if(copiedFileOutside.is_open()){
				size_t lastSlashPos = sourcePath.rfind("/");
				string updatedPath = sourcePath.substr(lastSlashPos + 1);
				//Checks for the copied file would be a duplicate or not.If it isnt then create a new regular file and sets its datas.
				bool isDuplicateFile = false;
				for(const auto& _content: destinationDir->getContents()){
					if(_content->getName() == updatedPath){
						isDuplicateFile = true;
						break;
					}
				}

				if(!isDuplicateFile){
					//If the file opens,the content of the file will be copied is read char by char.
					std::ostringstream fileContentStream;
					char currentChar;

					//For new line characters,the "~" character is printed to symbolize the "\n" inside content of regularFile
					while (copiedFileOutside.get(currentChar)) {
						if (currentChar != '\n' && currentChar != '\r') {
							fileContentStream.put(currentChar);
						} else {
							// Check if the next character is also a newline character.
							char nextChar = copiedFileOutside.peek();
							if (nextChar != currentChar && (nextChar == '\n' || nextChar == '\r')) {
								// If the next character is a different newline character, consume it.
								copiedFileOutside.get();
							}
							fileContentStream.put('~');
						}
					}

					// Get the string representation of the file content without newlines.
					string fileContent = fileContentStream.str();
					// Calculate and store the fileSize as string.
					std::size_t contentSize = fileContent.size();
					std::ostringstream fileSizeStream;
					fileSizeStream << contentSize << " byte";
					string fileSize = fileSizeStream.str();

				
					regularFile* createdRegularFile = new regularFile(updatedPath);
					createdRegularFile->setPath(destinationPath + "/" + updatedPath);
					createdRegularFile->setDate(createdRegularFile->getCurrentDateFormatted());
					createdRegularFile->setSize(fileSize);
					createdRegularFile->setContentsOfFile(fileContent);

					destinationDir->pushBackContent(createdRegularFile);
				}else{
					throw std::runtime_error("ERROR!There is a file with the same name of the copied file in the destination directory.");
				}
				
				copiedFileOutside.close();
			}else{
				cout << "The selected file isnt within original OS. So, checking myOS." << endl;
				//The sourcePath is parsed into pieces based on "/".The first and last part is extracted and sourceDir is searched.
				size_t firstSlashPos = sourcePath.find("/");
				size_t lastSlashPos = sourcePath.rfind("/");
				string updatedPath = sourcePath.substr(firstSlashPos + 1, lastSlashPos - firstSlashPos);
				directory* sourceDir = findDirectory(dynamic_cast<directory*>(disk), updatedPath);
				
				//Then find the last part of sourcePath which is the file wanted for copy.
				if(sourceDir){
					file* copiedFileInside = nullptr;
					string searchedFile = sourcePath.substr(lastSlashPos + 1);
					bool isDuplicateFile = false;
					for(const auto& _content: destinationDir->getContents()){
						if(_content->getName() == searchedFile){
							isDuplicateFile = true;
							break;
						}
					}

					//If the copied file wont be a duplicate file then find the file that will be copied and call virtual cp() function.
					if(!isDuplicateFile){
						for(const auto& content : sourceDir->getContents()){
							if(content->getName() == searchedFile ){
								copiedFileInside = content;
								break;
							}
						}
						if(copiedFileInside){
							copiedFileInside->cp(destinationDir);
						}else{
							throw std::runtime_error("ERROR!There is not a file with name " + searchedFile + " in the disk.");
						}
					}else{
						throw std::runtime_error("ERROR!There is a file with the same name of the copied file in the destination directory.");
					}
				}else{
					throw std::runtime_error("ERROR!There is not such a source path.");
				}
			}
		}else{
			throw std::runtime_error("ERROR!The destination cant be found.");
		}
	}

	//help function shows the possible command and how they must be used.
	void myShell::help(){
		cout << "-----Available Commands for myShell and Their Usage-----\nls: ls command shows the files of the current directory.\n\tUsage Example: Root> ls\nls -R: ls recursive command shows the files of the current directory and also shows the files inside subdirectories.\n\tUsage Example: Root> ls -R\nmkdir: mkdir command creates a directory with the entered name.There cannot be two directories with the same name.\n\tUsage Example: Root> mkdir mydir\ncd: cd command moves to selected directory.\n\tUsage Examples: Root> cd Documents  /  Root> cd Documents/Notes  / Root> cd . / Root> cd ..\nrm: rm command can delete any kind of file but it can only remove an empty directory\n\tUsage Example: Root> rm random.txt\ncat: cat command takes the name of the file to show its content.\n\tUsage Example: Root> cat random.txt\ncp: cp command creates a copy of the sourceFile(source file can be any kind of file) within the destinationDirectory.\n\tUsage Example: Root> cp Root/Reports/LastYear/2023Programme.txt  Root/Documents  -> This command creates a copy of 2023Programme.txt inside Documents directory\nlink: link command creates a link within the destinationDirectory to the sourceFile(sourceFile can be any kind of file).\n\tUsage Example: Root> link Root/Documents/novel.txt Root/Reports/Images  ->  This command creates a link inside Images directory which shows the novel.txt\nhelp: help command shows possible commands.\n\tUsage Example: Root> help\nexit: Close the shell after it saves the disk into disk.txt\n";
		
	}

	bool myShell::isDiskLimitExceed(){
		//updates the whole disk's size.Then checks if disk is greater than 1000000 Bytes or 10MB
		updateDiskSize(dynamic_cast<directory*>(disk));
		string sizeString = disk->getSize();
		size_t spacePos = sizeString.find(' ');
		string numericPart = sizeString.substr(0, spacePos);
		size_t sizeV = stoul(numericPart);

		if(sizeV > 1000000){
			return true;
		}else{
			return false;
		}
	}

	void myShell::updateDiskSize(directory* calculatedDirectory){
		//Calculates the each file size according to their type.If it is directory calls updateDiskSize function recursively for the files inside it.
		//If it is a regular file directly adds its size to totalSize.
		//If it is a softLinkedFile then goes through the link to find real file and calculates its size.
		size_t totalSize = 0;
		for(const auto& content: calculatedDirectory->getContents()){
			if(dynamic_cast<directory*>(content)){
				updateDiskSize(dynamic_cast<directory*>(content));
				string sizeString = content->getSize();
				size_t spacePos = sizeString.find(' ');
				string numericPart = sizeString.substr(0, spacePos);
				size_t sizeV = stoul(numericPart);
				totalSize += sizeV;
			}else if(dynamic_cast<regularFile*>(content)){
				string sizeString = content->getSize();
				size_t spacePos = sizeString.find(' ');
				string numericPart = sizeString.substr(0, spacePos);
				size_t sizeV = stoul(numericPart);
				totalSize += sizeV;
			}else if(dynamic_cast<softLinkedFile*>(content)){
				string _pathToFile = dynamic_cast<softLinkedFile*>(content)->getPathToFile();
				size_t firstSlashPos = _pathToFile.find("/");
				size_t lastSlashPos = _pathToFile.rfind("/");
				string updatedPath = _pathToFile.substr(firstSlashPos + 1, lastSlashPos - firstSlashPos);
				directory* sourceDir = findDirectory(dynamic_cast<directory*>(disk), updatedPath);
				if(sourceDir){
						string searchedFile = _pathToFile.substr(lastSlashPos + 1);
						for(const auto& _content : sourceDir->getContents()){
							if(_content->getName() == searchedFile){
								string sizeString = content->getSize();
								size_t spacePos = sizeString.find(' ');
								string numericPart = sizeString.substr(0, spacePos);
								size_t sizeV = stoul(numericPart);
								totalSize += sizeV;
								break;
							}
						}
				}else{
					throw std::runtime_error("ERROR!There is not such a source path for size calculation of softLinkedFile.");
				}

			}else{
				throw std::runtime_error("ERROR!The file type is unknown for size calculation.");
			}
		}
		//Finally sets the size of the disk.
		std::ostringstream oss;
		oss << totalSize << " byte" ;
		calculatedDirectory->setSize(oss.str());
	}

	void myShell::loadDisk() {
		std::ifstream diskFile("disk.txt");
		if (!diskFile.is_open()) {
			throw std::runtime_error("ERROR!Could not open disk.txt.");
		}

		string line;
		string type, name, path, date, size;

		if (std::getline(diskFile, line)) { //The first line is read initially which must be the Root.If it isnt Root then throws exception.
			std::istringstream iss(line);
			std::getline(iss, type, ',');
			std::getline(iss, name, ',');
			std::getline(iss, path, ',');
			std::getline(iss, date, ',');
			std::getline(iss, size);
			if (type != "Directory" || name != "Root") {
				disk = nullptr;
				throw std::runtime_error("ERROR!Invalid disk.txt format.");
			} else {
				directory* createdDirectory = new directory(name);
				createdDirectory->setPath(path);
				createdDirectory->setDate(date);
				createdDirectory->setSize(size);
				createdDirectory->setParent(nullptr);
				disk = createdDirectory;
			}
		} else {
			directory* createdDirectory = new directory("Root");
			createdDirectory->setPath("Root");
			createdDirectory->setDate(currentDirectory->getCurrentDateFormatted());
			createdDirectory->setSize("0 Bytes");
			createdDirectory->setParent(nullptr);
			disk = createdDirectory;
			return;
		}

		while (std::getline(diskFile, line)) {  //reads the disk.txt line by line and separate them to its datas.
			std::istringstream iss(line);
			std::getline(iss, type, ',');
			std::getline(iss, name, ',');
			std::getline(iss, path, ',');
			std::getline(iss, date, ',');
			
			//According to its path the correct destination is found and according to the type correct object is created and sets to destination.
			size_t firstSlashPos = path.find("/");
			size_t lastSlashPos = path.rfind("/");
			string updatedPath = path.substr(firstSlashPos + 1, lastSlashPos - firstSlashPos);
			directory* parentDir = findDirectory(dynamic_cast<directory*>(disk), updatedPath);

			if (!parentDir) {
				throw std::runtime_error("ERROR!There is a problem about path in disk.txt.");
			} else {
				if (parentDir && type == "Directory") {
					std::getline(iss, size);
					directory* createdDirectory = new directory(name);
					createdDirectory->setPath(path);
					createdDirectory->setDate(date);
					createdDirectory->setSize(size);
					createdDirectory->setParent(parentDir);

					parentDir->pushBackContent(createdDirectory);
				} else if (parentDir && type == "RegularFile") {
					string content;
					std::getline(iss, size, ',');
					std::getline(iss, content);
					regularFile* createdRegularFile = new regularFile(name);
					createdRegularFile->setPath(path);
					createdRegularFile->setDate(date);
					createdRegularFile->setSize(size);
					createdRegularFile->setContentsOfFile(content);

					parentDir->pushBackContent(createdRegularFile);
				} else if (parentDir && type == "SoftLinkedFile") {
					string content;
					std::getline(iss, size, ',');
					std::getline(iss, content);
					softLinkedFile* createdSoftLinkedFile = new softLinkedFile(name);
					createdSoftLinkedFile->setPath(path);
					createdSoftLinkedFile->setDate(date);
					createdSoftLinkedFile->setSize(size);
					createdSoftLinkedFile->setPathToFile(content);

					parentDir->pushBackContent(createdSoftLinkedFile);
				} else {
					throw std::runtime_error("ERROR!Invalid file type.");
				}
			}
		}
		diskFile.close();
	}

	directory* myShell::findDirectory(directory* parentDir, string _path) {
		//The path is seperated based on "/" and for each iteration file is searched.
		while (!_path.empty()) {
			size_t firstSlashPos = _path.find("/");
			string currentDirName = _path.substr(0, firstSlashPos);
			bool isDirectoryFound = false;

			for (file* f : parentDir->getContents()) {
				directory* childDir = dynamic_cast<directory*>(f);
				if (childDir && childDir->getName() == currentDirName) {
					parentDir = childDir;
					isDirectoryFound = true;
					_path = _path.substr(firstSlashPos + 1);
					break;
				}
			}
			if (!isDirectoryFound) {
				return nullptr;
			}
		}
		return parentDir;
	}

	void myShell::saveDisk() {
		//Firstly checks diskBegin is a directory which would be Root directory,then printDisk function is called.
		std::ofstream diskFile("disk.txt");
		if (!diskFile.is_open()) {
			throw std::runtime_error("ERROR!Disk.txt cant open for saving.");
		}
		directory* diskBegin = dynamic_cast<directory*>(disk);
		if(diskBegin){
			diskFile << "Directory," << diskBegin->getName() << "," << diskBegin->getPath() << "," << diskBegin->getDate()
						<< "," << diskBegin->getSize() << endl;
			printDisk(diskFile, diskBegin);
		}else{
			throw std::runtime_error("ERROR!Incorrect disk type.There might be problem while loading the disk.");
		}

		diskFile.close();
	}

	void myShell::printDisk(std::ofstream& outputFile, directory* selectedDirectory) {
		//By going through disk which is kind of a tree structure the all objects is printed to disk.txt.
		for (const auto& objectToPrint : selectedDirectory->getContents()) {
			if (dynamic_cast<directory*>(objectToPrint)) {
				outputFile << "Directory," << objectToPrint->getName() << "," << objectToPrint->getPath() << "," << objectToPrint->getDate()
						<< "," << objectToPrint->getSize() << endl;

				printDisk(outputFile, dynamic_cast<directory*>(objectToPrint));
			} else if (dynamic_cast<regularFile*>(objectToPrint)) {
				outputFile << "RegularFile," << objectToPrint->getName() << "," << objectToPrint->getPath() << "," << objectToPrint->getDate()
						<< "," << objectToPrint->getSize() << ",";
				for (const auto& a : dynamic_cast<regularFile*>(objectToPrint)->getContentsofFile()) {
					outputFile << a;
				}
				outputFile << endl;
			} else if (dynamic_cast<softLinkedFile*>(objectToPrint)) {
				outputFile << "SoftLinkedFile," << objectToPrint->getName() << "," << objectToPrint->getPath() << "," << objectToPrint->getDate()
						<< "," << objectToPrint->getSize() << "," << dynamic_cast<softLinkedFile*>(objectToPrint)->getPathToFile() << endl;
			}
		}
	}

	void myShell::startShell(){
		disk = nullptr;
		loadDisk(); //loadDisk function loads the informations of disk.txt
		if(disk == nullptr || !(dynamic_cast<directory*>(disk))){
			throw std::runtime_error("ERROR!There is a problem in the disk about root.");
		}
		currentDirectory = dynamic_cast<directory*>(disk);

		help();

		string input;
		string command;
		vector<string> parameters;
		bool isLimitExceed = false;

		while(true){
			try{
				command.clear();
				parameters.clear();

				std::cout << currentDirectory->getPath() << "> ";
				std::getline(std::cin, input);

				// Parse the input of the user for its command and parameters
				parseInput(input, command, parameters);

				// To close the myShell and save the disk.txt enter exit command.
				if(command == "exit"){
					cout << "Exiting the shell.\n";
					break;
				}

				if(command == "ls"){
					if(parameters.size() == 1 && parameters[0] == "-R"){
						ls("-R");
					}else if(parameters.size() == 0){
						ls("");
					}else{
						throw std::runtime_error("ERROR!Invalid parameters for ls.");
					}
				}else if(command == "mkdir"){
					if (parameters.size() == 1){
						mkdir(parameters[0]);
					}else{
						throw std::runtime_error("ERROR!Invalid number of parameters for mkdir.");
					}
				}else if(command == "rm"){
					if(parameters.size() == 1){
						rm(parameters[0]);
					}else{
						throw std::runtime_error("ERROR!Invalid number of parameters for rm.");
					}
					isLimitExceed = isDiskLimitExceed();
				}else if(command == "cp" && !isLimitExceed){
					if(parameters.size() == 2){
						cp(parameters[0], parameters[1]);
					}else{
						throw std::runtime_error("ERROR!Invalid number of parameters for cp.");
					}
					isLimitExceed = isDiskLimitExceed();
					if(isLimitExceed)
						throw std::runtime_error("ERROR!The disk limit is passed, to copy another file you must remove some files firstly.");					
				}else if(command == "link" && !isLimitExceed){
					if(parameters.size() == 2){
						link(parameters[0], parameters[1]);
					}else
						throw std::runtime_error("ERROR!Invalid number of parameters for link.");
					isLimitExceed = isDiskLimitExceed();
					if(isLimitExceed)
						throw std::runtime_error("ERROR!The disk limit is passed, to link another file you must remove some files firstly.");	
				}else if (command == "cd") {
					if (parameters.size() == 1) {
						cd(parameters[0]);
					} else {
						throw std::runtime_error("ERROR!Invalid number of parameters for cd.");
					}
				}else if (command == "cat") {
					if (parameters.size() == 1) {
						cat(parameters[0]); 
					} else {
						throw std::runtime_error("ERROR!Invalid number of parameters for cat.");
					} 
				}else if(command == "help"){
					if (parameters.size() == 0){
						help();
					} else {
						throw std::runtime_error("ERROR!Invalid number of parameters for help.");
					}
				}else{
					throw std::runtime_error("ERROR!Invalid command.");
				}
			}
			catch(std::runtime_error& e){
				cout << "Exception throwned: " << e.what() << endl;
			}
			catch(...){
				cout << "Exception throwned." << endl;
			}
		}

		saveDisk(); //saveDisk function saves every information to disk.txt
		deleteDiskObjects(disk);
	}

	void myShell::parseInput(const string& input, string& command, vector<string>& parameters){
		std::istringstream iss(input);
		iss >> command;

		std::string param;
		while(iss >> param){
			parameters.push_back(param);
    	}
	}

	void myShell::deleteDiskObjects(file* object) {
        if (object == nullptr) {
            return;
        }
        // If the object is a directory, recursively delete its contents
        if (directory* dir = dynamic_cast<directory*>(object)) {
            for (file* content : dir->getContents()) {
                deleteDiskObjects(content);
            }
        }
        // Delete the current object
        delete object;
    }
}