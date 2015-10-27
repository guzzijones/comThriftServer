#include "iostream"
#include "string"
#include "stdio.h"
#ifdef __cplusplus
extern "C"
{
#endif
#include <unistd.h>
#include <signal.h>
#ifdef __cplusplus
}
#endif



class execCommand{

   std::string _command;
   std::string _parms;
   
   std::string _result;
   int _exitStatus;

public:
   execCommand(std::string command,std::string parms):_command(command),_parms(parms){};
   bool parse_output();

};
