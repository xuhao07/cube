#include "cube.h"

// step operation kind table
const S_STEPOPERATION S_STEPOPERATION_TABLE[] = 
{
    {E_AXIS_Y, E_DIR_CW, {0, 0, 1}, "U",    1},
    {E_AXIS_Y, E_DIR_CW, {0, 1, 1}, "u",    1},
    {E_AXIS_Y, E_DIR_CW, {1, 1, 1}, "y",    0},
    {E_AXIS_Y, E_DIR_CW, {0, 1, 0}, "MU",   2},
    {E_AXIS_Y, E_DIR_CW, {1, 0, 0}, "D\'",  1},
    {E_AXIS_Y, E_DIR_CW, {1, 1, 0}, "d\'",  1},
    {E_AXIS_Z, E_DIR_CW, {0, 0, 1}, "F",    1},
    {E_AXIS_Z, E_DIR_CW, {0, 1, 1}, "f",    1},
    {E_AXIS_Z, E_DIR_CW, {1, 1, 1}, "z",    0},
    {E_AXIS_Z, E_DIR_CW, {0, 1, 0}, "MF",   2},
    {E_AXIS_Z, E_DIR_CW, {1, 0, 0}, "B\'",  1},
    {E_AXIS_Z, E_DIR_CW, {1, 1, 0}, "b\'",  1},
    {E_AXIS_X, E_DIR_CW, {1, 0, 0}, "L\'",  1},
    {E_AXIS_X, E_DIR_CW, {1, 1, 0}, "l\'",  1},
    {E_AXIS_X, E_DIR_CW, {0, 0, 1}, "R",    1},
    {E_AXIS_X, E_DIR_CW, {0, 1, 1}, "r",    1},
    {E_AXIS_X, E_DIR_CW, {1, 1, 1}, "x",    0},
    {E_AXIS_X, E_DIR_CW, {0, 1, 0}, "MR",   2},
    {E_AXIS_Y, E_DIR_ANTICW, {0, 0, 1}, "U\'",  1},
    {E_AXIS_Y, E_DIR_ANTICW, {0, 1, 1}, "u\'",  1},
    {E_AXIS_Y, E_DIR_ANTICW, {1, 1, 1}, "y\'",  0},
    {E_AXIS_Y, E_DIR_ANTICW, {0, 1, 0}, "MU\'", 2},
    {E_AXIS_Y, E_DIR_ANTICW, {1, 0, 0}, "D",    1},
    {E_AXIS_Y, E_DIR_ANTICW, {1, 1, 0}, "d",    1},
    {E_AXIS_Z, E_DIR_ANTICW, {0, 0, 1}, "F\'",  1},
    {E_AXIS_Z, E_DIR_ANTICW, {0, 1, 1}, "f\'",  1},
    {E_AXIS_Z, E_DIR_ANTICW, {1, 1, 1}, "z\'",  0},
    {E_AXIS_Z, E_DIR_ANTICW, {0, 1, 0}, "MF\'", 2},
    {E_AXIS_Z, E_DIR_ANTICW, {1, 0, 0}, "B",    1},
    {E_AXIS_Z, E_DIR_ANTICW, {1, 1, 0}, "b",    1},
    {E_AXIS_X, E_DIR_ANTICW, {1, 0, 0}, "L",    1},
    {E_AXIS_X, E_DIR_ANTICW, {1, 1, 0}, "l",    1},
    {E_AXIS_X, E_DIR_ANTICW, {0, 0, 1}, "R\'",  1},
    {E_AXIS_X, E_DIR_ANTICW, {0, 1, 1}, "r\'",  1},
    {E_AXIS_X, E_DIR_ANTICW, {1, 1, 1}, "x\'",  0},
    {E_AXIS_X, E_DIR_ANTICW, {0, 1, 0}, "MR\'", 2},
};

const char *apColor[E_COL_NUM] = {"Gr ", "Bl ", "Wh ", "Ye ", "Re ", "Or "};

const int32_t s32MaxLayer = LAYER_NUM - 1;

