#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "file.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

namespace myOS{
    class directory : public file {
        public:
            directory(const string& _name){ setName(_name); }
            const vector<file*>& getContents() const { return contentsOfDirectory; }
            void setContents(const vector<file*>& newContents){ contentsOfDirectory = newContents; }
            void setParent(directory* parentDir){ parentDirectory = parentDir; }
            void pushBackContent(file* newContent);

            void cp(directory*& destinationDir) override;
            void cat(directory* begin) override;
            void rm() override; 
            void ls() const;
            void lsRecursive() const;
            void cd(directory*& currentDirectory, const string& pathToDirectory);
            void mkdir(const string& directoryName); 
        private:
            vector<file*> contentsOfDirectory;
            directory* parentDirectory;
	};
}


#endif //DIRECTORY_H