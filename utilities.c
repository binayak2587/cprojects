#include <sqlhdr.h>
#include <sqliapi.h>
#line 1 "../common/utilities.ec"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <search.h>
#include <stdarg.h>
#include <math.h>
#include <sys/types.h>
#include <ctype.h>

/* 
 * $include common.h;
 */
#line 14 "../common/utilities.ec"

#line 14 "../common/utilities.ec"
#line 1 "../common//common.h"
#ifndef _common
#define _common

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <search.h>
#include <stdarg.h>
#include <math.h>
#include <sys/types.h>
#include <ctype.h>
#include "tables.h"

/* Constants */
#define SUCCESS               0
#define ERROR                 1
#define WARNING               2

#define FLD_FOUND 0
#define FLD_NOT_FOUND 1
#define LINE_FOUND 0
#define LINE_NOT_FOUND 1

#define NUM_STX_PATHS 5
#define FL_NM_SIZE 100
#define PATH_SIZE 150
#define HOST_NM_SIZE 50

#define DIR_SEPR "/"

/*STAR PGM EXCUTION PATH*/
#define TMPDIR "/tmp/"
#define STARBIN "/u/starsoft/bin/"
#define STARDIR "/u/starsoft/"

#define CMPY_ID_SIZE        3
#define LGN_ID_SIZE         8
#define LNG_SIZE            2
#define MSR_SIZE            1
#define UM_SIZE         3
#define LGTH_DCML_SIZE      4
#define WDTH_DCML_SIZE      4
#define RDM_DIM_DCML_SIZE   4
#define GA_SIZE_DCML_SIZE   5
#define IDIA_DCML_SIZE      5
#define ODIA_DCML_SIZE      5
#define FRM_SIZE            6
#define GRD_SIZE            8
#define FNSH_SIZE           8
#define EF_SIZE             3
#define SIZE_SIZE           15
#define CUS_ID_SIZE         8
#define GA_TYP_SIZE         1
#define GA_SIZE_SIZE        8
#define CTY_SIZE            3
#define PRTR_SIZE           50
#define NBR_CPY_SIZE        3

#define LONG_LBL_SIZE       75
#define IS_REPORT 1
#define IS_DOC 0

#define WHS_SIZE	3
#define BRH_SIZE	3

#define BEGIN_YEAR	1600
#define END_YEAR	9999

#define FOUR_HUNDRED_YEARS_NUM_DAYS		146097

#define SPACES				"                                                                                                    " /* 100 spaces */
#define ZEROS				"00000000000000000000000000000000000000000000000000" /* 50 zeros */

#define EXIT_PGM_ERR \
	exit(pvtiRtnSts); \

static int cumulDaysPer_400Years[]={0,36525,73049,109573};
static int cumulDaysPer_LY100Years[]={0,1461,2922,4383,5844,7305,8766,10227,11688,13149,14610,16071,17532,18993,20454,21915,23376,24837,26298,27759,29220,30681,32142,33603,35064};
static int cumulDaysPer_100Years[]={0,1460,2921,4382,5843,7304,8765,10226,11687,13148,14609,16070,17531,18992,20453,21914,23375,24836,26297,27758,29219,30680,32141,33602,35063};
static int cumulDaysPer_LY4Years[]={0,366,731,1096};
static int cumulDaysPer_4Years[]={0,365,730,1095};
static int cumulDaysPer_Month[]={0,31,59,90,120,151,181,212,243,273,304,334,365};
static int cumulDaysPer_LYMonth[]={0,31,60,91,121,152,182,213,244,274,305,335,366};
static int daysPer_Month[]={31,28,31,30,31,30,31,31,30,31,30,31};
static int daysPer_LYMonth[]={31,29,31,30,31,30,31,31,30,31,30,31};

FILE *gDataFlPtr = NULL;

char strTZ[35];
int gDocTyp = 1;
int gIsExcel = 0;

int giCustomPrec = 0;
int giNumDcmlPls = 4;
char gBasMsr[MSR_SIZE+1];
char gBasLng[LNG_SIZE+1];
char gCmpyId[CMPY_ID_SIZE+1];
char gLgnId[LGN_ID_SIZE+1] = "";
char gLng[LNG_SIZE+1] = "en";
char gCty[CTY_SIZE+1] = "USA";

char gXMLTmplNm[501] = "";
char gDataFlNm[501] = "";
char gOutputFlNm[501] = "";
char gLogFlNm[501] = "";

char gAltAccHostNm[HOST_NM_SIZE+1];
char gJetFormPath[PATH_SIZE+1];
char gMdfPath[PATH_SIZE+1];
char gDataPath[PATH_SIZE+1];
char gImgPath[PATH_SIZE+1];
char gWorkPath[PATH_SIZE+1];
char gLogoPath[PATH_SIZE+1];
char gWinCtlPath[PATH_SIZE+1];
char gIniPath[PATH_SIZE+1];
char gResubmitPath[PATH_SIZE+1];
int giIsResubmit;
char gCustomTmplPath[PATH_SIZE+1];

int giDbgLvl=0;
int gInHouse=0;
int gNumStxPaths=0;
int gSrchMdfDone=0;
struct gStructStxPath
{
    char Nm[PATH_SIZE+1];
    int iExist;
} gStxPath[NUM_STX_PATHS];

struct gStructStxPath gStxCstmTmplPath[NUM_STX_PATHS];
int giNumCstmTmplPaths = 0;
int gCstmTmplSrchDone = 0;
int pvtiRtnSts;

struct genericlist {
   int ns,ni,nf;
   char **Strings;
   int *Integers;
   long double  *Floats;
   struct genericlist *next;
};
typedef struct genericlist *glistptr;

glistptr gFirstExcelNode;
glistptr tmpExcelNode;

struct scropt gScropt;
struct scrcsc gScrcsc;
struct mxrusr gMxrusr;
struct scrlnc gScrlnc;

#endif
#line 156 "../common//common.h"
#line 15 "../common/utilities.ec"

int cstmFprintf(FILE *sLogFlPtr, char *format, ...);
int logMsg(char *sErrFmt, ...);
void printExcelData(char *, char *, int );



char *getDataPath(void)
{
	if (giIsResubmit) /* 219578 */
		return gResubmitPath;
	else
		return gDataPath;
}
char *getImgPath(void)
{
	return gImgPath;
}

char *getWorkPath(void)
{
	return gWorkPath;
}

char *getLogoPath(void)
{
	return gLogoPath;
}

char *getIniPath(void)
{
	return gIniPath;
}

/*---------------------------------------------------------------------------*/
/*-------------------------------- initDB -----------------------------------*/
/*---------------------------------------------------------------------------*/
int initDB(void)
{
	char sDbInstNm[101] = "";
	char sDbNm[101] = "";
/*
 * 	EXEC SQL BEGIN DECLARE SECTION;
 */
#line 56 "../common/utilities.ec"
#line 57 "../common/utilities.ec"
  char dbConnStr[501] = "";
int l_iSQLCode;
int l_iSQLErr;
  char sStatus[11] = "";
/*
 * 	EXEC SQL END DECLARE SECTION;
 */
#line 61 "../common/utilities.ec"


	memset(sDbInstNm, '\0', sizeof(sDbInstNm));
	memset(sDbNm, '\0', sizeof(sDbNm));
	memset(dbConnStr, '\0', sizeof(dbConnStr));

	strcpy(sDbInstNm, getenv("INFORMIXSERVER"));
	strcpy(sDbNm, getenv("DATABASE"));
logMsg("\n %s",sDbNm);
	/* Connect to database */
	sprintf(dbConnStr, "%s@%s", sDbNm, sDbInstNm);
/*
 * 	EXEC SQL connect to :dbConnStr;
 */
#line 72 "../common/utilities.ec"
  {
#line 72 "../common/utilities.ec"
  sqli_connect_open(ESQLINTVERSION, 0, dbConnStr, (char *)0, (ifx_conn_t *)0, 0);
#line 72 "../common/utilities.ec"
  }
	if (sqlca.sqlcode < -100)
	{
		sprintf(sStatus, "%05d%03d",abs(sqlca.sqlcode),abs(sqlca.sqlerrd[1]));
		return ERROR;
	} /*- end if -*/

/*
 * 	EXEC SQL set isolation to dirty read;
 */
#line 79 "../common/utilities.ec"
  {
#line 79 "../common/utilities.ec"
  static const char *sqlcmdtxt[] =
#line 79 "../common/utilities.ec"
    {
#line 79 "../common/utilities.ec"
    "set isolation to dirty read",
    0
    };
#line 79 "../common/utilities.ec"
  static ifx_statement_t _SQ0 = {0};
#line 79 "../common/utilities.ec"
  sqli_stmt(ESQLINTVERSION, &_SQ0, sqlcmdtxt, 0, (ifx_sqlvar_t *)0, (struct value *)0, (ifx_literal_t *)0, (ifx_namelist_t *)0, (ifx_cursor_t *)0, -1, 0, 0);
#line 79 "../common/utilities.ec"
  }
	if (sqlca.sqlcode < -100)
	{
		sprintf(sStatus, "%05d%03d",abs(sqlca.sqlcode),abs(sqlca.sqlerrd[1]));
		return ERROR;
	} /*- end if -*/

	if (getLocalizationInfo(gLgnId, gLng, gCty) != 0)
		return ERROR;

	return SUCCESS;
} /*- end initDB() -*/

/*---------------------------------------------------------------------------*/
/*-------------------------------- closeDB -----------------------------------*/
/*---------------------------------------------------------------------------*/
void closeDB(void)
{

/*
 * 	EXEC SQL disconnect current;
 */
#line 98 "../common/utilities.ec"
  {
#line 98 "../common/utilities.ec"
  sqli_connect_close(3, (char *)0, 0, 0);
#line 98 "../common/utilities.ec"
  }

} /*- end closeDB() -*/

int cstmInit(char *sPgmNm)
{
	char dtStr[18] = "";
	char sDataFlNm[501] = "";
	char sLgnId[9] = "";
	char sCmpyId[3+1] = "";
	time_t now;
	char sDate[15] = "";
	char sTime[26] = "";
	struct tm *ltp;

	/* Open Database */
	if (initDB() == ERROR) {
		return ERROR;
	}

	getEnvVars(); /* Get values for environment variables */

	memcpy(gScrcsc.cmpy_id, gCmpyId, CMPY_ID_SIZE);
	if (readScrcsc(&gScrcsc) != 0)
		return ERROR;

	if (readScropt(&gScropt) != 0)
		return ERROR;

	strcpy(gBasMsr, gScrcsc.bas_msr);
	strcpy(gBasLng, gScrcsc.bas_lng);

	getDateTm(dtStr);

	memset(gLogFlNm, '\0', sizeof(gLogFlNm));
	sprintf(gLogFlNm, "/tmp/%s_%s.log", sPgmNm, dtStr);

	/*now = time(NULL);
	ltp = (struct tm *)localtime(&now);
	strftime(sDate, sizeof(sDate)-1, "%Y%m%d", ltp);
	strftime(sTime, sizeof(sTime)-1, "%I%M%S", ltp);*/

	/* Set sPgmNm
	if (gblSetPgmNm(sPgmNm)==1)
	{
		return 1;
	} */

	memset(gXMLTmplNm, '\0', sizeof(gXMLTmplNm));
	sprintf(gXMLTmplNm, "%s.xml", sPgmNm);


	/*Prepare Data file name */
	memset(sDataFlNm, '\0', 501);
	strcpy(sDataFlNm, (char *)getDataPath());

	strncat(sDataFlNm, sPgmNm, strlen(sPgmNm));
	strcat(sDataFlNm, "_");
	strcat(sDataFlNm, dtStr);

	if (gIsExcel)
	{/* Data file for Excel format */
		strcat(sDataFlNm, ".xls");
	}
	else
	{/* Data file for PDF format */
		strcat(sDataFlNm, ".dat");
	}

	strcpy(gDataFlNm, sDataFlNm);

	if ((gDataFlPtr=fopen(sDataFlNm, "w")) ==NULL)
	{
		/* Log Error */
		logMsg("Error: Unable to create data file '%s'.", sDataFlNm);
		return ERROR;
	}

	return SUCCESS;
}

/*cstmInit for view mode, in case if we need dat file to be generated with specific file name and in location tmp*/
int cstmInitViewMode(char *fileName)
{
	char sDataFlNm[501] = "";
	char sLgnId[9] = "";
	char sCmpyId[3+1] = "";
	time_t now;
	char sDate[15] = "";
	char sTime[26] = "";
	struct tm *ltp;

	/* Open Database */
	if (initDB() == ERROR) {
		return ERROR;
	}

	getEnvVars(); /* Get values for environment variables */

	memcpy(gScrcsc.cmpy_id, gCmpyId, CMPY_ID_SIZE);
	if (readScrcsc(&gScrcsc) != 0)
		return ERROR;

	if (readScropt(&gScropt) != 0)
		return ERROR;

	strcpy(gBasMsr, gScrcsc.bas_msr);
	strcpy(gBasLng, gScrcsc.bas_lng);

	memset(sDataFlNm, '\0', sizeof(sDataFlNm));
	sprintf(sDataFlNm, "/tmp/%s",fileName);
	
	if ((gDataFlPtr=fopen(sDataFlNm, "w")) ==NULL)
	{
	/* Log Error */
		logMsg("Error: Unable to create data file '%s'.", sDataFlNm);
		return ERROR;
	}

	return SUCCESS;
}

void ltrim(char *str)
{
	int len=0,i,j,ctr;
	
	len=strlen(str);
	i=0;ctr=0;

	while(str[0] == ' ')
	{
		for(j=0;j<len;j++)
			str[j] = str[j+1];
	}
   return;
}

void rtrim(char *str)
{
    int k;

    k = strlen(str)-1;
    while (k>=0 && str[k]==' ')
    {
       str[k] = '\0';
       k--;
    }

    return;
}

int concat1(register char *sRtnStr, register int iRtnStr, register char *str1)
{
    int iLen1=0;

    iLen1 = strlen(str1);
    memset(sRtnStr, '\0', iRtnStr);

    if (iRtnStr > iLen1 && str1)
        strncpy(sRtnStr, str1, iLen1);

    return 0;

}

void concat2( register char *sRtnStr, register int iRtnStr, register char *str1, register char *str2)
{
    int iLen1=0, iLen2=0;

    iLen1 = strlen(str1);
    iLen2 = strlen(str2);

    memset(sRtnStr,'\0',iRtnStr);

    if (iRtnStr > iLen1  && str1)
        strncpy(sRtnStr, str1, iLen1);
    if (iRtnStr > (iLen1 + iLen2) && str2)
        strncat(sRtnStr, str2, iLen2);

    return;
}

void concat3( register char *sRtnStr, register int iRtnStr, register char *str1, register char *str2, register char *str3)
{
    int iLen1=0, iLen2=0, iLen3=0;

    iLen1 = strlen(str1);
    iLen2 = strlen(str2);
    iLen3 = strlen(str3);

    memset(sRtnStr,'\0',iRtnStr);

    if (iRtnStr > iLen1  && str1)
        strncpy(sRtnStr, str1, iLen1);
    if (iRtnStr > (iLen1 + iLen2) && str2)
        strncat(sRtnStr, str2, iLen2);
    if (iRtnStr > (iLen1 + iLen2 + iLen3 ) && str3)
        strncat(sRtnStr, str3, iLen3);

    return;
}

