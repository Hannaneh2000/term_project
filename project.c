/**
 * @file project.c
 * @file regs.txt
 * @file in.txt
 * @brief term project
 * @version: V1.09
 * @date 25 january 2023
 * @author Hannaneh Hakkak
 * @warning
 * Warning Test
 * @note fundamentals of programming.
 * \mainpage 
 * CPU registers
**/
/**
 * Include File
 * @brief includes
**/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int S[32];  /**Conditional Registers*/
int Imm, j=0;
int situation[8];
/**
 * Red text color
 * @brief redcolor out put
 * @param void
 * @return void
**/
void red()
{
    printf("\033[1;31m");
}
/**
 * yellow text color
 * @brief yellowcolor out put
 * @param void
 * @return void
**/
void yellow()
{
    printf("\033[1;33m");
}
/**
 * green text color
 * @brief greencolor out put
 * @param void
 * @return void
**/
void green()
{
    printf("\033[1;32m");
}
/**
 * white text color
 * @brief whitecolor out put
 * @param void
 * @return void
**/
void white()
{
    printf("\033[1;37m");
}
/**
 * blue text color
 * @brief bluecolor out put
 * @param void
 * @return void
**/
void blue()
{
    printf("\033[1;34m");
}
/**
 * Purple text color
 * @brief purplecolor out put
 * @param void
 * @return void
**/
void purple()
{
    printf("\033[1;35m");
}
/**
 * reset text color
 * @brief resetcolor out put
 * @param void
 * @return void
**/
void reset()
{
    printf("\033[1;0m");
}
/**
 * Parityflag
 * @brief Status[0] of the last Command
 * @param int result
 * @return void
**/
void parity_flag(int result)
{
    int count = 0;
    while (result >0)
    {
        if (result % 2 == 1)
            count++;
        result /=2;
    }
    if (count % 2 == 1)
        situation[0] = 1;
    else
        situation[0] = 0;   
}
/**
 * Zeroflag
 * @brief Status[1] of the last Command: Numbers of zeros
 * @param int result
 * @return void
**/
void zero_flag(int result)
{
    if (result == 0)
        situation[1] = 1;
    else
        situation[1] = 0;   
}
/**
 * Signflag
 * @brief Status[2] of the last Command: Sign
 * @param int result
 * @return void
**/
void sign_flag(int result)
{
    if (result < 0)
        situation[2] = 1;
    else
        situation[2] = 0;   
}
/**
 * Overflowflag add
 * @brief Status[5] of the last Command: overflow
 * @param int result
 * @return void
**/
void overflow_flag_add(int a, int b, int c)
{
    if (b>0 && c>0 && a <0 || b<0 && c < 0 && a > 0)
        situation[5] = 1;
    else
        situation[5] = 0;
}
/**
 * Overflowflag Sub
 * @brief Status[5] of the last Command: overflow
 * @param int result
 * @return void
**/
void overflow_flag_sub(int a, int b, int c)
{
    if (b>0 && c <0 && a <0 || b<0 && c > 0 && a > 0)
        situation[5] = 1;
    else
        situation[5] = 0;
}
/**
 * Overflowflag Mull
 * @brief Status[5] of the last Command: overflow
 * @param int result
 * @return void
**/
void overflow_flag_mull(int a, int b, int c)
{
    if (b !=0 && (a/b) != c)
        situation[5] = 1;
    else
        situation[5] = 0;
}
/**
 * ADD
 * @brief adding two registers
 * @param int rd, rs & rt
 * @return void
**/
void ADD(int rd, int rs, int rt)
{
    S[rd]= S[rs] + S[rt];
    parity_flag(S[rd]);
    zero_flag(S[rd]);
    sign_flag(S[rd]);
    overflow_flag_add(S[rd], S[rs], S[rt]);
}
/**
 * SUB
 * @brief subing two registers
 * @param int rd, rs & rt
 * @return void
**/
void SUB(int rd, int rs, int rt)
{
    S[rd]= S[rs] - S[rt];
    parity_flag(S[rd]);
    zero_flag(S[rd]);
    sign_flag(S[rd]);
    overflow_flag_sub(S[rd], S[rs], S[rt]);
}
/**
 * AND
 * @brief AND two registers 
 * @param int rd, rs, rt
 * @return void
**/
void AND(int rd, int rs, int rt)
{
    S[rd]= S[rs] & S[rt];
    parity_flag(S[rd]);
    zero_flag(S[rd]);
    sign_flag(S[rd]);
}
/**
 * OR
 * @brief OR two registers
 * @param int number rd, rs, rt
 * @return void
**/
void OR(int rd, int rs, int rt)
{
    S[rd]= S[rs] | S[rt];
    parity_flag(S[rd]);
    zero_flag(S[rd]);
    sign_flag(S[rd]);
}
/**
 * XOR
 * @brief XOR two registers
 * @param int rd, rs, rt
 * @return void
**/
void XOR(int rd, int rs, int rt)
{
    S[rd]= S[rs] ^ S[rt];
    parity_flag(S[rd]);
    zero_flag(S[rd]);
    sign_flag(S[rd]);
}
/**
 * DIV
 * @brief divide two registers
 * @param int rs & rt
 * @return void
**/
void DIV(int rt, int rs)
{
    int quotient, remain;
    quotient = S[rt]/S[rs];
    remain = S[rt]%S[rs];
    S[rt] = quotient;
    S[rs] = remain;
    parity_flag(S[rt]);
    zero_flag(S[rt]);
    sign_flag(S[rt]);
}
/**
 * MULL
 * @brief multiply two registers: 4 more bits in rt &  4 less bits in rs
 * @param int rs & rt
 * @return void
**/
void MULL(int rt, int rs)
{
    int multi;
    multi = S[rt] * S[rs];
    S[rt] = multi / 16;
    S[rs] = multi % 16;
    // S[rt] = multi <<4;
    // S[rs] = multi >>4;
    // S[rt] = multi & 15;
    // S[rs] = multi & 240;
    // S[rt] = multi & 00001111;
    // S[rs] = multi & 11110000;
    parity_flag(multi);
    zero_flag(multi);
    sign_flag(multi);
    overflow_flag_mull(S[rt], S[rs], multi);
}
/**
 * ADDI
 * @brief adding a registers and a number
 * @param int rt, rs, Imm
 * @return void
**/
void ADDI(int rt, int rs, int Imm)
{
    S[rt]= S[rs] + Imm;
    parity_flag(S[rt]);
    zero_flag(S[rt]);
    sign_flag(S[rt]);
    overflow_flag_add(S[rt], S[rs], Imm);
}
/**
 * SUBI
 * @brief subbing a registers and a number
 * @param int rt, rs & Imm
 * @return void
**/
void SUBI(int rt, int rs, int Imm)
{
    S[rt]= S[rs] - Imm;
    parity_flag(S[rt]);
    zero_flag(S[rt]);
    sign_flag(S[rt]);
    overflow_flag_sub(S[rt], S[rs], Imm);
}
/**
 * ANDI
 * @brief  AND a register with a number
 * @param int rt, rs & Imm
 * @return void
**/
void ANDI(int rt, int rs, int Imm)
{
    S[rt]= S[rs] & Imm;
    parity_flag(S[rt]);
    zero_flag(S[rt]);
    sign_flag(S[rt]);
}
/**
 * ORI
 * @brief OR a register with a number
 * @param int rt, rs & Imm
 * @return void
**/
void ORI(int rt, int rs, int Imm)
{
    S[rt]= S[rs] | Imm;
    parity_flag(S[rt]);
    zero_flag(S[rt]);
    sign_flag(S[rt]);
}
/**
 * XORI
 * @brief XOR a register with a number
 * @param int rt, rs & Imm
 * @return void
**/
void XORI(int rt, int rs, int Imm)
{
    S[rt]= S[rs] ^ Imm;
    parity_flag(S[rt]);
    zero_flag(S[rt]);
    sign_flag(S[rt]);
}
/**
 * MOV
 * @brief put a number in a register
 * @param[in] int (integer number rt & Imm)
 * @return void
**/
void MOV(int rt, int Imm)
{
    S[rt]= Imm;
}
/**
 * SWP
 * @brief swap two registers
 * @param int rt & rs
 * @return void
**/
void SWP(int rt, int rs)
{
    int c;
    c = S[rt];
    S[rt]= S[rs];
    S[rs] = c;
}
/**
 * DUMP_REGS
 * @brief print all register's value
 * @param void
 * @return void
**/
void DUMP_REGS()
{
    purple();
    printf("Register:\n");
    green();
    for (int i = 0; i < 32; i++)
        printf("%d  ", S[i]);
    printf("\n");
    purple();
    printf("Status:\n");
    green();
    for (int i = 0; i < 8; i++)
        printf("%d  ", situation[i]);
    printf("\n");
    reset();
}
/**
 * DUMP_REGS_F
 * @brief save the value of all registers in regs.tx
 * @param void
 * @return void
**/
void DUMP_REGS_F(int e)
{
    FILE *file;
    file=fopen("regs.txt", "w");
    // if (file == NULL)
    //     printf("Error Dump Regs F in line %d\n", e);
    // else
    // {
    for (int i = 0; i < 32; i++)
        fprintf(file, " %d ", S[i]);
    fprintf(file, "\n");
    for (int i = 0; i < 8; i++)
        fprintf(file, " %d ", situation[i]);
    // }
    fclose(file);
}
/**
 * INPUT
 * @brief getting register[0] value
 * @param void
 * @return void
**/
void INPUT()
{
    blue();
    printf("enter S0 value: ");
    scanf(" %d", &S[0]);
    reset();
}
/**
 * OUTPUT
 * @brief print register[0] value
 * @param void
 * @return void
**/
void OUTPUT()
{
    printf("%d", S[0]);
    printf("\n");
}
int stack[50]; /**Global variable stack*/
/**
 * PUSH
 * @brief  push stacks set value in stack[0]
 * @param int rs
 * @return void
**/
void push(int n)
{
    for (int i = 0; i < 50; i++)
        stack[i+1] = stack[i];
    stack[0] = S[n];
}
/**
 * POP
 * @brief pull stacks
 * @param int rt
 * @return void
**/
void pop(int n)
{
    S[n] = stack[0];
    for (int i = 0; i < 50; i++)
        stack[i] = stack[i+1];
}
/**
 * Error_index
 * @brief checking the errors for negative index and more than 31 index
 * @param int (a, b, c, d[15], z
 * @return int 1 or 0
**/
int error_index(int a, int b, int c, char d[15], int z)
{
    int f=0;
    if (a <0 || b < 0 || c < 0)
    {
        printf("%s negative index error in line %d \n", d, z);
        f = 5;
    }
    if (a > 31 || b > 31 || c > 31)
    {
        printf("%s value index error in line %d \n", d, z);
        f =5;
    }
    if(f != 5)
        return 2;
    return 1;
}
/**
 * main
 * \section main
 * @brief run all the code lines that is written in our file
 * @param int argc, *argv[]
 * @return 0
**/
int main(int argc, char *argv[])
{
    // char Name[100];
    char buffer[1000];
    // scanf("%s", Name);
    FILE *Inputs;
    if (argc <2)
        Inputs = fopen("in.txt", "r");
    else
        Inputs = fopen(argv[1], "r");
    int jmpcount = 0, checkline=0;
    while(fscanf(Inputs, "%[^\n]\n", buffer) != EOF)
        checkline++;
    rewind(Inputs);
    int lineerror;
    while(fscanf(Inputs, "%[^\n]\n", buffer) != EOF) 
    {
        reset();
        lineerror++;
        // jmpcount++;
        char forms[15] = {'\0'};
        for (int i = 0; i< sizeof(buffer); i++)
            buffer[i] = toupper(buffer[i]);
        for (j = 0; (buffer[j]!= ' ' && buffer[j]!= '\n' && buffer[j]!= '/' && buffer[j]!= '\0'); j++)
            forms[j] = buffer[j];
        int result, one, two;
        if(forms[0] != '\0')
        {
            if (strcmp(forms, "EXIT") == 0)
                exit(0);
            else if (strcmp(forms, "ADD") == 0)
            {
                sscanf(buffer, "ADD S%d, S%d, S%d", &result, &one, &two);
                if (error_index(result, one, two, forms, lineerror) == 2)
                    ADD(result, one, two);
            }
            else if (strcmp(forms, "JMP") == 0)
            {
                jmpcount++;
                if (jmpcount > 10)
                {
                    red();
                    printf("loop skip in line %d\n", lineerror);
                    white();
                }
                else
                {
                    int lines = 1;
                    // int chars = 0;
                    sscanf(buffer, "JMP %d", &result);
                    if (result <= 0)
                        {
                            yellow();
                            printf("line %d: Negative Error in JMP\n", lineerror);
                            reset();
                        }
                    else if (result > checkline)
                        {
                            yellow();
                            printf("line %d: Error in JMP: More %d lines\n", lineerror, checkline);
                            reset();
                        }
                    else
                    {
                        rewind(Inputs);
                        lineerror = result-1;
                        while (lines != result)
                        {
                            // chars++;
                            if (fgetc(Inputs) == '\n')
                                lines++;
                        }
                        // fseek(Inputs, chars, SEEK_SET);
                        // fscanf(Inputs, "%[^\n]\n", buffer);
                    }
                }
            }
            else if (strcmp(forms, "SKIE") == 0)
            {
                sscanf(buffer, "SKIE S%d, S%d", &one, &two);
                if (error_index(one, two, 1, forms, lineerror) == 2)
                {
                    if (S[one] == S[two])
                    {
                        fscanf(Inputs, "%[^\n]\n", buffer);
                        lineerror++;
                    }
                }
            }
            else if(strcmp(forms, "SUB") == 0)
            {
                sscanf(buffer, "SUB S%d, S%d, S%d", &result, &one, &two);
                if (error_index(result, one, two, forms, lineerror) == 2)
                    SUB(result, one, two);
            }
            else if(strcmp(forms, "AND") == 0)
            {
                sscanf(buffer, "AND S%d, S%d, S%d", &result, &one, &two);
                if (error_index(result, one, two, forms, lineerror) == 2)
                    AND(result, one, two);
            }
            else if(strcmp(forms, "XOR") == 0)
            {
                sscanf(buffer, "XOR S%d, S%d, S%d", &result, &one, &two);
                if (error_index(result, one, two, forms, lineerror) == 2)
                    XOR(result, one, two);
            }
            else if(strcmp(forms, "OR") == 0)
            {
                sscanf(buffer, "OR S%d, S%d, S%d", &result, &one, &two);
                if (error_index(result, one, two, forms, lineerror) == 2)
                    OR(result, one, two);
            }
            else if(strcmp(forms, "ADDI") == 0)
            {
                sscanf(buffer, "ADDI S%d, S%d, %d", &result, &one, &two);
                if (error_index(result, one, 1, forms, lineerror) == 2)
                    ADDI(result, one, two);
            }
            else if(strcmp(forms, "SUBI") == 0)
            {
                sscanf(buffer, "SUBI S%d, S%d, %d", &result, &one, &two);
                if (error_index(result, one, 1, forms, lineerror) == 2)
                    SUBI(result, one, two);
            }
            else if(strcmp(forms, "ANDI") == 0)
            {
                sscanf(buffer, "ANDI S%d, S%d, %d", &result, &one, &two);
                if (error_index(result, one, 1, forms, lineerror) == 2)
                    ANDI(result, one, two);
            }
            else if(strcmp(forms, "XORI") == 0)
            {
                sscanf(buffer, "XORI S%d, S%d, %d", &result, &one, &two);
                if (error_index(result, one, 1, forms, lineerror) == 2)
                    XORI(result, one, two);
            }
            else if(strcmp(forms, "ORI") == 0)
            {
                sscanf(buffer, "ORI S%d, S%d, %d", &result, &one, &two);
                if (error_index(result, one, 1, forms, lineerror) == 2)
                    ORI(result, one, two);
            }
            else if(strcmp(forms, "MOV") == 0)
            {
                if (buffer[8] == 'S' || buffer[9] == 'S')
                {
                    sscanf(buffer, "MOV S%d, S%d", &result, &one);
                    if (error_index(result, one, 1, forms, lineerror) == 2)
                        MOV(result, S[one]);
                }
                else
                {
                    sscanf(buffer, "MOV S%d, %d", &result, &one);
                    if (error_index(result, 1, 1, forms, lineerror) == 2)
                        MOV(result, one);
                }
            }
            else if(strcmp(forms, "SWP") == 0)
            {
                sscanf(buffer, "SWP S%d, S%d", &result, &one);
                if (error_index(result, one, 1, forms, lineerror) == 2)
                    SWP(result, one);
            }
            else if(strcmp(forms, "PUSH") == 0)
            {
                sscanf(buffer, "PUSH S%d", &result);
                if (error_index(result, 1, 1, forms, lineerror) == 2)
                    push(result);
            }
            else if(strcmp(forms, "POP") == 0)
            {
                sscanf(buffer, "POP S%d", &result);
                if (error_index(result, 1, 1, forms, lineerror) == 2)
                    pop(result);
            }
            else if(strcmp(forms, "DUMP_REGS") == 0)
                DUMP_REGS();
            else if(strcmp(forms, "DUMP_REGS_F") == 0)
                DUMP_REGS_F(lineerror);
            else if(strcmp(forms, "INPUT") == 0)
                INPUT();
            else if(strcmp(forms, "OUTPUT") == 0)
                OUTPUT();
            else if(strcmp(forms, "MULL") == 0)
            {
                sscanf(buffer, "MULL S%d, S%d", &result, &one);
                if (error_index(result, one, 1, forms, lineerror) == 2)
                    MULL(result, one);
            }
            else if(strcmp(forms, "DIV") == 0)
            {
                sscanf(buffer, "DIV S%d, S%d", &result, &one);
                if (error_index(result, one, 1, forms, lineerror) == 2)
                    DIV(result, one);
            }
            else
            {
                red();
                printf("Wrong Instructure in line %d\n", lineerror);
            }
        }
        }
    fclose(Inputs);
}
