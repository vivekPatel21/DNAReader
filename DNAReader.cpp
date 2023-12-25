//Author Vivek Patel

#include <iostream>
#include <cstring>
#include <vector>

// Function prototypes
bool hasSpace(const char* topStrand);
char* generateComplement(const char* topStrand);
char* recursiveBuilder(int size, int iteration, const char* topStrand, char* current);
std::vector<std::vector<char>> separatedStrands(const char* strand, int separater); // Corrected function name
void print2DVector(const std::vector<std::vector<char>>& charList);

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

std::vector<std::vector<char>> separatedStrands(const char* strand, int separater) {
    std::size_t size = std::strlen(strand);
    int cols = separater;
    int rows = (size + cols - 1) / cols;
    std::vector<std::vector<char>> charList(rows, std::vector<char>(cols));

    for (int i = 0; i < size; i++) {
        int row = i / cols;
        int col = i % cols;
        charList[row][col] = strand[i];
    }

    return charList;
}

void print2DVector(const std::vector<std::vector<char>>& charList) {
    for (const auto& row : charList) {
        std::cout << "[";
        for (auto it = row.begin(); it != row.end(); ++it) {
            std::cout << *it;
            if (std::next(it) != row.end()) {
                std::cout << ",";
            }
        }
        std::cout << "] ";
    }
    std::cout << std::endl;
}



int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <DNA sequence> <separator>" << std::endl;
        std::cout << "error: insufficient arguments" << std::endl;
        return 1;
    }

    const char* dnaSequence = argv[1];
    int separator = std::atoi(argv[2]);

    if (separator <= 0) {
        std::cerr << "Error: Separator must be a positive integer." << std::endl;
        return 1;
    }

    bool flag1 = hasSpace(dnaSequence);

    if (flag1) {
        std::cout << "This DNA is missing a nucleotide." << std::endl;
        return 1;
    }

    char* complementStrand = generateComplement(dnaSequence);

    std::size_t dnaSequenceSize = std::strlen(dnaSequence);
    std::size_t complementStrandSize = std::strlen(complementStrand);

    if (dnaSequenceSize != complementStrandSize) {
        std::cout << "This DNA is not the same size because one of the nucleotides is not real in the top strand." << std::endl;
        return 1;
    }

    std::vector<std::vector<char>> separatedDnaSequence = separatedStrands(dnaSequence, separator);
    std::vector<std::vector<char>> separatedComplement = separatedStrands(complementStrand, separator);

    std::cout << "Separated DNA Sequence and Complement Strands" << std::endl;
    print2DVector(separatedDnaSequence);
    print2DVector(separatedComplement);

    delete[] complementStrand;

    return 0;
}