void concat4( register char *sRtnStr, register int iRtnStr, register char *str1, register char *str2, register char *str3, register char *str4)
{
    int iLen1=0, iLen2=0, iLen3=0, iLen4=0;

    iLen1 = strlen(str1);
    iLen2 = strlen(str2);
    iLen3 = strlen(str3);
    iLen4 = strlen(str4);

    memset(sRtnStr,'\0',iRtnStr);

    if (iRtnStr > iLen1  && str1)
        strncpy(sRtnStr, str1, iLen1);
    if (iRtnStr > (iLen1 + iLen2) && str2)
        strncat(sRtnStr, str2, iLen2);
    if (iRtnStr > (iLen1 + iLen2 + iLen3 ) && str3)
        strncat(sRtnStr, str3, iLen3);
    if ( iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4) && str4)
        strncat(sRtnStr, str4, iLen4);

    return;
}

void concat5( register char *sRtnStr, register int iRtnStr, register char *str1, register char *str2, register char *str3,
            register char *str4, register char *str5)
{
    int iLen1=0, iLen2=0, iLen3=0, iLen4=0, iLen5=0;

    iLen1 = strlen(str1);
    iLen2 = strlen(str2);
    iLen3 = strlen(str3);
    iLen4 = strlen(str4);
    iLen5 = strlen(str5);

    memset(sRtnStr,'\0',iRtnStr);

    if (iRtnStr > iLen1  && str1)
        strncpy(sRtnStr, str1, iLen1);
    if (iRtnStr > (iLen1 + iLen2) && str2)
        strncat(sRtnStr, str2, iLen2);
    if (iRtnStr > (iLen1 + iLen2 + iLen3 ) && str3)
        strncat(sRtnStr, str3, iLen3);
    if ( iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4) && str4)
        strncat(sRtnStr, str4, iLen4);
    if ( iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5) && str5)
        strncat(sRtnStr, str5, iLen5);

    return;
}

void concat6( register char *sRtnStr, register int iRtnStr, register char *str1, register char *str2, register char *str3,
            register char *str4, register char *str5, register char *str6)
{
    int iLen1=0, iLen2=0, iLen3=0, iLen4=0, iLen5=0, iLen6=0;

    iLen1 = strlen(str1);
    iLen2 = strlen(str2);
    iLen3 = strlen(str3);
    iLen4 = strlen(str4);
    iLen5 = strlen(str5);
    iLen6 = strlen(str6);

    memset(sRtnStr,'\0',iRtnStr);

    if (iRtnStr > iLen1  && str1)
        strncpy(sRtnStr, str1, iLen1);
    if (iRtnStr > (iLen1 + iLen2) && str2)
        strncat(sRtnStr, str2, iLen2);
    if (iRtnStr > (iLen1 + iLen2 + iLen3 ) && str3)
        strncat(sRtnStr, str3, iLen3);
    if ( iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4) && str4)
        strncat(sRtnStr, str4, iLen4);
    if ( iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5) && str5)
        strncat(sRtnStr, str5, iLen5);
    if ( iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 + iLen6) && str6)
        strncat(sRtnStr, str6, iLen6);

    return;
}

void concat7( register char *sRtnStr, register int iRtnStr, register char *str1, register char *str2, register char *str3,
            register char *str4, register char *str5, register char *str6, register char *str7)
{
    int iLen1=0, iLen2=0, iLen3=0, iLen4=0, iLen5=0, iLen6=0, iLen7=0;

    iLen1 = strlen(str1);
    iLen2 = strlen(str2);
    iLen3 = strlen(str3);
    iLen4 = strlen(str4);
    iLen5 = strlen(str5);
    iLen6 = strlen(str6);
    iLen7 = strlen(str7);

    memset(sRtnStr,'\0',iRtnStr);

    if (iRtnStr > iLen1  && str1)
        strncpy(sRtnStr, str1, iLen1);
    if (iRtnStr > (iLen1 + iLen2) && str2)
        strncat(sRtnStr, str2, iLen2);
    if (iRtnStr > (iLen1 + iLen2 + iLen3 ) && str3)
        strncat(sRtnStr, str3, iLen3);
    if ( iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4) && str4)
        strncat(sRtnStr, str4, iLen4);
    if ( iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5) && str5)
        strncat(sRtnStr, str5, iLen5);
    if ( iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 + iLen6) && str6)
        strncat(sRtnStr, str6, iLen6);
    if ( iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 + iLen6 + iLen7) && str7)
        strncat(sRtnStr, str7, iLen7);
    return;
}

void concat8( register char *sRtnStr, register int iRtnStr, register char *str1, register char *str2,
			register char *str3, register char *str4, register char *str5, register char *str6,
			register char *str7, register char *str8)
{
	int iLen1=0, iLen2=0, iLen3=0, iLen4=0, iLen5=0, iLen6=0, iLen7=0, iLen8=0;

	iLen1 = strlen(str1);
	iLen2 = strlen(str2);
	iLen3 = strlen(str3);
	iLen4 = strlen(str4);
	iLen5 = strlen(str5);
	iLen6 = strlen(str6);
	iLen7 = strlen(str7);
	iLen8 = strlen(str8);

	memset(sRtnStr,'\0',iRtnStr);

	if (iRtnStr > iLen1  && str1)
		strncpy(sRtnStr, str1, iLen1);
	if (iRtnStr > (iLen1 + iLen2) && str2)
		strncat(sRtnStr, str2, iLen2);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 ) && str3)
		strncat(sRtnStr, str3, iLen3);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4) && str4)
		strncat(sRtnStr,str4, iLen4);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 ) && str5)
		strncat(sRtnStr,str5, iLen5);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 + iLen6 ) && str6)
		strncat(sRtnStr,str6, iLen6);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 + iLen6 + iLen7 ) && str7)
		strncat(sRtnStr,str7, iLen7);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 + iLen6 + iLen7 + iLen8 ) && str8)
		strncat(sRtnStr,str8, iLen8);

	return;
}

void concat9( register char *sRtnStr, register int iRtnStr, register char *str1, register char *str2,
			register char *str3, register char *str4, register char *str5, register char *str6,
			register char *str7, register char *str8, register char *str9)
{
	int iLen1=0, iLen2=0, iLen3=0, iLen4=0, iLen5=0, iLen6=0, iLen7=0, iLen8=0, iLen9=0;

	iLen1 = strlen(str1);
	iLen2 = strlen(str2);
	iLen3 = strlen(str3);
	iLen4 = strlen(str4);
	iLen5 = strlen(str5);
	iLen6 = strlen(str6);
	iLen7 = strlen(str7);
	iLen8 = strlen(str8);
	iLen9 = strlen(str9);

	memset(sRtnStr,'\0',iRtnStr);

	if (iRtnStr > iLen1  && str1)
		strncpy(sRtnStr, str1, iLen1);
	if (iRtnStr > (iLen1 + iLen2) && str2)
		strncat(sRtnStr, str2, iLen2);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 ) && str3)
		strncat(sRtnStr, str3, iLen3);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4) && str4)
		strncat(sRtnStr,str4, iLen4);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 ) && str5)
		strncat(sRtnStr,str5, iLen5);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 + iLen6 ) && str6)
		strncat(sRtnStr,str6, iLen6);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 + iLen6 + iLen7 ) && str7)
		strncat(sRtnStr,str7, iLen7);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 + iLen6 + iLen7 + iLen8 ) && str8)
		strncat(sRtnStr,str8, iLen8);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 + iLen6 + iLen7 + iLen8 + iLen9 ) && str9)
		strncat(sRtnStr,str9, iLen9);

	return;
}
void concat10( register char *sRtnStr, register int iRtnStr, register char *str1, register char *str2,
			register char *str3, register char *str4, register char *str5, register char *str6,
			register char *str7, register char *str8, register char *str9, register char *str10)
{
	int iLen1=0, iLen2=0, iLen3=0, iLen4=0, iLen5=0, iLen6=0, iLen7=0, iLen8=0, iLen9=0, iLen10=0;

	iLen1 = strlen(str1);
	iLen2 = strlen(str2);
	iLen3 = strlen(str3);
	iLen4 = strlen(str4);
	iLen5 = strlen(str5);
	iLen6 = strlen(str6);
	iLen7 = strlen(str7);
	iLen8 = strlen(str8);
	iLen9 = strlen(str9);
	iLen10 = strlen(str10);

	memset(sRtnStr,'\0',iRtnStr);

	if (iRtnStr > iLen1  && str1)
		strncpy(sRtnStr, str1, iLen1);
	if (iRtnStr > (iLen1 + iLen2) && str2)
		strncat(sRtnStr, str2, iLen2);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 ) && str3)
		strncat(sRtnStr, str3, iLen3);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4) && str4)
		strncat(sRtnStr,str4, iLen4);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 ) && str5)
		strncat(sRtnStr,str5, iLen5);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 + iLen6 ) && str6)
		strncat(sRtnStr,str6, iLen6);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 + iLen6 + iLen7 ) && str7)
		strncat(sRtnStr,str7, iLen7);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 + iLen6 + iLen7 + iLen8 ) && str8)
		strncat(sRtnStr,str8, iLen8);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 + iLen6 + iLen7 + iLen8 + iLen9 ) && str9)
		strncat(sRtnStr,str9, iLen9);
	if (iRtnStr > (iLen1 + iLen2 + iLen3 + iLen4 + iLen5 + iLen6 + iLen7 + iLen8 + iLen9 + iLen10) && str10)
		strncat(sRtnStr,str10, iLen10);

	return;
}

void upper(char *sStr)
{
	int i = 0;

	while ( sStr[i] )
	{
		sStr[i] = toupper(sStr[i]);
		i++;
	}
	return;
}

/* function to write error messgaes in a file */
int logMsg(char *sErrFmt, ...)
{
    va_list ap;
    FILE *fp = NULL;
    time_t now;
    char sDate[15] = "";
    char sTime[26] = "";
    char sFileNm[256] = "";
    char sInpStr[501] = "";
    struct tm *ltp;


    now = time(NULL);
    ltp = (struct tm *)localtime(&now);
    strftime(sDate, sizeof(sDate)-1, "%Y%m%d", ltp);

    fp = fopen(gLogFlNm, "a");
    if (fp == NULL)
    {
        return 1;
    }

    va_start(ap, sErrFmt);
    memset(sInpStr, '\0', sizeof(sInpStr));
    vsnprintf(sInpStr, sizeof(sInpStr)-1, sErrFmt, ap);
    va_end(ap);

    strftime(sTime, sizeof(sTime)-1, "%T", ltp);
    fprintf(fp, "[%s] %s\n", sTime, sInpStr);
    fclose(fp);
    return 0;
}

int printLabel(char *lblNm, char *dflt)
{
	if (gIsExcel )
		return (0);

	if (gDataFlPtr != NULL)
	{
		/*if ( gDocTyp == IS_DOC)
			gblFprintf("^field %s\n", lblNm);
		else*/
		cstmFprintf(gDataFlPtr, "^field %s\n", lblNm);

		/*if ( gDocTyp == IS_DOC)
		   gblFprintf("%s\n", dflt);
		else*/
			cstmFprintf(gDataFlPtr, "%s\n", dflt);

		fflush(gDataFlPtr );

	}

	return 0;
}

int printData(char *sData, char *fldNm, int dataType, int fldSize)
{
	long dataLen;
	char tmpStr[5000];
	memset(tmpStr,'\0', 5000);

	if (gIsExcel)
	{
		printExcelData(sData, fldNm, dataType);
		/*printExcelData(sData, fldNm,  dataType,  fldSize);
		cstmFprintf(gDataFlPtr,"%s\t", sData);*/
		return 0;
	}

	dataLen=strlen(sData);

	memcpy(tmpStr,sData,dataLen);
	if (gDataFlPtr != NULL)
	{
		/*if ( gDocTyp == IS_DOC)
		  gblFprintf("^field %s\n", fldNm);
		else*/
		  cstmFprintf(gDataFlPtr, "^field %s\n", fldNm);

		rtrim(tmpStr);
		if (tmpStr[0] != '\0')
		{
			if (tmpStr[dataLen-1] == '\n')
			{
				cstmFprintf(gDataFlPtr, "%s", tmpStr);

			}
			else
			{
				cstmFprintf(gDataFlPtr, "%s\n", tmpStr);
			}
		}
		fflush(gDataFlPtr );
	}

	return 0;
}

int cstmFprintf(FILE *sLogFlPtr, char *format, ...)
{
	int l_ret;
	int size = 500;
	int iLgth = 0;
	int iCount = 0;
	int bStart = 0;
	va_list ap;
	char *newstring;

	if (sLogFlPtr == NULL)
	{
		logMsg("Error: Data file is not open\n");
		return -1;
	}

	newstring = malloc(size); /* <<<<<<<----------- dynamically allocate -------- */
	va_start(ap, format);
	l_ret=0;

	while(1)
	{

		/*memset(newstring, '\0', size);*/
		#ifdef STXWIN
		l_ret = _vsnprintf(newstring, size, format, ap);
		#else
		l_ret = vsnprintf(newstring, size, format, ap);
		#endif
		if (l_ret > -1 && l_ret < size )
		{
			break;
		}
		if(l_ret > -1)
		{
			size = l_ret*2; /* precisely what is needed */
			newstring = realloc (newstring, size);
		}

		iCount++;
		if (iCount > 10000) /* Just in case this goes into infinite loop */
		{
			logMsg("Error: cstmFprintf function failed\n");
			va_end(ap);
			free(newstring);
			return -1;
		}

	}

	iCount = 0;
	l_ret = 0;
	iLgth = (int)strlen(newstring);
	while(iCount < iLgth)
	{

		if (bStart == 0)    /* Do this check only for first character */
		{
			if (newstring[iCount]  != '^')
			{
				if (newstring[iCount] != '\r') /*Remove ^M from the string */
				{
					if (fwrite(newstring + iCount, sizeof(char), 1, sLogFlPtr) < 1)
					{
						logMsg("Error:  cstmFprintf function failed\n");
						va_end(ap);
						free(newstring);
						return -1;
					}

					bStart = 1;
				}

			}
			else
			{
				/* check if ^ is followed by field, inline, comment, symbol, global, Field, reformat, tab, $Page */
				if ((memcmp(newstring + iCount + 1, "field", 5) == 0) ||
					(memcmp(newstring + iCount + 1, "symbol", 6) == 0) ||
					(memcmp(newstring + iCount + 1, "comment", 7) == 0) ||
					(memcmp(newstring + iCount + 1, "global", 6) == 0) ||
					(memcmp(newstring + iCount + 1, "Field", 5) == 0) ||
					(memcmp(newstring + iCount + 1, "tab", 3) == 0) ||
					(memcmp(newstring + iCount + 1, "inline", 6) == 0) ||
					(memcmp(newstring + iCount + 1, "$Page", 5) == 0) ||
					(memcmp(newstring + iCount + 1, "reformat", 8) == 0))
				{
					if (fwrite(newstring + iCount, sizeof(char), 1, sLogFlPtr) < 1)
					{
						logMsg("Error:  cstmFprintf function failed\n");
						va_end(ap);
						free(newstring);
						return -1;
					}

				}
				else /* otherwise Print space */
				{
					if (fwrite(" ", sizeof(char), 1, sLogFlPtr) < 1)
					{
						logMsg("Error:  cstmFprintf function failed\n");
						va_end(ap);
						free(newstring);
						return -1;
					}

				}

				bStart = 1;
			}
		}
		else
		{
			if (newstring[iCount] != '\r') /*Remove ^M from the string */
			{
				if (fwrite(newstring + iCount, sizeof(char), 1, sLogFlPtr) < 1)
				{
						logMsg("Error:  cstmFprintf function failed\n");
						va_end(ap);
						free(newstring);
						return -1;
				}
			}

		} /* end bStart */

		iCount = iCount + 1;
	}    /* end while */

	va_end(ap);
	fflush(sLogFlPtr);
	free(newstring);
	return(0); /* return 0 Success */
}

