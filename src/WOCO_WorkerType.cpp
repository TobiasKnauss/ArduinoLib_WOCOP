#include "WOCO_WorkerType.h"

//--------------------------------------------------------------------
WOCO_WorkerType::WOCO_WorkerType (bool i_TypeIsReply,
                                  bool i_ActionIsWrite)
: WOCO (i_TypeIsReply,
        i_ActionIsWrite)
{
}

//--------------------------------------------------------------------
WOCO_WorkerType::WOCO_WorkerType (bool     i_TypeIsReply,
                                  bool     i_ActionIsWrite,
                                  uint32_t i_WorkerType)
: WOCO (i_TypeIsReply,
        i_ActionIsWrite)
{
  m_WorkerType = i_WorkerType;
}

//--------------------------------------------------------------------
WOCO::ECommand WOCO_WorkerType::get_Command ()
{
  return ECommand::WorkerType;
}

//--------------------------------------------------------------------
uint8_t WOCO_WorkerType::get_CommandDataLength_ReadRequest ()
{
  return 0;
}

//--------------------------------------------------------------------
uint8_t WOCO_WorkerType::get_CommandDataLength_ReadReply ()
{
  return 4;
}

//--------------------------------------------------------------------
uint32_t WOCO_WorkerType::get_WorkerType ()
{
  return m_WorkerType;
}

//--------------------------------------------------------------------
WOCO_WorkerType* WOCO_WorkerType::CreateReadRequest ()
{
  return new WOCO_WorkerType (TYPE_Request, ACTION_Read);
}

//--------------------------------------------------------------------
WOCO_WorkerType* WOCO_WorkerType::CreateReadReply (uint32_t i_WorkerType)
{
  return new WOCO_WorkerType (TYPE_Reply, ACTION_Read, i_WorkerType);
}

//--------------------------------------------------------------------
::EResult WOCO_WorkerType::AnalyzeCommandData (uint8_t* i_pCommandDataBuffer,
                                               uint8_t  i_CommandDataBufferLength,
                                               uint8_t  i_CommandDataLength)
{
  ::EResult result = WOCO::AnalyzeCommandData(i_pCommandDataBuffer, i_CommandDataBufferLength, i_CommandDataLength);
  if (result != ::EResult::SUCCESS)
    return result;

  bool isOK = true;
  uint8_t* pCurrent = i_pCommandDataBuffer;

  if (get_TypeIsReply ())
    isOK &= RingBuffer_GetValueAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, m_WorkerType);
  if (!isOK)
    return ::EResult::FAIL_Buffer_GetValue;
  
  return ::EResult::SUCCESS;
}

//--------------------------------------------------------------------
::EResult WOCO_WorkerType::ComposeCommandData (uint8_t* i_pCommandDataBuffer,
                                               uint8_t  i_CommandDataBufferLength,
                                               uint8_t& o_CommandDataLength)
{
  ::EResult result = WOCO::ComposeCommandData (i_pCommandDataBuffer, i_CommandDataBufferLength, o_CommandDataLength);
  if (result != ::EResult::SUCCESS)
    return result;

  bool isOK = true;
  uint8_t* pCurrent = i_pCommandDataBuffer;

  if (get_TypeIsReply ())
    isOK &= RingBuffer_SetValueAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, m_WorkerType);
  if (!isOK)
    return ::EResult::FAIL_Buffer_SetValue;

  return ::EResult::SUCCESS;
}
