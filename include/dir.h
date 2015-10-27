extern "C"
{
#include <dirent.h>
}
#include <string>
#include <vector>
#include <iostream>
#include "distData.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/progress.hpp>
//#include <boost/numeric_cast.hpp>

class dir{

   std::string _dir;
   std::string _workingDir;
   std::string _totalDir;
   void addToDirObject(boost::filesystem::directory_iterator in_iter,comProto::fileType::type fileTypeIn);
   protected:

   public:
   comProto::directory _directory;
   std::vector<comProto::file> _files;
   dir(std::string dir, std::string workingDir);

   bool list();
   bool listBoost();

   
};
