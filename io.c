//****************************************************************************//
//  Copyright   neusoft
/// @file       io.cpp
/// @brief      io
/// @author     xuhao
/// @date       20151020
/// @note       io
//****************************************************************************//

//****************************************************************************//
//  include
//****************************************************************************//

#include "io.h"

//****************************************************************************//
//  constant definition
//****************************************************************************//

#define FILE_PATH "test.txt"

//****************************************************************************//
//  macro function definition
//****************************************************************************//

//****************************************************************************//
//  enumerate definition
//****************************************************************************//

//****************************************************************************//
//  structure definition
//****************************************************************************//

//****************************************************************************//
//  private function declaration
//****************************************************************************//

//****************************************************************************//
//  public function definition
//****************************************************************************//

////////////////////////////////////////////////////////////////////////////////
//  function        output
/// @brief          write i1_str to file i1_filepath
/// @note           write i1_str to file i1_filepath
/// @param[in]      i1_str              the string to be writed
/// @param[in]      i1_filepath         the filepath to write
/// @retval         
/// @author         xuhao
/// @date           20150930
////////////////////////////////////////////////////////////////////////////////
void stroutput(int8_t *s8Str, int8_t *s8Filepath)
{
    FILE *fp;

    if ((fp = fopen(s8Filepath, "a")) == NULL)
    {
        printf("cannot open file!");
        return;
    }

    fprintf(fp, "%s\n", s8Str);

    fclose(fp);

    return;
}

int32_t output(uint8_t *pOutput, int32_t size)
{
    int32_t i = 0;

    if (NULL == pOutput)
    {
        return -1;
    }

    FILE* fp = fopen("Cube.txt", "w");
    if (fp == NULL)
    {
        printf("File can't be created\n");
        fclose(fp);
        return -1;
    }

    for (i = 0; i < size; ++i)
    {
        switch (pOutput[i])
        {
        case 0:
            fprintf(fp, "   ");
            break;
        case 1:
            fprintf(fp, " Gr");
            break;
        case 2:
            fprintf(fp, " Bl");
            break;
        case 3:
            fprintf(fp, " Wh");
            break;
        case 4:
            fprintf(fp, " Ye");
            break;
        case 5:
            fprintf(fp, " Re");
            break;
        case 6:
            fprintf(fp, " Or");
            break;
        case 7:
            fprintf(fp, "\n");
            break;
        default:
            break;
        }
    }

    fprintf(fp, "\n");

    fclose(fp);

    return 0;
}