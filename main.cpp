//Author Vivek Patel

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

// Function prototypes
char* readFromFile(const char* filepath);
bool hasSpace(const char* topStrand);
char* generateComplement(const char* topStrand);
char* recursiveBuilder(int size, int iteration, const char* topStrand, char* current);
std::vector<std::vector<char>>seperatedStrands(const char*strand,int separater);

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
    char* buffer = new char[fileSize += 1]; // +1 for null terminator
    inputFile.read(buffer, fileSize);

    inputFile.close();

    buffer[fileSize] = '\0'; // Null-terminate the buffer

    return buffer; // Return the pointer to the allocated memory
}

bool hasSpace(const char* topStrand) {
    std::size_t size = std::strlen(topStrand);
    for (std::size_t i = 0; i < size; i++) {
        if (topStrand[i] == ' ') {
            return true;
        }
    }
    return false;
}

char* generateComplement(const char* topStrand) {
    std::size_t size = std::strlen(topStrand);
    char* buffer = new char[size + 1]; // +1 for null terminator
    buffer[size] = '\0'; // Null-terminate the buffer

    return recursiveBuilder(size, 0, topStrand, buffer);
}

char* recursiveBuilder(int size, int iteration, const char* topStrand, char* current) {
    if (iteration < size) {
        char currentChar = topStrand[iteration];
        switch (currentChar) {
            case 'G':
                current[iteration] = 'C';
                break;
            case 'C':
                current[iteration] = 'G';
                break;
            case 'A':
                current[iteration] = 'T';
                break;
            case 'T':
                current[iteration] = 'A';
                break;
            default:
                iteration = size; // There is no matching character.
        }
        return recursiveBuilder(size, iteration + 1, topStrand, current);
    }
    return current;
}

std::vector<std::vector<char>>seperatedStrands(const char*strand,int separater){
    std::size_t size = std::strlen(strand);
    int cols = separater;
    int rows = (size + cols - 1) / cols;
    std::vector<std::vector<char>> charList(rows, std::vector<char>(cols));

    for(int i = 0; i < size; i++){
        int row = i/cols;
        int col = i % cols;
        charList[row][col] =strand[i];
    }

    return charList;
}

void print2DVector(const std::vector<std::vector<char>>& charList) {
    for (const auto& row : charList) {
        for (char element : row) {
            std::cout << element << ' ';
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filepath>" << std::endl;
        std::cout << "error length too short";
        return 1;
    }

    const char* filepath = argv[1];

    char* topStrand = readFromFile(filepath);

    bool flag1 = hasSpace(topStrand);

    if (flag1) {
        std::cout << "This DNA is missing a purine." << std::endl;
        delete[] topStrand;
        return 1;
    }

    char* complementStrand = generateComplement(topStrand);

    std::size_t topStrandSize = std::strlen(topStrand);
    std::size_t complementStrandSize = std::strlen(complementStrand);

    if(topStrandSize!=complementStrandSize){
        std::cout << "This DNA is not the same size, because one of the nucleotides are not real in the top strand." <<std::endl;
        return 1;
    } else {
        std::cout << "There is no real problem in this DNA segment at first glance." << std::endl;
    }



    std::vector<std::vector<char>>seperatedTopStrand = seperatedStrands(topStrand,argc);
    std::vector<std::vector<char>>seperatedCompliment = seperatedStrands(complementStrand,argc);

    std::cout << "Separated Top Strand and Compliment Strands" << std::endl;
    print2DVector(seperatedTopStrand);
    print2DVector(seperatedCompliment);


    delete[] topStrand;
    delete[] complementStrand;

    return 0;
}
