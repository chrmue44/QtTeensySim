#include <dirent.h>
#include<cstring>


void* openDir(const char* dir) {
   DIR * d = opendir(dir); // open the path
   return (void*)d;
}


int getDirEntry(void* d, char* buf, size_t size, bool& isDir) {
  int retVal = 0;
  DIR* dp = (DIR*)d;
  struct dirent * dir; // for the directory entries
  dir = readdir(dp);
  if(dir != NULL) {
    strncpy(buf, dir->d_name, size);
    if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 ) // if it is a directory
       isDir = true;
     else
       isDir = false;
  }
  else
    retVal = 1;
  return retVal;
}

void closeDir(void* d) {
  DIR* dp = (DIR*)d;
  closedir(dp); // finally close the directory
}

