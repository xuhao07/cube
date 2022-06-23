#ifndef _CUBE_H_
#define _CUBE_H_

#include "common.h"
#include "io.h"

#define LAYER_NUM 3

#define STEPLEN_MAX 3
#define FACE_MAX 6
#define SMALLFACE_MAX 9

// step 1
#define LD_TO_DF "L\'F\'"
#define DL_TO_DF "L\'D\'LD"
#define LU_TO_DF "LF\'L\'"
#define UL_TO_DF "U\'FF"
#define RD_TO_DF "RF"
#define DR_TO_DF "RDR\'D\'"
#define RU_TO_DF "R\'FR"
#define UR_TO_DF "UFF"
#define LB_TO_DF "DDBDD"
#define BL_TO_DF "D\'L\'D"
#define LF_TO_DF "F\'"
#define FL_TO_DF "D\'LD"
#define RB_TO_DF "DDB\'DD"
#define BR_TO_DF "DRD\'"
#define RF_TO_DF "F"
#define FR_TO_DF "DR\'D\'"
#define DB_TO_DF "BDDB\'DD"
#define BD_TO_DF "BDRD\'"
#define FD_TO_DF "F\'DR\'D\'"
#define UB_TO_DF "UUFF"
#define BU_TO_DF "UR\'FR"
#define UF_TO_DF "FF"
#define FU_TO_DF "U\'R\'FR"

// step 2
#define LDB_TO_RDF "LUUL\'F\'U\'F"
#define DBL_TO_RDF "B\'UUBF\'U\'F"
#define BLD_TO_RDF "LUUL\'RUR\'"
#define LFD_TO_RDF "L\'ULU\'RUR\'"
#define FDL_TO_RDF "L\'U\'LRUR\'"
#define DLF_TO_RDF "L\'U\'LF\'U\'F"
#define LBU_TO_RDF "UUF\'U\'F"
#define BUL_TO_RDF "UURUUR\'U\'RUR\'"
#define ULB_TO_RDF "UURUR\'"
#define LUF_TO_RDF "U\'RUUR\'U\'RUR\'"
#define UFL_TO_RDF "U\'RUR\'"
#define FLU_TO_RDF "U\'F\'U\'F"
#define RBD_TO_RDF "BUB\'RUR\'"
#define BDR_TO_RDF "BUB\'F\'U\'F"
#define DRB_TO_RDF "BU\'B\'UF\'U\'F"
#define DFR_TO_RDF "RU\'R\'F\'U\'F"
#define FRD_TO_RDF "F\'UFRUR\'"
#define RUB_TO_RDF "URUUR\'U\'RUR\'"
#define UBR_TO_RDF "URUR\'"
#define BRU_TO_RDF "UF\'U\'F"
#define RFU_TO_RDF "F\'U\'F"
#define FUR_TO_RDF "RUUR\'U\'RUR\'"
#define URF_TO_RDF "RUR\'"

// step 3
#define LB_TO_RF "yyR\'F\'RURU\'R\'FyyU\'R\'F\'RURU\'R\'F"
#define BL_TO_RF "yyR\'F\'RURU\'R\'FyyFRF\'U\'F\'UFR\'"
#define LF_TO_RF "y\'R\'F\'RURU\'R\'FyUFRF\'U\'F\'UFR\'"
#define FL_TO_RF "y\'R\'F\'RURU\'R\'FyR\'F\'RURU\'R\'F"
#define RB_TO_RF "yR\'F\'RURU\'R\'Fy\'U\'FRF\'U\'F\'UFR\'"
#define BR_TO_RF "yR\'F\'RURU\'R\'Fy\'UUR\'F\'RURU\'R\'F"
#define FR_TO_RF "R\'F\'RURU\'R\'FUUFRF\'U\'F\'UFR\'"
#define LU_TO_RF "UUR\'F\'RURU\'R\'F"
#define UL_TO_RF "U\'FRF\'U\'F\'UFR\'"
#define RU_TO_RF "R\'F\'RURU\'R\'F"
#define UR_TO_RF "UFRF\'U\'F\'UFR\'"
#define UB_TO_RF "UUFRF\'U\'F\'UFR\'"
#define BU_TO_RF "UR\'F\'RURU\'R\'F"
#define UF_TO_RF "FRF\'U\'F\'UFR\'"
#define FU_TO_RF "U\'R\'F\'RURU\'R\'F"

// step 4
#define STEP4_COND1 "FRUR\'U\'F\'"
#define STEP4_COND2 "fRUR\'U\'f\'"
#define STEP4_COND3 "FRUR\'U\'F\'fRUR\'U\'f\'"

