#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
using std::string;
using std::vector;

namespace myOS{
	class directory;
    class file{
		public:
			const string getName()const{ return name; }
			void setName(const string& _name){	name = _name; }
			const string getDate()const{ return date; }
			void setDate(const string& _date){ date = _date; }
			const string getSize()const{ return size; }
			void setSize(string _size){size = _size; }
			const string getPath() const{ return path; }
			void setPath(const string& _path){ path = _path; }
			const string getCurrentDateFormatted();
			
			virtual void cp(directory*& destinationDir) = 0;
			virtual void cat(directory* begin) = 0; 
			virtual void rm() = 0;
			virtual~file() = default;
		private:
			string name;
			string path;
			string date;
			string size;
	};
}
    
#endif //FILE_H