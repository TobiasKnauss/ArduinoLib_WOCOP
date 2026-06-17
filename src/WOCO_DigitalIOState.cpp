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
::EResult WOCO_DigitalIOState::AnalyzeCommandData ( ByteBuffer* i_pCommandDataBuffer,
                                                    uint16_t    i_CommandDataLength)
{
  ::EResult result = WOCO::AnalyzeCommandData (i_pCommandDataBuffer, i_CommandDataLength);
  if (result != ::EResult::SUCCESS)
    return result;

  if (get_TypeIsRequest ()
  ||  get_ActionIsRead ())
  {
    i_pCommandDataBuffer->ReadValueAndMovePtr (m_IONumber);
    if (get_TypeIsReply ()
    ||  get_ActionIsWrite ())
      i_pCommandDataBuffer->ReadValueAndMovePtr (m_IOState);
  }

  return ::EResult::SUCCESS;
}

//--------------------------------------------------------------------
::EResult WOCO_DigitalIOState::ComposeCommandData ( ByteBuffer* i_pCommandDataBuffer,
                                                    uint16_t&   o_CommandDataLength)
{
  ::EResult result = WOCO::ComposeCommandData (i_pCommandDataBuffer, o_CommandDataLength);
  if (result != ::EResult::SUCCESS)
    return result;

  if (get_TypeIsRequest ()
  ||  get_ActionIsRead ())
  {
    i_pCommandDataBuffer->WriteValueAndMovePtr (m_IONumber);
    if (get_TypeIsReply ()
    ||  get_ActionIsWrite ())
      i_pCommandDataBuffer->WriteValueAndMovePtr (m_IOState);
  }

  return ::EResult::SUCCESS;
}
