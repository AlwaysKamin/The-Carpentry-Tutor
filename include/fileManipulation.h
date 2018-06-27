//
// Created by Kamin Fay on 6/7/18.
//

#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>

typedef std::vector<std::string> stringvec;
typedef std::vector<char*> charvec;
const struct file {
    std::string alias;
};



static const int clamp_size_t_to_int(const size_t data);
static bool vector_string_items_getter(void* data, int idx, const char** out_text);

int getNumberOfFiles(const std::string& name, stringvec& v);
void read_directoryToString(const std::string& name, stringvec& v);

void read_directory(const std::string& name, stringvec& v, charvec& vc, char* fileListTemp[]);
char *convert(const std::string & s);

void clearVectors(stringvec& v, charvec& vc);

void readFile(std::string fileName);