glistptr cstmInitList(int numstr,int numint,int numflt,...)
{
   glistptr head;
   int i,j,k;
   va_list args;
   char *shold;
   int ihold;
   long double  fhold;

   if ( (numstr<0) || (numint<0) || (numflt<0) )
   {
      fprintf(stderr,"cstmInit: parameter count less than 0.\n");
      return(NULL);
   }
   else
      head = (glistptr) malloc(sizeof(struct genericlist));

    if (!head)
    {
       fprintf(stderr,"cstmInit: error mallocing structure memory.\n");
       return(NULL);
    }

   va_start(args,numflt);

   /* store the counts in the structure. */
   head->ns = numstr; head->ni = numint; head->nf = numflt;

   /* malloc the memory for the structure, based upon the counts.
      After the memory for the structure is malloced. Loop
      through the field count, malloc the memory for the
      fields and assign the fields. */
   if (numstr>0)
   {
      head->Strings = (char **) malloc(sizeof(char *) * numstr);
      if (!head->Strings)
      {
	   fprintf(stderr,"cstmInit: error mallocing structure memory.\n");
	   return(NULL);
      }

      for (i = 0; i < numstr; i++)
      {
 		 shold = va_arg (args,char *);
		 head->Strings[i] = (char *)malloc(sizeof(char) * (strlen(shold) + 1));
		 strcpy(head->Strings[i], shold);
      }
   }

   if (numint>0)
   {
      head->Integers = (int *) malloc(sizeof(int) * numint);
      if (!head->Integers)
      {
	   fprintf(stderr,"cstmInit: error mallocing structure memory.\n");
	   return(NULL);
      }

      for (j = 0; j < numint; j++)
      {
	   ihold = (int) va_arg(args,double);
	   head->Integers[j] = ihold;
      }
   }

   if (numflt>0)
   {
      head->Floats = (long double  *) malloc(sizeof(long double ) * numflt);
      if (!head->Floats)
      {
	   fprintf(stderr,"cstmInit: error mallocing structure memory.\n");
	   return(NULL);
      }

      for (k = 0; k < numflt; k++)
      {
  	   fhold = (long double ) va_arg(args,long double );
	   head->Floats[k] = fhold;
      }
   }

   va_end(args);

   /* now assign the next pointer to null */

   head->next = NULL;

   /* now return the head pointer */

   return(head);

}

int cstmAddNode(glistptr start, ...)
{
   glistptr node;
   glistptr traverse;
   int i,j,k;
   va_list args;
   char *shold;
   int ihold;
   long double  fhold;
   int nums,numi,numf;

   if (!start)
   {
      return(0);
   }

   /* retrieve the field counts from the head node */
   nums = start->ns;
   numi = start->ni;
   numf = start->nf;

   /* traverse to the end of the list */
   for (traverse = start; traverse->next; traverse = traverse->next)
	{
		/* Current and Next nodes are same then break the loop to avoid the issue of infinite loop.
		Otherwise the program stuck here */
		if (traverse == traverse->next)
		{
			traverse->next = NULL;
			break;
		}
	}

   /* malloc space for the new node */
   node = (glistptr) malloc(sizeof(struct genericlist));
   if (!node)
   {
      fprintf(stderr,"cstmAddNode: error mallocing structure memory.\n");
      return(0);
   }

   va_start(args,start);

   /* store the counts in the structure. */
   node->ns = nums; node->ni = numi; node->nf = numf; node->next = NULL;

   /* malloc the memory for the structure, based upon the counts.
      After the memory for the structure is malloced. Loop
      through the field count, malloc the memory for the
      fields and assign the fields. */
   if (nums>0)
   {
      node->Strings = (char **) malloc(sizeof(char *) * nums);
      if (!node->Strings)
      {
	    fprintf(stderr,"cstmAddNode: error mallocing structure memory.\n");
	    return(0);
      }

      for (i = 0; i < nums; i++)
      {
	   shold = va_arg(args,char *);
	   node->Strings[i] = (char *) malloc(sizeof(char) * (strlen(shold) + 1));
	   strcpy(node->Strings[i], shold);
      }
   }

   if (numi>0)
   {
      node->Integers = (int *) malloc(sizeof(int) * numi);
      if (!node->Integers)
      {
	 	fprintf(stderr,"cstmAddNode: error mallocing structure memory.\n");
	 	return(0);
      }

      for (j = 0; j < numi; j++)
      {
	 	ihold = (int) va_arg(args,double);
	 	node->Integers[j] = ihold;
      }
   }

   if (numf>0)
   {
      node->Floats = (long double  *) malloc(sizeof(long double ) * numf);
      if (!node->Floats)
      {
	 	fprintf(stderr,"cstmAddNode: error mallocing structure memory.\n");
	 	return(0);
      }

      for (k = 0; k < numf; k++)
      {
	 	fhold = (long double ) va_arg(args,long double );
	 	node->Floats[k] = fhold;
      }
   }

   va_end(args);

   /* now assign the next pointer to null */

   node->next = NULL;

   /* now connect this new node to the list */

   traverse->next = node;

   /* return success */
   return(1);
}

void cstmDel(glistptr start)
{
   int i,j,k;
   glistptr traverse = 0L;
   glistptr temp = 0L;

   if(!start)
   {
      return;
   }

   for(traverse = start;traverse->next;traverse = temp)
   {

      temp = traverse->next;

      /* free the heap space used */

      for (i = 0; i < traverse->ns; i++)
	 	free(traverse->Strings[i]);

      if(traverse->ns > 0) free(traverse->Strings);
      if(traverse->ni > 0) free(traverse->Integers);
      if(traverse->nf > 0) free(traverse->Floats);

      free(traverse);

   }
}

void printExcelData(char *sData, char *fldNm, int dataType)
{
	/*char *sData = NULL;*/
	char *sDataStr = NULL;
	char *sTemp = NULL;
	int iCount = 0;

	/*rplTabsRtrimSpaces(tmpExcelNode->Strings[1]);*/

	if (dataType == 1) /*  Numeric field */
	{
		cstmFprintf(gDataFlPtr,"%s\t", sData);
	}
	else
	{
		sDataStr = sData;
		/* Replace double quotes with two quotes as character data will be
		enclosed in double quotes. Excel will replace again two quotes with
		single one. */
		if (strchr(sData, '"') != NULL)
		{
			sTemp = sData;
			sDataStr = calloc(strlen(sTemp) * 2, sizeof(char));
			for (iCount=0; *sTemp != '\0'; sTemp++, iCount++)
			{
				*(sDataStr + iCount) = *sTemp;
				if ( *sTemp == '"')
				{
					iCount++;
					*(sDataStr + iCount) = '"';
				}
			}
		}

		/* If cell data is in multiple lines, do not add "=" */
		if (strchr(sData, '\n') != NULL)
		{
			cstmFprintf(gDataFlPtr,"\"%s\"\t", sDataStr);
		}
		else
		{
			/* Enclose data in double quotes and add prefix '=' */
			cstmFprintf(gDataFlPtr,"=\"%s\"\t", sDataStr);
		}
	}

	/*fprintf(gDataFlPtr,"\r\n");*/
}

/*
	This routine is used to remove end spaces/tabs and tabs in the data to spaces
*/
int rplTabsRtrimSpaces(char *line)
{
	int k = 0;
	int iFlg = 0;

	k = strlen(line) - 1;
	while (k >= 0)
	{
		/*Check for end spaces and tabs, replace them with null character*/
		if (iFlg == 0 && (line[k] == ' ' || line[k] == '\t'))
		{
			line[k] = '\0';
		}
		else if (iFlg == 1 && line[k] == '\t')
		{
			line[k] = ' ';
		}
		else
		{
			iFlg = 1;
		}

		k--;
		/*The following line is to avoid line[k] to crash accessing unavailable memory*/
		if (k < 0)
		{
			break;
		}
	}

	return 0;
}

int getEnvVars(void)
{
	char *sTmpEnv;
	int iRet = 0;
	static int iDone;
	char *token;
	char lineTmp321[321];
	int i=0;
	char *sGetEnv;
	char sCustomTmplPath[2100] = "";
	int iSize = 0;
	char line321[321] = "";

	if (iDone==1){return 0;}

	memset(gAltAccHostNm,'\0',HOST_NM_SIZE +1);
	memset(gJetFormPath,'\0',PATH_SIZE+1);
	memset(gMdfPath,'\0',PATH_SIZE+1);
	memset(gIniPath,'\0',PATH_SIZE+1);
	memset(gDataPath,'\0',PATH_SIZE+1);
	memset(gWorkPath,'\0',PATH_SIZE+1);
	memset(gImgPath,'\0',PATH_SIZE+1);
	memset(gLogoPath,'\0',PATH_SIZE+1);
	memset(gResubmitPath,'\0',PATH_SIZE+1);
	giIsResubmit = 0;
	memset(gCustomTmplPath, '\0', sizeof(gCustomTmplPath));
	giNumCstmTmplPaths = 0;
	gCstmTmplSrchDone = 0;

	gInHouse=0;
	for (i = 0;i<NUM_STX_PATHS;i++ )
	{
		memset(gStxPath[i].Nm,'\0',PATH_SIZE+1);
		gStxPath[i].iExist=0;
	}

	for (i = 0; i< NUM_STX_PATHS; i++ )
	{/* Initialize array for Custom Template directory */
		memset(gStxCstmTmplPath[i].Nm, '\0', PATH_SIZE+1);
		gStxCstmTmplPath[i].iExist = 0;
	}


	/* set Debug Level */
	sGetEnv = (char *)getenv("RPT_DEBUG");

	if (sGetEnv)
	{
		if (memcmp(sGetEnv, "1", 1) == 0)
		{
			giDbgLvl = 1;
		}
		else
		{
			giDbgLvl = 0;
		}
	}

	/* Determine whether InHouse */
	sGetEnv = (char *)getenv("INHOUSESETUP");

	if (sGetEnv)
	{
		if (memcmp(sGetEnv, "Y", 1) == 0)
		{
			gInHouse = 1;
		}
		else
		{
			gInHouse = 0;
		}
	}

	/*if(gInHouse==0)
	{*/
		sTmpEnv =(char *)getenv("STRATIXDIR");
		if (checkEnvVar(sTmpEnv,"STRATIXDIR",PATH_SIZE-5)==1){return 1;}
		sprintf(gMdfPath,"%s%spgms%s",sTmpEnv,DIR_SEPR,DIR_SEPR);

		sTmpEnv =(char *)getenv("HOME");
		if (checkEnvVar(sTmpEnv,"HOME",PATH_SIZE-5)==1){return 1;}
		sprintf(gLogoPath,"%s%slogo%s",sTmpEnv,DIR_SEPR,DIR_SEPR);
	/*}
	else
	{
		sTmpEnv =(char *)getenv("INHOUSEMDFDIR");
		memset (line321,'\0',321);
		memcpy(line321,sTmpEnv,strlen(sTmpEnv));
		if (checkEnvVar(line321,"INHOUSEMDFDIR",PATH_SIZE-5)==1){return 1;}
		if (line321!=NULL)
		{
			if (strchr(line321, ':' ) ==NULL)
			{
				* This is just a default, in case we are InHouse and don't have the : in INHOUSEMDFDIR
				In the case of LIVE, we will never have : in the STRATIXDIR variable, so in that case
				this is also a default, and not needed in Principle  *
				gNumStxPaths =1;
				sprintf(gStxPath[0].Nm,"%s%s",line321,DIR_SEPR);
			}
			else
			{
				gNumStxPaths =0;
				memset (lineTmp321,'\0',321);
				memcpy(lineTmp321,line321,strlen(line321));
				token = strtok(lineTmp321, ":");
				while( token != NULL )
				{
					sprintf(gStxPath[gNumStxPaths].Nm,"%s%s",token,DIR_SEPR);
					gNumStxPaths++;
					* Get next token: *
					token = strtok(NULL, ":");
					if (gNumStxPaths==NUM_STX_PATHS){break;}
				}
				*Restore Last Val so we can validate it*
				memset (line321,'\0',321);
				strcpy(line321,gStxPath[gNumStxPaths-1].Nm);
			}
		}
		sprintf(gMdfPath,"%s",line321);

		sTmpEnv =(char *)getenv("INHOUSELOGODIR");
		if (checkEnvVar(sTmpEnv,"INHOUSELOGODIR",PATH_SIZE)==1){return 1;}
		sprintf(gLogoPath,"%s%s",sTmpEnv,DIR_SEPR);
	}*/

	sTmpEnv =(char *)getenv("WORKDIR");
	memset (line321,'\0',321);
	memcpy(line321,sTmpEnv,strlen(sTmpEnv));
	if (checkEnvVar(line321,"WORKDIR",PATH_SIZE-8)==1){return 1;}
	if (line321!=NULL)
	{
		if (strchr(line321, ':' ) !=NULL)
		{
			memset (lineTmp321,'\0',321);
			memcpy(lineTmp321,line321,strlen(line321));
			token = strtok(lineTmp321, ":");
			if (token!=NULL)
			{
				memset (line321,'\0',321);
				strcpy(line321,token);
			}
		}
	}

	sprintf(gWorkPath,"%s%s",line321,DIR_SEPR);
	sprintf(gDataPath,"%s%sspool%s",line321,DIR_SEPR,DIR_SEPR);

	sTmpEnv =(char *)getenv("STRATIXARCHIVE");
	memset (line321,'\0',321);
	memcpy(line321,sTmpEnv,strlen(sTmpEnv));
	if (checkEnvVar(line321,"STRATIXARCHIVE",PATH_SIZE)==1){return 1;}
	if (line321 != NULL)
	{
		if (strchr(line321, ':' ) !=NULL)
		{
			memset (lineTmp321,'\0',321);
			memcpy(lineTmp321,line321,strlen(line321));
			token = strtok(lineTmp321, ":");
			if (token!=NULL)
			{
				memset (line321,'\0',321);
				strcpy(line321,token);
			}
		}
	}
	sprintf(gResubmitPath,"%s%s",line321,DIR_SEPR);

	sTmpEnv =(char *)getenv("STRATIXDATADIR");
	memset (line321,'\0',321);
	memcpy(line321,sTmpEnv,strlen(sTmpEnv));
	if (checkEnvVar(line321,"STRATIXDATADIR",PATH_SIZE-8)==1){return 1;}
	if (line321!=NULL)
	{
		if (strchr(line321, ':' ) !=NULL)
		{
			memset (lineTmp321,'\0',321);
			memcpy(lineTmp321,line321,strlen(line321));
			token = strtok(lineTmp321, ":");
			if (token!=NULL)
			{
				memset (line321,'\0',321);
				strcpy(line321,token);
			}
		}
	}

	sprintf(gImgPath,"%s%simages%s",line321,DIR_SEPR,DIR_SEPR);

	sTmpEnv =(char *)getenv("STRATIXTEMPLATEDIR");
	memset (line321,'\0', sizeof(line321));
	if (sTmpEnv != NULL)
	{
		iSize = strlen(sTmpEnv);
		if (iSize > 0)
		{
			if (strchr(sTmpEnv, ':' ) == NULL)
			{
				memset (line321,'\0', sizeof(line321));
				memcpy(line321, sTmpEnv, strlen(sTmpEnv));
				if (checkEnvVar(line321,"STRATIXTEMPLATEDIR",PATH_SIZE-8)==1){return 1;}
				giNumCstmTmplPaths = 1;
				sprintf(gStxCstmTmplPath[0].Nm, "%s%s", line321, DIR_SEPR);
			}
			else
			{
				giNumCstmTmplPaths = 0;
				memset (sCustomTmplPath, '\0', sizeof(sCustomTmplPath));
				memcpy(sCustomTmplPath, sTmpEnv, strlen(sTmpEnv));
				token = strtok(sCustomTmplPath, ":");
				while( token != NULL )
				{
					sprintf(gStxCstmTmplPath[giNumCstmTmplPaths].Nm,"%s%s",token,DIR_SEPR);
					giNumCstmTmplPaths++;
					/* Get next token: */
					token = strtok(NULL, ":");
					if (giNumCstmTmplPaths == NUM_STX_PATHS){break;}
				}
			}
		}
	}

	iDone=1;
	return 0;
}

