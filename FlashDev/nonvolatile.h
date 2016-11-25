#ifndef __NONVOLATILE__H__
#define __NONVOLATILE__H__

#include "calibration.h"
#include "board.h"
typedef struct {
	int32_t Kp;
	int32_t Ki;
	int32_t Kd;
	int32_t Threshold;
	bool parametersVaild;
} PIDparams_t;

typedef struct {
	int32_t currentMa;
	int32_t currentHoldMa;
	int32_t errorLimit;
	bool parametersVaild;
} SystemParams_t;

#ifdef NZS_FAST_CAL
typedef struct {
	uint16_t angle[16384];
	uint16_t checkSum;
}FastCal_t;
#endif

typedef struct {
	FlashCalData_t CalibrationTable;
	PIDparams_t PIDparams;
	SystemParams_t SystemParams;
#ifdef NZS_FAST_CAL
	FastCal_t FastCal;
#endif
} nvm_t;

#ifdef NZS_FAST_CAL
extern  const uint16_t  NVM_flash[16640];
#else
extern  const uint16_t  NVM_flash[256];
#endif
#define NVM ((const nvm_t *)NVM_flash)

bool nvmWriteCalTable(void *ptrData, uint32_t size);
bool nvmWritePID(int32_t Kp, int32_t Ki, int32_t Kd, int32_t Threshold);
bool nvmWriteSystemParms(int32_t currentMa, int32_t currentHoldMa, int32_t errorLimit);


#endif // __NONVOLATILE__H__