// malloc memory, call freeCube to free
int32_t createCube(S_CUBE **ppCube)
{
    S_CUBE *pCube = NULL;
    int32_t i = 0;
    int32_t j = 0;
    int32_t k = 0;
    int32_t index = 0;

    if (NULL == ppCube)
    {
        printf("%s INPUT ERROR!!\n", __FUNCTION__);
        return EINVAL;
    }

    if (NULL != *ppCube)
    {
        printf("%s the cube is already exists!! free old, create new.\n", __FUNCTION__);
        freeCube(ppCube);
    }

    pCube = (S_CUBE *)malloc(sizeof(S_CUBE));
    if (NULL == pCube)
    {
        printf("%s MALLOC ERROR\n", __FUNCTION__);
        return ENOMEM;
    }
    memset(pCube, 0x00, sizeof(S_CUBE));

    // alloc space and init color(original cube)
    for (i = 0; i < LAYER_NUM; ++i)
    {
        for (j = 0; j < LAYER_NUM; ++j)
        {
            // left faces
            pCube->box[0][i][j].face[E_AXIS_X] = pCube->faceBuffer + (index++);
            pCube->box[0][i][j].face[E_AXIS_X]->color = E_COL_RED;

            // right faces
            pCube->box[s32MaxLayer][i][j].face[E_AXIS_X] = pCube->faceBuffer + (index++);
            pCube->box[s32MaxLayer][i][j].face[E_AXIS_X]->color = E_COL_ORANGE;

            // down faces
            pCube->box[i][0][j].face[E_AXIS_Y] = pCube->faceBuffer + (index++);
            pCube->box[i][0][j].face[E_AXIS_Y]->color = E_COL_BLUE;

            // up faces
            pCube->box[i][s32MaxLayer][j].face[E_AXIS_Y] = pCube->faceBuffer + (index++);
            pCube->box[i][s32MaxLayer][j].face[E_AXIS_Y]->color = E_COL_GREEN;

            // back faces
            pCube->box[i][j][0].face[E_AXIS_Z] = pCube->faceBuffer + (index++);
            pCube->box[i][j][0].face[E_AXIS_Z]->color = E_COL_YELLOW;

            // front faces
            pCube->box[i][j][s32MaxLayer].face[E_AXIS_Z] = pCube->faceBuffer + (index++);
            pCube->box[i][j][s32MaxLayer].face[E_AXIS_Z]->color = E_COL_WHITE;
        }
    }

    // creat link
    for (i = 0; i < LAYER_NUM; ++i)
    {
        for (j = 0; j < LAYER_NUM; ++j)
        {
            for (k = 0; k < LAYER_NUM; ++k)
            {
                // axis_x(0:left; max layer:right) faces
                if ((i == 0) || (i == s32MaxLayer))
                {
                    pCube->box[i][j][k].face[E_AXIS_X]->pNext[E_AXIS_X][E_DIR_CW] = pCube->box[i][k][s32MaxLayer-j].face[E_AXIS_X];
                    pCube->box[i][j][k].face[E_AXIS_X]->pNext[E_AXIS_X][E_DIR_ANTICW] = pCube->box[i][s32MaxLayer-k][j].face[E_AXIS_X];
                    pCube->box[i][j][k].face[E_AXIS_X]->pNext[E_AXIS_Y][E_DIR_CW] = pCube->box[s32MaxLayer-k][j][i].face[E_AXIS_Z];
                    pCube->box[i][j][k].face[E_AXIS_X]->pNext[E_AXIS_Y][E_DIR_ANTICW] = pCube->box[k][j][s32MaxLayer-i].face[E_AXIS_Z];
                    pCube->box[i][j][k].face[E_AXIS_X]->pNext[E_AXIS_Z][E_DIR_CW] = pCube->box[j][s32MaxLayer-i][k].face[E_AXIS_Y];
                    pCube->box[i][j][k].face[E_AXIS_X]->pNext[E_AXIS_Z][E_DIR_ANTICW] = pCube->box[s32MaxLayer-j][i][k].face[E_AXIS_Y];
                }
                // axis_y(0:down; max layer:up) faces
                if ((j == 0) || (j == s32MaxLayer))
                {
                    pCube->box[i][j][k].face[E_AXIS_Y]->pNext[E_AXIS_X][E_DIR_CW] = pCube->box[i][k][s32MaxLayer-j].face[E_AXIS_Z];
                    pCube->box[i][j][k].face[E_AXIS_Y]->pNext[E_AXIS_X][E_DIR_ANTICW] = pCube->box[i][s32MaxLayer-k][j].face[E_AXIS_Z];
                    pCube->box[i][j][k].face[E_AXIS_Y]->pNext[E_AXIS_Y][E_DIR_CW] = pCube->box[s32MaxLayer-k][j][i].face[E_AXIS_Y];
                    pCube->box[i][j][k].face[E_AXIS_Y]->pNext[E_AXIS_Y][E_DIR_ANTICW] = pCube->box[k][j][s32MaxLayer-i].face[E_AXIS_Y];
                    pCube->box[i][j][k].face[E_AXIS_Y]->pNext[E_AXIS_Z][E_DIR_CW] = pCube->box[j][s32MaxLayer-i][k].face[E_AXIS_X];
                    pCube->box[i][j][k].face[E_AXIS_Y]->pNext[E_AXIS_Z][E_DIR_ANTICW] = pCube->box[s32MaxLayer-j][i][k].face[E_AXIS_X];
                }
                // axis_z(0:back; max layer:front) faces
                if ((k == 0) || (k == s32MaxLayer))
                {
                    pCube->box[i][j][k].face[E_AXIS_Z]->pNext[E_AXIS_X][E_DIR_CW] = pCube->box[i][k][s32MaxLayer-j].face[E_AXIS_Y];
                    pCube->box[i][j][k].face[E_AXIS_Z]->pNext[E_AXIS_X][E_DIR_ANTICW] = pCube->box[i][s32MaxLayer-k][j].face[E_AXIS_Y];
                    pCube->box[i][j][k].face[E_AXIS_Z]->pNext[E_AXIS_Y][E_DIR_CW] = pCube->box[s32MaxLayer-k][j][i].face[E_AXIS_X];
                    pCube->box[i][j][k].face[E_AXIS_Z]->pNext[E_AXIS_Y][E_DIR_ANTICW] = pCube->box[k][j][s32MaxLayer-i].face[E_AXIS_X];
                    pCube->box[i][j][k].face[E_AXIS_Z]->pNext[E_AXIS_Z][E_DIR_CW] = pCube->box[j][s32MaxLayer-i][k].face[E_AXIS_Z];
                    pCube->box[i][j][k].face[E_AXIS_Z]->pNext[E_AXIS_Z][E_DIR_ANTICW] = pCube->box[s32MaxLayer-j][i][k].face[E_AXIS_Z];
                }
            }
        }
    }

    *ppCube = pCube;

    return 0;
}

// free cube
int32_t freeCube(S_CUBE **ppCube)
{
    if (NULL == ppCube)
    {
        printf("%s INPUT ERROR!!\n", __FUNCTION__);
        return -1;
    }

    if (NULL == *ppCube)
    {
        printf("%s the cube is already free!!\n", __FUNCTION__);
        return -1;
    }

    // free spaces
    free(*ppCube);
    *ppCube = NULL;

    return 0;
}

// output cube to file
int32_t outputCube(S_CUBE *pCube, char *pcPath)
{
    int32_t i = 0;
    int32_t j = 0;
    int32_t cnt = 0;

    if (NULL == pCube)
    {
        printf("%s INPUT ERROR!!\n", __FUNCTION__);
        return -1;
    }

    FILE* fp = fopen(pcPath, "a");
    if (fp == NULL)
    {
        printf("File can't be added\n");
        fclose(fp);
        return -1;
    }

    // Line 1~9
    for (i = 0; i < 9; ++i)
    {
        if (i < 3)
        {
            for (j = 0; j < 3; ++j)
            {
                // 3 for left face up space
                fprintf(fp, "   ");
            }
            fprintf(fp, "%s", apColor[pCube->box[0][2][i-0].face[E_AXIS_Y]->color]);
            fprintf(fp, "%s", apColor[pCube->box[1][2][i-0].face[E_AXIS_Y]->color]);
            fprintf(fp, "%s", apColor[pCube->box[2][2][i-0].face[E_AXIS_Y]->color]);
        }
        else if (i < 6)
        {
            fprintf(fp, "%s", apColor[pCube->box[0][2-(i-3)][0].face[E_AXIS_X]->color]);
            fprintf(fp, "%s", apColor[pCube->box[0][2-(i-3)][1].face[E_AXIS_X]->color]);
            fprintf(fp, "%s", apColor[pCube->box[0][2-(i-3)][2].face[E_AXIS_X]->color]);
            fprintf(fp, "%s", apColor[pCube->box[0][2-(i-3)][2].face[E_AXIS_Z]->color]);
            fprintf(fp, "%s", apColor[pCube->box[1][2-(i-3)][2].face[E_AXIS_Z]->color]);
            fprintf(fp, "%s", apColor[pCube->box[2][2-(i-3)][2].face[E_AXIS_Z]->color]);
            fprintf(fp, "%s", apColor[pCube->box[2][2-(i-3)][2].face[E_AXIS_X]->color]);
            fprintf(fp, "%s", apColor[pCube->box[2][2-(i-3)][1].face[E_AXIS_X]->color]);
            fprintf(fp, "%s", apColor[pCube->box[2][2-(i-3)][0].face[E_AXIS_X]->color]);
            fprintf(fp, "%s", apColor[pCube->box[2][2-(i-3)][0].face[E_AXIS_Z]->color]);
            fprintf(fp, "%s", apColor[pCube->box[1][2-(i-3)][0].face[E_AXIS_Z]->color]);
            fprintf(fp, "%s", apColor[pCube->box[0][2-(i-3)][0].face[E_AXIS_Z]->color]);
        }
        else
        {
            for (j = 0; j < 3; ++j)
            {
                // 3 for left face down space
                fprintf(fp, "   ");
            }
            fprintf(fp, "%s", apColor[pCube->box[0][0][2-(i-6)].face[E_AXIS_Y]->color]);
            fprintf(fp, "%s", apColor[pCube->box[1][0][2-(i-6)].face[E_AXIS_Y]->color]);
            fprintf(fp, "%s", apColor[pCube->box[2][0][2-(i-6)].face[E_AXIS_Y]->color]);
        }

        fprintf(fp, "\n");
    }

    fprintf(fp, "\n");

    fclose(fp);

    return 0;
}

