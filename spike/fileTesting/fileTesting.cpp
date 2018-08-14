

#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <sys/types.h>

#include <dirent.h>

typedef std::vector<std::string> stringvec;
typedef std::vector<char*> charvec;



char *convert(const std::string & s)
{
    char *pc = new char[s.size()+1];
    std::strcpy(pc, s.c_str());
    return pc;
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



void read_directory(const std::string& name, stringvec& v, char* fileListTemp[]){
    charvec vc;
//    char *fileList[100];
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

    for(int i = 0; i < numberOfFiles; i++){
        std::cout << fileListTemp[i] << std::endl;
    }

    for(int i = 0;i < vc.size(); i++){
        delete[] vc[i];
    }
}

int main(void){

    std::string passing = "Fuckthisshit";

    std::string command = "python ../templates/testingExternal.py"; // Do all of the file reads from python in specific 
    system(command.c_str());

//    int res = system("../../templates create.py");
//
//    stringvec v;
//    int numberOfFiles = getNumberOfFiles("../templates/", v);
//    std::cout << numberOfFiles << std::endl;
//    v.clear();
//    char *fileListTemp[numberOfFiles];
//    read_directory("../templates/", v, fileListTemp);
//
//    char testOutput[4] = {'h', 'e', 'l', 'l'};
//    int w, l, h;
//    int tempType;
//    int size;
//    //char type;
//
//    std::cout << testOutput << std::endl;
//
//    std::string fileName;
//    std::string textIn;
//    std::cout << "Please input the file name you would like to read: " << std::endl;
//    std::cin >> fileName;
//
//    fileName = fileName + ".block";
//    std::ifstream outputFile;
//    outputFile.open("../templates/" + fileName);
//
//    typedef enum {
//        LENGTH,
//        WIDTH,
//        HEIGHT
//    } type;
//
//        while (outputFile >> tempType){
//            switch(tempType){
//                case LENGTH:
//                    outputFile >> size;
//                    std::cout << size << std::endl;
//                    break;
//                case WIDTH:
//                    outputFile >> size;
//                    std::cout << size << std::endl;
//                    break;
//                case HEIGHT:
//                    outputFile >> size;
//                    std::cout << size << std::endl;
//                    break;
//                default:
//                    break;
//
//
//            }
//        }
//
//
//
//    outputFile.close();
//
//    std::cout << "Please input the file name of the file you would like to delete:" << std::endl;
//    std::cin >> fileName;
//
//    fileName = fileName + ".block";
//    std::remove(("../templates/" + fileName).c_str());

    return 0;
}