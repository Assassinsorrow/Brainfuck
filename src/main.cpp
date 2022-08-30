#include <iostream>
#include <vector>
#include <fstream>

class Brainfuck {
  public:
    int mp; // memory pointer
    int ip; // instruction pointer
    const char* instructions; // using char* for now because i dont feel like working with msvc's weirdness
    std::vector<char> memory;

    Brainfuck(const char* program) {
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
            }
            ip++;
        }
    };
};

int main(int argc, char** argv) {
    char buffer[] = ">++++++++[<+++++++++>-]<.>>+>+>++>[-]+<[>[->+<<++++>]<<]>.+++++++..+++.>>+++++++.<<<[[-]<[-]>]<+++++++++++++++.>>.+++.------.--------.>>+.>++++.";
    Brainfuck interpreter = Brainfuck(buffer);
    interpreter.interpret();
    return 0;
}