int checkEnvVar( char *Val, char *Name, int MaxLen)
{
    if (Val == NULL)
    {
        return 1;
    }
    if ((int)strlen(Val) > MaxLen)
    {
        return 1;
    }
    return 0;
}

void cstmTerm(void)
{
	closeDB();

	if (gDataFlPtr != NULL)
	{
		/* If pointer is still open then close it */
		fclose(gDataFlPtr);
		gDataFlPtr = NULL;
	}

	return;
}

void srchCstmTmplFile(char *sTmplNm)
{
	int i=0;

	gCstmTmplSrchDone=1;
	for(i=0;i < giNumCstmTmplPaths; i++)
	{
		if(getMdfFlExst(gStxCstmTmplPath[i].Nm, sTmplNm) == 1)
		{
			gStxCstmTmplPath[i].iExist=1;
			return;
		}
	}
}

char *getCustomTmplPath(char *sTmplNm)
{/* 255636: Custom directory that contains the templates modified by customer */
	int i=0;

	memset(gCustomTmplPath, '\0', sizeof(gCustomTmplPath));

	if (gCstmTmplSrchDone == 0)
	{
		srchCstmTmplFile(sTmplNm);
	}

	for(i=0; i < giNumCstmTmplPaths; i++)
	{
		if(gStxCstmTmplPath[i].iExist == 1)
		{
			strcpy(gCustomTmplPath, gStxCstmTmplPath[i].Nm);
			break;
		}
	}
	return gCustomTmplPath;
}

int getMdfFlExst(char *sPath, char *sFlNm)
{
	char sTmplFl[351] = "";
	struct stat buf;
	int result=0;
	memset(sTmplFl,'\0', sizeof(sTmplFl));
	sprintf(sTmplFl,"%s%s",sPath,sFlNm);

	result = stat( sTmplFl, &buf );

	/* Check if statistics are valid: */
	if ( result == 0 )
	{
		/*File Exists*/
		return 1;
	} else
	{
		/*Error*/
		return 0;
	}
}

void srchMdfFile(char *mdfFlNm)
{
	int i=0;

	gSrchMdfDone=1;
	for(i=0;i<gNumStxPaths;i++)
	{
		if(getMdfFlExst(gStxPath[i].Nm,mdfFlNm)==1)
		{
			gStxPath[i].iExist=1;
			return;
		}
	}
}

char *getTmplPath(char *mdfNm)
{
	int iFound=0;
	int i=0;
    /*if(gInHouse==0)
    {*/
        return gMdfPath;
    /*}
    else
    {
        if (gSrchMdfDone==0)
        {
            srchMdfFile(mdfNm);
        }
        for(i=0;i<gNumStxPaths;i++)
        {
            if(gStxPath[i].iExist==1)
            {
                return gStxPath[i].Nm;
            }
        }
        return gStxPath[0].Nm;
    }*/
}

void fmtDate(char *inStr, char *sOutStr)
{/* This routine will return the formatted date for the corresponding input server value */
/*
         10  WS-FMT-INPUT-FLDS.
             15  WS-I-DATE-STRNG-VAL             PIC X(8).
			 15	 WS-I-DT-STY					 PIC X(30). "yyyy-MM-dd"
															M/d/yyyy
															d-M-yyyy
															d.M.yyyy
															d/MM/yyyy
															dd-MM-yyyy
															dd.MM.yy
															dd.MM.yyyy
															dd/MM/yyyy
															yyyy-MM-dd
															yyyy.MM.dd.
			 15	 WS-I-DT-SEPR		              PIC X(1).  "-"
			 15  WS-I-FMT-NUM                     PIC 9(1).
															1: As returned from scrlnc
															2: Suppress century in the year
															3: Suppress year

         10  WS-FMT-OUTPUT-FLDS.
             15  WS-O-SHRT-DT-STRNG              PIC X(15).

		Input example: "20121207yyyy-MM-dd                    -1"
*/

	char sYr[5]="", sMth[3]="", sDay[3]="", sDtVal[9]="", sDtSty[16]="", sDtSepr[2]="";
    int i =0;
    int iDtFmtLen = 0;
	char cFmtNum='\0', sFmtVal[16]="";


	memset(sOutStr, ' ', 15);

	memcpy(sDtVal, inStr, 8);
    if (memcmp(sDtVal, "00000000", 8) == 0) /* check if date is empty then pass blanks back */
    {
        return;
    }

	memcpy(sDtSty, inStr+8, 15);
    rtrim(sDtSty);
    iDtFmtLen = strlen(sDtSty);

	memset(sDtSepr, '\0', sizeof(sDtSepr));
	memcpy(sDtSepr, inStr+38, 1);
	cFmtNum = *(inStr+39);

    memset(sFmtVal, '\0', sizeof(sFmtVal));
	memset(sYr, '\0', sizeof(sYr));
    memset(sMth, '\0', sizeof(sMth));
    memset(sDay, '\0', sizeof(sDay));
	
	memcpy(sYr, sDtVal, 4);
    memcpy(sMth, sDtVal + 4, 2);
    memcpy(sDay, sDtVal + 6, 2);

    for (i=0; i<=iDtFmtLen; i++)
    {
		if ((memcmp(sDtSty + i, "YYYY", 4) == 0) || (memcmp(sDtSty + i, "yyyy", 4) == 0))
		{
			switch (cFmtNum)
			{
				case '1':
					strcat(sFmtVal, sYr);	
					break;
				case '2':
					strcat(sFmtVal, sYr+2);	/* suppress century  */
					break;
			}
			
			i = i + 4;
			if (cFmtNum == '3')
			{
				continue;
			}				
		}
		else if ((memcmp(sDtSty + i, "YY", 2) == 0) || (memcmp(sDtSty + i, "yy", 2) == 0))
		{
			if (cFmtNum != '3')
				strcat(sFmtVal, sYr + 2);

			i = i + 2;
		}
		else if ((memcmp(sDtSty + i, "MM", 2) == 0) || (memcmp(sDtSty + i, "mm", 2) == 0))
		{
			strcat(sFmtVal, sMth);
			i = i + 2;
		}
		else if ((memcmp(sDtSty + i, "M", 1) == 0) || (memcmp(sDtSty + i, "m", 1) == 0))
		{
			sprintf(sMth, "%01.0d", atoi(sMth));
			strcat(sFmtVal, sMth);
			i = i + 1;/*strlen(sMth);*/
		}
		else if ((memcmp(sDtSty + i, "DD", 2) == 0) || (memcmp(sDtSty + i, "dd", 2) == 0))
		{
			strcat(sFmtVal, sDay);
			i = i + 2;
		}
		else if ((memcmp(sDtSty + i, "D", 1) == 0) || (memcmp(sDtSty + i, "d", 1) == 0))
		{
			sprintf(sDay, "%01.0d", atoi(sDay));
			strcat(sFmtVal, sDay);
			i = i + 1;/*strlen(sDay);*/
		}

		strcat(sFmtVal, sDtSepr);

	}

	memcpy(sOutStr, sFmtVal, strlen(sFmtVal)-1);
	return;
}

void fmtTm(char *inStr, char *sOutStr)
{
    /* This routine will return the formatted date and time for the corresponding input server value */
/*
         10  WS-FMT-INPUT-FLDS.
             15  WS-I-TM-STRNG-VAL				PIC X(9).
			 15	 WS-I-TM-STY					PIC X(15).
													H.mm.ss
													H:mm:ss
													HH:mm.ss
													HH:mm:ss
													h:mm:ss tt
													hh:mm:ss tt
			 15	 WS-I-TM-SEPR					PIC X(1).  ":"
			 15  WS-I-FMT-NUM                   PIC 9(1).
															1: Print sec
															2: Suppress sec


         10  WS-FMT-OUTPUT-FLDS.
             15  WS-O-TM-STRNG              PIC X(15).

		Input example: "201212000H.mm.ss        .1"
*/
	time_t rawtime;
    struct tm * timeinfo;
    char sHr[3], sMin[3], sSec[3];
    char sAMPM[100];
    char sTrimAMPM[101];
	char cFmtNum, sFmtVal[16]="", sTmSty[16]="", sTmSepr[2]="";


	memset(sOutStr, ' ', 15);
    memset(sHr, '\0', sizeof(sHr));
    memset(sMin, '\0', sizeof(sMin));
    memset(sSec, '\0', sizeof(sSec));

	memcpy(sHr, inStr, 2);
    memcpy(sMin, inStr + 2, 2);
    memcpy(sSec, inStr + 4, 2);

	memset(sTmSepr, '\0', sizeof(sTmSepr));
	memcpy(sTmSepr, inStr+24, 1);
	cFmtNum = *(inStr+25);

    /* get current timeinfo and modify it to user's choice */
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    timeinfo->tm_hour = atoi(sHr);
    timeinfo->tm_min = atoi(sMin);
    timeinfo->tm_sec = atoi(sSec);

    /* Check the format and convert into 24 hour format*/
	memcpy(sTmSty, inStr+9, 15);
    rtrim(sTmSty);

    if ((strstr(sTmSty, "HH")!= NULL) || (strstr(sTmSty, "hh")!= NULL))
        strftime(sHr, 3, "%H", timeinfo);
    else
        strftime(sHr, 3, "%I", timeinfo);


    strcpy(sFmtVal, sHr);
    strcat(sFmtVal, sTmSepr);
    strcat(sFmtVal, sMin);

    /* Print seconds */
    if (cFmtNum == '1')
    {
        strcat(sFmtVal, sTmSepr);
        strcat(sFmtVal, sSec);
    }

    /* Add AM / PM */
    if ((strstr(sTmSty, "TT")!= NULL) || (strstr(sTmSty, "tt")!= NULL))
    {
        memset(sAMPM, '\0', sizeof(sAMPM));

        if (timeinfo->tm_hour > 11) /* PM */
			strcpy(sAMPM, "PM");
            /*gblGetLabel2(sAMPM, LONG_CPTN_VAR_SIZE + 1, "0000027709", SHRT_LBL, (char *)gblDocLng, (char *)gblBasLng, "en");*/
        else /* AM */
			strcpy(sAMPM, "AM");
            /*gblGetLabel2(sAMPM, LONG_CPTN_VAR_SIZE + 1, "0000027708", SHRT_LBL, (char *)gblDocLng, (char *)gblBasLng, "en");*/

		memcpy(sTrimAMPM, sAMPM, strlen(sAMPM));
        rtrim(sTrimAMPM);

        if ((int)strlen(sFmtVal) + 1 + (int)strlen(sTrimAMPM) < 16) /* if there is enough space then only */
        {
            strcat(sFmtVal, " ");
            strcat(sFmtVal, sTrimAMPM);
        }
    }

	memcpy(sOutStr, sFmtVal, strlen(sFmtVal));
}

void fmtDateTm(char *inStr, char *sOutStr)
{
	/*
         10  WS-FMT-INPUT-FLDS.
             15  WS-I-DATE-STRNG-VAL            PIC X(8).
			 15	 WS-I-DT-STY					PIC X(30).
			 15	 WS-I-DT-SEPR					PIC X(1).  "-"
             15  WS-I-TM-STRNG-VAL				PIC X(9).
			 15	 WS-I-TM-STY					PIC X(15).
 			 15	 WS-I-TM-SEPR					PIC X(1).  ":"
			 15  WS-I-FMT-NUM                     PIC 9(1).
													1: As returned from scrlnc
													2: Suppress century in the year, suppress sec
													3: Suppress year, suppress sec

         10  WS-FMT-OUTPUT-FLDS.
             15  WS-O-SHRT-DT-STRNG              PIC X(31).

		Input example: "20121107yyyy-dd-MM                    -201212000HH.mm.ss       .2"
*/

	char sRtnStr[17] = "";
	char sInDtStr[41] = "";
	char sInTmStr[27] = "";
	char cFmtNum = '\0';

	memset(sInDtStr, '\0', sizeof(sInDtStr));
	memset(sInTmStr, '\0', sizeof(sInTmStr));

	memcpy(sInDtStr, inStr, 39);
	sInDtStr[39] = *(inStr+64);
		
	memcpy(sInTmStr, inStr+39, 25);
	sInTmStr[25] = '2';

	fmtDate(sInDtStr, sRtnStr);
	rtrim(sRtnStr);
	strcat(sRtnStr, " ");
	strcpy(sOutStr, sRtnStr);

	fmtTm(sInTmStr, sOutStr+strlen(sRtnStr));

	return;
}

