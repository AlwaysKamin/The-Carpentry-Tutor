//
// Created by Kamin Fay on 6/7/18.
//

#include "fileManipulation.h"

static const int clamp_size_t_to_int(const size_t data) {
    static const int max_int = std::numeric_limits<int>::max();
    return static_cast<int>(data > max_int ? max_int : data);
}

static bool vector_string_items_getter(void* data, int idx, const char** out_text) {
    const std::vector<std::string>* fileNames = reinterpret_cast<std::vector<std::string>*>(data);
    const int elementCount = clamp_size_t_to_int(fileNames->size());
    if (idx < 0 || idx >= elementCount) return false;
    *out_text = fileNames->at(idx).data();
    return true;
}

int getNumberOfFiles(const std::string& name, stringvec& v){
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while((dp = readdir(dirp)) != NULL){
        v.push_back(dp->d_name);
    }
    closedir(dirp);
    return v.size();
}

void read_directoryToString(const std::string& name, stringvec& v){
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while((dp = readdir(dirp)) != NULL){
        v.push_back(dp->d_name);
    }
    closedir(dirp);

//    for(int i = 0; i < v.size(); i++) {
//        std::cout << "V content: " << v[i] << std::endl;
//    }
}


void read_directory(const std::string& name, stringvec& v, charvec& vc, char* fileListTemp[]){

    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while((dp = readdir(dirp)) != NULL){
        v.push_back(dp->d_name);
    }
    closedir(dirp);

    std::transform(v.begin(), v.end(), std::back_inserter(vc), convert);
    int numberOfFiles = vc.size();
    char *fileNames[numberOfFiles];

    for(int i = 0; i < vc.size(); i++) {
        fileListTemp[i] = vc[i];
    }
//
//    for(int i = 0; i < numberOfFiles; i++){
//        std::cout << fileListTemp[i] << std::endl;
//    }

//    for(int i = 0;i < vc.size(); i++){
//        delete[] vc[i];
//    }
}

void clearVectors(stringvec& v, charvec& vc){
    v.clear();
    vc.clear();
}

char *convert(const std::string & s)
{
    char *pc = new char[s.size()+1];
    std::strcpy(pc, s.c_str());
    return pc;
}

void readFile(std::string fileName){
    std::ifstream file;
    file.open("../templates/" + fileName);
    std::string tempFileLine;

    if(file.eof())
    {
        std::cout << "There was an error opening the file...Awkward..." << std::endl;
    }else{
        while(std::getline(file, tempFileLine)){
            std::cout << tempFileLine << std::endl;
        };
    }

    file.close();
}