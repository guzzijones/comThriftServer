#include "dir.h"
namespace fs = boost::filesystem;


dir::dir(std::string dir, std::string workingDir){
   _dir=dir;
   _workingDir=workingDir;
   fs::path tmpDir(dir);
   fs::path tmpWorkingDir(workingDir);
   fs::path full_path= tmpDir / tmpWorkingDir;
   //need to join using boost
   _totalDir=full_path.string();
}

bool dir::list(){
   DIR * dir;
   struct dirent *ent;
   
   //need to join working dir to dir
   if((dir = opendir(_totalDir.c_str()))!=NULL){
      while((ent=readdir(dir))!=NULL){
        comProto::file tmpFile;
        std::string temp=ent->d_name; 
         tmpFile.__set_name(temp);
      }
   }
   else{
      return false;
   }
   closedir(dir);
   return true;
}
void dir::addToDirObject(fs::directory_iterator in_iter,comProto::fileType::type fileTypeIn){
   comProto::directory tmpDir;
   comProto::file tmpFile;
   std::string temp=in_iter->path().filename().string(); 
   std::cout << "----Filename String: " << temp << std::endl;
   std::cout << "----Filename Type:" << fileTypeIn << std::endl;
   if(fileTypeIn==comProto::fileType::type::File){
      std::cout << "----size: " << fs::file_size(in_iter->path()) << std::endl; 
      uintmax_t size =  fs::file_size(in_iter->path());
      double sizeD = double(size);
      tmpFile.__set_size(sizeD);
   }
   tmpFile.__set_name(temp);
   tmpFile.__set_thefileType(fileTypeIn);
   _files.push_back(tmpFile); 
   _directory.__set_files(_files);         
}
bool dir::listBoost(){

   fs::path full_path(fs::initial_path<fs::path>());

   fs::path p=fs::system_complete(fs::path(_totalDir.c_str()));

   unsigned long file_count = 0;
   unsigned long dir_count = 0;
   unsigned long other_count = 0;
   unsigned long err_count = 0; 

   if ( !fs::exists( full_path ) )
  {
    std::cout << "\nNot found: " << p.string() << std::endl;
    return false;
  }   

  if (fs::is_directory(p))
  {
    std::cout << "\nIn directory: " << p << "\n\n";
    fs::directory_iterator end_iter;
    for (fs::directory_iterator dir_itr(p);
          dir_itr != end_iter;
          ++dir_itr)
    {
      try
      {
        if (fs::is_directory(dir_itr->status()))
        {
          ++dir_count;
          std::cout << dir_itr->path().filename() << " [directory]\n";
          addToDirObject(dir_itr,comProto::fileType::type::Dir);         
         //dir
        }
        else if (fs::is_regular_file(dir_itr->status()))
        {
         //file
          ++file_count;
          std::cout << "name: "<< dir_itr->path().filename() << "\n";
          addToDirObject(dir_itr,comProto::fileType::type::File);         
        }
        else
        {
         //other
          ++other_count;
          std::cout << dir_itr->path().filename() << " [other]\n";
          addToDirObject(dir_itr,comProto::fileType::type::Other);         
        }

      }
      catch (const std::exception & ex)
      {
        ++err_count;
        std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
      }
    }
    std::cout << "\n" << file_count << " files\n"
              << dir_count << " directories\n"
              << other_count << " others\n"
              << err_count << " errors\n";
  }
  else // must be a file
  {
    std::cout << "\nFound: " << p << "\n";    
    return false;

  }
  std::cout << "length of _files in directory: " << _directory.files.size() << std::endl;
  return true;
}

