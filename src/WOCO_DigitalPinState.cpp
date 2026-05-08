#include "WOCO_DigitalPinState.h"

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
uint16_t WOCO_DigitalPinState::GetCommand ()
{
  return (uint16_t)ECommand::DigitalPinState;
}

//--------------------------------------------------------------------
uint8_t WOCO_DigitalPinState::GetPinNumber ()
{
  return m_PinNumber;
}

//--------------------------------------------------------------------
bool WOCO_DigitalPinState::GetPinState ()
{
  return m_PinState;
}

//--------------------------------------------------------------------
uint8_t WOCO_DigitalPinState::GetPayloadLength_ReadRequest ()
{
  return 1;
}

//--------------------------------------------------------------------
uint8_t WOCO_DigitalPinState::GetPayloadLength_ReadReply ()
{
  return 2;
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

  if (GetMessageTypeIsRequest ()
  ||  GetActionIsRead ())
  {
    isOK &= RingBuffer_GetValueAndMovePtr (i_pPayloadBuffer, i_PayloadBufferLength, pCurrent, m_PinNumber);
    if (GetMessageTypeIsReply ()
    ||  GetActionIsWrite ())
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
  if (GetActionIsWrite ())
    RingBuffer_SetValueAndMovePtr (i_pPayloadBuffer, i_PayloadBufferLength, pCurrent, m_PinState);

  return ::EResult::SUCCESS;
}
