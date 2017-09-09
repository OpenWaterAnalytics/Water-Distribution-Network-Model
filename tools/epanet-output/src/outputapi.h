/*
 * outputapi.h
 *
 *  Created on: Jun 4, 2014
 *      Author: mtryby
 */

#ifndef OUTPUTAPI_H_
#define OUTPUTAPI_H_
/* Epanet Results binary file API */

#define MAXFNAME     259   // Max characters in file name
#define MAXID         31   // Max characters in ID name

// This is an opaque pointer to struct. Do not access variables.
typedef void* ENR_Handle;

typedef enum elmType {
	ENR_node = 1,
    ENR_link = 2
} ENR_ElementType;

typedef enum apiFunc {
    ENR_getSeries    = 1,
    ENR_getAttribute = 2,
    ENR_getResult    = 3,
	ENR_getReacts    = 4,
	ENR_getEnergy    = 5
} ENR_ApiFunction;

typedef enum elmCount {
    ENR_nodeCount  = 1,
    ENR_tankCount  = 2,
    ENR_linkCount  = 3,
    ENR_pumpCount  = 4,
    ENR_valveCount = 5
} ENR_ElementCount;

typedef enum unit {
    ENR_flowUnits   = 1,
    ENR_pressUnits  = 2
} ENR_Units;

typedef enum time {
	ENR_reportStart = 1,
	ENR_reportStep  = 2,
	ENR_simDuration = 3,
	ENR_numPeriods  = 4
}ENR_Time;

typedef enum nodeAttr {
    ENR_demand   = 1,
    ENR_head     = 2,
    ENR_pressure = 3,
    ENR_quality  = 4
} ENR_NodeAttribute;

typedef enum linkAttr {
    ENR_flow         = 1,
    ENR_velocity     = 2,
    ENR_headloss     = 3,
    ENR_avgQuality   = 4,
    ENR_status       = 5,
    ENR_setting      = 6,
    ENR_rxRate       = 7,
    ENR_frctnFctr    = 8
} ENR_LinkAttribute;


#ifdef WINDOWS
  #ifdef __cplusplus
  #define DLLEXPORT extern "C" __declspec(dllexport) __stdcall
  #else
  #define DLLEXPORT __declspec(dllexport) __stdcall
  #endif
#else
  #ifdef __cplusplus
  #define DLLEXPORT extern "C"
  #else
  #define DLLEXPORT
  #endif
#endif


int DLLEXPORT ENR_init(ENR_Handle* p_handle_out);
// wrapped
int DLLEXPORT ENR_open(ENR_Handle p_handle_in, const char* path);
// wrapped
int DLLEXPORT ENR_getVersion(ENR_Handle p_handle_in, int* int_out);
// wrapped
int DLLEXPORT ENR_getNetSize(ENR_Handle p_handle_in, ENR_ElementCount t_enum, int* int_out);
// wrapped
int DLLEXPORT ENR_getUnits(ENR_Handle p_handle_in, ENR_Units t_enum, int* int_out);
// wrapped
int DLLEXPORT ENR_getTimes(ENR_Handle p_handle_in, ENR_Time t_enum, int* int_out);
// wrapped
int DLLEXPORT ENR_getElementName(ENR_Handle p_handle_in, ENR_ElementType t_enum,
		int elementIndex, char** string_out);
// wrapped, tested

int DLLEXPORT ENR_getEnergyUsage(ENR_Handle p_handle_in, int pumpIndex,
		int* int_out, float** float_out, int* int_dim);
// wrapped
int DLLEXPORT ENR_getNetReacts(ENR_Handle p_handle_in, float** float_out, int* int_dim);
// wrapped

//float* DLLEXPORT ENR_newOutValueSeries(ENR_Handle p_handle_in, int startPeriod,
//        int endPeriod, int* length, int* errcode);
// deprecate? yes
//float* DLLEXPORT ENR_newOutValueArray(ENR_Handle p_handle_in, ENR_ApiFunction func,
//        ENR_ElementType type, int* length, int* errcode);
// deprecate? yes

int DLLEXPORT ENR_getNodeSeries(ENR_Handle p_handle_in, int nodeIndex, ENR_NodeAttribute t_enum,
        int startPeriod, int endPeriod, float** ARGOUTVIEWM_ARRAY1, int* DIM1);

int DLLEXPORT ENR_getLinkSeries(ENR_Handle p_handle_in, int linkIndex, ENR_LinkAttribute t_enum,
        int startPeriod, int endPeriod, float** ARGOUTVIEWM_ARRAY1, int* DIM1);

int DLLEXPORT ENR_getNodeAttribute(ENR_Handle p_handle_in, int periodIndex,
        ENR_NodeAttribute t_enum, float** ARGOUTVIEWM_ARRAY1, int* DIM1);
// wrapped and tested
int DLLEXPORT ENR_getLinkAttribute(ENR_Handle p_handle_in, int periodIndex,
        ENR_LinkAttribute t_enum, float** ARGOUTVIEWM_ARRAY1, int* DIM1);
// wrapped and tested

int DLLEXPORT ENR_getNodeResult(ENR_Handle p_handle_in, int periodIndex, int nodeIndex,
		float** float_out, int* int_dim);

int DLLEXPORT ENR_getLinkResult(ENR_Handle p_handle_in, int periodIndex, int linkIndex,
		float** float_out, int* int_dim);

int DLLEXPORT ENR_close(ENR_Handle* p_handle_out);
// wrapped and tested

void DLLEXPORT ENR_free(void** array);
// deprecate? no
void DLLEXPORT ENR_clearError(ENR_Handle p_handle_in);
// wrapped
int DLLEXPORT ENR_checkError(ENR_Handle p_handle_in, char** msg_buffer);
// wrapped

#endif /* OUTPUTAPI_H_ */
