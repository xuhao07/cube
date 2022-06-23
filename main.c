//****************************************************************************//
//  Copyright   neusoft
/// @file       main.cpp
/// @brief      main
/// @author     xuhao
/// @date       20150930
/// @note       main
//****************************************************************************//

//****************************************************************************//
//  include
//****************************************************************************//

#include "common.h"
#include "quicksort.h"
#include "dijkstra.h"
#include "cube.h"

#define CUBE

//****************************************************************************//
//  constant definition
//****************************************************************************//
#ifdef DIJKSTRA /* test for dijkstra */
#define MAXNUM 6
#endif /* test for dijkstra */
#define MOVECUBE "LRL\'UUUDU\'DFDDFRBLL'B\'R\'"
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

#if 0 /* digui */
uint32_t func(uint32_t u4_year)
{
    uint32_t u4_ret = 1;
    uint32_t u4_loop = 0;
    if (3 < u4_year)
    {
        for(u4_loop = 0; u4_loop < u4_year - 3; ++u4_loop)
        {
            u4_ret += func(u4_loop);
        }
    }

    return u4_ret;
}
#else /* diedai */
uint32_t func(uint32_t u4_year)
{
    uint32_t u4_num = 0;
    uint32_t au4_num[M] = {0};
    uint32_t u4_iloop = 0;
    uint32_t u4_jloop = 0;

    for(u4_iloop = 0; u4_iloop < u4_year + 1; ++u4_iloop)
    {
        if (u4_iloop < 4)
        {
            au4_num[u4_iloop] = 1;
        }
        else
        {
            u4_num = 0;

            for (u4_jloop = 0; u4_jloop < u4_iloop - 2; ++u4_jloop)
            {
                u4_num += au4_num[u4_jloop];
            }

            au4_num[u4_iloop] = u4_num;
        }
    }

    return au4_num[u4_year];
}
#endif /* xuhaodebug */

