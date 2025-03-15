#ifndef REGULARFILE_H
#define REGULARFILE_H

#include "file.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

namespace myOS{
    class regularFile : public file{
		public:
			regularFile(const string& _name){ setName(_name); }
			const vector<char> getContentsofFile()const{ return contentsOfFile; }
			void setContentsOfFile(const string& content) { contentsOfFile.assign(content.begin(), content.end()); }
			void cp(directory*& destinationDir)override;
			void cat(directory* begin)override; 
			void rm() override; 
		private:
			vector<char> contentsOfFile;
	};
}

#endif //REGULARFILE_H