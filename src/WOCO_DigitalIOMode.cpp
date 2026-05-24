#include <IOHelper.h>

#include "WOCO_DigitalIOMode.h"

//--------------------------------------------------------------------
WOCO_DigitalIOMode::WOCO_DigitalIOMode (bool i_TypeIsReply,
                                        bool i_ActionIsWrite)
: WOCO (i_TypeIsReply,
        i_ActionIsWrite)
{
}

//--------------------------------------------------------------------
WOCO_DigitalIOMode::WOCO_DigitalIOMode (bool    i_TypeIsReply,
                                        bool    i_ActionIsWrite,
                                        uint8_t i_IONumber,
                                        uint8_t i_IOMode)
: WOCO (i_TypeIsReply,
        i_ActionIsWrite)
{
  m_IONumber = i_IONumber;
  m_IOMode   = i_IOMode;
}

//--------------------------------------------------------------------
WOCO::ECommand WOCO_DigitalIOMode::get_Command ()
{
  return ECommand::DigitalIOMode;
}

//--------------------------------------------------------------------
uint16_t WOCO_DigitalIOMode::get_CommandDataLength_ReadRequest ()
{
  return 1;
}

//--------------------------------------------------------------------
uint16_t WOCO_DigitalIOMode::get_CommandDataLength_ReadReply ()
{
  return 2;
}

//--------------------------------------------------------------------
uint8_t WOCO_DigitalIOMode::get_IONumber ()
{
  return m_IONumber;
}

//--------------------------------------------------------------------
uint8_t WOCO_DigitalIOMode::get_IOMode ()
{
  return m_IOMode;
}

//--------------------------------------------------------------------
WOCO_DigitalIOMode* WOCO_DigitalIOMode::CreateReadRequest (uint8_t i_IONumber)
{
  return new WOCO_DigitalIOMode (TYPE_Request, ACTION_Read, i_IONumber, 0);
}

//--------------------------------------------------------------------
WOCO_DigitalIOMode* WOCO_DigitalIOMode::CreateReadReply ( uint8_t i_IONumber,
                                                          uint8_t i_IOMode)
{
  return new WOCO_DigitalIOMode (TYPE_Reply, ACTION_Read, i_IONumber, i_IOMode);
}

//--------------------------------------------------------------------
WOCO_DigitalIOMode* WOCO_DigitalIOMode::CreateWriteRequest (uint8_t i_IONumber,
                                                            uint8_t i_IOMode)
{
  if (!isPinModeValid (i_IOMode))
    return nullptr;

  return new WOCO_DigitalIOMode (TYPE_Request, ACTION_Write, i_IONumber, i_IOMode);
}

//--------------------------------------------------------------------
WOCO_DigitalIOMode* WOCO_DigitalIOMode::CreateWriteReply ()
{
  return new WOCO_DigitalIOMode (TYPE_Reply, ACTION_Write, 0, 0);
}

//--------------------------------------------------------------------
::EResult WOCO_DigitalIOMode::AnalyzeCommandData (uint8_t*  i_pCommandDataBuffer,
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
      isOK &= RingBuffer_GetValueAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, m_IOMode);
  }
  if (!isOK)
    return ::EResult::FAIL_Buffer_GetValue;

  return ::EResult::SUCCESS;
}

//--------------------------------------------------------------------
::EResult WOCO_DigitalIOMode::ComposeCommandData (uint8_t*  i_pCommandDataBuffer,
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
      isOK &= RingBuffer_SetValueAndMovePtr (i_pCommandDataBuffer, i_CommandDataBufferLength, pCurrent, m_IOMode);
  }
  if (!isOK)
    return ::EResult::FAIL_Buffer_SetValue;

  return ::EResult::SUCCESS;
}
