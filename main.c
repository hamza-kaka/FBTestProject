/*! 
@file main file for full bridge 
@brief 
@details 

@author Hamza Naeem Kakakhel
@copyright Taraz Technologies Pvt. Ltd.
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_uart.h"
#include "fsl_ftm.h" 
#include "pin_mux.h"
#include "clock_config.h"
#include "UserConfig.h"
/*******************************************************************************
 * Defines
 ******************************************************************************/
#define BOARD_FTM_BASEADDR FTM0
#define BOARD_FIRST_FTM_CHANNEL 0U
#define BOARD_SECOND_FTM_CHANNEL 1U

/* Get source clock for FTM driver */
#define FTM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_FastPeriphClk)
/*******************************************************************************
 * Enums
 ******************************************************************************/

/*******************************************************************************
 * Structs
 ******************************************************************************/

 /*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
ftm_config_t ftmInfo;
ftm_chnl_pwm_signal_param_t ftmParam[2];

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{

    uint8_t ch;
		int test;
    uart_config_t config;
 
	
	
    BOARD_InitPins();
    BOARD_BootClockRUN();

		
	/* Configure ftm params with frequency 10kHZ */
    ftmParam[0].chnlNumber            = (ftm_chnl_t)BOARD_FIRST_FTM_CHANNEL;
    ftmParam[0].level                 = kFTM_LowTrue;
    ftmParam[0].dutyCyclePercent      = 50U;
    ftmParam[0].firstEdgeDelayPercent = 0U;
    ftmParam[0].enableDeadtime        = DEADTIME_EN;

    ftmParam[1].chnlNumber            = (ftm_chnl_t)BOARD_SECOND_FTM_CHANNEL;
    ftmParam[1].level                 = kFTM_LowTrue;
    ftmParam[1].dutyCyclePercent      = 50U;
    ftmParam[1].firstEdgeDelayPercent = 0U;
    ftmParam[1].enableDeadtime        = DEADTIME_EN;
	
	 FTM_GetDefaultConfig(&ftmInfo);
	 ftmInfo.deadTimeValue = DEADTIME_VAL; 
	 ftmInfo.deadTimePrescale = kFTM_Deadtime_Prescale_16;
    /* Initialize FTM module */
    FTM_Init(BOARD_FTM_BASEADDR, &ftmInfo);

    FTM_SetupPwm(BOARD_FTM_BASEADDR, ftmParam, 2U, kFTM_ComplementaryPwm, SWITCING_FREQ, FTM_SOURCE_CLOCK);
    FTM_StartTimer(BOARD_FTM_BASEADDR, kFTM_SystemClock);

}

/* EOF */







