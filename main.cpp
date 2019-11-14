
#include <stdio.h>

#define byte char

#define INSTR_STORE_INT 0x01
#define INSTR_ADD 0x02
#define INSTR_PUSH 0x03
#define INSTR_JMP 0x04
#define INSTR_END 0x00
#define INSTR_LOAD_INT 0x05
#define INSTR_LE_JMP 0x06
#define INSTR_PRINT 0x07

#define VAR_X 0x00

class Instruction {
public:
    byte command;
};

class Stack {
public:
    byte *data;
    int pointer;

    Stack() {
        data = new byte[3];
        pointer = 0;
    }

    void print() {
        for (int i = 0; i < 3; i++) {
            printf("\nSTACK[%d] = %d", i, data[i]);
        }
    }

    void push(byte d) {
        data[pointer] = d;
        pointer++;
    }

    byte pop() {
        pointer--;
        byte tmp = data[pointer];
        data[pointer] = 0;
        return tmp;
    }
};



int main() {

    Stack stack;
    byte *memory = new byte[3];
    int programPtr = 0;

    byte *program = new byte[20] {

            //int x = 0;
            INSTR_PUSH,
            0x00,
            INSTR_STORE_INT,
            VAR_X,

            //x++;
            INSTR_LOAD_INT,
            VAR_X,
            INSTR_PUSH,
            0x01,
            INSTR_ADD,
            INSTR_STORE_INT,
            VAR_X,

            //print(x);
            INSTR_PRINT,
            VAR_X,

            //while(x < 10)
            INSTR_LOAD_INT,
            VAR_X,
            INSTR_PUSH,
            0x0A,
            INSTR_LE_JMP,
            0x04,

            INSTR_END
    };

    bool running = true;

    while (running)
    {
        byte command = program[programPtr];

        switch (command)
        {
            case INSTR_STORE_INT:
            {
                byte memory_location = program[programPtr + 1];
                byte value = stack.pop();
                memory[memory_location] = value;
                printf("\nINSTR_STORE_INT %d %d", memory_location, value);
                programPtr += 2;
            }
                break;
            case INSTR_LOAD_INT:
            {
                printf("\nINSTR_LOAD_INT");
                byte memory_location = program[programPtr + 1];
                stack.push(memory[memory_location]);
                programPtr += 2;
            }
                break;

            case INSTR_PUSH:
            {
                printf("\nINSTR_PUSH");
                stack.push( program[programPtr + 1] );
                programPtr += 2;
            }
                break;
            case INSTR_ADD:
            {
                printf("\nINSTR_ADD");
                int value = stack.pop() + stack.pop();
                stack.push(value);
                programPtr += 1;
            }
                break;
            case INSTR_END:{
                running = false;
            }
                break;

            case INSTR_PRINT:{
                byte memory_location = program[programPtr + 1];
                printf("print function \n %d", memory[memory_location]);
                programPtr += 2;
            }
                break;
            case  INSTR_LE_JMP:{
                byte ValueOne,ValueTwo;
                byte memory_location = program[programPtr + 1];
                ValueOne=stack.pop();
                ValueTwo=stack.pop();
                if(ValueTwo<ValueOne){
                    programPtr=memory_location;
                } else{
                    programPtr+=2;
                }

            }
                break;


        }

        stack.print();

        for (int i = 0; i < 3; i++) {
            printf("\nMEM[%d] = %d", i , memory[i]);
        }

        printf("\n-------------------------------------------------\n");
    }

    getchar();

    return 0;
}