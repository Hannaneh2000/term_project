#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int S[32];
int Imm, j=0;
int situation[8];
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
void zero_flag(int result)
{
    if (result == 0)
        situation[1] = 1;
    else
        situation[1] = 0;   
}
void sign_flag(int result)
{
    if (result < 0)
        situation[2] = 1;
    else
        situation[2] = 0;   
}
void overflow_flag_add(int a, int b, int c)
{
    if (b>0 && c>0 && a <0 || b<0 && c < 0 && a > 0)
        situation[5] = 1;
    else
        situation[5] = 0;
}
void overflow_flag_sub(int a, int b, int c)
{
    if (b>0 && c <0 && a <0 || b<0 && c > 0 && a > 0)
        situation[5] = 1;
    else
        situation[5] = 0;
}
void overflow_flag_mull(int a, int b, int c)
{
    if (b !=0 && (a/b) != c)
        situation[5] = 1;
    else
        situation[5] = 0;
}
void ADD(int rd, int rs, int rt)
{
    S[rd]= S[rs] + S[rt];
    parity_flag(S[rd]);
    zero_flag(S[rd]);
    sign_flag(S[rd]);
    overflow_flag_add(S[rd], S[rs], S[rt]);
}
void SUB(int rd, int rs, int rt)
{
    S[rd]= S[rs] - S[rt];
    parity_flag(S[rd]);
    zero_flag(S[rd]);
    sign_flag(S[rd]);
    overflow_flag_sub(S[rd], S[rs], S[rt]);
}
void AND(int rd, int rs, int rt)
{
    S[rd]= S[rs] & S[rt];
    parity_flag(S[rd]);
    zero_flag(S[rd]);
    sign_flag(S[rd]);
}
void OR(int rd, int rs, int rt)
{
    S[rd]= S[rs] | S[rt];
    parity_flag(S[rd]);
    zero_flag(S[rd]);
    sign_flag(S[rd]);
}
void XOR(int rd, int rs, int rt)
{
    S[rd]= S[rs] ^ S[rt];
    parity_flag(S[rd]);
    zero_flag(S[rd]);
    sign_flag(S[rd]);
}
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
    overflow_flag_mull(S[rt], S[rs], Imm);
}
void ADDI(int rt, int rs, int Imm)
{
    S[rt]= S[rs] + Imm;
    parity_flag(S[rt]);
    zero_flag(S[rt]);
    sign_flag(S[rt]);
    overflow_flag_add(S[rt], S[rs], Imm);
}
void SUBI(int rt, int rs, int Imm)
{
    S[rt]= S[rs] - Imm;
    parity_flag(S[rt]);
    zero_flag(S[rt]);
    sign_flag(S[rt]);
    overflow_flag_sub(S[rt], S[rs], Imm);
}
void ANDI(int rt, int rs, int Imm)
{
    S[rt]= S[rs] & Imm;
    parity_flag(S[rt]);
    zero_flag(S[rt]);
    sign_flag(S[rt]);
}
void ORI(int rt, int rs, int Imm)
{
    S[rt]= S[rs] | Imm;
    parity_flag(S[rt]);
    zero_flag(S[rt]);
    sign_flag(S[rt]);
}
void XORI(int rt, int rs, int Imm)
{
    S[rt]= S[rs] ^ Imm;
    parity_flag(S[rt]);
    zero_flag(S[rt]);
    sign_flag(S[rt]);
}
void MOV(int rt, int Imm)
{
    S[rt]= Imm;
}
void SWP(int rt, int rs)
{
    int c;
    c = S[rt];
    S[rt]= S[rs];
    S[rs] = c;
}
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
    reset();
}
void DUMP_REGS_F()
{
    FILE *file;
    file=fopen("regs.txt", "w");
    if (file == NULL)
    {
        printf("Error Dump Regs F");
    }
    else
    {
        for (int i = 0; i < 32; i++)
            fprintf(file, " %d ", S[i]);
        fprintf(file, "\n");
        for (int i = 0; i < 8; i++)
            fprintf(file, " %d ", situation[i]);
    }
    // fwrite(S, sizeof(int), 32, file);
    // fwrite(situation, sizeof(char), 8, file);
    fclose(file);
}
void INPUT()
{
    scanf("%d", &S[0]);
}
void OUTPUT()
{
    printf("%d", S[0]);
}
int stack[50];
void push(int n)
{
    for (int i = 0; i < 50; i++)
        stack[i+1] = stack[i];
    stack[0] = S[n];
}
void pop(int n)
{
    S[n] = stack[0];
    for (int i = 0; i < 50; i++)
        stack[i] = stack[i+1];
}

