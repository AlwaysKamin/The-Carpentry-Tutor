

#include "fileManipulation.h"



int getNumberOfFiles(const std::string& name, stringvec& v){
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while((dp = readdir(dirp)) != NULL){
        v.push_back(dp->d_name);
    }
    closedir(dirp);
    return v.size();
}



void read_directory(const std::string& name, stringvec& v, charvec& vc, char* fileListTemp[]){

    DIR* dirp = opendir(name.c_str()); // Opens a directory stream and calls it dirp
    struct dirent * dp; // format of directories
    while((dp = readdir(dirp)) != NULL){
        v.push_back(dp->d_name); // Adds each item in the directory to the list
    }
    closedir(dirp);

    std::transform(v.begin(), v.end(), std::back_inserter(vc), convert);
    int numberOfFiles = vc.size();
    char *fileNames[numberOfFiles];

    for(int i = 0; i < vc.size(); i++) {
        fileListTemp[i] = vc[i];
    }

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

void newFile(std::string fileName, block &block){
    std::ofstream file;
    file.open("../templates/" + fileName);

    if(file.eof()){
        std::cout << "There was an error opening the file... Awkward... " << std::endl;
    }else{
        file << "0" << std::endl;
        file << "0" << std::endl;
        file << "1" << std::endl;
        file << "0" << std::endl;
        file << "2" << std::endl;
        file << "0" << std::endl;
    }

    file.close();
}

void saveFile(std::string fileName, block &block){
    std::ofstream file;
    std::string command = "rm ../templates/" + fileName;
    std::cout << command << std::endl;
    system(command.c_str());
    file.open("../templates/" + fileName);

    if(file.eof()){
        std::cout << "There was an error opening the file... Awkward... " << std::endl;
    }else{
        std::cout << "Loading data into file" << std::endl;
        std::cout << "0" << std::endl;
        std::cout << int(block.getLength()) << std::endl;
        std::cout << "1" << std::endl;
        std::cout << int(block.getWidth()) << std::endl;
        std::cout << "2" << std::endl;
        std::cout << int(block.getHeight()) << std::endl;
        file << "0" << std::endl;
        file << int(block.getLength()) << std::endl;
        file << "1" << std::endl;
        file << int(block.getWidth()) << std::endl;
        file << "2" << std::endl;
        file << int(block.getHeight()) << std::endl;
    }

    file.close();
}

void readFile(std::string fileName, block &block){
    typedef enum {
        LENGTH,
        WIDTH,
        HEIGHT
    } type;

    int tempType;
    int tempWidth = 0;
    int tempHeight = 0;
    int tempLength = 0;

    std::ifstream file;
    file.open("../templates/" + fileName);
    std::string tempFileLine;

    if(file.eof())
    {
        std::cout << "There was an error opening the file...Awkward..." << std::endl;
    }else{

        std::cout << "Opening File Name: " << fileName << std::endl;
        while (file >> tempType){
            switch(tempType){
                case LENGTH:
                    file >> tempLength;
                    std::cout << tempLength << std::endl;
                    break;
                case WIDTH:
                    file >> tempWidth;
                    std::cout << tempWidth << std::endl;
                    break;
                case HEIGHT:
                    file >> tempHeight;
                    std::cout << tempHeight << std::endl;
                    break;
                default:
                    break;
            }
        }
        block.setBlockSize(tempWidth, tempHeight, tempLength);
    }

    file.close();
}