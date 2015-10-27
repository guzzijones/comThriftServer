#include "execCommand.h"

bool execCommand::parse_output(){

  FILE *fp;
  char path[1035];

  /* Open the command for reading. */
  std::string command=_command + " " + _parms +  " 2>&1";
  fp = popen(command.c_str(), "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    _exitStatus=-1;
  }

  /* Read the output a line at a time - output it. */
  while (fgets(path, sizeof(path)-1, fp) != NULL) {
   _result+=path;
//    printf("%s", path);
  }

  /* close */
  _exitStatus=pclose(fp);
  _exitStatus=_exitStatus/256;

  return 0;
}