int pvtIofD(int year, int month, int day)
{
	int year_diff;
	int num_days = 0;
	char tempreturn[9];

	year_diff = year - BEGIN_YEAR;

	num_days = ((int)(year_diff / 400)) * FOUR_HUNDRED_YEARS_NUM_DAYS;
	year_diff -= ((int)(year_diff / 400)) * 400;

	num_days += cumulDaysPer_400Years[((int)(year_diff / 100))];
	year_diff -= ((int)(year_diff / 100)) * 100;

	if((year%400) < 100)
	{
		num_days += cumulDaysPer_LY100Years[((int)(year_diff / 4))];
		year_diff -= ((int)(year_diff / 4)) * 4;
	}
	else
	{
		num_days += cumulDaysPer_100Years[((int)(year_diff / 4))];
		year_diff -= ((int)(year_diff / 4)) * 4;
	}

	if(((year%100) < 4) && ((year%400) > 99))
		num_days += cumulDaysPer_4Years[year_diff];
	else num_days += cumulDaysPer_LY4Years[year_diff];


	if((!(year % 4)) && ((year % 100) || (!(year % 400))))
	{
		num_days += cumulDaysPer_LYMonth[month-1] + day;
	}
	else
	{
		num_days += cumulDaysPer_Month[month-1] + day;
	}

	return num_days;
}

int pvtWeekDay(char *date, char *nameofday)
{
	int year;
	int day;
	int month;
	int days;
	int i;

	for(i = 0; i < 8; i++)
	if((date[i] < '0') || (date[i] > '9'))
	{
		memcpy(nameofday, "999", 3);
		return -1;
	}

	if(convertCheckDate(date,&year, &month, &day))
	{
		memcpy(nameofday, "999", 3);
		return -1;
	}

	days = pvtIofD(year, month, day);

	switch((days - 1) % 7)
	{
		case 0 : memcpy(nameofday, "SAT", 3);
				 break;
		case 1 : memcpy(nameofday, "SUN", 3);
				 break;
		case 2 : memcpy(nameofday, "MON", 3);
				 break;
		case 3 : memcpy(nameofday, "TUE", 3);
				 break;
		case 4 : memcpy(nameofday, "WED", 3);
				 break;
		case 5 : memcpy(nameofday, "THU", 3);
				 break;
		case 6 : memcpy(nameofday, "FRI", 3);
				 break;
	}

	return days;
}

void getWeekday(char *date, char *nameofday)
{
	pvtWeekDay(date, nameofday);
}

void replace5by3(char *st2)
{ /* replaces the 5 after the decimal point by 3.
		assumes that the only time fraction for Standard or Daylight is that of 30 minutes */
	char *st1;

	st1=st2;
	while (*st1 != '.' && *st1 != '\0')
		st1++;
	if (*st1 == '.')
	{
		st1++;
		if (*st1 == '5')
			*st1 = '3';
	}	
	return;
}

void convDttmToLocal(char *inString,char *tab,char *tabKey,char *comId, char *cty,char *st,char *pv,char *status)
{
/*
 * 	EXEC SQL begin declare section;
 */
#line 1821 "../common/utilities.ec"
#line 1822 "../common/utilities.ec"
  char *database;
  char *server;
  char tzCty[4];
  char tzTmzn[6];
  char tzProv[3];
  char keyCol[8];
  char comKey[4];
  char tzStd[11];
  char tzDst[11];
float tzStdOfs = 0;
float tzDstOfs = 0;
int tzStMth = 0;
int tzStWk = 0;
int tzStDy;
int tzStHh;
int tzStMm;
int tzEndMth = 0;
int tzEndWk = 0;
int tzEndDy;
int tzEndHh;
int tzEndMm;
int rowCount = 0;
  char str1[100];
/*
 * 	EXEC SQL end declare section;
 */
#line 1845 "../common/utilities.ec"

	char fract[4];
	char outStr[5];
	char outString[20] = "\0";
	char dowString[12];
	char day[4];
	char *pt1, *pt2;
	char tabType[2];
	int year, month, days;
	/*char strTZ[35] = "\0";*/ /* to be commented out before incorporating into pln_sql.ec */
	char curTZ[30] = "\0"; /* to save the current TZ value */

	char str2[10] = "\0";
	time_t time1;
	struct tm ltp;
	struct tm *ltp1;
	char *datestring; /* used for debugging statements (commented out) */
	char temp[10];
	int len;
	int applyDst = 1;

	memset(temp,'\0',10);
	memset(day, '\0',4);
	memset(str1,'\0',100);
	memset(str2,'\0',10);

	/* check the input date value for errors*/
	memcpy(temp,inString,8);
	temp[8]='\0';
	if (convertCheckDate(temp, &year, &month, &days))
	{
		memcpy(status,"6",1);
		return;
	}

	/* unravel the input string and store the parts in tm fields */
	memcpy(temp,inString,4);
	temp[4]='\0';
	ltp.tm_year=atoi(temp) - 1900; /* years since 1900 */

	memcpy(temp,inString+4,2);
	temp[2] = '\0';
	ltp.tm_mon = atoi(temp) -1 ; /* months numbered 0-11 */

	memcpy(temp,inString+6,2);
	temp[2] = '\0';
	ltp.tm_mday = atoi(temp);

	memcpy(temp,inString+8,2);
	temp[2] = '\0';
	ltp.tm_hour = atoi(temp);

	memcpy(temp,inString+10,2);
	temp[2] = '\0';
	ltp.tm_min = atoi(temp);

	memcpy(temp,inString+12,2);
	temp[2] = '\0';
	ltp.tm_sec = atoi(temp);

	memcpy(fract, inString+14,3);
	fract[3]='\0';

	ltp.tm_isdst=-1; /* decide at run time whether DST is to be used */

	strcpy(curTZ, getenv("TZ"));
	sprintf(strTZ, "TZ=%s", curTZ);
	putenv("TZ=Dummy_allocation_to_allow_malloc_sufficient_space_for_future");
	putenv("TZ=GMT0");
	tzset();
	time1=mktime(&ltp);
	datestring = ctime(&time1);

	/* check the type of input arguments */
	memcpy(tabType,tab,1);
	if (tabType[0] == 's')
	{
		memcpy(tzCty,cty,3);
		tzCty[3] = '\0';
		memcpy(tzTmzn,st,5);
		tzTmzn[5] = '\0';
		memcpy(tzProv,pv,2);
		tzProv[2] = '\0';
	}
	else if ((tabType[0] == 'b') || (tabType[0] == 'w'))
	{
		memcpy(keyCol,tabKey,3);
		keyCol[3]='\0';
		memcpy(comKey,comId,3);
		comKey[3]='\0';
	}
	else
	{
		memcpy(status,"2",1);
		putenv(strTZ);
		return;
	}

	/* Use the data in the scrtzn table to make up the TZ string for the
	local environment */

	/* if the input is on scrbrh or scrwhs tables, get the country and timezones
	from the table using the given key values */
	if (tabType[0] == 'b')
	{
/*
 * 		EXEC SQL select brh_cty, brh_tmzn, brh_st_prov into :tzCty, :tzTmzn, :tzProv
 * 			from scrbrh_rec
 * 			where brh_brh = :keyCol and brh_cmpy_id = :comKey;
 */
#line 1950 "../common/utilities.ec"
  {
#line 1952 "../common/utilities.ec"
  static const char *sqlcmdtxt[] =
#line 1952 "../common/utilities.ec"
    {
#line 1952 "../common/utilities.ec"
    "select brh_cty , brh_tmzn , brh_st_prov from scrbrh_rec where brh_brh = ? and brh_cmpy_id = ?",
    0
    };
#line 1952 "../common/utilities.ec"
static ifx_cursor_t _SQ0 = {0};
  static ifx_sqlvar_t _sqibind[] = 
    {
      { 100, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
#line 1952 "../common/utilities.ec"
    };
  static ifx_sqlvar_t _sqobind[] = 
    {
      { 100, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
#line 1952 "../common/utilities.ec"
    };
#line 1952 "../common/utilities.ec"
  _sqibind[0].sqldata = keyCol;
#line 1952 "../common/utilities.ec"
  _sqibind[1].sqldata = comKey;
#line 1952 "../common/utilities.ec"
  _sqobind[0].sqldata = tzCty;
#line 1952 "../common/utilities.ec"
  _sqobind[1].sqldata = tzTmzn;
#line 1952 "../common/utilities.ec"
  _sqobind[2].sqldata = tzProv;
#line 1952 "../common/utilities.ec"
  sqli_slct(ESQLINTVERSION, &_SQ0,sqlcmdtxt,2,_sqibind,3,_sqobind,0,(ifx_literal_t *)0,(ifx_namelist_t *)0,0);
#line 1952 "../common/utilities.ec"
  }

		if (sqlca.sqlcode == 100)
		{
			memcpy(status,"3",1);
			putenv(strTZ);
			return;
		}
	}
	else if (tabType[0] == 'w')
	{
/*
 * 		EXEC SQL select whs_cty, whs_tmzn, whs_st_prov into :tzCty, :tzTmzn, :tzProv
 * 			from scrwhs_rec
 * 			where whs_whs = :keyCol and whs_cmpy_id = :comKey;
 */
#line 1963 "../common/utilities.ec"
  {
#line 1965 "../common/utilities.ec"
  static const char *sqlcmdtxt[] =
#line 1965 "../common/utilities.ec"
    {
#line 1965 "../common/utilities.ec"
    "select whs_cty , whs_tmzn , whs_st_prov from scrwhs_rec where whs_whs = ? and whs_cmpy_id = ?",
    0
    };
#line 1965 "../common/utilities.ec"
static ifx_cursor_t _SQ0 = {0};
  static ifx_sqlvar_t _sqibind[] = 
    {
      { 100, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
#line 1965 "../common/utilities.ec"
    };
  static ifx_sqlvar_t _sqobind[] = 
    {
      { 100, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
#line 1965 "../common/utilities.ec"
    };
#line 1965 "../common/utilities.ec"
  _sqibind[0].sqldata = keyCol;
#line 1965 "../common/utilities.ec"
  _sqibind[1].sqldata = comKey;
#line 1965 "../common/utilities.ec"
  _sqobind[0].sqldata = tzCty;
#line 1965 "../common/utilities.ec"
  _sqobind[1].sqldata = tzTmzn;
#line 1965 "../common/utilities.ec"
  _sqobind[2].sqldata = tzProv;
#line 1965 "../common/utilities.ec"
  sqli_slct(ESQLINTVERSION, &_SQ0,sqlcmdtxt,2,_sqibind,3,_sqobind,0,(ifx_literal_t *)0,(ifx_namelist_t *)0,0);
#line 1965 "../common/utilities.ec"
  }
		if (sqlca.sqlcode == 100)
		{
			memcpy(status,"4",1);
			putenv(strTZ);
			return;
		}
	}
	/* in other cases, the country and timezones are given as input directly*/

	/* read the scrtzx table to determine if DST is to be applied */
/*
 * 	EXEC SQL select count(*) into :rowCount from scrtzx_rec  where trim(tzx_cty) = :tzCty and trim(tzx_st_prov)=:tzProv
 * 			and trim(tzx_tmzn)=:tzTmzn and tzx_dst_aplc = 0;
 */
#line 1976 "../common/utilities.ec"
  {
#line 1977 "../common/utilities.ec"
  static const char *sqlcmdtxt[] =
#line 1977 "../common/utilities.ec"
    {
#line 1977 "../common/utilities.ec"
    "select count ( * ) from scrtzx_rec where trim ( tzx_cty ) = ? and trim ( tzx_st_prov ) = ? and trim ( tzx_tmzn ) = ? and tzx_dst_aplc = 0",
    0
    };
#line 1977 "../common/utilities.ec"
static ifx_cursor_t _SQ0 = {0};
  static ifx_sqlvar_t _sqibind[] = 
    {
      { 100, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
#line 1977 "../common/utilities.ec"
    };
  static ifx_sqlvar_t _sqobind[] = 
    {
      { 102, sizeof(rowCount), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
#line 1977 "../common/utilities.ec"
    };
#line 1977 "../common/utilities.ec"
  _sqibind[0].sqldata = tzCty;
#line 1977 "../common/utilities.ec"
  _sqibind[1].sqldata = tzProv;
#line 1977 "../common/utilities.ec"
  _sqibind[2].sqldata = tzTmzn;
#line 1977 "../common/utilities.ec"
  _sqobind[0].sqldata = (char *) &rowCount;
#line 1977 "../common/utilities.ec"
  sqli_slct(ESQLINTVERSION, &_SQ0,sqlcmdtxt,3,_sqibind,1,_sqobind,0,(ifx_literal_t *)0,(ifx_namelist_t *)0,0);
#line 1977 "../common/utilities.ec"
  }
	if (rowCount > 0)
		applyDst = 0; /* do not apply DST */

/*
 * 	EXEC SQL select tzn_std_tmzn, tzn_dylgt_tmzn, tzn_std_ut_ofst, tzn_dylgt_ut_ofst, tzn_dylgt_strt_mth, tzn_dylgt_strt_wk, tzn_dylgt_strt_dy,
 * 			tzn_dylgt_strt_hr, tzn_dylgt_strt_mm, tzn_dylgt_end_mth, tzn_dylgt_end_wk, tzn_dylgt_end_dy, tzn_dylgt_end_hr, tzn_dylgt_end_mm
 * 			into :tzStd, :tzDst, :tzStdOfs, :tzDstOfs, :tzStMth, :tzStWk, :tzStDy,
 * 				:tzStHh, :tzStMm, :tzEndMth, :tzEndWk, :tzEndDy, :tzEndHh, :tzEndMm
 * 			from scrtzn_rec where trim(tzn_cty)=:tzCty and trim(tzn_tmzn)=:tzTmzn;
 */
#line 1981 "../common/utilities.ec"
  {
#line 1985 "../common/utilities.ec"
  static const char *sqlcmdtxt[] =
#line 1985 "../common/utilities.ec"
    {
#line 1985 "../common/utilities.ec"
    "select tzn_std_tmzn , tzn_dylgt_tmzn , tzn_std_ut_ofst , tzn_dylgt_ut_ofst , tzn_dylgt_strt_mth , tzn_dylgt_strt_wk , tzn_dylgt_strt_dy , tzn_dylgt_strt_hr , tzn_dylgt_strt_mm , tzn_dylgt_end_mth , tzn_dylgt_end_wk , tzn_dylgt_end_dy , tzn_dylgt_end_hr , tzn_dylgt_end_mm from scrtzn_rec where trim ( tzn_cty ) = ? and trim ( tzn_tmzn ) = ?",
    0
    };
#line 1985 "../common/utilities.ec"
static ifx_cursor_t _SQ0 = {0};
  static ifx_sqlvar_t _sqibind[] = 
    {
      { 100, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
#line 1985 "../common/utilities.ec"
    };
  static ifx_sqlvar_t _sqobind[] = 
    {
      { 100, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 104, sizeof(tzStdOfs), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 104, sizeof(tzDstOfs), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzStMth), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzStWk), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzStDy), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzStHh), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzStMm), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzEndMth), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzEndWk), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzEndDy), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzEndHh), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzEndMm), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
#line 1985 "../common/utilities.ec"
    };
#line 1985 "../common/utilities.ec"
  _sqibind[0].sqldata = tzCty;
#line 1985 "../common/utilities.ec"
  _sqibind[1].sqldata = tzTmzn;
#line 1985 "../common/utilities.ec"
  _sqobind[0].sqldata = tzStd;
#line 1985 "../common/utilities.ec"
  _sqobind[1].sqldata = tzDst;
#line 1985 "../common/utilities.ec"
  _sqobind[2].sqldata = (char *) &tzStdOfs;