////////////////////////////////////////////////////////////////////////////////
//  function        main
/// @brief          main
/// @note           for test
/// @param[in]      
/// @param[out]     
/// @retval         
/// @author         xuhao
/// @date           20150930
////////////////////////////////////////////////////////////////////////////////
int32_t main()
{
#ifdef CUBE /* test for cube */
    uint8_t movenum = 0;
    int32_t i4_ret = 0;
    S_CUBE *pCube = NULL;
    uint8_t str[10000];
    int32_t strsize = 0;
    S_STEPOPERATION step[10000];
    int32_t stepnum = 0;

    memset(str, 0x00, sizeof(str));
    memset(step, 0x00, sizeof(step));

    strsize = strlen(MOVECUBE);
    // RUR\'URUUR\'
    memcpy(str, MOVECUBE, strsize);

    i4_ret = createCube(&pCube);
    outputCube(pCube, "/mnt/d/platform/xuhao/output.txt");
    stroutput(str, "/mnt/d/platform/xuhao/output.txt");

    i4_ret = chgcube_str(pCube, str, strsize);
    outputCube(pCube, "/mnt/d/platform/xuhao/output.txt");

    memset(str, 0x00, strsize);
    strsize = 0;

    i4_ret = sevenstep(pCube, str, &strsize);

    i4_ret = calstepnum(str, &strsize, &movenum);
    
    stroutput(str, "/mnt/d/platform/xuhao/output.txt");
    outputCube(pCube, "/mnt/d/platform/xuhao/output.txt");

    freeCube(&pCube);
#endif /* test for cube */
#ifdef SINGLELIST /* test for singlelist */
    LIST testlist;
    NODE *testnode1;
    NODE *testnode2;
    NODE *testnode3;
    NODE *testnode4;
    NODE *testnode5;
    NODE *testnode6;
    int32_t i4_testdata = 0;
    uint32_t u4_testpos = 0;

    testnode1 = (NODE *)malloc(sizeof(NODE));
    testnode2 = (NODE *)malloc(sizeof(NODE));
    testnode3 = (NODE *)malloc(sizeof(NODE));
    testnode4 = (NODE *)malloc(sizeof(NODE));
    testnode5 = (NODE *)malloc(sizeof(NODE));
    testnode6 = (NODE *)malloc(sizeof(NODE));
    memset(&testlist, 0x00, sizeof(LIST));
    memset(testnode1, 0x00, sizeof(NODE));
    memset(testnode2, 0x00, sizeof(NODE));
    memset(testnode3, 0x00, sizeof(NODE));
    memset(testnode4, 0x00, sizeof(NODE));
    memset(testnode5, 0x00, sizeof(NODE));
    memset(testnode6, 0x00, sizeof(NODE));
    testnode1->i4_data = 1;
    testnode2->i4_data = 2;
    testnode3->i4_data = 3;
    testnode4->i4_data = 4;
    testnode5->i4_data = 5;
    testnode6->i4_data = 6;

    printLink(&testlist);
    newList(&testlist);
    printf("newList()\n");
    printLink(&testlist);

    delList(&testlist);
    printf("delList()\n");
    printLink(&testlist);

    insAft(&testlist, testnode1);
    printf("insAft()\n");
    printLink(&testlist);

    insBeg(&testlist, testnode2);
    printf("insBeg()\n");
    printLink(&testlist);

    insNode(&testlist, testnode3, 0);
    printf("insNode()\n");
    printLink(&testlist);

    remAft(&testlist);
    printf("remAft()\n");
    printLink(&testlist);

    remBeg(&testlist);
    printf("remBeg()\n");
    printLink(&testlist);

    remNode(&testlist, 0);
    printf("remNode()\n");
    printLink(&testlist);

    insAft(&testlist, testnode4);
    printf("insAft()\n");
    printLink(&testlist);

    insBeg(&testlist, testnode5);
    printf("insBeg()\n");
    printLink(&testlist);

    insNode(&testlist, testnode6, 0);
    printf("insNode()\n");
    printLink(&testlist);

    setData(&testlist, 40, 0);
    printf("setData()\n");
    printLink(&testlist);

    getData(&testlist, &i4_testdata, 0);
    printf("getData() i4_testdata = %d\n", i4_testdata);
    printLink(&testlist);

    findData(&testlist, 40, &u4_testpos);
    printf("findData() u4_testpos = %d\n", u4_testpos);
    printLink(&testlist);
#endif /* test for singlelist */
#ifdef DIJKSTRA /* test for dijkstra */
    uint32_t aru4_distance[][MAXNUM] = 
    {
        {0, 7, 9, M, M, 14,},
        {7, 0, 10, 15, M, M,},
        {9, 10, 0, 11, M, 2,},
        {M, 15, 11, 0, 6, M,},
        {M, M, M, 6, 0, 9,},
        {14, M, 2, M, 9, 0,}, 
    };
    uint32_t aru4_wayinfo[MAXNUM][MAXNUM] = {0};
    uint32_t *aru4_input[MAXNUM] = {NULL};
    uint32_t aru4_outputdist[MAXNUM] = {0};
    uint32_t *aru4_outputway[MAXNUM] = {NULL};
    uint32_t i = 0;
    uint32_t j = 0;

    for (i = 0; i < MAXNUM; ++i)
    {
        aru4_input[i] = aru4_distance[i];
        aru4_outputway[i] = aru4_wayinfo[i];
    }

    printf("input:\n");
    for (i = 0; i < MAXNUM; ++i)
    {
        for (j = 0; j < MAXNUM; ++j)
        {
            printf("%5d ", aru4_input[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    dijkstra(aru4_input, aru4_outputdist, aru4_outputway, 5 - 1, MAXNUM);

    printf("output:\n");
    for (i = 0; i < MAXNUM; ++i)
    {
        printf("%5d ", aru4_outputdist[i]);
    }
    printf("\n");

    printf("input:\n");
    for (i = 0; i < MAXNUM; ++i)
    {
        for (j = 0; j < MAXNUM; ++j)
        {
            if (0 != aru4_outputway[i][j])
            {
                printf("%2d ", aru4_outputway[i][j]);
            }
            if ((j < MAXNUM - 1) && (0 != aru4_outputway[i][j + 1]))
            {
                printf("¨");
            }
        }
        printf("\n");
    }
    printf("\n");
#endif /* test for dijkstra */
#ifdef QUICKSORT /* test for quicksort */
    int32_t ari4_num[6] = {0};
    int32_t i4_loop = 0;

    ari4_num[0] = 6;
    ari4_num[1] = 5;
    ari4_num[2] = 4;
    ari4_num[3] = 3;
    ari4_num[4] = 2;
    ari4_num[5] = 1;

    quicksort(ari4_num, 0, sizeof(ari4_num)/sizeof(int32_t) - 1);

    for (i4_loop = 0; i4_loop < 6; ++i4_loop)
    {
        printf("ari4_num[%d] = %d\n", i4_loop, ari4_num[i4_loop]);
    }
#endif /* test for quicksort */
    return 0;
}
