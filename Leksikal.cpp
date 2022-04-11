#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

using namespace std;

bool isPunctuator(char ch)                  //periksa apakah karakter yang diberikan adalah tanda baca atau bukan
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
        ch == '&' || ch == '|')
        {
            return true;
        }
    return false;
}

bool validIdentifier(char* str)                     //periksa apakah pengenal yang diberikan valid atau tidak
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isPunctuator(str[0]) == true)
        {
            return false;
        }                                   //jika karakter pertama dari string adalah digit atau karakter khusus, pengidentifikasi tidak valid
    int a,len = strlen(str);
    if (len == 1)
    {
        return true;
    }                                       //jika panjangnya satu, validasi sudah selesai, maka kembalikan true
    else
    {
    for (a = 1 ; a < len ; a++)                     //pengenal tidak boleh berisi karakter khusus
    {
        if (isPunctuator(str[a]) == true)
        {
            return false;
        }
    }
    }
    return true;
}

bool isOperator(char ch)                            //periksa apakah karakter yang diberikan adalah operator atau bukan
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=' || ch == '|' || ch == '&')
    {
       return true;
    }
    return false;
}

bool isKeyword(char *str)                       //periksa apakah substring yang diberikan adalah kata kunci atau bukan
{
    if (!strcmp(str, "if") || !strcmp(str, "else") ||
        !strcmp(str, "while") || !strcmp(str, "do") ||
        !strcmp(str, "break") ||  !strcmp(str, "continue")
        || !strcmp(str, "int") || !strcmp(str, "double")
        || !strcmp(str, "float") || !strcmp(str, "return")
        || !strcmp(str, "char") || !strcmp(str, "case")
        || !strcmp(str, "long") || !strcmp(str, "short")
        || !strcmp(str, "typedef") || !strcmp(str, "switch")
        || !strcmp(str, "unsigned") || !strcmp(str, "void")
        || !strcmp(str, "static") || !strcmp(str, "struct")
        || !strcmp(str, "sizeof") || !strcmp(str,"long")
        || !strcmp(str, "volatile") || !strcmp(str, "typedef")
        || !strcmp(str, "enum") || !strcmp(str, "const")
        || !strcmp(str, "union") || !strcmp(str, "extern")
        || !strcmp(str,"bool"))
        {
            return true;
        }
    else
    {
       return false;
    }
}

bool isNumber(char* str)                            //periksa apakah substring yang diberikan adalah angka atau bukan
{
    int b, len = strlen(str),numOfDecimal = 0;
    if (len == 0)
    {
        return false;
    }
    for (b = 0 ; b < len ; b++)
    {
        if (numOfDecimal > 1 && str[b] == '.')
        {
            return false;
        } else if (numOfDecimal <= 1)
        {
            numOfDecimal++;
        }
        if (str[b] != '0' && str[b] != '1' && str[b] != '2'
            && str[b] != '3' && str[b] != '4' && str[b] != '5'
            && str[b] != '6' && str[b] != '7' && str[b] != '8'
            && str[b] != '9' || (str[b] == '-' && b > 0))
            {
                return false;
            }
    }
    return true;
}

char* subString(char* realStr, int l, int c)                //ekstrak substring yang diperlukan dari string utama
{
    int d;

    char* str = (char*) malloc(sizeof(char) * (c - l + 2));

    for (d = l; d <= c; d++)
    {
        str[d - l] = realStr[d];
        str[c - l + 1] = '\0';
    }
    return str;
}

void parse(char* str)                       //menguraikan ekspresi
{
    int left = 0, right = 0;
    int len = strlen(str);
    while (right <= len && left <= right) {
        if (isPunctuator(str[right]) == false)          //jika karakter adalah angka atau alfabet
            {
                right++;
            }

        if (isPunctuator(str[right]) == true && left == right)      //jika karakter adalah tanda baca
            {
            if (isOperator(str[right]) == true)
            {
                std::cout<< str[right] <<" adalah sebuah operator\n";
            }
            right++;
            left = right;
            } else if (isPunctuator(str[right]) == true && left != right
                   || (right == len && left != right))          //periksa apakah substring yang diuraikan adalah kata kunci atau pengenal atau nomor
            {
            char* sub = subString(str, left, right - 1);   //ekstrak substring

            if (isKeyword(sub) == true)
                        {
                            cout<< sub <<" adalah sebuah kata kunci\n";
                        }
            else if (isNumber(sub) == true)
                        {
                            cout<< sub <<" adalah sebuah angka atau bilangan\n";
                        }
            else if (validIdentifier(sub) == true
                     && isPunctuator(str[right - 1]) == false)
                     {
                         cout<< sub <<" adalah pengidentifikasi yang valid\n";
                     }
            else if (validIdentifier(sub) == false
                     && isPunctuator(str[right - 1]) == false)
                     {
                         cout<< sub <<" adalah pengidentifikasi yang tidak valid\n";
                     }

            left = right;
            }
    }
    return;
}

int main()
{
	cout << "- - - - - PROGRAM SCAN SEDERHANA - - - - -" <<"\n\n";
    char e[20] = "int x = 2y - z + 5";
    char f[20] = "int a = 5b x 3 : c";
    parse(e);
    parse(f);
    return 0;
}