#line 1985 "../common/utilities.ec"
  _sqobind[3].sqldata = (char *) &tzDstOfs;
#line 1985 "../common/utilities.ec"
  _sqobind[4].sqldata = (char *) &tzStMth;
#line 1985 "../common/utilities.ec"
  _sqobind[5].sqldata = (char *) &tzStWk;
#line 1985 "../common/utilities.ec"
  _sqobind[6].sqldata = (char *) &tzStDy;
#line 1985 "../common/utilities.ec"
  _sqobind[7].sqldata = (char *) &tzStHh;
#line 1985 "../common/utilities.ec"
  _sqobind[8].sqldata = (char *) &tzStMm;
#line 1985 "../common/utilities.ec"
  _sqobind[9].sqldata = (char *) &tzEndMth;
#line 1985 "../common/utilities.ec"
  _sqobind[10].sqldata = (char *) &tzEndWk;
#line 1985 "../common/utilities.ec"
  _sqobind[11].sqldata = (char *) &tzEndDy;
#line 1985 "../common/utilities.ec"
  _sqobind[12].sqldata = (char *) &tzEndHh;
#line 1985 "../common/utilities.ec"
  _sqobind[13].sqldata = (char *) &tzEndMm;
#line 1985 "../common/utilities.ec"
  sqli_slct(ESQLINTVERSION, &_SQ0,sqlcmdtxt,2,_sqibind,14,_sqobind,0,(ifx_literal_t *)0,(ifx_namelist_t *)0,0);
#line 1985 "../common/utilities.ec"
  }

	if (sqlca.sqlcode == 100)
	{
		memcpy(status,"5",1);
		putenv(strTZ);
		return;
	}

	/* make correction for "last week" in March if March has 5 Sundays in the year.
	This correction is only for European Union states abiding by the "last week
	in March" convention for the start of the DST */
	memcpy(temp,inString,4);
	temp[4]='\0';
	if ((tzStMth == 3) && (tzStWk == 4)) /* last week of March */
	{ /* find out what day of the week the 1st of March for that year is */
		memset(dowString,'\0',11);
		/* call a function from "pln_dateroutine" to determine the day of the week */
		sprintf(dowString,"%s0301",temp);
		getWeekday(dowString,day);
		if (memcmp(day,"999",3)==0)
		{
			memcpy(status,"6",1);
			putenv(strTZ);
			return;
		}
		if ((memcmp(day,"SUN",3)==0) || (memcmp(day,"FRI",3)==0) || (memcmp(day,"SAT",3)==0))
			tzStWk = 5;
	}

	/* make a similar correction for the "last week" in October to mark the end of the
	DST. This applies to EU  */
	if ((tzEndMth == 10) && (tzEndWk == 4)) /* last week of October */
	{ /* find out what day of the week the 1st of October for that year is */
		memset(dowString,'\0',11);
		sprintf(dowString,"%s1001",temp);
		getWeekday(dowString,day);
		if (memcmp(day,"999",3)==0)
		{
			memcpy(status,"6",1);
			putenv(strTZ);
			return;
		}
		if ((memcmp(day,"SUN",3)==0) || (memcmp(day,"FRI",3)==0) || (memcmp(day,"SAT",3)==0))
			tzEndWk = 5;
	}

	/* assemble the TZ string */
	/* a typical TZ string should be of the form:
		"TZ=EST5:00EDT4:00,M4.5.0/2:00,M10.4.0/2:00"*/
	tzStdOfs = tzStdOfs - 2*tzStdOfs; /* reverse the sign on the offset value */
	/* convert the decimal part of the Offset into a minute representation */
	sprintf(str2,"%6.2f", tzStdOfs);
	replace5by3(str2);
	len=strlen(tzStd);
	rtrim(tzStd);
	sprintf(str1,"TZ=%s%s", tzStd, str2); /* only these two fields are mandatory */
	if ((tzDst[0] != ' ') && (tzDst[0] != '\0') && applyDst)
	{
		len=strlen(tzDst);
		rtrim(tzDst);
		sprintf(str1, "%s%s", str1, tzDst);
		if (tzDstOfs != 0)
		{
			tzDstOfs = tzDstOfs - 2*tzDstOfs; /* reverse the sign on the offset value */
			sprintf(str2,"%6.2f", tzDstOfs);
			replace5by3(str2);
			sprintf(str1, "%s%s", str1, str2);
			if (tzStMth != 0)
			{
				sprintf(str1, "%s,M%i.%i.%i", str1, tzStMth,tzStWk,tzStDy);
				if (tzStHh != 0)
				{
					if (tzStMm < 10)
					sprintf(str1, "%s/%i:0%i", str1, tzStHh,tzStMm);
					else
					sprintf(str1, "%s/%i:%i", str1, tzStHh,tzStMm);
				}
				if (tzEndMth != 0)
				{
					sprintf(str1, "%s,M%i.%i.%i", str1, tzEndMth, tzEndWk,tzEndDy);
					if (tzEndHh != 0)
					{
						if (tzEndMm < 10)
							sprintf(str1, "%s/%i:0%i", str1, tzEndHh, tzEndMm);
					else
						sprintf(str1, "%s/%i:%i", str1, tzEndHh, tzEndMm);
					}
				}
			}
		}
	}

	/* prepare the TZ string according to required format */
	/* first remove all extra spaces in the string */
	pt1 = str1;
	while (*pt1 != '\0')
	{
		if (*pt1 == ' ')
		{
			pt2 = pt1;
			while (*(pt2+1) != '\0')
			{
				*pt2 = *(pt2+1);
				pt2++;
			}
			*pt2='\0';
		}
		if (*pt1 != ' ')
		pt1++;
	}
	/* now change the period character into a colon for all hour:minute representations */
	pt1 = str1;
	while ((*pt1 != ',') && (*pt1 != '\0'))
	{
		if (*pt1 == '.')
			*pt1 = ':';
		pt1++;
	}

	putenv(str1);
	tzset();
	ltp1=(struct tm *)localtime(&time1);

	/* assemble the outstring from the values in ltp1 structure */

	memset(outStr,'\0',5);
	sprintf(outStr, "%4d", 1900+ltp1->tm_year);
	memcpy(outString,outStr,4);
	if (ltp1->tm_mon >= 9)
		sprintf(outStr,"%2d", ltp1->tm_mon+1);
	else
		sprintf(outStr,"0%1d", ltp1->tm_mon+1);
	memcpy(outString+4,outStr,2);

	if (ltp1->tm_mday >= 10)
		sprintf(outStr,"%2d", ltp1->tm_mday);
	else
		sprintf(outStr,"0%1d", ltp1->tm_mday);
	memcpy(outString+6,outStr,2);

	if (ltp1->tm_hour >= 10)
		sprintf(outStr,"%2d", ltp1->tm_hour);
	else
		sprintf(outStr,"0%1d", ltp1->tm_hour);
	memcpy(outString+8,outStr,2);

	if (ltp1->tm_min >= 10)
		sprintf(outStr,"%2d", ltp1->tm_min);
	else
		sprintf(outStr,"0%1d", ltp1->tm_min);
	memcpy(outString+10,outStr,2);

	if (ltp1->tm_sec >= 10)
		sprintf(outStr,"%2d", ltp1->tm_sec);
	else
		sprintf(outStr,"0%1d", ltp1->tm_sec);
	memcpy(outString+12,outStr,2);

	memcpy(outString+14,fract,3);

	memcpy(inString,outString,17);
	memcpy(status,"0",1);
	putenv(strTZ);
	return ;
}

