#include "Arduino.h"
#include "WOCO_WorkerName.h"

//--------------------------------------------------------------------
WOCO_WorkerName::WOCO_WorkerName (bool i_TypeIsReply,
                                  bool i_ActionIsWrite)
: WOCO (i_TypeIsReply,
        i_ActionIsWrite)
{
  memset (m_WorkerName, 0x00, sizeof (m_WorkerName));
}

//--------------------------------------------------------------------
WOCO_WorkerName::WOCO_WorkerName (bool    i_TypeIsReply,
                                  bool    i_ActionIsWrite,
                                  char*   i_pWorkerName,
                                  uint8_t i_WorkerNameLength)
: WOCO (i_TypeIsReply,
        i_ActionIsWrite)
{
  memset (m_WorkerName, 0x00, sizeof (m_WorkerName));

  if (i_pWorkerName != nullptr)
  {
    memcpy (m_WorkerName, i_pWorkerName, min (sizeof (m_WorkerName), i_WorkerNameLength));
  }
}

//--------------------------------------------------------------------
WOCO::ECommand WOCO_WorkerName::get_Command ()
{
  return ECommand::WorkerName;
}

//--------------------------------------------------------------------
uint8_t WOCO_WorkerName::get_CommandDataLength_ReadRequest ()
{
  return 0;
}

//--------------------------------------------------------------------
uint8_t WOCO_WorkerName::get_CommandDataLength_ReadReply ()
{
  return 32;
}

//--------------------------------------------------------------------
char* WOCO_WorkerName::get_WorkerName (uint8_t& o_Length)
{
  o_Length = sizeof (m_WorkerName);
  return m_WorkerName;
}

//--------------------------------------------------------------------
WOCO_WorkerName* WOCO_WorkerName::CreateReadRequest ()
{
  return new WOCO_WorkerName (TYPE_Request, ACTION_Read);
}

//--------------------------------------------------------------------
WOCO_WorkerName* WOCO_WorkerName::CreateReadReply (char*   i_pWorkerName,
                                                   uint8_t i_WorkerNameLength)
{
  return new WOCO_WorkerName (TYPE_Reply, ACTION_Read, i_pWorkerName, i_WorkerNameLength);
}

//--------------------------------------------------------------------
::EResult WOCO_WorkerName::AnalyzeCommandData (uint8_t* i_pCommandDataBuffer,
                                               uint8_t  i_CommandDataBufferLength,
                                               uint8_t  i_CommandDataLength)
{
  ::EResult result = WOCO::AnalyzeCommandData(i_pCommandDataBuffer, i_CommandDataBufferLength, i_CommandDataLength);
  if (result != ::EResult::SUCCESS)
    return result;

  bool isOK = true;
  uint8_t* pCurrent = i_pCommandDataBuffer;

  if (get_TypeIsReply ())
    isOK &= RingBuffer_GetBytesAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, sizeof (m_WorkerName), (uint8_t*)m_WorkerName);
  if (!isOK)
    return ::EResult::FAIL_Buffer_GetValue;
  
  return ::EResult::SUCCESS;
}

//--------------------------------------------------------------------
::EResult WOCO_WorkerName::ComposeCommandData (uint8_t* i_pCommandDataBuffer,
                                               uint8_t  i_CommandDataBufferLength,
                                               uint8_t& o_CommandDataLength)
{
  ::EResult result = WOCO::ComposeCommandData (i_pCommandDataBuffer, i_CommandDataBufferLength, o_CommandDataLength);
  if (result != ::EResult::SUCCESS)
    return result;

  bool isOK = true;
  uint8_t* pCurrent = i_pCommandDataBuffer;

  if (get_TypeIsReply ())
    isOK &= RingBuffer_SetBytesAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, sizeof (m_WorkerName), (uint8_t*)m_WorkerName);
  if (!isOK)
    return ::EResult::FAIL_Buffer_SetValue;

  return ::EResult::SUCCESS;
}
