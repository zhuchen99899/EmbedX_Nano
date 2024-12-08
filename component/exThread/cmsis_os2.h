/**
 * @file cmsis_os2.h
 * @author ZC (387646983@qq.com)
 * @brief  this is cmsis_os2_api  for EmbedX_Nano  mutex and Semaphore
 * @version 0.1
 * @date 2024-12-08
 * @note 使用cmsis_os2 api 可跨平台兼容EmbedX_Nano 中的device组件 以及timer组件
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _CMSIS_OS2_H_
#define _CMSIS_OS2_H_

#ifndef __NO_RETURN
#if   defined(__CC_ARM)
#define __NO_RETURN __declspec(noreturn)
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#define __NO_RETURN __attribute__((__noreturn__))
#elif defined(__GNUC__)
#define __NO_RETURN __attribute__((__noreturn__))
#elif defined(__ICCARM__)
#define __NO_RETURN __noreturn
#else
#define __NO_RETURN
#endif
#endif


/* ==================== [Includes] ========================================== */


#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */
#define osWaitForever         0xFFFFFFFFU ///< Wait forever timeout value.

// Mutex attributes (attr_bits in \ref osMutexAttr_t).
#define osMutexRecursive      0x00000001U ///< Recursive mutex.
#define osMutexPrioInherit    0x00000002U ///< Priority inherit protocol.
#define osMutexRobust         0x00000008U ///< Robust mutex.

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/// Status code values returned by CMSIS-RTOS functions.
typedef enum {
  osOK                      =  0,         ///< Operation completed successfully.
  osError                   = -1,         ///< Unspecified RTOS error: run-time error but no other error message fits.
  osErrorTimeout            = -2,         ///< Operation not completed within the timeout period.
  osErrorResource           = -3,         ///< Resource not available.
  osErrorParameter          = -4,         ///< Parameter error.
  osErrorNoMemory           = -5,         ///< System is out of memory: it was impossible to allocate or reserve memory for the operation.
  osErrorISR                = -6,         ///< Not allowed in ISR context: the function cannot be called from interrupt service routines.
  osStatusReserved          = 0x7FFFFFFF  ///< Prevents enum down-size compiler optimization.
} osStatus_t;
 

/// Attributes structure for mutex.
typedef struct {
  const char                   *name;   ///< name of the mutex
  uint32_t                 attr_bits;   ///< attribute bits
  void                      *cb_mem;    ///< memory for control block
  uint32_t                   cb_size;   ///< size of provided memory for control block
} osMutexAttr_t;

// /// Attributes structure for semaphore.
// typedef struct {
//   const char                   *name;   ///< name of the semaphore
//   uint32_t                 attr_bits;   ///< attribute bits
//   void                      *cb_mem;    ///< memory for control block
//   uint32_t                   cb_size;   ///< size of provided memory for control block
// } osSemaphoreAttr_t;

// /// Attributes structure for timer.
// typedef struct {
//   const char                   *name;   ///< name of the timer
//   uint32_t                 attr_bits;   ///< attribute bits
//   void                      *cb_mem;    ///< memory for control block
//   uint32_t                   cb_size;   ///< size of provided memory for control block
// } osTimerAttr_t;

// /// Timer type.
// typedef enum {
//   osTimerOnce               = 0,          ///< One-shot timer.
//   osTimerPeriodic           = 1           ///< Repeating timer.
// } osTimerType_t;


// /// Attributes structure for message queue.
// typedef struct {
//   const char                   *name;   ///< name of the message queue
//   uint32_t                 attr_bits;   ///< attribute bits
//   void                      *cb_mem;    ///< memory for control block
//   uint32_t                   cb_size;   ///< size of provided memory for control block
//   void                      *mq_mem;    ///< memory for data storage
//   uint32_t                   mq_size;   ///< size of provided memory for data storage
// } osMessageQueueAttr_t;


 /// \details Mutex ID identifies the mutex.
typedef void *osMutexId_t;

// /// Timer callback function.
// typedef void (*osTimerFunc_t) (void *argument);

// /// \details Semaphore ID identifies the semaphore.
// typedef void *osSemaphoreId_t;

