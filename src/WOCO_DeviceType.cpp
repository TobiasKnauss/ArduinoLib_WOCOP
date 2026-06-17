#include "WOCO_DeviceType.h"

//--------------------------------------------------------------------
WOCO_DeviceType::WOCO_DeviceType (bool i_TypeIsReply,
                                  bool i_ActionIsWrite)
: WOCO (i_TypeIsReply,
        i_ActionIsWrite)
{
}

//--------------------------------------------------------------------
WOCO_DeviceType::WOCO_DeviceType (bool     i_TypeIsReply,
                                  bool     i_ActionIsWrite,
                                  uint32_t i_DeviceType)
: WOCO (i_TypeIsReply,
        i_ActionIsWrite)
{
  m_DeviceType = i_DeviceType;
}

//--------------------------------------------------------------------
WOCO::ECommand WOCO_DeviceType::get_Command ()
{
  return ECommand::DeviceType;
}

//--------------------------------------------------------------------
uint16_t WOCO_DeviceType::get_CommandDataLength_ReadRequest ()
{
  return 0;
}

//--------------------------------------------------------------------
uint16_t WOCO_DeviceType::get_CommandDataLength_ReadReply ()
{
  return 4;
}

//--------------------------------------------------------------------
uint32_t WOCO_DeviceType::get_DeviceType ()
{
  return m_DeviceType;
}

//--------------------------------------------------------------------
WOCO_DeviceType* WOCO_DeviceType::CreateReadRequest ()
{
  return new WOCO_DeviceType (TYPE_Request, ACTION_Read);
}

//--------------------------------------------------------------------
WOCO_DeviceType* WOCO_DeviceType::CreateReadReply (uint32_t i_DeviceType)
{
  return new WOCO_DeviceType (TYPE_Reply, ACTION_Read, i_DeviceType);
}

//--------------------------------------------------------------------
::EResult WOCO_DeviceType::AnalyzeCommandData ( ByteBuffer* i_pCommandDataBuffer,
                                                uint16_t    i_CommandDataLength)
{
  ::EResult result = WOCO::AnalyzeCommandData (i_pCommandDataBuffer, i_CommandDataLength);
  if (result != ::EResult::SUCCESS)
    return result;

  bool isOK = true;

  if (get_TypeIsReply ())
    isOK &= i_pCommandDataBuffer->ReadValueAndMovePtr (m_DeviceType, c_InvertByteOrder);
  if (!isOK)
    return ::EResult::FAIL_Buffer_ReadValue;

  return ::EResult::SUCCESS;
}

//--------------------------------------------------------------------
::EResult WOCO_DeviceType::ComposeCommandData ( ByteBuffer* i_pCommandDataBuffer,
                                                uint16_t&   o_CommandDataLength)
{
  ::EResult result = WOCO::ComposeCommandData (i_pCommandDataBuffer, o_CommandDataLength);
  if (result != ::EResult::SUCCESS)
    return result;

  bool isOK = true;

  if (get_TypeIsReply ())
    isOK &= i_pCommandDataBuffer->WriteValueAndMovePtr (m_DeviceType, c_InvertByteOrder);
  if (!isOK)
    return ::EResult::FAIL_Buffer_WriteValue;

  return ::EResult::SUCCESS;
}
