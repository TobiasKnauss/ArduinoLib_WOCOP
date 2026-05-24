#include "WOCO_DigitalIOState.h"

//--------------------------------------------------------------------
WOCO_DigitalIOState::WOCO_DigitalIOState (bool i_TypeIsReply,
                                          bool i_ActionIsWrite)
: WOCO (i_TypeIsReply,
        i_ActionIsWrite)
{
}

//--------------------------------------------------------------------
WOCO_DigitalIOState::WOCO_DigitalIOState (bool    i_TypeIsReply,
                                          bool    i_ActionIsWrite,
                                          uint8_t i_IONumber,
                                          bool    i_IOState)
: WOCO (i_TypeIsReply,
        i_ActionIsWrite)
{
  m_IONumber = i_IONumber;
  m_IOState  = i_IOState;
}

//--------------------------------------------------------------------
WOCO::ECommand WOCO_DigitalIOState::get_Command ()
{
  return ECommand::DigitalIOState;
}

//--------------------------------------------------------------------
uint16_t WOCO_DigitalIOState::get_CommandDataLength_ReadRequest ()
{
  return 1;
}

//--------------------------------------------------------------------
uint16_t WOCO_DigitalIOState::get_CommandDataLength_ReadReply ()
{
  return 2;
}

//--------------------------------------------------------------------
uint8_t WOCO_DigitalIOState::get_IONumber ()
{
  return m_IONumber;
}

//--------------------------------------------------------------------
bool WOCO_DigitalIOState::get_IOState ()
{
  return m_IOState;
}

//--------------------------------------------------------------------
WOCO_DigitalIOState* WOCO_DigitalIOState::CreateReadRequest (uint8_t i_IONumber)
{
  return new WOCO_DigitalIOState (TYPE_Request, ACTION_Read, i_IONumber, LOW);
}

//--------------------------------------------------------------------
WOCO_DigitalIOState* WOCO_DigitalIOState::CreateReadReply ( uint8_t i_IONumber,
                                                            bool    i_IOState)
{
  return new WOCO_DigitalIOState (TYPE_Reply, ACTION_Read, i_IONumber, i_IOState);
}

//--------------------------------------------------------------------
WOCO_DigitalIOState* WOCO_DigitalIOState::CreateWriteRequest (uint8_t i_IONumber,
                                                              bool    i_IOState)
{
  return new WOCO_DigitalIOState (TYPE_Request, ACTION_Write, i_IONumber, i_IOState);
}

//--------------------------------------------------------------------
WOCO_DigitalIOState* WOCO_DigitalIOState::CreateWriteReply ()
{
  return new WOCO_DigitalIOState (TYPE_Reply, ACTION_Write, 0, LOW);
}

//--------------------------------------------------------------------
::EResult WOCO_DigitalIOState::AnalyzeCommandData ( uint8_t*  i_pCommandDataBuffer,
                                                    uint16_t  i_CommandDataBufferLength,
                                                    uint16_t  i_CommandDataLength)
{
  ::EResult result = WOCO::AnalyzeCommandData (i_pCommandDataBuffer, i_CommandDataBufferLength, i_CommandDataLength);
  if (result != ::EResult::SUCCESS)
    return result;

  bool isOK = true;
  uint8_t* pCurrent = i_pCommandDataBuffer;

  if (get_TypeIsRequest ()
  ||  get_ActionIsRead ())
  {
    isOK &= RingBuffer_GetValueAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, m_IONumber);
    if (get_TypeIsReply ()
    ||  get_ActionIsWrite ())
      isOK &= RingBuffer_GetValueAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, m_IOState);
  }
  if (!isOK)
    return ::EResult::FAIL_Buffer_GetValue;

  return ::EResult::SUCCESS;
}

//--------------------------------------------------------------------
::EResult WOCO_DigitalIOState::ComposeCommandData ( uint8_t*  i_pCommandDataBuffer,
                                                    uint16_t  i_CommandDataBufferLength,
                                                    uint16_t& o_CommandDataLength)
{
  ::EResult result = WOCO::ComposeCommandData (i_pCommandDataBuffer, i_CommandDataBufferLength, o_CommandDataLength);
  if (result != ::EResult::SUCCESS)
    return result;

  bool isOK = true;
  uint8_t* pCurrent = i_pCommandDataBuffer;

  if (get_TypeIsRequest ()
  ||  get_ActionIsRead ())
  {
    isOK &= RingBuffer_SetValueAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, m_IONumber);
    if (get_TypeIsReply ()
    ||  get_ActionIsWrite ())
      isOK &= RingBuffer_SetValueAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, m_IOState);
  }
  if (!isOK)
    return ::EResult::FAIL_Buffer_SetValue;

  return ::EResult::SUCCESS;
}