void convDttmToGmt(char *inString,char *tab,char *tabKey,char *comId, char *cty,char *st,char *pv,char *status)
{
/*
 * 	EXEC SQL begin declare section;
 */
#line 2154 "../common/utilities.ec"
#line 2155 "../common/utilities.ec"
  char *database;
  char *server;
  char tzCty[4];
  char tzTmzn[6];
  char tzProv[3];
  char tzStd[11];
  char tzDst[11];
  char keyCol[8];
  char comKey[4];
float tzStdOfs = 0;
float tzDstOfs = 0;
int tzStMth = 0;
int tzStWk = 0;
int tzStDy;
int tzStHh;
int tzStMm;
int tzEndMth = 0;
int tzEndWk = 0;
int tzEndDy;
int tzEndHh;
int tzEndMm;
int rowCount = 0;
  char str1[100] = "\0";
/*
 *   	EXEC SQL end declare section;
 */
#line 2178 "../common/utilities.ec"


	char fract[4];
    char outStr[5];
    char outString[20];
    char dowString[12];
    char day[4];
    char *pt1, *pt2;
    char tabType[2];
    int year, month, days;
    /* char strTZ[35] = "\0"; */ /* to be commented out before incorporating into pln_sql.ec */
    char curTZ[30] = "\0"; /* to save the current TZ value */
    char str2[10] = "\0";
	time_t time1;
    struct tm ltp;
    struct tm *ltp1;
    char *datestring; /* used for debugging statements (commented out) */
    char temp[10];
    int len;
    int applyDst = 1;

    memset(temp,'\0',10);
    memset(dowString,'\0',12);
    memset(day,'\0',4);
    memset(outString,'\0',20);
    memset(str1,'\0',100);
    memset(str2,'\0',10);

    /* check the input date value for errors*/
    memcpy(temp,inString,8);
    temp[8]='\0';
    if (convertCheckDate(temp, &year, &month, &days))
    {
		memcpy(status,"6",1);
		return;
    }

    /* unravel the input string and store the parts in tm fields */
    memcpy(temp,inString,4);
    temp[4]='\0';
    ltp.tm_year=atoi(temp) - 1900; /* years since 1900 */

    memcpy(temp,inString+4,2);
    temp[2] = '\0';
    ltp.tm_mon = atoi(temp) -1 ; /* months numbered 0-11 */

    memcpy(temp,inString+6,2);
    temp[2] = '\0';
    ltp.tm_mday = atoi(temp);

    memcpy(temp,inString+8,2);
    temp[2] = '\0';
    ltp.tm_hour = atoi(temp);

    memcpy(temp,inString+10,2);
    temp[2] = '\0';
    ltp.tm_min = atoi(temp);

    memcpy(temp,inString+12,2);
    temp[2] = '\0';
    ltp.tm_sec = atoi(temp);

    memcpy(fract, inString+14,3);
    fract[3]='\0';

    ltp.tm_isdst=-1; /* decide at run time whether DST is to be used */

    strcpy(curTZ, getenv("TZ"));
    sprintf(strTZ, "TZ=%s", curTZ);
    putenv("TZ=Dummy_allocation_to_allow_malloc_sufficient_space_for_future");

     /* check the type of input arguments */
    memcpy(tabType,tab,1);
    if (tabType[0] == 's')
    {
        memcpy(tzCty,cty,3);
        tzCty[3] = '\0';
        memcpy(tzTmzn,st,5);
        tzTmzn[5] = '\0';
        memcpy(tzProv,pv,2);
        tzProv[2] = '\0';
    }
    else if ((tabType[0] == 'b') || (tabType[0] == 'w'))
    {
		memcpy(keyCol,tabKey,3);
		keyCol[3]='\0';
		memcpy(comKey, comId,3);
		comKey[3]='\0';
    }
    else
    {
		memcpy(status,"2",1);
		putenv(strTZ);
		return;
    }

    /* Use the data in the scrtzn table to make up the TZ string for the
       local environment */

     /* if the input is on scrbrh or scrwhs tables, get the country and timezones
       from the table using the given key value */
    if (tabType[0] == 'b')
    {
      	
/*
 * 		EXEC SQL select brh_cty, brh_tmzn, brh_st_prov into :tzCty, :tzTmzn, :tzProv
 * 			from scrbrh_rec
 * 			where brh_brh = :keyCol and brh_cmpy_id = :comKey;
 */
#line 2282 "../common/utilities.ec"
  {
#line 2284 "../common/utilities.ec"
  static const char *sqlcmdtxt[] =
#line 2284 "../common/utilities.ec"
    {
#line 2284 "../common/utilities.ec"
    "select brh_cty , brh_tmzn , brh_st_prov from scrbrh_rec where brh_brh = ? and brh_cmpy_id = ?",
    0
    };
#line 2284 "../common/utilities.ec"
static ifx_cursor_t _SQ0 = {0};
  static ifx_sqlvar_t _sqibind[] = 
    {
      { 100, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
#line 2284 "../common/utilities.ec"
    };
  static ifx_sqlvar_t _sqobind[] = 
    {
      { 100, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
#line 2284 "../common/utilities.ec"
    };
#line 2284 "../common/utilities.ec"
  _sqibind[0].sqldata = keyCol;
#line 2284 "../common/utilities.ec"
  _sqibind[1].sqldata = comKey;
#line 2284 "../common/utilities.ec"
  _sqobind[0].sqldata = tzCty;
#line 2284 "../common/utilities.ec"
  _sqobind[1].sqldata = tzTmzn;
#line 2284 "../common/utilities.ec"
  _sqobind[2].sqldata = tzProv;
#line 2284 "../common/utilities.ec"
  sqli_slct(ESQLINTVERSION, &_SQ0,sqlcmdtxt,2,_sqibind,3,_sqobind,0,(ifx_literal_t *)0,(ifx_namelist_t *)0,0);
#line 2284 "../common/utilities.ec"
  }

		if (sqlca.sqlcode == 100)
		{
			memcpy(status,"3",1);
			putenv(strTZ);
			return;
		}

    }
    else if (tabType[0] == 'w')
    {
/*
 * 		EXEC SQL select whs_cty, whs_tmzn, whs_st_prov into :tzCty, :tzTmzn, :tzProv
 * 			from scrwhs_rec
 * 			where whs_whs = :keyCol and whs_cmpy_id = :comKey;
 */
#line 2296 "../common/utilities.ec"
  {
#line 2298 "../common/utilities.ec"
  static const char *sqlcmdtxt[] =
#line 2298 "../common/utilities.ec"
    {
#line 2298 "../common/utilities.ec"
    "select whs_cty , whs_tmzn , whs_st_prov from scrwhs_rec where whs_whs = ? and whs_cmpy_id = ?",
    0
    };
#line 2298 "../common/utilities.ec"
static ifx_cursor_t _SQ0 = {0};
  static ifx_sqlvar_t _sqibind[] = 
    {
      { 100, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
#line 2298 "../common/utilities.ec"
    };
  static ifx_sqlvar_t _sqobind[] = 
    {
      { 100, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
#line 2298 "../common/utilities.ec"
    };
#line 2298 "../common/utilities.ec"
  _sqibind[0].sqldata = keyCol;
#line 2298 "../common/utilities.ec"
  _sqibind[1].sqldata = comKey;
#line 2298 "../common/utilities.ec"
  _sqobind[0].sqldata = tzCty;
#line 2298 "../common/utilities.ec"
  _sqobind[1].sqldata = tzTmzn;
#line 2298 "../common/utilities.ec"
  _sqobind[2].sqldata = tzProv;
#line 2298 "../common/utilities.ec"
  sqli_slct(ESQLINTVERSION, &_SQ0,sqlcmdtxt,2,_sqibind,3,_sqobind,0,(ifx_literal_t *)0,(ifx_namelist_t *)0,0);
#line 2298 "../common/utilities.ec"
  }
		if (sqlca.sqlcode == 100)
		{
			memcpy(status,"4",1);
			putenv(strTZ);
			return;
		}
    }
	
	 /* in other cases, the country and timezones are given as input directly*/

	/* read the scrtzx table to determine if DST is to be applied */
/*
 * 	EXEC SQL select count(*) into :rowCount from scrtzx_rec  where trim(tzx_cty) = :tzCty and trim(tzx_st_prov)=:tzProv and trim(tzx_tmzn)=:tzTmzn and tzx_dst_aplc = 0;
 */
#line 2310 "../common/utilities.ec"
  {
#line 2310 "../common/utilities.ec"
  static const char *sqlcmdtxt[] =
#line 2310 "../common/utilities.ec"
    {
#line 2310 "../common/utilities.ec"
    "select count ( * ) from scrtzx_rec where trim ( tzx_cty ) = ? and trim ( tzx_st_prov ) = ? and trim ( tzx_tmzn ) = ? and tzx_dst_aplc = 0",
    0
    };
#line 2310 "../common/utilities.ec"
static ifx_cursor_t _SQ0 = {0};
  static ifx_sqlvar_t _sqibind[] = 
    {
      { 100, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
#line 2310 "../common/utilities.ec"
    };
  static ifx_sqlvar_t _sqobind[] = 
    {
      { 102, sizeof(rowCount), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
#line 2310 "../common/utilities.ec"
    };
#line 2310 "../common/utilities.ec"
  _sqibind[0].sqldata = tzCty;
#line 2310 "../common/utilities.ec"
  _sqibind[1].sqldata = tzProv;
#line 2310 "../common/utilities.ec"
  _sqibind[2].sqldata = tzTmzn;
#line 2310 "../common/utilities.ec"
  _sqobind[0].sqldata = (char *) &rowCount;
#line 2310 "../common/utilities.ec"
  sqli_slct(ESQLINTVERSION, &_SQ0,sqlcmdtxt,3,_sqibind,1,_sqobind,0,(ifx_literal_t *)0,(ifx_namelist_t *)0,0);
#line 2310 "../common/utilities.ec"
  }
	if (rowCount > 0)
		applyDst = 0; /* do not apply DST */

/*
 * 		EXEC SQL select tzn_std_tmzn, tzn_dylgt_tmzn, tzn_std_ut_ofst, tzn_dylgt_ut_ofst, tzn_dylgt_strt_mth, tzn_dylgt_strt_wk, tzn_dylgt_strt_dy,
 * 			tzn_dylgt_strt_hr, tzn_dylgt_strt_mm, tzn_dylgt_end_mth, tzn_dylgt_end_wk, tzn_dylgt_end_dy, tzn_dylgt_end_hr, tzn_dylgt_end_mm
 * 			into :tzStd, :tzDst, :tzStdOfs, :tzDstOfs, :tzStMth, :tzStWk, :tzStDy,
 * 				:tzStHh, :tzStMm, :tzEndMth, :tzEndWk, :tzEndDy, :tzEndHh, :tzEndMm
 * 			from scrtzn_rec where trim(tzn_cty)=:tzCty and trim(tzn_tmzn)=:tzTmzn;
 */
#line 2314 "../common/utilities.ec"
  {
#line 2318 "../common/utilities.ec"
  static const char *sqlcmdtxt[] =
#line 2318 "../common/utilities.ec"
    {
#line 2318 "../common/utilities.ec"
    "select tzn_std_tmzn , tzn_dylgt_tmzn , tzn_std_ut_ofst , tzn_dylgt_ut_ofst , tzn_dylgt_strt_mth , tzn_dylgt_strt_wk , tzn_dylgt_strt_dy , tzn_dylgt_strt_hr , tzn_dylgt_strt_mm , tzn_dylgt_end_mth , tzn_dylgt_end_wk , tzn_dylgt_end_dy , tzn_dylgt_end_hr , tzn_dylgt_end_mm from scrtzn_rec where trim ( tzn_cty ) = ? and trim ( tzn_tmzn ) = ?",
    0
    };
#line 2318 "../common/utilities.ec"
static ifx_cursor_t _SQ0 = {0};
  static ifx_sqlvar_t _sqibind[] = 
    {
      { 100, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
#line 2318 "../common/utilities.ec"
    };
  static ifx_sqlvar_t _sqobind[] = 
    {
      { 100, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 100, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 104, sizeof(tzStdOfs), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 104, sizeof(tzDstOfs), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzStMth), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzStWk), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzStDy), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzStHh), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzStMm), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzEndMth), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzEndWk), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzEndDy), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzEndHh), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 102, sizeof(tzEndMm), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
#line 2318 "../common/utilities.ec"
    };
#line 2318 "../common/utilities.ec"
  _sqibind[0].sqldata = tzCty;
#line 2318 "../common/utilities.ec"
  _sqibind[1].sqldata = tzTmzn;
#line 2318 "../common/utilities.ec"
  _sqobind[0].sqldata = tzStd;
#line 2318 "../common/utilities.ec"
  _sqobind[1].sqldata = tzDst;
#line 2318 "../common/utilities.ec"
  _sqobind[2].sqldata = (char *) &tzStdOfs;
#line 2318 "../common/utilities.ec"
  _sqobind[3].sqldata = (char *) &tzDstOfs;
#line 2318 "../common/utilities.ec"
  _sqobind[4].sqldata = (char *) &tzStMth;
#line 2318 "../common/utilities.ec"
  _sqobind[5].sqldata = (char *) &tzStWk;
#line 2318 "../common/utilities.ec"
  _sqobind[6].sqldata = (char *) &tzStDy;
#line 2318 "../common/utilities.ec"
  _sqobind[7].sqldata = (char *) &tzStHh;
#line 2318 "../common/utilities.ec"
  _sqobind[8].sqldata = (char *) &tzStMm;
#line 2318 "../common/utilities.ec"
  _sqobind[9].sqldata = (char *) &tzEndMth;
#line 2318 "../common/utilities.ec"
  _sqobind[10].sqldata = (char *) &tzEndWk;
#line 2318 "../common/utilities.ec"
  _sqobind[11].sqldata = (char *) &tzEndDy;
#line 2318 "../common/utilities.ec"
  _sqobind[12].sqldata = (char *) &tzEndHh;
#line 2318 "../common/utilities.ec"
  _sqobind[13].sqldata = (char *) &tzEndMm;
#line 2318 "../common/utilities.ec"
  sqli_slct(ESQLINTVERSION, &_SQ0,sqlcmdtxt,2,_sqibind,14,_sqobind,0,(ifx_literal_t *)0,(ifx_namelist_t *)0,0);
#line 2318 "../common/utilities.ec"
  }

	if (sqlca.sqlcode == 100)
	{
		memcpy(status,"5",1);
		putenv(strTZ);
		return;
	}
    /* make correction for "last week" in March if March has 5 Sundays in the year.
       This correction is only for European Union states abiding by the "last week
       in March" convention for the start of the DST */
    memcpy(temp,inString,4);
    temp[4]='\0';
    if ((tzStMth == 3) && (tzStWk == 4)) /* last week of March */
    { /* find out what day of the week the 1st of March for that year is */
      memset(dowString,'\0',11);
      sprintf(dowString,"%s0301",temp);
      /* call a function from "pln_dateroutine" to find out the day of the week */
		getWeekday(dowString,day);
      if (memcmp(day,"999",3)==0)
      { memcpy(status,"6",1);
        putenv(strTZ);
        return;
      }
      if ((memcmp(day,"SUN",3)==0) || (memcmp(day,"FRI",3)==0) || (memcmp(day,"SAT",3)==0))
        tzStWk = 5;
    }

    /* make a similar correction for the "last week" in October to mark the end of the
       DST. This applies to EU. */
    if ((tzEndMth == 10) && (tzEndWk == 4)) /* last week of October */
    { /* find out what day of the week the 1st of October for that year is */
      memset(dowString,'\0',11);
      sprintf(dowString,"%s1001",temp);
		getWeekday(dowString,day);
      if (memcmp(day,"999",3)==0)
      { memcpy(status,"6",1);
        putenv(strTZ);
        return;
      }
      if ((memcmp(day,"SUN",3)==0) || (memcmp(day,"FRI",3)==0) || (memcmp(day,"SAT",3)==0))
        tzEndWk = 5;
    }

    /* assemble the TZ string */
    tzStdOfs = tzStdOfs - 2*tzStdOfs; /* reverse the sign on the Off-set value */
    /* convert the decimal part of the offset into the minute represention  */
    sprintf(str2,"%6.2f", tzStdOfs);
    replace5by3(str2);

    rtrim(tzStd);
    sprintf(str1,"TZ=%s%s", tzStd, str2); /* only these two fields are mandatory */
    if ((tzDst[0] != ' ') && (tzDst[0] != '\0') && applyDst)
    {
      rtrim(tzDst);
      sprintf(str1, "%s%s", str1, tzDst);
      if (tzDstOfs != 0)
      { tzDstOfs = tzDstOfs - 2*tzDstOfs; /* reverse the sign on the Offset value */
        sprintf(str2,"%6.2f", tzDstOfs);
        replace5by3(str2);
        sprintf(str1, "%s%s", str1, str2);
      }
      if (tzStMth != 0)
      { sprintf(str1, "%s,M%i.%i.%i", str1, tzStMth,tzStWk,tzStDy);
        if (tzStHh != 0)
        { if (tzStMm < 10)
            sprintf(str1, "%s/%i:0%i", str1, tzStHh,tzStMm);
          else
            sprintf(str1, "%s/%i:%i", str1, tzStHh,tzStMm);
        }
        if (tzEndMth != 0)
        { sprintf(str1, "%s,M%i.%i.%i", str1, tzEndMth, tzEndWk,tzEndDy);
          if (tzEndHh != 0)
          { if (tzEndMm < 10)
              sprintf(str1, "%s/%i:0%i", str1, tzEndHh, tzEndMm);
            else
              sprintf(str1, "%s/%i:%i", str1, tzEndHh, tzEndMm);
          }
        }
      }
    }

    /* prepare the TZ string according to required format */
    /* first remove all extra spaces in the string */
    pt1 = str1;
    while (*pt1 != '\0')
    { if (*pt1 == ' ')
      { pt2 = pt1;
        while (*(pt2+1) != '\0')
        { *pt2 = *(pt2+1);
          pt2++;
        }
        *pt2='\0';
      }
      if (*pt1 != ' ')
        pt1++;
    }
    /* now change the period character into a colon for all hour:minute representations */
    pt1 = str1;
    while ((*pt1 != ',') && (*pt1 != '\0'))
    { if (*pt1 == '.')
        *pt1 = ':';
      pt1++;
    }

    /*printf("The TZ string is: %s\n",str1);*/
    putenv(str1);
    tzset();
    time1=mktime(&ltp);
    ltp1=(struct tm *)gmtime(&time1);
    /*fprintf(stdout, "%d:%d:%d\n", ltp1->tm_hour, ltp1->tm_min, ltp1->tm_sec); */

    /* assemble the outstring from the values in ltp1 structure */

    memset(outStr,'\0',5);
    sprintf(outStr, "%4d", 1900+ltp1->tm_year);
    memcpy(outString,outStr,4);

	if (ltp1->tm_mon >= 9)
		sprintf(outStr,"%2d", ltp1->tm_mon+1);
    else
		sprintf(outStr,"0%1d", ltp1->tm_mon+1);
	memcpy(outString+4,outStr,2);

	if (ltp1->tm_mday >= 10)
		sprintf(outStr,"%2d", ltp1->tm_mday);
    else
		sprintf(outStr,"0%1d", ltp1->tm_mday);
	memcpy(outString+6,outStr,2);

	if (ltp1->tm_hour >= 10)
		sprintf(outStr,"%2d", ltp1->tm_hour);
    else
		sprintf(outStr,"0%1d", ltp1->tm_hour);
	memcpy(outString+8,outStr,2);

	if (ltp1->tm_min >= 10)
		sprintf(outStr,"%2d", ltp1->tm_min);
    else
		sprintf(outStr,"0%1d", ltp1->tm_min);
	memcpy(outString+10,outStr,2);

	if (ltp1->tm_sec >= 10)
		sprintf(outStr,"%2d", ltp1->tm_sec);
    else
		sprintf(outStr,"0%1d", ltp1->tm_sec);
	memcpy(outString+12,outStr,2);
	memcpy(outString+14,fract,3);

    /* datestring = ctime(&time1);
    printf("%s\n", datestring); */
    memcpy(inString,outString,17);
    memcpy(status,"0",1);
    putenv(strTZ);
    return;

}

void subMintFrmDttm(char *sOutptDttm, char *sInptDttm, int iMinutes)
{
	char sDt[21]="";
	char sDtYr[11]="";
	char sDtMth[11]="";
	char sDtDy[11]="";
	char sHr[11]="";
	char sMin[11]="";
	char sSec[11]="";

	char sMth[11]="";
	char sYr[11]="";
	char sDy[11]="";
	time_t rawtime;

	struct tm * timeinfo={ 0 };

	memset(sOutptDttm, '\0', 20);

	memset(sDtYr, '\0', sizeof(sDtYr));
	memset(sDtMth, '\0', sizeof(sDtMth));
	memset(sDtDy, '\0', sizeof(sDtDy));

	memcpy(sDtYr, sInptDttm, 4);
	memcpy(sDtMth, sInptDttm + 4, 2);
	memcpy(sDtDy, sInptDttm + 6, 2);

	memcpy(sHr, sInptDttm+8, 2);
	memcpy(sMin, sInptDttm + 10, 2);
	memcpy(sSec, sInptDttm + 12, 2);

	/* get current timeinfo and modify it to user's choice */
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	timeinfo->tm_year = atoi(sDtYr) - 1900;
	timeinfo->tm_mon = atoi(sDtMth) - 1;
	timeinfo->tm_mday = atoi(sDtDy);
	timeinfo->tm_hour = atoi(sHr);
	timeinfo->tm_min = atoi(sMin) - iMinutes;
	timeinfo->tm_sec = atoi(sSec);
	timeinfo->tm_isdst = -1;
	mktime(timeinfo);

	strftime(sOutptDttm, 15, "%C%y%m%d%H%M%S", timeinfo);
	sprintf(sOutptDttm+14, sInptDttm+14, 3);
	return;
}

int getDateTm(char *argv1)
{
	struct timeval tp;
	struct timezone tz;
	struct tm *ltp;
	char tmpdate[18];

	memset(tmpdate,'\0',18);
	gettimeofday(&tp,&tz);
	ltp = (struct tm *)localtime(&tp.tv_sec);
	strftime(tmpdate,15, "%C%y%m%d%H%M%S", ltp);
	sprintf(tmpdate+14,"%03d",tp.tv_usec/1000);
	memcpy(argv1,tmpdate,17);
	return(0);
}

