

#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>

#include "block.hpp"

typedef std::vector<std::string> stringvec;
typedef std::vector<char*> charvec;
const struct file {
    std::string alias;
};





int getNumberOfFiles(const std::string& name, stringvec& v);

void read_directory(const std::string& name, stringvec& v, charvec& vc, char* fileListTemp[]);
char *convert(const std::string & s);

void clearVectors(stringvec& v, charvec& vc);

void readFile(std::string fileName, block &block);
void newFile(std::string fileName, block &block);
void saveFile(std::string fileName, block &block);