// change string to step operation
int32_t chgstepin(uint8_t *pStr, int32_t strsize, S_STEPOPERATION *pStep, int32_t *pStepnum)
{
    int32_t s32Ret = 0;
    int32_t i = 0;
    int32_t j = 0;
    int32_t strsizecnt = 0;
    int32_t stepnumcnt = 0;
    uint8_t stepname[STEPLEN_MAX];
    uint8_t stepnamelen = 0;

    if ((NULL == pStr) || (NULL == pStep))
    {
        printf("%s INPUT ERROR!!\n", __FUNCTION__);
        return -1;
    }

    memset(&stepname, 0x00, sizeof(stepname));

    for (i = 0; i < strsize; ++i)
    {
        stepname[stepnamelen++] = pStr[i];
        // judge one step operation end
        if ((pStr[i] == '\'') || (i == strsize - 1) || ((pStr[i] != 'M') && (pStr[i + 1] != '\'')))
        {
            // find the step operation from step operation table
            for (j = 0; j < sizeof(S_STEPOPERATION_TABLE)/sizeof(S_STEPOPERATION); ++j)
            {
                if ((stepnamelen == strlen((char*)S_STEPOPERATION_TABLE[j].pcStepname)) && (0 == memcmp(&stepname, S_STEPOPERATION_TABLE[j].pcStepname, stepnamelen)))
                {
                    memcpy(&pStep[stepnumcnt++], &S_STEPOPERATION_TABLE[j], sizeof(S_STEPOPERATION));
                    memset(&stepname, 0x00, sizeof(stepname));
                    stepnamelen = 0;
                    break;
                }
            }

            // if cant find the step operation from step operation table, print error
            if (0 != stepnamelen)
            {
                printf("%s INPUT STRING ERROR!\n", __FUNCTION__);
                memset(pStep, 0x00, 10000);
                return -1;
            }
        }
    }

    *pStepnum = stepnumcnt;

    return 0;
}

// change step operation to string
int32_t chgstepout(S_STEPOPERATION *pStep, int32_t stepnum, uint8_t *pStr, int32_t *pStrsize)
{
    int32_t s32Ret = 0;
    int32_t i = 0;
    int32_t j = 0;
    int32_t strsizecnt = 0;

    if ((NULL == pStep) || (NULL == pStr))
    {
        printf("%s INPUT ERROR!!\n", __FUNCTION__);
        return -1;
    }

    for (i = 0; i < stepnum; ++i)
    {
        // TBD
        for (j = 0; j < (int32_t)strlen(pStep[i].pcStepname); ++j)
        {
            // write step operation name to string
            pStr[strsizecnt++] = pStep[i].pcStepname[j];
        }
    }

    *pStrsize = strsizecnt;

    return 0;
}

// change cube multi step operation
int32_t chgcube_mutlstep(S_CUBE *pCube, S_STEPOPERATION *pStep, int32_t stepnum)
{
    int32_t s32Ret = 0;
    int32_t i = 0;

    for (i = 0; i < stepnum; ++i)
    {
        chgcube_onestep(pCube, &pStep[i]);
    }

    return 0;
}

// change cube single step operation
int32_t chgcube_onestep(S_CUBE *pCube, S_STEPOPERATION *pStep)
{
    int32_t s32Ret = 0;
    S_CUBE *pCubetmp = NULL;
    int32_t i = 0;
    int32_t j = 0;
    int32_t k = 0;

    if ((NULL == pCube) || (NULL == pStep))
    {
        printf("%s INPUT ERROR!!\n", __FUNCTION__);
        return -1;
    }

    // create temp cube, copy color to the temp cube
    s32Ret = createCube(&pCubetmp);

    for (i = 0; i < LAYER_NUM; ++i)
    {
        for (j = 0; j < LAYER_NUM; ++j)
        {
            for (k = 0; k < LAYER_NUM; ++k)
            {
                if (i != 1)
                {
                    pCubetmp->box[i][j][k].face[E_AXIS_X]->color = pCube->box[i][j][k].face[E_AXIS_X]->color;
                }
                if (j != 1)
                {
                    pCubetmp->box[i][j][k].face[E_AXIS_Y]->color = pCube->box[i][j][k].face[E_AXIS_Y]->color;
                }
                if (k != 1)
                {
                    pCubetmp->box[i][j][k].face[E_AXIS_Z]->color = pCube->box[i][j][k].face[E_AXIS_Z]->color;
                }
            }
        }
    }

    // change cube
    for (i = 0; i < LAYER_NUM; ++i)
    {
        if ((pStep->axis == E_AXIS_X) && (!pStep->layerchgflg[i]))
        {
            continue;
        }
        for (j = 0; j < LAYER_NUM; ++j)
        {
            if ((pStep->axis == E_AXIS_Y) && (!pStep->layerchgflg[j]))
            {
                continue;
            }
            for (k = 0; k < LAYER_NUM; ++k)
            {
                if ((pStep->axis == E_AXIS_Z) && (!pStep->layerchgflg[k]))
                {
                    continue;
                }
                if (((i == 0) || (i == s32MaxLayer)) && (pCube->box[i][j][k].face[E_AXIS_X]->pNext[pStep->axis][pStep->direction]))
                {
                    pCube->box[i][j][k].face[E_AXIS_X]->pNext[pStep->axis][pStep->direction]->color = pCubetmp->box[i][j][k].face[E_AXIS_X]->color;
                }
                if (((j == 0) || (j == s32MaxLayer)) && (pCube->box[i][j][k].face[E_AXIS_Y]->pNext[pStep->axis][pStep->direction]))
                {
                    pCube->box[i][j][k].face[E_AXIS_Y]->pNext[pStep->axis][pStep->direction]->color = pCubetmp->box[i][j][k].face[E_AXIS_Y]->color;
                }
                if (((k == 0) || (k == s32MaxLayer)) && (pCube->box[i][j][k].face[E_AXIS_Z]->pNext[pStep->axis][pStep->direction]))
                {
                    pCube->box[i][j][k].face[E_AXIS_Z]->pNext[pStep->axis][pStep->direction]->color = pCubetmp->box[i][j][k].face[E_AXIS_Z]->color;
                }
            }
        }
    }

    s32Ret = freeCube(&pCubetmp);

    return 0;
}

