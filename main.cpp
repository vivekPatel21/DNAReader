//Author Vivek Patel

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

char* readFromFile(const char* filepath) {
    std::ifstream inputFile(filepath);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return nullptr; // Use nullptr for error handling
    }

    // Determine the size of the file
    inputFile.seekg(0, std::ios::end);
    std::streampos fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    // Allocate memory for the char array
    char* buffer = new char[fileSize];

    inputFile.read(buffer, fileSize);

    inputFile.close();

    return buffer; // Return the pointer to the allocated memory
}

bool isSpace(const char* topStrand){
    std::size_t size = std::strlen(topStrand);
    for(int i = 0; i < size; i++){
        if (std::isspace(topStrand[i])){
            return true;
        }
    }
    return false;
}

char* compliment(const char* topStrand){
    /*TODO make the compliment to the top strand, after checking if there is a space or randomly in the string.
        Compliment must be the same length and as well as that there is a specific convention to follow.
     */
    std::size_t size = std::strlen(topStrand);
    for(int i = 0;i < size; i++){

    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filepath>" << std::endl;
        std::cout <<"error length too short";
        return 1;
    }

    const char* filepath = argv[1];

    char*SeperatedStrand = readFromFile(filepath); //this is going to keep the top stand of DNA

    bool flag1 = isSpace(SeperatedStrand);
    //don't compliment if there is a missing part.
    if(flag1){
        std::cout<<"This DNA is missing a purine.";
        return 1;
    }
    //char*compliment  =

    return 0;
}
