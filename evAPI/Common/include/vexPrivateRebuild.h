/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     vexPrivateRebuild.h                                         */
/*    Author:     Jayden Liffick                                              */
/*    Created:    6 Aug 2023                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef VEXPRIVATEREBUILD_H
#define VEXPRIVATEREBUILD_H

#include "stdint.h"
#include "stdbool.h"

#ifdef __cplusplus
extern "C" {
#endif

//Typedef used for returns that are probably void, but know known for certain
typedef void undefined;

//*Tasks functions

/**
 * @brief Adds a task.
 * @param callback The function to run as the task.
 * @param interval Unknown. Whenever used by vex, it is 2.
 * @param label The name of the task.
 * @returns The ID of the created task.
 * @warning This function is untested and not guaranteed to function as expected.
*/
uint32_t vexTaskAdd(int (* callback)(void), int interval, const char *label);

/*
  vexTaskAddSimple
  vexTaskAddSimpleWithPriority
*/

/**
 * @brief Adds a task with an argument.
 * @param callback The function to run as the task.
 * @param interval Unknown. Whenever used by vex, it is 2.
 * @param arg A pointer to the argument data for the task.
 * @param label The name of the task.
 * @returns The ID of the created task.
 * @warning This function is untested and not guaranteed to function as expected.
*/
uint32_t vexTaskAddWithArg(int (* callback)(void), int interval, void *arg, const char *label);

/**
 * @brief Adds a task with a priority.
 * @param callback The function to run as the task.
 * @param interval Unknown. Whenever used by vex, it is 2.
 * @param label The name of the task.
 * @param priority The priority of the task. Ranges from 0-15.
 * @returns The ID of the created task.
 * @warning This function is untested and not guaranteed to function as expected.
*/
uint32_t vexTaskAddWithPriority(int (* callback)(void), int interval, const char *label, int32_t priority);

/**
 * @brief Adds a task with an argument and a priority.
 * @param callback The function to run as the task.
 * @param interval Unknown. Whenever used by vex, it is 2.
 * @param arg A pointer to the argument data for the task.
 * @param label The name of the task.
 * @param priority The priority of the task. Ranges from 0-15.
 * @returns The ID of the created task.
 * @warning This function is untested and not guaranteed to function as expected.
*/
uint32_t vexTaskAddWithPriorityWithArg(int (* callback)(void), int interval, void *arg, const char *label, int32_t priority);
/*
  vexTaskBreakpointDump
  vexTaskBreakpointSet
  vexTaskCheckTimeslice
  undefined vexTaskCompletionIdSet(  );
  vexTaskFree
  vexTaskGet
  vexTaskGetArgs
  vexTaskGetCallback
*/

/**
 * @brief Gets the callback and ID of a task.
 * @param index The index of the task to get the data from.
 * @param callback_id A pointer to a variable that will store the ID of the task.
 * @returns The callback function of the task.
*/
void *vexTaskGetCallbackAndId(uint32_t index, int *callback_id);

/**
 * @returns The index of the task this function is called in.
*/
uint32_t vexTaskGetIndex();

/**
 * @returns Gets the task index of a task.
*/
uint32_t vexTaskGetTaskIndex();

/*
  vexTaskGetTaskIndexWithId
*/

/**
 * @returns How many tasks the VEX computer can run concurrently.
*/
uint32_t vexTaskHardwareConcurrency(void);

//vexTaskPriorityGet

/**
 * @brief Gets the priority of a task.
 * @param callback A callback to the task function.
 * @param ID The ID of the task.
 * @returns The current priority of the task.
*/
int32_t vexTaskPriorityGetWithId(void *callback, int ID);

//vexTaskPrioritySet

/**
 * @brief Sets the priority of a task.
 * @param callback A callback to the task function.
 * @param ID The ID of the task.
 * @param priority The new priority for the task.
*/
undefined vexTaskPrioritySetWithId(void *callback, int ID, uint32_t priority);

/*
  vexTaskProgramResume
  vexTaskProgramSuspend
*/

/**
 * @brief This function is called when stopping the main loop.
 * @param main Always provided the address of main.
 * @warning This function is untested and may have strange behavior.
*/
undefined vexTaskRemoveAllUser(int *main);

/*
  vexTaskResume
  vexTaskResumeWithCurrent
*/

/**
 * @brief Resumes a task.
 * @param callback A callback to the task function.
 * @param ID The ID of the task.
*/
undefined vexTaskResumeWithId(void *callback, int ID);

/**
 * @brief Has an unknown purpose.
*/
undefined vexTasksDump();

//vexTaskSetArgs


/**
 * @brief Pauses the task / thread it is run in for a specified amount of ms.
 * @param time The time to sleep in ms.
*/
void vexTaskSleep(uint32_t time);

/**
 * @brief Checks if tasks are running.
 * @returns True if tasks are running.
 * @warning This function is untested and may have strange behavior.
*/
uint32_t vexTasksRun();

/*
  vexTaskStackDefaultSizeGet
  vexTaskStackSizeGet
  vexTaskStackTopGet
  vexTaskStackUseGet
  vexTaskStateGet
*/

/**
 * @brief Gets the state of the task.
 * @param callback A callback to the task function.
 * @param ID The ID of the task.
 * @returns The task state.
 * @warning This function is untested. The return value of 99 has significance, vex::thread won't
 *          stop a thread if it returns is 99. The task is also joinable if it isn't 99. 0 Also has
 *          significance with vex::smartdrive, although its meaning is unknown.
*/
uint32_t vexTaskStateGetWithId(void *callback, int ID);

/*
  vexTaskStop
  vexTaskStopAll
  vexTaskStopAllUser
*/

/**
 * @brief Stops a task.
 * @param callback A callback to the task function.
 * @param ID The ID of the task.
*/
undefined vexTaskStopWithId(void *callback, int ID);

/*
  vexTaskSuspend
  vexTaskSuspendCurrent
*/

/**
 * @brief Suspends a task.
 * @param callback A callback to the task function.
 * @param ID The ID of the task.
*/
undefined vexTaskSuspendWithId(void *callback, int ID);

//vexTaskWaitForExit

/**
 * @brief Waits for a given task to exit.
 * @param callback A callback to the task function.
 * @param ID The ID of the task.
*/
undefined vexTaskWaitForExitWithId(void *callback, int ID);

/**
 * @brief Has an unknown purpose, but is always called after all tasks are stopped.
*/
undefined vexTaskYield();

//*Display functions

/**
 * @returns True if the display is set to light mode. False in dark mode.
*/
bool vexDisplayThemeIdGet();

/**
 * @returns True if the display is inverted. False in normal mode.
*/
bool vexDisplayRotateFlagGet();

void vexDisplayClipRegionSetWithIndex(int32_t index, int32_t x1, int32_t y1, int32_t x2, int32_t y2);

//*Other
int32_t vexAdiAddrLedSet(uint32_t index, uint32_t port, uint32_t *pData, uint32_t nOffset, uint32_t nLength, uint32_t options);

#ifdef __cplusplus
}
#endif

#endif // VEXPRIVATEREBUILD_H