#include "directory.h"
#include "regularFile.h"
#include "softLinkedFile.h"
#include "file.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
using std::string;
using std::cout;
using std::endl;


namespace myOS{
    void directory::pushBackContent(file* newContent){
		contentsOfDirectory.push_back(newContent);
	}

	//Prints the files based on its type and datas.
	void directory :: ls() const{
		cout << getPath() << ":" << endl;
		for (const auto& content : contentsOfDirectory) {
			if(dynamic_cast<directory*>(content)){
				cout << "D ";
				cout << content->getName() << "\t" << content->getDate() << endl;
			}else if(dynamic_cast<regularFile*>(content)){
				cout << "F ";
				cout << content->getName() << "\t" << content->getDate() << "\t" << content->getSize() << endl;
			}else if(dynamic_cast<softLinkedFile*>(content)){
				cout << "L ";
				cout << content->getName() << "\t" << content->getDate() << "\t" << content->getSize() << "\t" 
											<< dynamic_cast<softLinkedFile*>(content)->getPathToFile() << endl;
			}
		}

		cout << "D .\t" << getDate() << endl;
		if(parentDirectory){
			cout << "D ..\t" << parentDirectory->getDate() << endl;
		}
	}

	void directory::lsRecursive()const{
		ls(); // Print the contents of the current directory first

		for (const auto& content : contentsOfDirectory) {
			// Check if the content is a directory before calling lsRecursive
			if (dynamic_cast<directory*>(content)) {
				dynamic_cast<directory*>(content)->lsRecursive();
			}
		}
	}

	//mkdşr firstly checks the the created directory will be a duplicate,if it wont the creates a default directory.
	void directory::mkdir(const string& directoryName){
		bool isDirectoryDuplicate = false;
		for(const auto& content: contentsOfDirectory){
			if(content->getName() == directoryName){
				isDirectoryDuplicate = true;
				throw std::runtime_error("Error!There is already a directory with selected name.");
			}
		}
		if(!isDirectoryDuplicate){
			directory* createdDirectory = new directory(directoryName);
			createdDirectory->setDate(getCurrentDateFormatted());  
			createdDirectory->setPath(getPath() + "/" + directoryName);
			createdDirectory->setSize("0 Byte");
			createdDirectory->setParent(this);

			contentsOfDirectory.push_back(createdDirectory);
		}
	}

	void directory::cd(directory*& currentDirectory, const string& pathToDirectory) {
		if(pathToDirectory == "."){
			cout << "You are in the " << currentDirectory->getName() << " directory\n";
		}else if (pathToDirectory == ".."){
			// Move to the parent directory if available
			if(parentDirectory){
				currentDirectory = parentDirectory;
			}else{
				throw std::runtime_error("ERROR!Already in the root directory.");
			}
		}else{
			// Tokenize the path and navigate through directories
			std::istringstream iss(pathToDirectory);
			string directoryName;
			directory* tempDirectory = this;  // Start from the current directory

			while (std::getline(iss, directoryName, '/')) {
				bool directoryFound = false;

				// Check if the current directory has the desired subdirectory
				for (const auto& content : tempDirectory->getContents()) {
					if (content->getName() == directoryName && dynamic_cast<directory*>(content)) {
						tempDirectory = dynamic_cast<directory*>(content);
						directoryFound = true;
						break;
					}
				}

				if (!directoryFound) {
					throw std::runtime_error("ERROR!Directory '" + directoryName + "' not found within the " + tempDirectory->getName());
				}
			}
			// Set the current directory to the last found directory
			currentDirectory = tempDirectory;
		}
	}

	//rm function checks the directory if it is empty or not if it is empty then it is deletable.
	void directory::rm(){
		if(this->getContents().size() == 0){
			delete this;
		}else{
			throw std::runtime_error("ERROR!You can only delete an empty directory.");
		}
	}

	void directory::cat(directory* begin){
		cout << "Selected file is a directory." << endl;
		ls();
	}

	//cp function firstly creates the copy of this(itself) then to create the copy of its contents calls virtual cp function.
	void directory::cp(directory*& destinationDir){
		directory* createdDirectory = new directory(getName());
		createdDirectory->setDate(getCurrentDateFormatted());
		createdDirectory->setSize(getSize());
		createdDirectory->setParent(destinationDir);
		createdDirectory->setPath(destinationDir->getPath() + "/" + getName());

		// Recursively copy contents to the new directory
		for (const auto& content : contentsOfDirectory) {
			content->cp(createdDirectory);
		}

		// Add the new directory to the destination directory
		destinationDir->pushBackContent(createdDirectory);
	}
}