// /// \details Timer ID identifies the timer.
// typedef void *osTimerId_t;

// /// \details Message Queue ID identifies the message queue.
// typedef void *osMessageQueueId_t;

/* ==================== [Public Prototypes] ========================================== *//// Create and Initialize a Mutex object.

//  ==== Mutex Management Functions ====

/// Create and Initialize a Mutex object.
/// \param[in]     attr          mutex attributes; NULL: default values.
/// \return mutex ID for reference by other functions or NULL in case of error.
osMutexId_t osMutexNew (const osMutexAttr_t *attr);

/// Acquire a Mutex or timeout if it is locked.
/// \param[in]     mutex_id      mutex ID obtained by \ref osMutexNew.
/// \param[in]     timeout       \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
/// \return status code that indicates the execution status of the function.
osStatus_t osMutexAcquire (osMutexId_t mutex_id, uint32_t timeout);

/// Release a Mutex that was acquired by \ref osMutexAcquire.
/// \param[in]     mutex_id      mutex ID obtained by \ref osMutexNew.
/// \return status code that indicates the execution status of the function.
osStatus_t osMutexRelease (osMutexId_t mutex_id);

/// Delete a Mutex object.
/// \param[in]     mutex_id      mutex ID obtained by \ref osMutexNew.
/// \return status code that indicates the execution status of the function.
osStatus_t osMutexDelete (osMutexId_t mutex_id);


//  ==== Semaphore Management Functions ====

// /// Create and Initialize a Semaphore object.
// /// \param[in]     max_count     maximum number of available tokens.
// /// \param[in]     initial_count initial number of available tokens.
// /// \param[in]     attr          semaphore attributes; NULL: default values.
// /// \return semaphore ID for reference by other functions or NULL in case of error.
// osSemaphoreId_t osSemaphoreNew (uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr);

// /// Get name of a Semaphore object.
// /// \param[in]     semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
// /// \return name as NULL terminated string.
// const char *osSemaphoreGetName (osSemaphoreId_t semaphore_id);

// /// Acquire a Semaphore token or timeout if no tokens are available.
// /// \param[in]     semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
// /// \param[in]     timeout       \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
// /// \return status code that indicates the execution status of the function.
// osStatus_t osSemaphoreAcquire (osSemaphoreId_t semaphore_id, uint32_t timeout);

// /// Release a Semaphore token up to the initial maximum count.
// /// \param[in]     semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
// /// \return status code that indicates the execution status of the function.
// osStatus_t osSemaphoreRelease (osSemaphoreId_t semaphore_id);

// /// Get current Semaphore token count.
// /// \param[in]     semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
// /// \return number of tokens available.
// uint32_t osSemaphoreGetCount (osSemaphoreId_t semaphore_id);

// /// Delete a Semaphore object.
// /// \param[in]     semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
// /// \return status code that indicates the execution status of the function.
// osStatus_t osSemaphoreDelete (osSemaphoreId_t semaphore_id);


//  ==== Message Queue Management Functions ====

// /// Create and Initialize a Message Queue object.
// /// \param[in]     msg_count     maximum number of messages in queue.
// /// \param[in]     msg_size      maximum message size in bytes.
// /// \param[in]     attr          message queue attributes; NULL: default values.
// /// \return message queue ID for reference by other functions or NULL in case of error.
// osMessageQueueId_t osMessageQueueNew (uint32_t msg_count, uint32_t msg_size, const osMessageQueueAttr_t *attr);

// /// Get name of a Message Queue object.
// /// \param[in]     mq_id         message queue ID obtained by \ref osMessageQueueNew.
// /// \return name as NULL terminated string.
// const char *osMessageQueueGetName (osMessageQueueId_t mq_id);


// //  ==== Timer Management Functions ====

// /// Create and Initialize a timer.
// /// \param[in]     func          function pointer to callback function.
// /// \param[in]     type          \ref osTimerOnce for one-shot or \ref osTimerPeriodic for periodic behavior.
// /// \param[in]     argument      argument to the timer callback function.
// /// \param[in]     attr          timer attributes; NULL: default values.
// /// \return timer ID for reference by other functions or NULL in case of error.
// osTimerId_t osTimerNew (osTimerFunc_t func, osTimerType_t type, void *argument, const osTimerAttr_t *attr);