int32_t chgcube_str(S_CUBE *pCube, uint8_t *pStr, int32_t strsize)
{
    int32_t s32Ret = 0;
    S_STEPOPERATION step[10000];
    int32_t stepnum = 0;

    memset(&step, 0x00, sizeof(step));

    if ((NULL == pCube) || (NULL == pStr))
    {
        printf("%s INPUT ERROR!!\n", __FUNCTION__);
        return -1;
    }

    chgstepin(pStr, strsize, step, &stepnum);

    chgcube_mutlstep(pCube, step, stepnum);

    return 0;
}

int32_t sevenstep(S_CUBE *pCube, uint8_t *pStr, int32_t *pStrsize)
{
    int32_t s32Ret = 0;

    if (NULL == pCube)
    {
        printf("%s INPUT ERROR!!\n", __FUNCTION__);
        return -1;
    }

    sevenstep_1(pCube, pStr, pStrsize);
    stroutput(pStr, "/mnt/d/platform/xuhao/output.txt");
    outputCube(pCube, "/mnt/d/platform/xuhao/output.txt");
    sevenstep_2(pCube, pStr, pStrsize);
    stroutput(pStr, "/mnt/d/platform/xuhao/output.txt");
    outputCube(pCube, "/mnt/d/platform/xuhao/output.txt");
    sevenstep_3(pCube, pStr, pStrsize);
    stroutput(pStr, "/mnt/d/platform/xuhao/output.txt");
    outputCube(pCube, "/mnt/d/platform/xuhao/output.txt");
    sevenstep_4(pCube, pStr, pStrsize);
    stroutput(pStr, "/mnt/d/platform/xuhao/output.txt");
    outputCube(pCube, "/mnt/d/platform/xuhao/output.txt");
    sevenstep_5(pCube, pStr, pStrsize);
    sevenstep_6(pCube, pStr, pStrsize);
    sevenstep_7(pCube, pStr, pStrsize);

    return s32Ret;
}

