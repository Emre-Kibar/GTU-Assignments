#include "regularFile.h"
#include "file.h"
#include "directory.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace myOS{ 
    //cat function printts the content which stores in a vector<char>, char by char the "~" sign means newLine so print newline.
    void regularFile::cat(directory* begin){
        for(const auto& content: contentsOfFile){
            if(content == '~'){
                cout << "\n";
            }else{  
                cout << content; 
            }
        }
        cout << endl;
    }

    void regularFile::rm(){
        delete this;
    }
    //cp creates a new regularFile object and copies the data of the this object and sets to destinationDir.
    void regularFile::cp(directory*& destinationDir){
        regularFile* createdRegularFile = new regularFile(this->getName());
        createdRegularFile->setPath(destinationDir->getPath() + "/" + this->getName());
        createdRegularFile->setDate(getCurrentDateFormatted());
        createdRegularFile->setSize(this->getSize());
        vector<char> contentsVector = this->getContentsofFile();
        string contentsString(contentsVector.begin() , contentsVector.end()); 
        createdRegularFile->setContentsOfFile(contentsString);

        destinationDir->pushBackContent(createdRegularFile);
    }
}