// /// Get name of a timer.
// /// \param[in]     timer_id      timer ID obtained by \ref osTimerNew.
// /// \return name as NULL terminated string.
// const char *osTimerGetName (osTimerId_t timer_id);

// /// Start or restart a timer.
// /// \param[in]     timer_id      timer ID obtained by \ref osTimerNew.
// /// \param[in]     ticks         \ref CMSIS_RTOS_TimeOutValue "time ticks" value of the timer.
// /// \return status code that indicates the execution status of the function.
// osStatus_t osTimerStart (osTimerId_t timer_id, uint32_t ticks);

// /// Stop a timer.
// /// \param[in]     timer_id      timer ID obtained by \ref osTimerNew.
// /// \return status code that indicates the execution status of the function.
// osStatus_t osTimerStop (osTimerId_t timer_id);

// /// Check if a timer is running.
// /// \param[in]     timer_id      timer ID obtained by \ref osTimerNew.
// /// \return 0 not running, 1 running.
// uint32_t osTimerIsRunning (osTimerId_t timer_id);

// /// Delete a timer.
// /// \param[in]     timer_id      timer ID obtained by \ref osTimerNew.
// /// \return status code that indicates the execution status of the function.
// osStatus_t osTimerDelete (osTimerId_t timer_id);


// /// Put a Message into a Queue or timeout if Queue is full.
// /// \param[in]     mq_id         message queue ID obtained by \ref osMessageQueueNew.
// /// \param[in]     msg_ptr       pointer to buffer with message to put into a queue.
// /// \param[in]     msg_prio      message priority.
// /// \param[in]     timeout       \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
// /// \return status code that indicates the execution status of the function.
// osStatus_t osMessageQueuePut (osMessageQueueId_t mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout);

// /// Get a Message from a Queue or timeout if Queue is empty.
// /// \param[in]     mq_id         message queue ID obtained by \ref osMessageQueueNew.
// /// \param[out]    msg_ptr       pointer to buffer for message to get from a queue.
// /// \param[out]    msg_prio      pointer to buffer for message priority or NULL.
// /// \param[in]     timeout       \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
// /// \return status code that indicates the execution status of the function.
// osStatus_t osMessageQueueGet (osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout);

// /// Get maximum number of messages in a Message Queue.
// /// \param[in]     mq_id         message queue ID obtained by \ref osMessageQueueNew.
// /// \return maximum number of messages.
// uint32_t osMessageQueueGetCapacity (osMessageQueueId_t mq_id);

// /// Get maximum message size in a Memory Pool.
// /// \param[in]     mq_id         message queue ID obtained by \ref osMessageQueueNew.
// /// \return maximum message size in bytes.
// uint32_t osMessageQueueGetMsgSize (osMessageQueueId_t mq_id);

// /// Get number of queued messages in a Message Queue.
// /// \param[in]     mq_id         message queue ID obtained by \ref osMessageQueueNew.
// /// \return number of queued messages.
// uint32_t osMessageQueueGetCount (osMessageQueueId_t mq_id);

// /// Get number of available slots for messages in a Message Queue.
// /// \param[in]     mq_id         message queue ID obtained by \ref osMessageQueueNew.
// /// \return number of available slots for messages.
// uint32_t osMessageQueueGetSpace (osMessageQueueId_t mq_id);

// /// Reset a Message Queue to initial empty state.
// /// \param[in]     mq_id         message queue ID obtained by \ref osMessageQueueNew.
// /// \return status code that indicates the execution status of the function.
// osStatus_t osMessageQueueReset (osMessageQueueId_t mq_id);

// /// Delete a Message Queue object.
// /// \param[in]     mq_id         message queue ID obtained by \ref osMessageQueueNew.
// /// \return status code that indicates the execution status of the function.
// osStatus_t osMessageQueueDelete (osMessageQueueId_t mq_id);


#ifdef __cplusplus
}/* extern C */
#endif


#endif // _CMSIS_OS2_H_