int32_t sevenstep_1(S_CUBE *pCube, uint8_t *pStr, int32_t *pStrsize)
{
    int32_t i = 0;
    uint8_t str[10];    // $)AWn4s98vWV7{
    int32_t strsize = 0;

    if ((NULL == pCube) || (NULL == pStr) || (NULL == pStrsize))
    {
        printf("%s INPUT ERROR!!\n", __FUNCTION__);
        return -1;
    }

    memset(str, 0x00, sizeof(str));

    for (i = 0; i < 4; ++i)
    {
        // LD -> DF
        if ((pCube->box[0][0][1].face[E_AXIS_X]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][0][1].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(LD_TO_DF);
            memcpy(str, LD_TO_DF, strsize);
        }
        // DL -> DF
        else if ((pCube->box[0][0][1].face[E_AXIS_Y]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][0][1].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(DL_TO_DF);
            memcpy(str, DL_TO_DF, strsize);
        }
        // LU -> DF
        else if ((pCube->box[0][2][1].face[E_AXIS_X]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][1].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(LU_TO_DF);
            memcpy(str, LU_TO_DF, strsize);
        }
        // UL -> DF
        else if ((pCube->box[0][2][1].face[E_AXIS_Y]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][1].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(UL_TO_DF);
            memcpy(str, UL_TO_DF, strsize);
        }
        // RD -> DF
        else if ((pCube->box[2][0][1].face[E_AXIS_X]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][0][1].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(RD_TO_DF);
            memcpy(str, RD_TO_DF, strsize);
        }
        // DR -> DF
        else if ((pCube->box[2][0][1].face[E_AXIS_Y]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][0][1].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(DR_TO_DF);
            memcpy(str, DR_TO_DF, strsize);
        }
        // RU -> DF
        else if ((pCube->box[2][2][1].face[E_AXIS_X]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][1].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(RU_TO_DF);
            memcpy(str, RU_TO_DF, strsize);
        }
        // UR -> DF
        else if ((pCube->box[2][2][1].face[E_AXIS_Y]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][1].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(UR_TO_DF);
            memcpy(str, UR_TO_DF, strsize);
        }
        // LB -> DF
        else if ((pCube->box[0][1][0].face[E_AXIS_X]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][1][0].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(LB_TO_DF);
            memcpy(str, LB_TO_DF, strsize);
        }
        // BL -> DF
        else if ((pCube->box[0][1][0].face[E_AXIS_Z]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][1][0].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(BL_TO_DF);
            memcpy(str, BL_TO_DF, strsize);
        }
        // LF -> DF
        else if ((pCube->box[0][1][2].face[E_AXIS_X]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][1][2].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(LF_TO_DF);
            memcpy(str, LF_TO_DF, strsize);
        }
        // FL -> DF
        else if ((pCube->box[0][1][2].face[E_AXIS_Z]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][1][2].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(FL_TO_DF);
            memcpy(str, FL_TO_DF, strsize);
        }
        // RB -> DF
        else if ((pCube->box[2][1][0].face[E_AXIS_X]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][1][0].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(RB_TO_DF);
            memcpy(str, RB_TO_DF, strsize);
        }
        // BR -> DF
        else if ((pCube->box[2][1][0].face[E_AXIS_Z]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][1][0].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(BR_TO_DF);
            memcpy(str, BR_TO_DF, strsize);
        }
        // RF -> DF
        else if ((pCube->box[2][1][2].face[E_AXIS_X]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][1][2].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(RF_TO_DF);
            memcpy(str, RF_TO_DF, strsize);
        }
        // FR -> DF
        else if ((pCube->box[2][1][2].face[E_AXIS_Z]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][1][2].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(FR_TO_DF);
            memcpy(str, FR_TO_DF, strsize);
        }
        // DB -> DF
        else if ((pCube->box[1][0][0].face[E_AXIS_Y]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[1][0][0].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(DB_TO_DF);
            memcpy(str, DB_TO_DF, strsize);
        }
        // BD -> DF
        else if ((pCube->box[1][0][0].face[E_AXIS_Z]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[1][0][0].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(BD_TO_DF);
            memcpy(str, BD_TO_DF, strsize);
        }
        // DF -> DF
        else if ((pCube->box[1][0][2].face[E_AXIS_Y]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[1][0][2].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            // do nothing
        }
        // FD -> DF
        else if ((pCube->box[1][0][2].face[E_AXIS_Z]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[1][0][2].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(FD_TO_DF);
            memcpy(str, FD_TO_DF, strsize);
        }
        // UB -> DF
        else if ((pCube->box[1][2][0].face[E_AXIS_Y]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[1][2][0].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(UB_TO_DF);
            memcpy(str, UB_TO_DF, strsize);
        }
        // BU -> DF
        else if ((pCube->box[1][2][0].face[E_AXIS_Z]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[1][2][0].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(BU_TO_DF);
            memcpy(str, BU_TO_DF, strsize);
        }
        // UF -> DF
        else if ((pCube->box[1][2][2].face[E_AXIS_Y]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[1][2][2].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(UF_TO_DF);
            memcpy(str, UF_TO_DF, strsize);
        }
        // FU -> DF
        else if ((pCube->box[1][2][2].face[E_AXIS_Z]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[1][2][2].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(FU_TO_DF);
            memcpy(str, FU_TO_DF, strsize);
        }
        else
        {
            printf("%s ERROR, CUBE IS BROKEN\n", __FUNCTION__);
            return -1;
        }

        memcpy(str + strsize, "y\'", 2);
        strsize += 2;

        chgcube_str(pCube, str, strsize);

        memcpy(pStr + (*pStrsize), str, strsize);
        *pStrsize += strsize;

        memset(str, 0x00, sizeof(str));
        strsize = 0;
    }

    return 0;
}

int32_t sevenstep_2(S_CUBE *pCube, uint8_t *pStr, int32_t *pStrsize)
{
    int32_t i = 0;
    uint8_t str[20];    // $)AWn4s98vWV7{
    int32_t strsize = 0;

    if ((NULL == pCube) || (NULL == pStr) || (NULL == pStrsize))
    {
        printf("%s INPUT ERROR!!\n", __FUNCTION__);
        return -1;
    }

    memset(str, 0x00, sizeof(str));

    for (i = 0; i < 4; ++i)
    {
        // LDB -> RDF
        if ((pCube->box[0][0][0].face[E_AXIS_X]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][0][0].face[E_AXIS_Y]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][0][0].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(LDB_TO_RDF);
            memcpy(str, LDB_TO_RDF, strsize);
        }
        // DBL -> RDF
        else if ((pCube->box[0][0][0].face[E_AXIS_Y]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][0][0].face[E_AXIS_Z]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][0][0].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(DBL_TO_RDF);
            memcpy(str, DBL_TO_RDF, strsize);
        }
        // BLD -> RDF
        else if ((pCube->box[0][0][0].face[E_AXIS_Z]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][0][0].face[E_AXIS_X]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][0][0].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(BLD_TO_RDF);
            memcpy(str, BLD_TO_RDF, strsize);
        }
        // LFD -> RDF
        else if ((pCube->box[0][0][2].face[E_AXIS_X]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][0][2].face[E_AXIS_Z]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][0][2].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(LFD_TO_RDF);
            memcpy(str, LFD_TO_RDF, strsize);
        }
        // FDL -> RDF
        else if ((pCube->box[0][0][2].face[E_AXIS_Z]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][0][2].face[E_AXIS_Y]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][0][2].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(FDL_TO_RDF);
            memcpy(str, FDL_TO_RDF, strsize);
        }
        // DLF -> RDF
        else if ((pCube->box[0][0][2].face[E_AXIS_Y]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][0][2].face[E_AXIS_X]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][0][2].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(DLF_TO_RDF);
            memcpy(str, DLF_TO_RDF, strsize);
        }
        // LBU -> RDF
        else if ((pCube->box[0][2][0].face[E_AXIS_X]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][2][0].face[E_AXIS_Z]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][0].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(LBU_TO_RDF);
            memcpy(str, LBU_TO_RDF, strsize);
        }
        // BUL -> RDF
        else if ((pCube->box[0][2][0].face[E_AXIS_Z]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][2][0].face[E_AXIS_Y]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][0].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(BUL_TO_RDF);
            memcpy(str, BUL_TO_RDF, strsize);
        }
        // ULB -> RDF
        else if ((pCube->box[0][2][0].face[E_AXIS_Y]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][2][0].face[E_AXIS_X]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][0].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(ULB_TO_RDF);
            memcpy(str, ULB_TO_RDF, strsize);
        }
        // LUF -> RDF
        else if ((pCube->box[0][2][2].face[E_AXIS_X]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][2][2].face[E_AXIS_Y]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][2].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(LUF_TO_RDF);
            memcpy(str, LUF_TO_RDF, strsize);
        }
        // UFL -> RDF
        else if ((pCube->box[0][2][2].face[E_AXIS_Y]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][2][2].face[E_AXIS_Z]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][2].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(UFL_TO_RDF);
            memcpy(str, UFL_TO_RDF, strsize);
        }
        // FLU -> RDF
        else if ((pCube->box[0][2][2].face[E_AXIS_Z]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][2][2].face[E_AXIS_X]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][2].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(FLU_TO_RDF);
            memcpy(str, FLU_TO_RDF, strsize);
        }
        // RBD -> RDF
        else if ((pCube->box[2][0][0].face[E_AXIS_X]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][0][0].face[E_AXIS_Z]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][0][0].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(RBD_TO_RDF);
            memcpy(str, RBD_TO_RDF, strsize);
        }
        // BDR -> RDF
        else if ((pCube->box[2][0][0].face[E_AXIS_Z]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][0][0].face[E_AXIS_Y]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][0][0].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(BDR_TO_RDF);
            memcpy(str, BDR_TO_RDF, strsize);
        }
        // DRB -> RDF
        else if ((pCube->box[2][0][0].face[E_AXIS_Y]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][0][0].face[E_AXIS_X]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][0][0].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(DRB_TO_RDF);
            memcpy(str, DRB_TO_RDF, strsize);
        }
        // RDF -> RDF
        else if ((pCube->box[2][0][2].face[E_AXIS_X]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][0][2].face[E_AXIS_Y]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][0][2].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            // do nothing
        }
        // DFR -> RDF
        else if ((pCube->box[2][0][2].face[E_AXIS_Y]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][0][2].face[E_AXIS_Z]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][0][2].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(DFR_TO_RDF);
            memcpy(str, DFR_TO_RDF, strsize);
        }
        // FRD -> RDF
        else if ((pCube->box[2][0][2].face[E_AXIS_Z]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][0][2].face[E_AXIS_X]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][0][2].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(FRD_TO_RDF);
            memcpy(str, FRD_TO_RDF, strsize);
        }
        // RUB -> RDF
        else if ((pCube->box[2][2][0].face[E_AXIS_X]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][2][0].face[E_AXIS_Y]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][0].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(RUB_TO_RDF);
            memcpy(str, RUB_TO_RDF, strsize);
        }
        // UBR -> RDF
        else if ((pCube->box[2][2][0].face[E_AXIS_Y]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][2][0].face[E_AXIS_Z]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][0].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(UBR_TO_RDF);
            memcpy(str, UBR_TO_RDF, strsize);
        }
        // BRU -> RDF
        else if ((pCube->box[2][2][0].face[E_AXIS_Z]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][2][0].face[E_AXIS_X]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][0].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(BRU_TO_RDF);
            memcpy(str, BRU_TO_RDF, strsize);
        }
        // RFU -> RDF
        else if ((pCube->box[2][2][2].face[E_AXIS_X]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][2][2].face[E_AXIS_Z]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][2].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(RFU_TO_RDF);
            memcpy(str, RFU_TO_RDF, strsize);
        }
        // FUR -> RDF
        else if ((pCube->box[2][2][2].face[E_AXIS_Z]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][2][2].face[E_AXIS_Y]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][2].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(FUR_TO_RDF);
            memcpy(str, FUR_TO_RDF, strsize);
        }
        // URF -> RDF
        else if ((pCube->box[2][2][2].face[E_AXIS_Y]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][2][2].face[E_AXIS_X]->color == pCube->box[1][0][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][2].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(URF_TO_RDF);
            memcpy(str, URF_TO_RDF, strsize);
        }
        // ERROR
        else
        {
            printf("%s ERROR, CUBE IS BROKEN\n", __FUNCTION__);
            return -1;
        }

        memcpy(str + strsize, "y\'", 2);
        strsize += 2;

        chgcube_str(pCube, str, strsize);

        memcpy(pStr + (*pStrsize), str, strsize);
        *pStrsize += strsize;

        memset(str, 0x00, sizeof(str));
        strsize = 0;
    }

    return 0;
}