void red()
{
    printf("\033[1;31m");
}
void yellow()
{
    printf("\033[1;33m");
}
void green()
{
    printf("\033[1;32m");
}
void white()
{
    printf("\033[1;37m");
}
void blue()
{
    printf("\033[1;34m");
}
void purple()
{
    printf("\033[1;35m");
}
void reset()
{
    printf("\033[1;0m");
}

int error_index(int a, int b, int c, char d[15])
{
    int f=0;
    if (a <0 || b < 0 || c < 0)
    {
        printf("%c negative index error ", d);
        f = 5;
    }
        
    if (a > 31 || b > 31 || c > 31)
    {
        printf("%c value index error ", d);
        f =5;
    }
    if(f != 5)
        return 2;
    return 1;
}

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
    while(fscanf(Inputs, "%[^\n]\n", buffer) != EOF) 
    {
        reset();
        jmpcount++;
        char forms[15] = {'\0'};
        for (int i = 0; i< sizeof(buffer); i++)
            buffer[i] = toupper(buffer[i]);
        for (j = 0; (buffer[j]!= ' '); j++)
        {
            forms[j] = buffer[j];
            // if (buffer[j+1] == '\0')
            //     buffer[j+1]= ' ';
        }
        //|| (buffer[j]!= '\n')
        // forms[j+1]= '\0';
        int result, one, two;
        if (strcmp(forms, "EXIT") == 0)
            exit(0);
        else if (strcmp(forms, "ADD") == 0)
        {
            sscanf(buffer, "ADD S%d, S%d, S%d", &result, &one, &two);
            if (error_index(result, one, two, forms) == 2)
                ADD(result, one, two);
        }
        else if (strcmp(forms, "JMP") == 0)
        {
            jmpcount++;
            if (jmpcount > 10)
            {
                red();
                printf("loop skip");
                white();
                fscanf(Inputs, "%[^\n]\n", buffer);
                // jmpcount = 0;
            }
            else
            {
                int lines = 1, chars = 0;
                sscanf(buffer, "JMP %d", &result);
                if (result <= 0)
                    printf("Negative Error in JMP\n");
                else if (result > checkline)
                    printf("Error in JMP: More %d lines\n", checkline);
                else
                {
                    rewind(Inputs);
                    while (lines != result)
                    {
                        chars++;
                        if (fgetc(Inputs) == '\n')
                            lines++;
                    }
                    fseek(Inputs, chars, SEEK_SET);
                    fscanf(Inputs, "%[^\n]\n", buffer);
                }
            }
        }
        else if (strcmp(forms, "SKIE") == 0)
        {
            sscanf(buffer, "SKIE S%d, S%d", &one, &two);
            if (error_index(one, two, 1, forms) == 2)
            {
                if (S[one] == S[two])
                fscanf(Inputs, "%[^\n]\n", buffer);
            }
        }
        else if(strcmp(forms, "SUB") == 0)
        {
            sscanf(buffer, "SUB S%d, S%d, S%d", &result, &one, &two);
            if (error_index(result, one, two, forms) == 2)
                SUB(result, one, two);
        }
        else if(strcmp(forms, "AND") == 0)
        {
            sscanf(buffer, "AND S%d, S%d, S%d", &result, &one, &two);
            if (error_index(result, one, two, forms) == 2)
                AND(result, one, two);
        }
        else if(strcmp(forms, "XOR") == 0)
        {
            sscanf(buffer, "XOR S%d, S%d, S%d", &result, &one, &two);
            if (error_index(result, one, two, forms) == 2)
                XOR(result, one, two);
        }
        else if(strcmp(forms, "OR") == 0)
        {
            sscanf(buffer, "OR S%d, S%d, S%d", &result, &one, &two);
            if (error_index(result, one, two, forms) == 2)
                OR(result, one, two);
        }
        else if(strcmp(forms, "ADDI") == 0)
        {
            sscanf(buffer, "ADDI S%d, S%d, %d", &result, &one, &two);
            if (error_index(result, one, 1, forms) == 2)
                ADDI(result, one, two);
        }
        else if(strcmp(forms, "SUBI") == 0)
        {
            sscanf(buffer, "SUBI S%d, S%d, %d", &result, &one, &two);
            if (error_index(result, one, 1, forms) == 2)
                SUBI(result, one, two);
        }
        else if(strcmp(forms, "ANDI") == 0)
        {
            sscanf(buffer, "ANDI S%d, S%d, %d", &result, &one, &two);
            if (error_index(result, one, 1, forms) == 2)
                ANDI(result, one, two);
        }
        else if(strcmp(forms, "XORI") == 0)
        {
            sscanf(buffer, "XORI S%d, S%d, %d", &result, &one, &two);
            if (error_index(result, one, 1, forms) == 2)
                XORI(result, one, two);
        }
        else if(strcmp(forms, "ORI") == 0)
        {
            sscanf(buffer, "ORI S%d, S%d, %d", &result, &one, &two);
            if (error_index(result, one, 1, forms) == 2)
                ORI(result, one, two);
        }
        else if(strcmp(forms, "MOV") == 0)
        {
            if (buffer[8] == 'S' || buffer[9] == 'S')
            {
                sscanf(buffer, "MOV S%d, S%d", &result, &one);
                if (error_index(result, one, 1, forms) == 2)
                    MOV(result, S[one]);
            }
            else
            {
                sscanf(buffer, "MOV S%d, %d", &result, &one);
                if (error_index(result, 1, 1, forms) == 2)
                    MOV(result, one);
            }
        }
        else if(strcmp(forms, "SWP") == 0)
        {
            sscanf(buffer, "SWP S%d, S%d", &result, &one);
            if (error_index(result, one, 1, forms) == 2)
                SWP(result, one);
        }
        else if(strcmp(forms, "PUSH") == 0)
        {
            sscanf(buffer, "PUSH S%d", &result);
            if (error_index(result, 1, 1, forms) == 2)
                push(result);
        }
        else if(strcmp(forms, "POP") == 0)
        {
            sscanf(buffer, "POP S%d", &result);
            if (error_index(result, 1, 1, forms) == 2)
                pop(result);
        }
        else if(strcmp(forms, "DUMP_REGS") == 0)
            DUMP_REGS();
        else if(strcmp(forms, "DUMP_REGS_F") == 0)
            DUMP_REGS_F();
        else if(strcmp(forms, "INPUT") == 0)
            INPUT();
        else if(strcmp(forms, "OUTPUT") == 0)
            OUTPUT();
        else if(strcmp(forms, "MULL") == 0)
        {
            sscanf(buffer, "MULL S%d, S%d", &result, &one);
            if (error_index(result, one, 1, forms) == 2)
                MULL(result, one);
        }
        else if(strcmp(forms, "DIV") == 0)
        {
            sscanf(buffer, "DIV S%d, S%d", &result, &one);
            if (error_index(result, one, 1, forms) == 2)
                DIV(result, one);
        }
        else
        {
            red();
            printf("Wrong Instructure  ");
        }
    }
    fclose(Inputs);
}
