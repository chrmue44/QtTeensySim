#include "cSdCard.h"
#include <string>
#include <cstdio>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <filesystem>



#ifndef size_t
typedef std::size_t size_t;
#endif
#ifndef NULL
#define NULL 0
#endif

cSdCard* cSdCard::m_pthis = NULL;

cSdCard::cSdCard() {
  strcpy(m_actDir, "/");
  m_baseDir = std::string("/home/christian/prj/batdetector/data");
  getActPath();
}


cSdCard& cSdCard::inst()
{
  if(m_pthis == NULL)
     m_pthis = new cSdCard();
  return *m_pthis;
}


const char* cSdCard::getActPath()
{
  //getcwd(m_actDir, sizeof(m_actDir));
  return getActDir();
}

enSdRes cSdCard::mkDir(const char* name)
{
  std::string str = m_baseDir + "/";
  if(name[0] != '/')
  {
    str += m_actDir;
    str += "/";
  }
  str += name;
  std::filesystem::path p = str;
  std::filesystem::create_directory(p);
  enSdRes rc = enSdRes::OK;
  return rc;
}

enSdRes cSdCard::chdir(const char* name)
{
  enSdRes rc = enSdRes::OK;
  char dir[FILENAME_LEN];
  if(name[0] != '/')
    strncpy(dir, m_actDir, sizeof (dir));
  else
    dir[0] = 0;

//::chdir(name);
  if(strcmp(name, "..") == 0)
  {
      char* last = strrchr(dir, '/');
      if((last - &dir[0]) == 2)
        dir[3] = 0;
      else
        *(last) = 0;
      strncpy(m_actDir, dir, sizeof (m_actDir));
  }
  else
  {
    int len = strlen(dir);
    if ((len > 0) &&(dir[len - 1] != '/'))
      strcat(dir, "/");    
    strcat(dir, name);

    std::string str = m_baseDir + dir;
    DIR* pDir = opendir(str.c_str());
    if (pDir != nullptr)
    {
      (void) closedir (pDir);
      strncpy(m_actDir, dir, sizeof (m_actDir));
    }
    else
      rc = enSdRes::OPEN_DIR;
  }
  return rc;
}

enSdRes cSdCard::del(const char* name)
{
  std::string str = m_baseDir + m_actDir + "/";
  str += name;
  remove(str.c_str());
  return enSdRes::OK;
}

enSdRes cSdCard::deldir(const char* name)
{
  std::string str = m_baseDir + m_actDir + "/";
  str += name;
  remove(str.c_str());
  return enSdRes::OK;
}

enSdRes cSdCard::dir(tDirInfo& directory , bool terminal, size_t startIndex) {

  enSdRes result = enSdRes::OK;
  stDirEntry item;
  struct dirent * dir; // for the directory entries
  size_t index = 0;
  m_dirInfo.clear();
  char dirBuf[80];
  strncpy(dirBuf, m_baseDir.c_str(), sizeof(dirBuf));
  strcat(dirBuf, m_actDir);
  DIR * dp = opendir(dirBuf); // open the path
  if(dp==NULL)
    return enSdRes::OPEN_DIR; // if was not able return
  item.isDir = true;
  if(strlen(m_actDir) > 1) {
    strcpy(item.name, "..");
    m_dirInfo.push_back(item);
  }

  while ((dir = readdir(dp)) != NULL) {
    if(index >= startIndex)
    {
      strncpy(item.name, dir->d_name, sizeof(item.name));
      if(item.name[0] != '.') {
        if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 ) // if it is a directory
          item.isDir = true;
        else
          item.isDir = false;
        m_dirInfo.push_back(item);
      }
    }
    index++;
  }
  closedir(dp); // finally close the directory

  directory = m_dirInfo;
  return result;
}

uint32_t cSdCard::fileSize(tFILE& file) {
  fseek(file, 0, SEEK_END); // seek to end of file
  uint32_t size = ftell(file); // get current file pointer
  fseek(file, 0, SEEK_SET); // seek back to beginning of file    return 0;
  return size;
}

enSdRes cSdCard::setFilePos(tFILE file, size_t pos) {
  enSdRes retVal = (fseek(file, pos, SEEK_SET) == 0) ? enSdRes::OK : enSdRes::SEEK_ERR;
  return retVal;
}

enSdRes cSdCard::openFile(const char* name, tFILE& file, enMode mode)
{
  enSdRes retVal = enSdRes::OK;

  m_dispDir = std::string(name);

 // size_t start_pos = m_dispDir.find("0:");
 // if(start_pos != std::string::npos)
 //    m_dispDir.replace(start_pos, 2, m_baseDir);

  switch(mode)
  {
    case enMode::READ:
    file = fopen(getFullname((name)), "rb+");
      break;

  case enMode::WRITE:
      file = fopen(getFullname((name)), "wb+");
        break;

  }
  if(file == NULL)
    retVal = enSdRes::OPEN_FILE_ERR;
  return retVal;

}

enSdRes cSdCard::readFile(tFILE& file, void* buf, size_t& bytesRead, size_t bytesToRead) {
  bytesRead = fread(buf, 1, bytesToRead, file);
  return enSdRes::OK;
}

