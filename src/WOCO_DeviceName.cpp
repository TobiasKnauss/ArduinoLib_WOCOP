#include "Arduino.h"
#include "WOCO_DeviceName.h"

//--------------------------------------------------------------------
WOCO_DeviceName::WOCO_DeviceName (bool i_TypeIsReply,
                                  bool i_ActionIsWrite)
: WOCO (i_TypeIsReply,
        i_ActionIsWrite)
{
  memset (m_DeviceName, 0x00, sizeof (m_DeviceName));
}

//--------------------------------------------------------------------
WOCO_DeviceName::WOCO_DeviceName (bool    i_TypeIsReply,
                                  bool    i_ActionIsWrite,
                                  char*   i_pDeviceName,
                                  uint8_t i_DeviceNameLength)
: WOCO (i_TypeIsReply,
        i_ActionIsWrite)
{
  memset (m_DeviceName, 0x00, sizeof (m_DeviceName));
  if (i_pDeviceName != nullptr)
    memcpy (m_DeviceName, i_pDeviceName, min (sizeof (m_DeviceName) - 1, i_DeviceNameLength));
}

//--------------------------------------------------------------------
WOCO::ECommand WOCO_DeviceName::get_Command ()
{
  return ECommand::DeviceName;
}

//--------------------------------------------------------------------
bool WOCO_DeviceName::get_CommandData_IsLengthVariable ()
{
  return true;
}

//--------------------------------------------------------------------
uint16_t WOCO_DeviceName::get_CommandDataLength_ReadRequest ()
{
  return 0;
}

//--------------------------------------------------------------------
uint16_t WOCO_DeviceName::get_CommandDataLength_ReadReply ()
{
  return 0;
}

//--------------------------------------------------------------------
char* WOCO_DeviceName::get_DeviceName ()
{
  return m_DeviceName;
}

//--------------------------------------------------------------------
uint8_t WOCO_DeviceName::get_DeviceNameLength ()
{
  return strlen (m_DeviceName);
}

//--------------------------------------------------------------------
WOCO_DeviceName* WOCO_DeviceName::CreateReadRequest ()
{
  return new WOCO_DeviceName (TYPE_Request, ACTION_Read);
}

//--------------------------------------------------------------------
WOCO_DeviceName* WOCO_DeviceName::CreateReadReply (char*   i_pDeviceName,
                                                   uint8_t i_DeviceNameLength)
{
  return new WOCO_DeviceName (TYPE_Reply, ACTION_Read, i_pDeviceName, i_DeviceNameLength);
}

//--------------------------------------------------------------------
::EResult WOCO_DeviceName::AnalyzeCommandData ( ByteBuffer* i_pCommandDataBuffer,
                                                uint16_t    i_CommandDataLength)
{
  ::EResult result = WOCO::AnalyzeCommandData (i_pCommandDataBuffer, i_CommandDataLength);
  if (result != ::EResult::SUCCESS)
    return result;

  bool isOK = true;

  memset (m_DeviceName, 0x00, sizeof (m_DeviceName));
  if (get_TypeIsReply ())
    isOK &= i_pCommandDataBuffer->ReadBytesAndMovePtr (i_CommandDataLength, (uint8_t*)m_DeviceName, false);
  if (!isOK)
    return ::EResult::FAIL_Buffer_ReadValue;

  return ::EResult::SUCCESS;
}

//--------------------------------------------------------------------
::EResult WOCO_DeviceName::ComposeCommandData ( ByteBuffer* i_pCommandDataBuffer,
                                                uint16_t&   o_CommandDataLength)
{
  ::EResult result = WOCO::ComposeCommandData (i_pCommandDataBuffer, o_CommandDataLength);
  if (result != ::EResult::SUCCESS)
    return result;

  bool isOK = true;

  if (get_TypeIsReply ())
    isOK &= i_pCommandDataBuffer->WriteBytesAndMovePtr (get_DeviceNameLength (), (uint8_t*)get_DeviceName (), false);
  if (!isOK)
    return ::EResult::FAIL_Buffer_WriteValue;

  return ::EResult::SUCCESS;
}
