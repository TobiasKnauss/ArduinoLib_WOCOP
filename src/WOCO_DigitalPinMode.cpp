#include <IOHelper.h>

#include "WOCO_DigitalPinMode.h"

//--------------------------------------------------------------------
WOCO_DigitalPinMode::WOCO_DigitalPinMode (bool i_MessageTypeIsReply,
                                          bool i_ActionIsWrite)
: WOCO (i_MessageTypeIsReply,
        i_ActionIsWrite)
{
}

//--------------------------------------------------------------------
WOCO_DigitalPinMode::WOCO_DigitalPinMode (uint8_t i_PinNumber,
                                          uint8_t i_PinMode,
                                          bool    i_MessageTypeIsReply,
                                          bool    i_ActionIsWrite)
: WOCO (i_MessageTypeIsReply,
        i_ActionIsWrite)
{
  m_PinNumber = i_PinNumber;
  m_PinMode   = i_PinMode;
}

//--------------------------------------------------------------------
WOCO::ECommand WOCO_DigitalPinMode::get_Command ()
{
  return ECommand::DigitalPinMode;
}

//--------------------------------------------------------------------
uint8_t WOCO_DigitalPinMode::get_PayloadLength_ReadRequest ()
{
  return 1;
}

//--------------------------------------------------------------------
uint8_t WOCO_DigitalPinMode::get_PayloadLength_ReadReply ()
{
  return 2;
}

//--------------------------------------------------------------------
uint8_t WOCO_DigitalPinMode::get_PinNumber ()
{
  return m_PinNumber;
}

//--------------------------------------------------------------------
uint8_t WOCO_DigitalPinMode::get_PinMode ()
{
  return m_PinMode;
}

//--------------------------------------------------------------------
WOCO_DigitalPinMode* WOCO_DigitalPinMode::CreateReadRequest (uint8_t i_PinNumber)
{
  return new WOCO_DigitalPinMode (i_PinNumber, 0, false, false);
}

//--------------------------------------------------------------------
WOCO_DigitalPinMode* WOCO_DigitalPinMode::CreateReadReply (uint8_t i_PinNumber,
                                                           uint8_t i_PinMode)
{
  return new WOCO_DigitalPinMode (i_PinNumber, i_PinMode, true, false);
}

//--------------------------------------------------------------------
WOCO_DigitalPinMode* WOCO_DigitalPinMode::CreateWriteRequest (uint8_t i_PinNumber,
                                                              uint8_t i_PinMode)
{
  if (!isPinModeValid (i_PinMode))
    return 0;

  return new WOCO_DigitalPinMode (i_PinNumber, i_PinMode, false, true);
}

//--------------------------------------------------------------------
WOCO_DigitalPinMode* WOCO_DigitalPinMode::CreateWriteReply ()
{
  return new WOCO_DigitalPinMode (0, 0, true, true);
}

//--------------------------------------------------------------------
::EResult WOCO_DigitalPinMode::AnalyzePayload (uint8_t* i_pPayloadBuffer,
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
      isOK &= RingBuffer_GetValueAndMovePtr (i_pPayloadBuffer, i_PayloadBufferLength, pCurrent, m_PinMode);
  }
  if (!isOK)
    return ::EResult::FAIL_Buffer_GetValue;
  
  return ::EResult::SUCCESS;
}

//--------------------------------------------------------------------
::EResult WOCO_DigitalPinMode::ComposePayload (uint8_t* i_pPayloadBuffer,
                                               uint8_t  i_PayloadBufferLength,
                                               uint8_t& o_PayloadLength)
{
  ::EResult result = WOCO::ComposePayload (i_pPayloadBuffer, i_PayloadBufferLength, o_PayloadLength);
  if (result != ::EResult::SUCCESS)
    return result;

  uint8_t* pCurrent = i_pPayloadBuffer;
  RingBuffer_SetValueAndMovePtr (i_pPayloadBuffer, i_PayloadBufferLength, pCurrent, m_PinNumber);
  if (get_ActionIsWrite ())
    RingBuffer_SetValueAndMovePtr (i_pPayloadBuffer, i_PayloadBufferLength, pCurrent, m_PinMode);

  return ::EResult::SUCCESS;
}
