#include "WOCO_DigitalPinState.h"

//--------------------------------------------------------------------
WOCO_DigitalPinState::WOCO_DigitalPinState (bool i_MessageTypeIsReply,
                                            bool i_ActionIsWrite)
: WOCO (i_MessageTypeIsReply,
        i_ActionIsWrite)
{
}

//--------------------------------------------------------------------
WOCO_DigitalPinState::WOCO_DigitalPinState (uint8_t i_PinNumber,
                                            bool    i_PinState,
                                            bool    i_MessageTypeIsReply,
                                            bool    i_ActionIsWrite)
: WOCO (i_MessageTypeIsReply,
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
uint8_t WOCO_DigitalPinState::get_PayloadLength_ReadRequest ()
{
  return 1;
}

//--------------------------------------------------------------------
uint8_t WOCO_DigitalPinState::get_PayloadLength_ReadReply ()
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
  return new WOCO_DigitalPinState (i_PinNumber, false, false, false);
}

//--------------------------------------------------------------------
WOCO_DigitalPinState* WOCO_DigitalPinState::CreateReadReply (uint8_t i_PinNumber,
                                                             bool    i_PinState)
{
  return new WOCO_DigitalPinState (i_PinNumber, i_PinState, true, false);
}

//--------------------------------------------------------------------
WOCO_DigitalPinState* WOCO_DigitalPinState::CreateWriteRequest (uint8_t i_PinNumber,
                                                                bool    i_PinState)
{
  return new WOCO_DigitalPinState (i_PinNumber, i_PinState, false, true);
}

//--------------------------------------------------------------------
WOCO_DigitalPinState* WOCO_DigitalPinState::CreateWriteReply ()
{
  return new WOCO_DigitalPinState (0, false, true, true);
}

//--------------------------------------------------------------------
::EResult WOCO_DigitalPinState::AnalyzePayload (uint8_t* i_pPayloadBuffer,
                                                uint8_t  i_PayloadBufferLength,
                                                uint8_t  i_PayloadLength)
{
  ::EResult result = WOCO::AnalyzePayload (i_pPayloadBuffer, i_PayloadBufferLength, i_PayloadLength);
  if (result != ::EResult::SUCCESS)
    return result;

  bool isOK = true;
  uint8_t* pCurrent = i_pPayloadBuffer;

  // payload size combinations
  //         read  write
  // request   1     2
  // reply     2     0

  if (get_TypeIsRequest ()
  ||  get_ActionIsRead ())
  {
    isOK &= RingBuffer_GetValueAndMovePtr (i_pPayloadBuffer, i_PayloadBufferLength, pCurrent, m_PinNumber);
    if (get_TypeIsReply ()
    ||  get_ActionIsWrite ())
      isOK &= RingBuffer_GetValueAndMovePtr (i_pPayloadBuffer, i_PayloadBufferLength, pCurrent, m_PinState);
  }
  if (!isOK)
    return ::EResult::FAIL_Buffer_GetValue;
  
  return ::EResult::SUCCESS;
}

//--------------------------------------------------------------------
::EResult WOCO_DigitalPinState::ComposePayload (uint8_t* i_pPayloadBuffer,
                                                uint8_t  i_PayloadBufferLength,
                                                uint8_t& o_PayloadLength)
{
  ::EResult result = WOCO::ComposePayload (i_pPayloadBuffer, i_PayloadBufferLength, o_PayloadLength);
  if (result != ::EResult::SUCCESS)
    return result;

  uint8_t* pCurrent = i_pPayloadBuffer;
  RingBuffer_SetValueAndMovePtr (i_pPayloadBuffer, i_PayloadBufferLength, pCurrent, m_PinNumber);
  if (get_ActionIsWrite ())
    RingBuffer_SetValueAndMovePtr (i_pPayloadBuffer, i_PayloadBufferLength, pCurrent, m_PinState);

  return ::EResult::SUCCESS;
}
