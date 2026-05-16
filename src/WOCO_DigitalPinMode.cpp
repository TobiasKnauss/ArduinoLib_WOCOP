#include <IOHelper.h>

#include "WOCO_DigitalPinMode.h"

//--------------------------------------------------------------------
WOCO_DigitalPinMode::WOCO_DigitalPinMode (bool i_TypeIsReply,
                                          bool i_ActionIsWrite)
: WOCO (i_TypeIsReply,
        i_ActionIsWrite)
{
}

//--------------------------------------------------------------------
WOCO_DigitalPinMode::WOCO_DigitalPinMode (bool    i_TypeIsReply,
                                          bool    i_ActionIsWrite,
                                          uint8_t i_PinNumber,
                                          uint8_t i_PinMode)
: WOCO (i_TypeIsReply,
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
uint8_t WOCO_DigitalPinMode::get_CommandDataLength_ReadRequest ()
{
  return 1;
}

//--------------------------------------------------------------------
uint8_t WOCO_DigitalPinMode::get_CommandDataLength_ReadReply ()
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
  return new WOCO_DigitalPinMode (TYPE_Request, ACTION_Read, i_PinNumber, 0);
}

//--------------------------------------------------------------------
WOCO_DigitalPinMode* WOCO_DigitalPinMode::CreateReadReply (uint8_t i_PinNumber,
                                                           uint8_t i_PinMode)
{
  return new WOCO_DigitalPinMode (TYPE_Reply, ACTION_Read, i_PinNumber, i_PinMode);
}

//--------------------------------------------------------------------
WOCO_DigitalPinMode* WOCO_DigitalPinMode::CreateWriteRequest (uint8_t i_PinNumber,
                                                              uint8_t i_PinMode)
{
  if (!isPinModeValid (i_PinMode))
    return nullptr;

  return new WOCO_DigitalPinMode (TYPE_Request, ACTION_Write, i_PinNumber, i_PinMode);
}

//--------------------------------------------------------------------
WOCO_DigitalPinMode* WOCO_DigitalPinMode::CreateWriteReply ()
{
  return new WOCO_DigitalPinMode (TYPE_Reply, ACTION_Write, 0, 0);
}

//--------------------------------------------------------------------
::EResult WOCO_DigitalPinMode::AnalyzeCommandData (uint8_t* i_pCommandDataBuffer,
                                                   uint8_t  i_CommandDataBufferLength,
                                                   uint8_t  i_CommandDataLength)
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
      isOK &= RingBuffer_GetValueAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, m_PinMode);
  }
  if (!isOK)
    return ::EResult::FAIL_Buffer_GetValue;
  
  return ::EResult::SUCCESS;
}

//--------------------------------------------------------------------
::EResult WOCO_DigitalPinMode::ComposeCommandData (uint8_t* i_pCommandDataBuffer,
                                                   uint8_t  i_CommandDataBufferLength,
                                                   uint8_t& o_CommandDataLength)
{
  ::EResult result = WOCO::ComposeCommandData (i_pCommandDataBuffer, i_CommandDataBufferLength, o_CommandDataLength);
  if (result != ::EResult::SUCCESS)
    return result;

  uint8_t* pCurrent = i_pCommandDataBuffer;
  RingBuffer_SetValueAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, m_PinNumber);
  if (get_ActionIsWrite ())
    RingBuffer_SetValueAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, m_PinMode);

  return ::EResult::SUCCESS;
}
