

#include <map>
#include "fileManipulation.h"



int getNumberOfFiles(const std::string& name, stringvec& v){

     DIR* dirp = opendir(name.c_str());
     struct dirent * dp;
     while((dp = readdir(dirp)) != NULL){
         if(dp->d_name == "." || dp->d_name == ".."){

         }else {
             v.push_back(dp->d_name);
         }
     }
     closedir(dirp);
    return v.size();
}



void read_directory(const std::string& name, stringvec& v, charvec& vc, char* fileListTemp[]){

    DIR* dirp = opendir(name.c_str()); // Opens a directory stream and calls it dirp
    struct dirent * dp; // format of directories
    while((dp = readdir(dirp)) != NULL){
        if(dp->d_name == "." || dp->d_name == ".."){

        }else {
            v.push_back(dp->d_name);
        }
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

void saveFile(std::string fileName, block &block, bool newFile){
    std::ofstream file;
    std::string command = "rm ../templates/" + fileName;
    std::cout << command << std::endl;
    system(command.c_str());
    file.open("../templates/" + fileName);

    if(newFile){
        if(file.eof()){
            std::cout << "There was an error opening the file... Awkward... " << std::endl;
        }else{
            std::cout << "Creating a new file." << std::endl;
            file << "dim" << std::endl;
            file << 100 << std::endl;
            file << 100 << std::endl;
            file << 100 << std::endl;
        }
    }else{
        if(file.eof()){
            std::cout << "There was an error opening the file... Awkward... " << std::endl;
        }else{
            std::cout << "Loading data into file" << std::endl;
            file << "dim" << std::endl;
            file << int(block.getWidth()) << std::endl;
            file << int(block.getHeight()) << std::endl;
            file << int(block.getLength()) << std::endl;
        }
    }
    

    file.close();
}

void readFile(std::string fileName, block &block){
    typedef enum {
        LENGTH,
        WIDTH,
        HEIGHT
    } type;

    std::vector<int> blockDimensions;

    std::string tempType;
    int tempWidth = 0;
    int tempHeight = 0;
    int tempLength = 0;

    enum class headerType{
        DIM,    // DIM == 0
        DRILL   // DRILL == 1
    };

    std::map<std::string, headerType> headers = {
            {"dim", headerType::DIM},       //Maps string dim to enum DIM or 0
            {"drill", headerType::DRILL}    //Maps string drill to enum DRILL or 1
    };

    std::ifstream file;
    file.open("../templates/" + fileName);
    std::string tempFileLine;

    if(file.eof())
    {
        std::cout << "There was an error opening the file...Awkward..." << std::endl;
    }else{

        std::cout << "Opening File Name: " << fileName << std::endl;

        //Reads the file into tempType line by line
        while (file >> tempType){
            //translates the string into the maping for test header and prints the test header
            headerType testHeader = headers[tempType];
            std::cout << tempType << std::endl;

            //Switch case for test header, if DIM then it reads in the dimensions on the next three lines
            //l,w,h respectively
            switch(testHeader){
                case (headerType::DIM):
                    std::cout << "Header type found" << std::endl;
                    //Pushed the length, width and height of the block into blockDimensions[0][1]&[2]
                    file >> tempType;
                    blockDimensions.push_back(returnNum(tempType));
                    file >> tempType;
                    blockDimensions.push_back(returnNum(tempType));
                    file >> tempType;
                    blockDimensions.push_back(returnNum(tempType));
                    break;
                case(headerType::DRILL):
                    std::cout << "Drill header found" << std::endl;
                default:
                    break;
            }
        }

        std::cout << blockDimensions[0] << std::endl;
        std::cout << blockDimensions[1] << std::endl;
        std::cout << blockDimensions[2] << std::endl;
        block.setBlockSize(blockDimensions[0], blockDimensions[1], blockDimensions[2]);
    }

    file.close();
}

int returnNum(std::string toConvert){
    int num = std::stoi(toConvert); 
    return num;
}