int32_t sevenstep_3(S_CUBE *pCube, uint8_t *pStr, int32_t *pStrsize)
{
    int32_t i = 0;
    uint8_t str[35];    // $)AWn4s98vWV7{
    int32_t strsize = 0;

    if ((NULL == pCube) || (NULL == pStr) || (NULL == pStrsize))
    {
        printf("%s INPUT ERROR!!\n", __FUNCTION__);
        return -1;
    }

    memset(str, 0x00, sizeof(str));

    for (i = 0; i < 4; ++i)
    {
        // LB -> RF
        if ((pCube->box[0][1][0].face[E_AXIS_X]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][1][0].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(LB_TO_RF);
            memcpy(str, LB_TO_RF, strsize);
        }
        // BL -> RF
        else if ((pCube->box[0][1][0].face[E_AXIS_Z]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][1][0].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(BL_TO_RF);
            memcpy(str, BL_TO_RF, strsize);
        }
        // LF -> RF
        else if ((pCube->box[0][1][2].face[E_AXIS_X]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][1][2].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(LF_TO_RF);
            memcpy(str, LF_TO_RF, strsize);
        }
        // FL -> RF
        else if ((pCube->box[0][1][2].face[E_AXIS_Z]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][1][2].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(FL_TO_RF);
            memcpy(str, FL_TO_RF, strsize);
        }
        // RB -> RF
        else if ((pCube->box[2][1][0].face[E_AXIS_X]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][1][0].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(RB_TO_RF);
            memcpy(str, RB_TO_RF, strsize);
        }
        // BR -> RF
        else if ((pCube->box[2][1][0].face[E_AXIS_Z]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][1][0].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(BR_TO_RF);
            memcpy(str, BR_TO_RF, strsize);
        }
        // RF -> RF
        else if ((pCube->box[2][1][2].face[E_AXIS_X]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][1][2].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            // do nothing
        }
        // FR -> RF
        else if ((pCube->box[2][1][2].face[E_AXIS_Z]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][1][2].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(FR_TO_RF);
            memcpy(str, FR_TO_RF, strsize);
        }
        // LU -> RF
        else if ((pCube->box[0][2][1].face[E_AXIS_X]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][2][1].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(LU_TO_RF);
            memcpy(str, LU_TO_RF, strsize);
        }
        // UL -> RF
        else if ((pCube->box[0][2][1].face[E_AXIS_Y]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][2][1].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(UL_TO_RF);
            memcpy(str, UL_TO_RF, strsize);
        }
        // RU -> RF
        else if ((pCube->box[2][2][1].face[E_AXIS_X]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][2][1].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(RU_TO_RF);
            memcpy(str, RU_TO_RF, strsize);
        }
        // UR -> RF
        else if ((pCube->box[2][2][1].face[E_AXIS_Y]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[2][2][1].face[E_AXIS_X]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(UR_TO_RF);
            memcpy(str, UR_TO_RF, strsize);
        }
        // UB -> RF
        else if ((pCube->box[1][2][0].face[E_AXIS_Y]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[1][2][0].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(UB_TO_RF);
            memcpy(str, UB_TO_RF, strsize);
        }
        // BU -> RF
        else if ((pCube->box[1][2][0].face[E_AXIS_Z]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[1][2][0].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(BU_TO_RF);
            memcpy(str, BU_TO_RF, strsize);
        }
        // UF -> RF
        else if ((pCube->box[1][2][2].face[E_AXIS_Y]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[1][2][2].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(UF_TO_RF);
            memcpy(str, UF_TO_RF, strsize);
        }
        // FU -> RF
        else if ((pCube->box[1][2][2].face[E_AXIS_Z]->color == pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[1][2][2].face[E_AXIS_Y]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(FU_TO_RF);
            memcpy(str, FU_TO_RF, strsize);
        }
        // ERROR
        else
        {
            printf("%s ERROR, CUBE IS BROKEN\n", __FUNCTION__);
            return -1;
        }

        memcpy(str + strsize, "y\'", 2);
        strsize += 2;

        chgcube_str(pCube, str, strsize);

        memcpy(pStr + (*pStrsize), str, strsize);
        *pStrsize += strsize;

        memset(str, 0x00, sizeof(str));
        strsize = 0;
    }

    return 0;
}

int32_t sevenstep_4(S_CUBE *pCube, uint8_t *pStr, int32_t *pStrsize)
{
    int32_t i = 0;
    uint8_t str[30];    // $)AWn4s98vWV7{
    int32_t strsize = 0;
    uint8_t flg = 0;

    if ((NULL == pCube) || (NULL == pStr) || (NULL == pStrsize))
    {
        printf("%s INPUT ERROR!!\n", __FUNCTION__);
        return -1;
    }

    memset(str, 0x00, sizeof(str));

    for (i = 0; i < 4; ++i)
    {
        if ((pCube->box[1][2][2].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][1].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[1][2][0].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][1].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color))
        {
            flg = 1;
        }
        else if ((pCube->box[1][2][2].face[E_AXIS_Y]->color != pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][1].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[1][2][0].face[E_AXIS_Y]->color != pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][1].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color))
        {
            strsize = strlen(STEP4_COND1);
            memcpy(str, STEP4_COND1, strsize);
            flg = 1;
        }
        else if ((pCube->box[1][2][2].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][1].face[E_AXIS_Y]->color != pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[1][2][0].face[E_AXIS_Y]->color != pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][1].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color))
        {
            strsize = strlen(STEP4_COND2);
            memcpy(str, STEP4_COND2, strsize);
            flg = 1;
        }
        else if ((pCube->box[1][2][2].face[E_AXIS_Y]->color != pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][1].face[E_AXIS_Y]->color != pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[1][2][0].face[E_AXIS_Y]->color != pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][1].face[E_AXIS_Y]->color != pCube->box[1][2][1].face[E_AXIS_Y]->color))
        {
            strsize = strlen(STEP4_COND3);
            memcpy(str, STEP4_COND3, strsize);
            flg = 1;
        }

        if (flg)
        {
            chgcube_str(pCube, str, strsize);

            memcpy(pStr + (*pStrsize), str, strsize);
            *pStrsize += strsize;
            break;
        }
        else
        {
            memcpy(str, "y\'", 2);
            strsize = 2;

            chgcube_str(pCube, str, strsize);

            memcpy(pStr + (*pStrsize), str, strsize);
            *pStrsize += strsize;

            memset(str, 0x00, sizeof(str));
            strsize = 0;
        }
    }

    if (!flg)
    {
        printf("%s ERROR, CUBE IS BROKEN\n", __FUNCTION__);
        return -1;
    }

    return 0;
}

