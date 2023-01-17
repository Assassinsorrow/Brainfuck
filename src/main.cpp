#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Brainfuck {
  public:
    int mp; // memory pointer
    int ip; // instruction pointer
    std::string instructions;
    std::vector<char> memory;

    Brainfuck(const std::string program) {
        this->memory = std::vector<char>(30000, 0);
        this->instructions = program;
        this->ip = 0;
        this->mp = 0;
    };
    // >
    void incrementPointer() {
        mp++;
    };
    // <
    void decrementPointer() {
        mp--;
    };
    // +
    void incrementValue() {
        memory[mp]++;
    };
    // -
    void decrementValue() {
        memory[mp]--;
    };
    // ,
    void inputValue() {
        std::cin >> memory[mp];
    };
    // .
    void outputValue() {
        std::cout << memory[mp];
    };
    // [
    void jumpForward() {
        if (memory[mp] == 0) {
            int value = 1;
            while (value != 0) {
                ip++;
                if (instructions[ip] == '[') {
                    value++;
                } else if (instructions[ip] == ']') {
                    value--;
                }
            }
        }
    };
    // ] 
    void jumpBackward() {
        if (memory[mp] != 0) {
            int value = 1;
            while (value != 0) {
                ip--;
                if (instructions[ip] == '[') {
                    value--;
                } else if (instructions[ip] == ']') {
                    value++;
                }
            }
        }
    };
    void interpret(){
        while (instructions[ip] != '\0') {
            switch (instructions[ip]) {
                case '>':
                    incrementPointer();
                    break;
                case '<':
                    decrementPointer();
                    break;
                case '+':
                    incrementValue();
                    break;
                case '-':
                    decrementValue();
                    break;
                case '.':
                    outputValue();
                    break;
                case ',':
                    inputValue();
                    break;
                case '[':
                    jumpForward();
                    break;
                case ']':
                    jumpBackward();
                    break;
                default:  // Assume this is a comment
                    break;
            }
            ip++;
        }
    };
};

int main(int argc, char** argv) {
    if (argc < 2){
        printf("No arguments given\n");
        printf("Usage: brainfuck <file>\n");
        return 0;
    }
    std::string sourceDir = argv[1];

    std::fstream file;
    file.open(sourceDir, std::ios::in);
    // check if file exists on disk 
    if (file.fail()) {
        printf("File not found\n");
        return 0;
    }
    std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    Brainfuck interpreter = Brainfuck(buffer);
    interpreter.interpret();
    return 0;
}