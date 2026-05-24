#include "WOCO_DigitalPinState.h"

//--------------------------------------------------------------------
WOCO_DigitalPinState::WOCO_DigitalPinState (bool i_TypeIsReply,
                                            bool i_ActionIsWrite)
: WOCO (i_TypeIsReply,
        i_ActionIsWrite)
{
}

//--------------------------------------------------------------------
WOCO_DigitalPinState::WOCO_DigitalPinState (bool    i_TypeIsReply,
                                            bool    i_ActionIsWrite,
                                            uint8_t i_PinNumber,
                                            bool    i_PinState)
: WOCO (i_TypeIsReply,
        i_ActionIsWrite)
{
  m_PinNumber = i_PinNumber;
  m_PinState  = i_PinState;
}

//--------------------------------------------------------------------
WOCO::ECommand WOCO_DigitalPinState::get_Command ()
{
  return ECommand::DigitalPinState;
}

//--------------------------------------------------------------------
uint16_t WOCO_DigitalPinState::get_CommandDataLength_ReadRequest ()
{
  return 1;
}

//--------------------------------------------------------------------
uint16_t WOCO_DigitalPinState::get_CommandDataLength_ReadReply ()
{
  return 2;
}

//--------------------------------------------------------------------
uint8_t WOCO_DigitalPinState::get_PinNumber ()
{
  return m_PinNumber;
}

//--------------------------------------------------------------------
bool WOCO_DigitalPinState::get_PinState ()
{
  return m_PinState;
}

//--------------------------------------------------------------------
WOCO_DigitalPinState* WOCO_DigitalPinState::CreateReadRequest (uint8_t i_PinNumber)
{
  return new WOCO_DigitalPinState (TYPE_Request, ACTION_Read, i_PinNumber, LOW);
}

//--------------------------------------------------------------------
WOCO_DigitalPinState* WOCO_DigitalPinState::CreateReadReply (uint8_t i_PinNumber,
                                                             bool    i_PinState)
{
  return new WOCO_DigitalPinState (TYPE_Reply, ACTION_Read, i_PinNumber, i_PinState);
}

//--------------------------------------------------------------------
WOCO_DigitalPinState* WOCO_DigitalPinState::CreateWriteRequest (uint8_t i_PinNumber,
                                                                bool    i_PinState)
{
  return new WOCO_DigitalPinState (TYPE_Request, ACTION_Write, i_PinNumber, i_PinState);
}

//--------------------------------------------------------------------
WOCO_DigitalPinState* WOCO_DigitalPinState::CreateWriteReply ()
{
  return new WOCO_DigitalPinState (TYPE_Reply, ACTION_Write, 0, LOW);
}

//--------------------------------------------------------------------
::EResult WOCO_DigitalPinState::AnalyzeCommandData (uint8_t*  i_pCommandDataBuffer,
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
    isOK &= RingBuffer_GetValueAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, m_PinNumber);
    if (get_TypeIsReply ()
    ||  get_ActionIsWrite ())
      isOK &= RingBuffer_GetValueAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, m_PinState);
  }
  if (!isOK)
    return ::EResult::FAIL_Buffer_GetValue;

  return ::EResult::SUCCESS;
}

//--------------------------------------------------------------------
::EResult WOCO_DigitalPinState::ComposeCommandData (uint8_t*  i_pCommandDataBuffer,
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
    isOK &= RingBuffer_SetValueAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, m_PinNumber);
    if (get_TypeIsReply ()
    ||  get_ActionIsWrite ())
      isOK &= RingBuffer_SetValueAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, m_PinState);
  }
  if (!isOK)
    return ::EResult::FAIL_Buffer_SetValue;

  return ::EResult::SUCCESS;
}
