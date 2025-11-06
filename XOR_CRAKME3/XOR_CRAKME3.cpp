#include <stdio.h>
#include <iostream>
#include <limits.h>


int xor_crpty(char* Nome)
{
    signed int ResultadoXOR; // eax
    signed int TamanhoNome; // ebp
    signed int result;
    signed int v3; // esi
    char key[] = "CrackMe1";



    TamanhoNome = strlen(Nome);
    printf("Resultado =\n");
    for (v3 = 0; v3 < TamanhoNome; ++v3)
    {
        result = Nome[v3] ^= key[v3];
        printf("%02X", result & 0xF);
    }
    return 0;
}

int main()
{

    char Nome[SCHAR_MAX] = { 0 };

    printf("Digite qual String Quer Passar No Calculo: ");
    scanf_s("%s", Nome, _countof(Nome));

    int resultado = xor_crpty(Nome);

    
}

