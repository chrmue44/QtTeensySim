#ifndef CSDCARD_H
#define CSDCARD_H

#include <wchar.h>
#include <my_vector.h>
#include<cstdio>
#include <string>
//SEEK_SET#include <sys/ioctl.h>
#include <stdio.h>
#include "objhndlglib.h"

#define FILENAME_LEN    80
#define MAX_DIRENTRIES  30
#define WRITE_BLOCK_SIZE  1024   ///< block size for file transfer from host to device

typedef int FRESULT;
typedef FILE* tFILE;
typedef char BYTE;
typedef uint32_t UINT;
#ifndef size_t
typedef std::size_t size_t;
#endif

#define FA_READ    1
#define FA_WRITE   2

enum enSdRes
{
  OK = 0,
  MOUNT_FAILED = 1,
  OPEN_DIR = 2,
  END_OF_DIR = 3,
  READ_ERR = 4,
  WRITE_ERR = 5,
  LINE_ERR = 6,
  CLOSE_ERR = 7,
  MKDIR_ERR = 8,
  DEL_ERR = 9,
  OPEN_FILE_ERR = 10,
  INT_ERR = 11,
  UNMOUNT_ERR = 12,
  RENAME_ERR = 13,
  SEEK_ERR = 14,
  FORMAT_ERR = 15,
};

enum enMode {
  READ,
  WRITE
};


struct stDirEntry {
  char name[FILENAME_LEN];
  size_t fSize;
  bool isDir;
};

#ifdef MEMPOOL
typedef mpVector<stDirEntry> tDirInfo;
#else
typedef my_vector<stDirEntry, MAX_DIRENTRIES> tDirInfo;
#endif
class cSdCard {
 public:
   static cSdCard& inst();
   cSdCard();
   
   bool isFileTransferActive() {return m_fileTransferActive;}

   enSdRes mount() {}
   
   enSdRes unmount() {}
   
   enSdRes dir(tDirInfo& directory , bool terminal = false, size_t startIndex = 0);
   enSdRes dir(tDirInfo& directory, bool terminal, const char* ext, size_t startIndex);

   enSdRes del(const char* name);

   enSdRes deldir(const char* name);

   enSdRes mkDir(const char* name);

   /**
    * change directory:
    * 1. "0:/...": absolute path
    * 2. "..": one level up ("../.." not possible)
    * 3. "name1/name2": relative path from actual dir
    */
   enSdRes chdir(const char* name);
   
   const char* getActPath();
   
   char* getActDir() { return m_actDir; }
  /**
    * open a file
    * mode flags: 
    * FA_READ:  Specifies read access to the object. Data can be read from the file.
    * FA_WRITE  Specifies write access to the object. Data can be written to the file. Combine with FA_READ for read-write access.
    * FA_OPEN_EXISTING  Opens the file. The function fails if the file is not existing. (Default)
    * FA_CREATE_NEW Creates a new file. The function fails with FR_EXIST if the file is existing.
    * FA_CREATE_ALWAYS  Creates a new file. If the file is existing, it will be truncated and overwritten.
    * FA_OPEN_ALWAYS  Opens the file if it is existing. If not, a new file will be created.
    * FA_OPEN_APPEND  Same as FA_OPEN_ALWAYS except the read/write pointer is set end of the file.
    *
    **/
   enSdRes openFile(const char* name, tFILE& file, enMode mode);
   
   enSdRes readFile(tFILE& file, void* buf, size_t& bytesRead, size_t bytesToRead);

   enSdRes readLine(tFILE& file, void* buf, size_t bufSize, size_t& bytesRead);

   enSdRes writeFile(tFILE& file, const char* buf, size_t& bytesWritten, size_t bytesToWrite);

   enSdRes closeFile(tFILE& file);

   uint32_t fileSize(tFILE& file);

   size_t getFilePos(tFILE file) { return ftell(file); }

   enSdRes setFilePos(tFILE file, size_t pos);

   bool eof(tFILE& file) { return (feof(file) > 0); }

   FRESULT sendFileToTerminal(char* name);
   enSdRes readFileFromTerminal(char* name);
   enSdRes sendFileToTerminal(char* name, int delayTime);


   size_t available(tFILE& file)
   {
       size_t currentPos=ftell(file);
       fseek(file, 0, SEEK_END);            // move to end of file
       size_t length = ftell(file);  // get current position
       fseek(file, currentPos, SEEK_SET);   // go back to where we started
       return length - currentPos;
   }

   enSdRes format() { return enSdRes::OK;}

   /*
    * get free memory in kByte
    */

   enSdRes getFreeMem(size_t& freeSpaceKb, size_t& totSpacekB)
   {
     freeSpaceKb = 1234567;
     totSpacekB = 128000000;
   }

 protected:
   /**
    * transform path name to TCHAR
    * if path starts with "0:", result is simply <name> transformed to TCHAR (absolute path)
    * if path is relative, result is <actDir>/<name> transformed to TCHAR
    */
//  void transformPathName(TCHAR* buf, UINT bufsize, const char* name);
   const char* getFullname(const char* name)
   {
      m_fullName = m_baseDir + name;
      return m_fullName.c_str();
   }


 private:
  char m_actDir[FILENAME_LEN];   ///< actual directory
  tDirInfo m_dirInfo;  ///< content of actual directory
  static cSdCard* m_pthis;
  std::string m_baseDir;
  std::string m_dispDir;  ///< directory to display in simulation
  std::string m_fullName;
  bool m_fileTransferActive = false;
};

#endif //#ifndef CSDCARD_H