void getUTDateTm(char *argv1)
{
	struct timeval tp;
	struct timezone tz;
	struct tm *ltp;
	char tmpdate[18];

	memset(tmpdate,'\0',18);
	gettimeofday(&tp,&tz);
	ltp = (struct tm *)gmtime(&tp.tv_sec);
	strftime(tmpdate, 15,"%C%y%m%d%H%M%S", ltp);
	sprintf(tmpdate+14,"%03d",tp.tv_usec/1000);
	memcpy(argv1,tmpdate,17);

	return ;
}

/* Get Branch or Warehouse Local Time */
int getBrhWhsLocalTime(char *sDtTm, char *brhWhsFlg, char *brhWhsNm)
{
	char tmpStatus[2];
	char sTempBrhWhs[WHS_SIZE + BRH_SIZE + 1];
	char sSpaces[WHS_SIZE + BRH_SIZE + 1];
	int iSize = 0;
	
	tmpStatus[0]='0';

	getUTDateTm(sDtTm);
	strcpy(tmpStatus, "0");

	if (*brhWhsFlg == 'w')
		iSize = WHS_SIZE;
	else
		iSize = BRH_SIZE;
	
	memset(sTempBrhWhs, '\0', sizeof(sTempBrhWhs) - 1 );
	memset(sSpaces, ' ', sizeof(sSpaces) - 1);
	memset(sSpaces, '\0', sizeof(sSpaces) - 1 );
	
	if (*brhWhsNm == '\0' || memcmp(brhWhsNm, sSpaces, iSize) == 0)	/* if Brh/Whs is null or spaces then return */
		return 1;
	else
	{
		/* brhWhsNm may contain more characters than Brh/Whs size,  send only the required chars to  convDttmToLocal */
		memcpy(sTempBrhWhs, brhWhsNm, iSize);	
	}
	convDttmToLocal(sDtTm, brhWhsFlg, sTempBrhWhs, gCmpyId, " ", " ", " ", tmpStatus);
	if (tmpStatus[0] != '0')  /* Status returned is not 0    */
		return 1;
	else
		return 0;
}

int callMergePgm(void)
{
	int iRtn = 0;
	char sCmd1[1501] = "";
	char sXMLFlPath[PATH_SIZE+FL_NM_SIZE+1] = "";
	char sOutFlNm[FL_NM_SIZE+1] = "";

	if (gIsExcel)
	{
		return 0;
	}
	/* First check XML file in Custom Template Directory */
	memset(sXMLFlPath, '\0', PATH_SIZE  + FL_NM_SIZE + 2);
	strcpy(sXMLFlPath, getCustomTmplPath(gXMLTmplNm));
	if (sXMLFlPath[0] == '\0')
	{/* If Custom Directory Path is not set or XML file not found there then use standard path i.e. $STRATIXDIR/pgms */
		sprintf(sXMLFlPath, "%s%s", getTmplPath(gXMLTmplNm), gXMLTmplNm);
	}
	else
	{/* Concat Custom directory path and XML file name */
		strcat(sXMLFlPath, gXMLTmplNm);
	}

	sprintf(sOutFlNm, "%-.*s.pdf", strlen(gDataFlNm)-4, gDataFlNm);
	memset(gOutputFlNm, '\0', sizeof(gOutputFlNm));
	strcpy(gOutputFlNm, sOutFlNm);

	sprintf(sCmd1,"nice irsmerge -c%s/stxconf/irsmerge.conf -t %s -d %s -p pdf -o \"%s\" 2> /dev/null 1> /dev/null", getenv("HOME"), sXMLFlPath, gDataFlNm, sOutFlNm);

	iRtn = system(sCmd1);
	iRtn = iRtn/256;
	if (iRtn != 0)
	{

		logMsg("Merge operation failed for '%s'", sCmd1);
		return iRtn;
	}

	return (iRtn);
}

/*---------------------------------------------------------------------------*/
/*-------------------------------- initDB -----------------------------------*/
/*---------------------------------------------------------------------------*/
int cstmInitDB(void)
{
	char sDbInstNm[101] = "";
	char sDbNm[101] = "";
/*
 * 	EXEC SQL BEGIN DECLARE SECTION;
 */
#line 2641 "../common/utilities.ec"
#line 2642 "../common/utilities.ec"
  char dbConnStr[501] = "";
int l_iSQLCode;
int l_iSQLErr;
  char sStatus[11] = "";
/*
 * 	EXEC SQL END DECLARE SECTION;
 */
#line 2646 "../common/utilities.ec"


	int iSts= 0;

	memset(sDbInstNm, '\0', sizeof(sDbInstNm));
	memset(sDbNm, '\0', sizeof(sDbNm));
	memset(dbConnStr, '\0', sizeof(dbConnStr));

	strcpy(sDbInstNm, getenv("INFORMIXSERVER"));
	strcpy(sDbNm, getenv("DATABASE"));

	if (sDbInstNm[0] == '\0')
	{
		logMsg("Environment variable INFORMIXSERVER is not set.");
		iSts = 1;
	}

	if (sDbNm[0] == '\0')
	{
		logMsg("Environment variable DATABASE is not set.");
		iSts = 1;
	}

	if (iSts == 1)
		exit(1);

	/* Connect to database */
	sprintf(dbConnStr, "%s@%s", sDbNm, sDbInstNm);
/*
 * 	EXEC SQL connect to :dbConnStr;
 */
#line 2674 "../common/utilities.ec"
  {
#line 2674 "../common/utilities.ec"
  sqli_connect_open(ESQLINTVERSION, 0, dbConnStr, (char *)0, (ifx_conn_t *)0, 0);
#line 2674 "../common/utilities.ec"
  }
	if (sqlca.sqlcode < -100)
	{
		sprintf(sStatus, "%05d%03d",abs(sqlca.sqlcode),abs(sqlca.sqlerrd[1]));
		logMsg("Unable to connect to database. SQL ERROR: %s", sStatus);
		return ERROR;
	} /*- end if -*/

/*
 * 	EXEC SQL set isolation to dirty read;
 */
#line 2682 "../common/utilities.ec"
  {
#line 2682 "../common/utilities.ec"
  static const char *sqlcmdtxt[] =
#line 2682 "../common/utilities.ec"
    {
#line 2682 "../common/utilities.ec"
    "set isolation to dirty read",
    0
    };
#line 2682 "../common/utilities.ec"
  static ifx_statement_t _SQ0 = {0};
#line 2682 "../common/utilities.ec"
  sqli_stmt(ESQLINTVERSION, &_SQ0, sqlcmdtxt, 0, (ifx_sqlvar_t *)0, (struct value *)0, (ifx_literal_t *)0, (ifx_namelist_t *)0, (ifx_cursor_t *)0, -1, 0, 0);
#line 2682 "../common/utilities.ec"
  }
	if (sqlca.sqlcode < -100)
	{
		sprintf(sStatus, "%05d%03d",abs(sqlca.sqlcode),abs(sqlca.sqlerrd[1]));
		logMsg("Unable to set isolation to dirty read. SQL ERROR: %s", sStatus);
		return ERROR;
	} /*- end if -*/

	if (getLocalizationInfo(gLgnId, gLng, gCty) != 0)
		return ERROR;

	return SUCCESS;
} /*- end initDB() -*/

/*---------------------------------------------------------------------------*/
/*-------------------------------- closeDB -----------------------------------*/
/*---------------------------------------------------------------------------*/
void cstmCloseDB(void)
{

/*
 * 	EXEC SQL disconnect current;
 */
#line 2702 "../common/utilities.ec"
  {
#line 2702 "../common/utilities.ec"
  sqli_connect_close(3, (char *)0, 0, 0);
#line 2702 "../common/utilities.ec"
  }

} /*- end closeDB() -*/

int printField(FILE *inpFlPtr, char *sFldNm, char *sData)
{
	if (inpFlPtr != NULL)
	{
		cstmFprintf(inpFlPtr, "^field %s\n", sFldNm);

		if (sData[0] != '\0')
		{
			cstmFprintf(inpFlPtr, "%s\n", sData);
		}
		fflush(inpFlPtr );
	}

	return 0;
}

int serachFldAndRewind(FILE *inFlPtr, char *sSearchStr, int iSearchStrLen)
{
	char line[1001] = "";
	int iLen  = 0;

	while (fgets(line, 1000, inFlPtr))
	{
		iLen = strlen(line) -1;
		if (iLen == iSearchStrLen && memcmp(line, sSearchStr, iLen) == 0)
		{/* If field found, return from ahere and rewind the file */
			rewind(inFlPtr);
			return FLD_FOUND;
		}
	}
	rewind(inFlPtr);
	return FLD_NOT_FOUND;
}

int serachFldAndGetData(FILE *inFlPtr, char *sSearchStr, int iSearchStrLen, char *sRtnStr, int iRtnStrSize)
{
	char line[1001] = "";
	int iLen  = 0;

	memset(sRtnStr, '\0', iRtnStrSize);
	while (fgets(line, 1000, inFlPtr))
	{
		iLen = strlen(line) -1;
		if (iLen == iSearchStrLen && memcmp(line, sSearchStr, iLen) == 0)
		{/* If field found, read next line to get the data */
			fgets(line, 1000, inFlPtr);
			rtrim(line);
			if (strstr(line, "^field") == NULL)
			{
				memcpy(sRtnStr, line, strlen(line)-1);
			}

			rewind(inFlPtr);
			return FLD_FOUND;
		}
	}
	rewind(inFlPtr);
	return FLD_NOT_FOUND;
}


int searchAndRplStr(char *inFlPathAndNm, char *outFlPathAndNm, char *sSrchStr, int iSrchStrLen, char *sRplStr, int iRplStrLen, int iSaveInpFl)
{
	FILE *inFlPtr = NULL;
	FILE *outFlPtr = NULL;
	char line[5001];
	char sCmd[1001] = "";
	int iLen = 0;
	int iRtnSts = 1;

	if ((inFlPtr = fopen(inFlPathAndNm, "r+b" )) != NULL )
	{
		if ((outFlPtr = fopen( outFlPathAndNm, "w+b" )) != NULL )
		{
			while (fgets(line, 5000, inFlPtr))
			{
				iLen = strlen(line) - 1;
				if (memcmp(line, sSrchStr, iSrchStrLen) == 0)
				{/* If search string found, replace it with the RplStr */
					fputs( sRplStr, outFlPtr);
					iRtnSts = 0;
				}
				else
				{
					if (strlen(line) == 5000)
						fwrite( line, sizeof(char), strlen(line)-1 , outFlPtr);
					else
						fwrite( line, sizeof(char), strlen(line) , outFlPtr);
				}
			}
		}
		else
		{
			fclose(inFlPtr);
			return 1;
		}
	}
	else
	{
		return 1;
	}

	fclose(inFlPtr);
	fclose(outFlPtr);

	if (iRtnSts != 0 )
	{
		memset(sCmd, '\0', sizeof(sCmd));
		sprintf(sCmd, "/bin/rm %s 2>/dev/null\0", outFlPathAndNm);
		system(sCmd);
		return 1;
	}

	/* Make a copy of original input file */
	if (iSaveInpFl)
	{
		memset(sCmd, '\0', sizeof(sCmd));
		sprintf(sCmd, "/bin/cp %s %s_star 2>/dev/null\0", inFlPathAndNm, inFlPathAndNm);
		system(sCmd);
	}

	/* Replace original file with the modified one */
	memset(sCmd, '\0', sizeof(sCmd));
	sprintf(sCmd, "/bin/mv %s %s 2>/dev/null\0", outFlPathAndNm, inFlPathAndNm);
	system(sCmd);

	return 0;
}

int getDataForSpecificLine(FILE *inFlPtr, int iDesiredLine, char *sRtnStr, int iRtnStrSize)
{
	char line[1001] = "";
	int iLen  = 0, iLineCount = 1;

	memset(sRtnStr, '\0', iRtnStrSize);
	while (fgets(line, 1000, inFlPtr))
	{
		iLen = strlen(line) -1;
		if (iLineCount == iDesiredLine)
		{
			memcpy(sRtnStr, line, iLen);

			rewind(inFlPtr);
			return LINE_FOUND;
		}
		iLineCount++;
	}
	rewind(inFlPtr);
	return LINE_NOT_FOUND;
}

int callLblMergePgm(char *sStdTmplNm, char *sCstmTmplNm, char *sDataFlNm)
{
	int iRtn = 0;
	char sCmd1[1501] = "";
	char sXMLFlPath[PATH_SIZE+FL_NM_SIZE+1] = "";
	char sOutFlNm[FL_NM_SIZE+1] = "";

	/* First check XML file in Custom Template Directory */
	memset(sXMLFlPath, '\0', PATH_SIZE  + FL_NM_SIZE + 2);
	strcpy(sXMLFlPath, getCustomTmplPath(sCstmTmplNm));
	if (sXMLFlPath[0] == '\0')
	{/* If Custom Directory Path is not set or XML file not found there then use standard path i.e. $STRATIXDIR/pgms */
		sprintf(sXMLFlPath, "%s%s", getTmplPath(sCstmTmplNm), sCstmTmplNm);
	}
	else
	{/* Concat Custom directory path and XML file name */
		strcat(sXMLFlPath, sCstmTmplNm);
	}

	sprintf(sOutFlNm, "%-.*s.zpl", strlen(sDataFlNm)-4, sDataFlNm);
	memset(gOutputFlNm, '\0', sizeof(gOutputFlNm));
	strcpy(gOutputFlNm, sOutFlNm);

	sprintf(sCmd1,"nice mergelbl -t %s -d %s -o \"%s\" -c \"\" -m 1 -s \"%s\" 2> /dev/null 1> /dev/null", sXMLFlPath, sDataFlNm, sOutFlNm, sStdTmplNm);

	iRtn = system(sCmd1);
	iRtn = iRtn/256;
	if (iRtn != 0)
	{

		logMsg("Merge operation failed for '%s'", sCmd1);
		return iRtn;
	}

	return (iRtn);
}


int padSpaceLeftRight(char *sRtnStr, int iRtnStrSize, char *sSrcString, int iSrcStrSize, int iReqTotLength, char *sDirection)
{
	/*Pads spaces to either left or right of the trimmed string
	If the trimmed string is "", it initializes it to a string of spaces with length iReqTotLength*/

	char sTrimString[251] = "", sSpaceStr[251] = "";
	int iStringLength = 0, iDifference = 0;

	memset(sRtnStr, '\0', iRtnStrSize);

	/*Strip off spaces*/
	memcpy(sTrimString, sSrcString, iSrcStrSize);
	rtrim(sTrimString);

	/*Check if the length of the string is too long*/
	iStringLength = strlen(sTrimString);
	if (iStringLength >= iReqTotLength)
	{
		strcpy(sRtnStr, sTrimString);
		return 0;
	}

	/*Find how many spaces to pad*/
	iDifference = iReqTotLength - iStringLength;

	memset(sSpaceStr, '\0', sizeof(sSpaceStr));
	memset(sSpaceStr, ' ', iDifference);

	/*Pad either left or right*/
	if (strncasecmp(sDirection, "L", 1) == 0)
	{
		concat2(sRtnStr, iRtnStrSize, sSpaceStr, sTrimString);
	}
	else
	{
		concat2(sRtnStr, iRtnStrSize, sTrimString, sSpaceStr);
	}
	return 0;
}


#line 2934 "../common/utilities.ec"
