#include "softLinkedFile.h"
#include "file.h"
#include "directory.h"
#include <string>
#include <sstream>
#include <stdexcept>
using std::string;

namespace myOS{
	//link sets the path to original file.
    void softLinkedFile::link(const string& _pathToFile){
		pathToFile = _pathToFile;
	}

	void softLinkedFile::rm(){
		delete this;
	}

	void softLinkedFile::cat(directory* begin){
		//Firstly search for original file using pathToFile
		string _pathToLink = this->getPathToFile();
		if(!_pathToLink.empty()){
			size_t firstSlashPos = _pathToLink.find("/");
			size_t lastSlashPos = _pathToLink.rfind("/");
			string searchedFile = _pathToLink.substr(lastSlashPos + 1);
			_pathToLink = _pathToLink.substr(firstSlashPos + 1, lastSlashPos - firstSlashPos);

			std::istringstream iss(_pathToLink);
			string directoryName;
			directory* tempDirectory = begin;  // Start from the current directory

			bool directoryFound = false;
			while (std::getline(iss, directoryName, '/')) {
				directoryFound = false;

				// Check if the current directory has the desired subdirectory
				for (const auto& content : tempDirectory->getContents()) {
					if (content->getName() == directoryName && dynamic_cast<directory*>(content)) {
						tempDirectory = dynamic_cast<directory*>(content);
						directoryFound = true;
						break;
					}
				}

				if (!directoryFound) {
					throw std::runtime_error("ERROR!The link isnt working properly.");	
				}
			}

			//Finds the original file and calls virtual cat function of original file.
			if(directoryFound){
				bool isSearchedFileFound = false;
				for(const auto& _content: tempDirectory->getContents()){
					if(searchedFile == _content->getName()){
						isSearchedFileFound = true;
						_content->cat(begin);
					}
				}
				if(!isSearchedFileFound){
					throw std::runtime_error("ERROR!There is not such a source path.");
				}
			}else{
				throw std::runtime_error("ERROR!The link isnt working properly.");
			}	
		}else{
			throw std::runtime_error("ERROR!The link isnt working properly.");
		}
	}

	//cp function creates a softLinkedFile,sets its datas and puts it to the destination
	void softLinkedFile::cp(directory*& destinationDir){
		softLinkedFile* createdSoftLinkedFile = new softLinkedFile(this->getName());
		createdSoftLinkedFile->setPath(destinationDir->getPath() + "/" + this->getName());
		createdSoftLinkedFile->setDate(getCurrentDateFormatted());
		createdSoftLinkedFile->setSize(this->getSize());
		createdSoftLinkedFile->setPathToFile(this->getPathToFile());

		destinationDir->pushBackContent(createdSoftLinkedFile);
	}

}