int32_t sevenstep_5(S_CUBE *pCube, uint8_t *pStr, int32_t *pStrsize)
{
    int32_t i = 0;
    uint8_t str[30];    // $)AWn4s308vWV7{
    int32_t strsize = 0;
    uint8_t flg = 0;

    if ((NULL == pCube) || (NULL == pStr) || (NULL == pStrsize))
    {
        printf("%s INPUT ERROR!!\n", __FUNCTION__);
        return -1;
    }

    memset(str, 0x00, sizeof(str));

    for (i = 0; i < 4; ++i)
    {
        if ((pCube->box[0][2][2].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][0].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][0].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][2].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color))
        {
            flg = 1;
        }
        else if ((pCube->box[0][2][2].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][0].face[E_AXIS_Z]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][0].face[E_AXIS_X]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][2].face[E_AXIS_Z]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color))
        {
            strsize = strlen(STEP5_COND1);
            memcpy(str, STEP5_COND1, strsize);
            flg = 1;
        }
        else if ((pCube->box[0][2][2].face[E_AXIS_Z]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][0].face[E_AXIS_X]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][0].face[E_AXIS_Z]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][2].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color))
        {
            strsize = strlen(STEP5_COND2);
            memcpy(str, STEP5_COND2, strsize);
            flg = 1;
        }
        else if ((pCube->box[0][2][2].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][0].face[E_AXIS_X]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][0].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][2].face[E_AXIS_Z]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color))
        {
            strsize = strlen(STEP5_COND3);
            memcpy(str, STEP5_COND3, strsize);
            flg = 1;
        }
        else if ((pCube->box[0][2][2].face[E_AXIS_Z]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][0].face[E_AXIS_Z]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][0].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][2].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color))
        {
            strsize = strlen(STEP5_COND4);
            memcpy(str, STEP5_COND4, strsize);
            flg = 1;
        }
        else if ((pCube->box[0][2][2].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][0].face[E_AXIS_Z]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][0].face[E_AXIS_Z]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][2].face[E_AXIS_Y]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color))
        {
            strsize = strlen(STEP5_COND5);
            memcpy(str, STEP5_COND5, strsize);
            flg = 1;
        }
        else if ((pCube->box[0][2][2].face[E_AXIS_X]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][0].face[E_AXIS_X]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][0].face[E_AXIS_Z]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][2].face[E_AXIS_Z]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color))
        {
            strsize = strlen(STEP5_COND6);
            memcpy(str, STEP5_COND6, strsize);
            flg = 1;
        }
        else if ((pCube->box[0][2][2].face[E_AXIS_X]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[0][2][0].face[E_AXIS_X]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][0].face[E_AXIS_X]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color) &&
            (pCube->box[2][2][2].face[E_AXIS_X]->color == pCube->box[1][2][1].face[E_AXIS_Y]->color))
        {
            strsize = strlen(STEP5_COND7);
            memcpy(str, STEP5_COND7, strsize);
            flg = 1;
        }

        if (flg)
        {
            chgcube_str(pCube, str, strsize);

            memcpy(pStr + (*pStrsize), str, strsize);
            *pStrsize += strsize;
            break;
        }
        else
        {
            // TBD
            memcpy(str, "y\'", 2);
            strsize = 2;

            chgcube_str(pCube, str, strsize);

            memcpy(pStr + (*pStrsize), str, strsize);
            *pStrsize += strsize;

            memset(str, 0x00, sizeof(str));
            strsize = 0;
        }
    }

    if (!flg)
    {
        printf("%s ERROR, CUBE IS BROKEN\n", __FUNCTION__);
        return -1;
    }

    return 0;
}

