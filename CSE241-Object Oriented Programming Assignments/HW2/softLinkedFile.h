#ifndef SOFTLINKEDFILE_H
#define SOFTLINKEDFILE_H

#include "file.h"
#include <string>
using std::string;

namespace myOS{
    class softLinkedFile : public file{
		public:
			softLinkedFile(const string& _name){setName(_name);}
			const string getPathToFile()const { return pathToFile; }
			void setPathToFile(const string& _pathToFile) { pathToFile = _pathToFile; }
 			void cp(directory*& destinationDir)override;
			void rm() override;
			void cat(directory* begin) override; 
			void link(const string& _pathToFile); 
		private:
			string pathToFile;
	};
}

#endif //SOFTLINKEDFILE_H