enSdRes cSdCard::writeFile(tFILE &file, const char *buf, size_t &bytesWritten, size_t bytesToWrite) {
  bytesWritten = fwrite(buf, 1, bytesToWrite, file);
  return enSdRes::OK;
}

enSdRes cSdCard::readLine(tFILE& file, void* buf, size_t bufSize, size_t& bytesRead) {
  char* pBuf = (char*)buf;
  bytesRead = 0;
  while (pBuf < ((char*)buf + bufSize)) {
    int res = fread(pBuf, 1, 1, file);
    if(res == 0)
      break;
    bytesRead += res;
    if(*pBuf == '\n')
      break;
    pBuf++;
  }
  if(*pBuf == '\n')
    return enSdRes::OK;
  else
    return enSdRes::READ_ERR;
}

enSdRes cSdCard::closeFile(tFILE& file)
{
  return fclose(file) == 0 ? enSdRes::OK : enSdRes::CLOSE_ERR;
}

enSdRes cSdCard::readFileFromTerminal(char* name)
{
  tFILE file;
  char buf[80];
  size_t bytesLeft;
  size_t bytesWritten = 0;
  enSdRes rc = OK;
  m_fileTransferActive = true;
  uint32_t startTime = millis();
  Serial.print("0"); //send reply to start file transfer

  while(Serial.available() < 10) {
    if((millis() - startTime) > 5000) {
      Serial.print("timeout receiving file");
      m_fileTransferActive = false;
      return INT_ERR;
    }
  }
  for(int i = 0; i < 10; i++)
    buf[i] = Serial.read();

  if(buf[9] == ':') {
    Serial.print("0");
    rc = openFile(name, file, WRITE);
    buf[9] = 0;
    bytesLeft = atoi(buf);

    while(bytesLeft > 0) {
      startTime = millis();
      size_t bytesToRead = WRITE_BLOCK_SIZE;
      if(bytesLeft < bytesToRead)
      bytesToRead = bytesLeft;
      size_t written = 0;
      while(bytesToRead > 0) {
        while(Serial.available() < 1) {
          if((millis() - startTime) > 5000) {
            Serial.print("2 timeout receiving file");
            m_fileTransferActive = false;
            closeFile(file);
            return INT_ERR;
          }
        }
        buf[0] = Serial.read();
        rc = writeFile(file, buf, bytesWritten, 1);
        written += bytesWritten;
        bytesToRead--;
        bytesLeft--;
      }
      Serial.printf("0 bytes written: %i", written);
    }
    rc = closeFile(file);
  }
  else {
    rc = INT_ERR;
    Serial.print("1");
  }
  m_fileTransferActive = false;
  return rc;
}

#define BUFLEN  64

enSdRes cSdCard::sendFileToTerminal(char* name, int delayTime)
{
  tFILE file;
  char buf[BUFLEN + 2];
  size_t bytesRead = 0;
  enSdRes rc = openFile(name, file, READ);
  if(rc == OK) {
    size_t size = fileSize(file);
    Serial.printf("%09u:",size);
    int cnt = 0;
    while(! eof(file)) {
      rc = readFile(file, &buf, bytesRead, BUFLEN);
      Serial.write(&buf[0],bytesRead);
      cnt++;
      if(cnt >= 32)
      {
        cnt = 0;
        delay(delayTime);
      }
    }
  }
  return rc;
}

enSdRes cSdCard::dir(tDirInfo& directory, bool terminal, const char* ext, size_t startIndex)
{
  enSdRes retVal = OK;
 /* TODO
    tFILE dir;
  tFILE file;

  if (!dir.open(m_actDir))
    return OPEN_DIR;

  if(terminal && (startIndex == 0))
    Serial.printf("dir: %s\n", m_actDir);
  m_dirInfo.clear();
  stDirEntry d;
  bool exitFlag = false;
  for(size_t i = 0; i < startIndex; i++) {
    bool ok = file.openNext(&dir, O_RDONLY);
    if (!ok) {
      exitFlag = true;
      break;
    }
    file.close();
  }

  if(exitFlag)
    retVal =  END_OF_DIR;
  else
  {
    for (int i = 0; i < MAX_DIRENTRIES; i++) {
      bool ok = file.openNext(&dir, O_RDONLY);
      if (! ok) {
        if(terminal)
          Serial.printf("dir end\n");
        break; // Error or end of dir
      }

      if(ext != NULL) {
        char* p = strrchr (d.name, '.');
        if(p == NULL)
          continue;
        p++;
        if(strcmp(p, ext) != 0)
          continue;
      }

      file.getName(d.name, FILENAME_LEN);
      if (file.isDir()) {
        d.isDir = true;
        d.fSize = 0;
        Serial.printf("[ %s ]\n", d.name);
      }
      else {
        d.isDir = false;
        d.fSize = file.fileSize();
        Serial.printf("%s : %u\n", d.name, d.fSize);
      }
      m_dirInfo.push_back(d);
      file.close();
    }
    d.isDir = true;
    d.fSize = 0;
    strcpy(d.name,"..");
    m_dirInfo.push_back(d);
    dir.close();
  }
  directory = m_dirInfo; */
  return retVal;
}
