#ifndef DIRHELPER_H
#define DIRHELPER_H


void* openDir(const char* dir);


int getDirEntry(void* d, char* buf, size_t size, bool& isDir);

void closeDir(void* d);

#endif // DIRHELPER_H
