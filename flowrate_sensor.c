/**
 * \addtogroup logging
 * @{
 *
 * \author Lukas Kempf
 * \brief Flowrate Sensor
 *
 *
 */

//*****************************************************************************
//
// flowrate_sensor.c - Flowrate Sensor
//
//*****************************************************************************

/* std lib includes */
#include <stdio.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
//#include "queue.h"

/* FatFs includes */
#include "flowrate_sensor.h"

#include "logging.h"
#include "fatfs/ff.h"

/* Measurement driver includes*/



//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
