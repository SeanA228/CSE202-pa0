#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
// Union to store 4 bytes as an array of bytes, an unsigned, signed, or float number
union value{
    unsigned uval;
    int sval;
    float fval;
    unsigned char bytes[4];
};

// converts the ASCII hex character c to binary
// returns the hex value of c if c is a valid hex digit, -1 otherwise
char hexDigit(char c){
    switch (c){
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6; 
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'a':
        case 'A':
            return 10;
        case 'b':
        case 'B':
            return 11;
        case 'c':
        case 'C':
            return 12;
        case 'd':
        case 'D':
            return 13;
        case 'e':
        case 'E':
            return 14;
        case 'f':
        case 'F':
            return 15;
        default:
            return -1;
    }
}

// reads 8 hex characters from string input and stores it in the union v
// returns -1 if the hexadecimal number is invalid, 0 otherwise
int read_hex(union value *v, char *input){
    if (strlen(input) != 8){
        return -1;
    }
    v->uval = 0;
    for (int i=0; i<8; i++){
        char c = input[i];
        int valid = hexDigit(c);
        if (valid == -1){
            return -1;
        }
        v->uval = (v->uval << 4) + valid;
     }

    return 0;
}

// returns true if x has any even bit equal to 1, 0 otherwise
int any_even_one(unsigned x){
    for (int i = 0; i< 32; i= i+2){
        unsigned new_x = x>>i;
        if ((new_x & 1)==1){
            return 1;
        }
    }
    return 0;
}

// returns a mask indicating the position of the left most one in x
int leftmost_one(unsigned x){
    if (x==0){
        return 0;
    }

    int count = 0; 

    while (x!=0){
        x = x>>1;
        count++;
    }
    
    return 1 << (count-1);
}

// returns x shifted n positions to the left with the n most significant bits of x 
// inserted at the right of x
unsigned rotate_left(unsigned x, int n){
    // unsigned int temp  = x;
    // x = x<<n;
    // temp = temp>> (32-n);
    // x = x | temp; 
    x = (x<<n) | (x>>(32-n));
    return x;
}


// returns x shifted n positions to the right with the n least significant bits of x 
// inserted at the left of x
unsigned rotate_right(unsigned x, int n);
// returns x+y if no overflow occurs
// returns TMAX if a positive overflow occurs
// returns TMIN if a negative overflow occurs
int saturating_add(int x, int y);
// multiplies the binary representation of a float number f by 2
unsigned float_twice(unsigned f);
// divides the binary representation of a float number f by 2
unsigned float_half(unsigned f);

int main(int argc, char** argv){
    if(argc != 3 && argc != 4){
        printf("Invalid number of arguments");
        exit(0);
    }

    union value value;

    if (strcmp(argv[1], "even") == 0){
            int valid = read_hex(&value, argv[2]);
            if (valid==-1){
                printf("Invalid hex value\n");
            }
            else{
                int result = any_even_one(value.uval);
                if (result == 1){
                    printf("True\n");
                }
                else{
                    printf("False\n");
                }
            }
    }

    if (strcmp(argv[1], "left") == 0){
         int valid = read_hex(&value, argv[2]);
            if (valid==-1){
                printf("Invalid hex value\n");
            }
            else{
                int result = leftmost_one(value.uval);
                printf("%08x\n", result);
            }
    }

    if (strcmp(argv[1], "lrotate")==0){
        int valid = read_hex(&value, argv[2]);
            if (valid==-1){
                printf("Invalid hex value\n");
            }
            else{
                unsigned result = rotate_left(value.uval, atoi(argv[3]));
                printf("%08x\n", result);
            }
    }



    return 0;
}