int32_t sevenstep_6(S_CUBE *pCube, uint8_t *pStr, int32_t *pStrsize)
{
    int32_t i = 0;
    uint8_t str[30];    // $)A!A??(.30??!A???
    int32_t strsize = 0;
    uint8_t chgflg = 1;
    uint8_t flg1 = 0;
    uint8_t flg2 = 0;
    uint8_t flg3 = 0;
    uint8_t flg4 = 0;

    if ((NULL == pCube) || (NULL == pStr) || (NULL == pStrsize))
    {
        printf("%s INPUT ERROR!!\n", __FUNCTION__);
        return -1;
    }

    memset(str, 0x00, sizeof(str));

    flg1 = (pCube->box[2][2][2].face[E_AXIS_Z]->color == pCube->box[0][2][2].face[E_AXIS_Z]->color);
    flg2 = (pCube->box[0][2][2].face[E_AXIS_X]->color == pCube->box[0][2][0].face[E_AXIS_X]->color);
    flg3 = (pCube->box[0][2][0].face[E_AXIS_Z]->color == pCube->box[2][2][0].face[E_AXIS_Z]->color);
    flg4 = (pCube->box[2][2][0].face[E_AXIS_X]->color == pCube->box[2][2][2].face[E_AXIS_X]->color);

    if (4 == (flg1 + flg2 + flg3 + flg4))
    {
        chgflg = 0;
    }
    else if (0 == (flg1 + flg2 + flg3 + flg4))
    {
        strsize = strlen(STEP6_COND);
        memcpy(str, STEP6_COND, strsize);

        chgcube_str(pCube, str, strsize);

        memcpy(pStr + (*pStrsize), str, strsize);
        *pStrsize += strsize;

        memset(str, 0x00, sizeof(str));
        strsize = 0;
    }

    if (chgflg)
    {
        flg1 = (pCube->box[2][2][2].face[E_AXIS_Z]->color == pCube->box[0][2][2].face[E_AXIS_Z]->color);
        flg2 = (pCube->box[0][2][2].face[E_AXIS_X]->color == pCube->box[0][2][0].face[E_AXIS_X]->color);
        flg3 = (pCube->box[0][2][0].face[E_AXIS_Z]->color == pCube->box[2][2][0].face[E_AXIS_Z]->color);
        flg4 = (pCube->box[2][2][0].face[E_AXIS_X]->color == pCube->box[2][2][2].face[E_AXIS_X]->color);

        if ((1 == flg1) && (0 == (flg2 + flg3 + flg4)))
        {
            strsize = strlen("y");
            memcpy(str, "y", strsize);
        }
        else if ((1 == flg2) && (0 == (flg1 + flg3 + flg4)))
        {
            // do nothing
        }
        else if ((1 == flg3) && (0 == (flg1 + flg2 + flg4)))
        {
            strsize = strlen("y\'");
            memcpy(str, "y\'", strsize);
        }
        else if ((1 == flg4) && (0 == (flg1 + flg2 + flg3)))
        {
            strsize = strlen("yy");
            memcpy(str, "yy", strsize);
        }
        else
        {
            printf("%s ERROR, CUBE IS BROKEN\n", __FUNCTION__);
            return -1;
        }

        memcpy(str + strsize, STEP6_COND, strlen(STEP6_COND));
        strsize += strlen(STEP6_COND);

        chgcube_str(pCube, str, strsize);

        memcpy(pStr + (*pStrsize), str, strsize);
        *pStrsize += strsize;

        memset(str, 0x00, sizeof(str));
        strsize = 0;
    }

    if (pCube->box[2][2][2].face[E_AXIS_Z]->color == pCube->box[0][1][1].face[E_AXIS_X]->color)
    {
        strsize = strlen("U");
        memcpy(str, "U", strsize);
    }
    else if (pCube->box[2][2][2].face[E_AXIS_Z]->color == pCube->box[1][1][0].face[E_AXIS_Z]->color)
    {
        strsize = strlen("UU");
        memcpy(str, "UU", strsize);
    }
    else if (pCube->box[2][2][2].face[E_AXIS_Z]->color == pCube->box[2][1][1].face[E_AXIS_X]->color)
    {
        strsize = strlen("U\'");
        memcpy(str, "U\'", strsize);
    }

    chgcube_str(pCube, str, strsize);

    memcpy(pStr + (*pStrsize), str, strsize);
    *pStrsize += strsize;

    return 0;
}

int32_t sevenstep_7(S_CUBE *pCube, uint8_t *pStr, int32_t *pStrsize)
{
    int32_t i = 0;
    uint8_t str[30];    // $)A!A??(.30??!A???
    int32_t strsize = 0;

    if ((NULL == pCube) || (NULL == pStr) || (NULL == pStrsize))
    {
        printf("%s INPUT ERROR!!\n", __FUNCTION__);
        return -1;
    }

    memset(str, 0x00, sizeof(str));

    if ((pCube->box[1][2][2].face[E_AXIS_Z]->color == pCube->box[1][1][2].face[E_AXIS_Z]->color) &&
        (pCube->box[0][2][1].face[E_AXIS_X]->color == pCube->box[0][1][1].face[E_AXIS_X]->color) &&
        (pCube->box[1][2][0].face[E_AXIS_Z]->color == pCube->box[1][1][0].face[E_AXIS_Z]->color) &&
        (pCube->box[2][2][1].face[E_AXIS_X]->color == pCube->box[2][1][1].face[E_AXIS_X]->color))
    {
        // do nothing
        return 0;
    }
    else if ((pCube->box[1][2][2].face[E_AXIS_Z]->color != pCube->box[1][1][2].face[E_AXIS_Z]->color) &&
        (pCube->box[0][2][1].face[E_AXIS_X]->color != pCube->box[0][1][1].face[E_AXIS_X]->color) &&
        (pCube->box[1][2][0].face[E_AXIS_Z]->color != pCube->box[1][1][0].face[E_AXIS_Z]->color) &&
        (pCube->box[2][2][1].face[E_AXIS_X]->color != pCube->box[2][1][1].face[E_AXIS_X]->color))
    {
        strsize = strlen(STEP7_COND1);
        memcpy(str, STEP7_COND1, strsize);

        chgcube_str(pCube, str, strsize);

        memcpy(pStr + (*pStrsize), str, strsize);
        *pStrsize += strsize;

        memset(str, 0x00, sizeof(str));
        strsize = 0;
    }

    for (i = 0; i < 4; ++i)
    {
        if ((pCube->box[1][2][2].face[E_AXIS_Z]->color != pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][2][1].face[E_AXIS_X]->color != pCube->box[1][1][2].face[E_AXIS_Z]->color) &&
            (pCube->box[1][2][0].face[E_AXIS_Z]->color == pCube->box[1][1][0].face[E_AXIS_Z]->color) &&
            (pCube->box[2][2][1].face[E_AXIS_X]->color != pCube->box[0][1][1].face[E_AXIS_X]->color))
        {
            strsize = strlen(STEP7_COND2);
            memcpy(str, STEP7_COND2, strsize);

            chgcube_str(pCube, str, strsize);

            memcpy(pStr + (*pStrsize), str, strsize);
            *pStrsize += strsize;
            break;
        }
        else if ((pCube->box[1][2][2].face[E_AXIS_Z]->color != pCube->box[0][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[0][2][1].face[E_AXIS_X]->color != pCube->box[2][1][1].face[E_AXIS_X]->color) &&
            (pCube->box[1][2][0].face[E_AXIS_Z]->color == pCube->box[1][1][0].face[E_AXIS_Z]->color) &&
            (pCube->box[2][2][1].face[E_AXIS_X]->color != pCube->box[1][1][2].face[E_AXIS_Z]->color))
        {
            strsize = strlen(STEP7_COND1);
            memcpy(str, STEP7_COND1, strsize);

            chgcube_str(pCube, str, strsize);

            memcpy(pStr + (*pStrsize), str, strsize);
            *pStrsize += strsize;
            break;
        }
        else
        {
            memcpy(str + strsize, "y\'", 2);
            strsize += 2;

            chgcube_str(pCube, str, strsize);

            memcpy(pStr + (*pStrsize), str, strsize);
            *pStrsize += strsize;

            memset(str, 0x00, sizeof(str));
            strsize = 0;
        }
    }

    return 0;
}

int32_t calstepnum(uint8_t *pStr, int32_t *pStrsize, uint8_t *pMovenum)
{
    uint8_t movenum = 0;
    S_STEPOPERATION step[10000];
    int32_t stepnum = 0;
    int32_t i = 0;

    chgstepin(pStr, *pStrsize, step, &stepnum);

    for (i = 0; i < stepnum; ++i)
    {
        movenum += step[i].movenum;
    }

    printf("movenum = %d\n", movenum);

    return 0;
}