// step 5
#define STEP5_COND1 "RUR\'URUUR\'"
#define STEP5_COND2 "L\'U\'LU\'L\'U\'U\'L"
#define STEP5_COND3 "F\'rUR\'U\'r\'FR"
#define STEP5_COND4 "rUR\'U\'r\'FRF\'"
#define STEP5_COND5 "RRD\'RU\'U\'R\'DRUUR"
#define STEP5_COND6 "RU\'U\'RRU\'RRU\'RRU\'U\'R"
#define STEP5_COND7 "RUR\'URU\'R\'URUUR\'"

// step 6
#define STEP6_COND "RUR\'U\'R\'FRRU\'R\'U\'RUR\'F\'"

// step 7
#define STEP7_COND1 "RU\'RURURU\'R\'U\'RR"
#define STEP7_COND2 "L\'UL\'U\'L\'U\'L\'ULULL"

// color: GREEN, BLUE, WHITE, YELLOW, RED, ORANGE
typedef enum
{
    E_COL_GREEN = 0,
    E_COL_BLUE,
    E_COL_WHITE,
    E_COL_YELLOW,
    E_COL_RED,
    E_COL_ORANGE,
    E_COL_NUM,
} EN_COLOR;

// position: UP, DOWN, FRONT, BACK, LEFT, RIGHT
typedef enum
{
    E_POS_UP = 0,
    E_POS_DOWN,
    E_POS_FRONT,
    E_POS_BACK,
    E_POS_LEFT,
    E_POS_RIGHT,
} EN_POSITION;

// axis: x(left_to_right), y(down_to_up), z(back_to_front)
typedef enum
{
    E_AXIS_X = 0,
    E_AXIS_Y,
    E_AXIS_Z,
    E_AXIS_NUM,
} EN_AXIS;

// DIR: CW, ANTICW
typedef enum
{
    E_DIR_CW = 0,
    E_DIR_ANTICW,
    E_DIR_NUM,
} EN_DIRECTION;

// step operation
typedef struct
{
    EN_AXIS axis;
    EN_DIRECTION direction;
    uint8_t layerchgflg[LAYER_NUM]; // 0:not chg; 1:chg
    char *pcStepname;
    uint8_t movenum;
} S_STEPOPERATION;

// small face
typedef struct S_SMALL_FACE
{
    EN_COLOR color;
    // first column of array for axis; second column of array for direction
    struct S_SMALL_FACE *pNext[E_AXIS_NUM][E_DIR_NUM];
} S_SMALL_FACE;

// small box
typedef struct
{
    // the face perpendicular to X/Y/Z axis: X for L/R; Y for D/U; Z for B/F
    S_SMALL_FACE *face[E_AXIS_NUM];
}S_SMALL_BOX;

// cube
typedef struct
{
    // 2 * E_AXIS_NUM is big faces number; LAYER_NUM * LAYER_NUM is small faces number in one big face
    S_SMALL_FACE faceBuffer[2 * E_AXIS_NUM * LAYER_NUM * LAYER_NUM];
    // 3*3*3 boxes: left_to_right, down_to_up, back_to_front
    S_SMALL_BOX box[LAYER_NUM][LAYER_NUM][LAYER_NUM];
} S_CUBE;

int32_t createCube(S_CUBE **pCube);
int32_t freeCube(S_CUBE **pCube);
int32_t outputCube(S_CUBE *pCube, char *pcPath);

int32_t chgstepin(uint8_t *pStr, int32_t strsize, S_STEPOPERATION *pStep, int32_t *pStepnum);
int32_t chgstepout(S_STEPOPERATION *pStep, int32_t stepnum, uint8_t *pStr, int32_t *pStrsize);
int32_t chgcube_mutlstep(S_CUBE *pCube, S_STEPOPERATION *pStep, int32_t stepnum);
int32_t chgcube_onestep(S_CUBE *pCube, S_STEPOPERATION *pStep);
int32_t chgcube_str(S_CUBE *pCube, uint8_t *pStr, int32_t strsize);
int32_t sevenstep_1(S_CUBE *pCube, uint8_t *pStr, int32_t *pStrsize);
int32_t sevenstep_2(S_CUBE *pCube, uint8_t *pStr, int32_t *pStrsize);
int32_t sevenstep_3(S_CUBE *pCube, uint8_t *pStr, int32_t *pStrsize);
int32_t sevenstep_4(S_CUBE *pCube, uint8_t *pStr, int32_t *pStrsize);
int32_t sevenstep_5(S_CUBE *pCube, uint8_t *pStr, int32_t *pStrsize);
int32_t sevenstep_6(S_CUBE *pCube, uint8_t *pStr, int32_t *pStrsize);
int32_t sevenstep_7(S_CUBE *pCube, uint8_t *pStr, int32_t *pStrsize);
int32_t sevenstep(S_CUBE *pCube, uint8_t *pStr, int32_t *pStrsize);
int32_t calstepnum(uint8_t *pStr, int32_t *pStrsize, uint8_t *pNum);

#endif // _CUBE_H_
