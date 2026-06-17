#include "WOCO.h"
#include "WOCO_AliveCheck.h"
#include "WOCO_DigitalIOMode.h"
#include "WOCO_DigitalIOState.h"
#include "WOCO_DeviceName.h"
#include "WOCO_DeviceType.h"

//--------------------------------------------------------------------
#define X(name) const char WOCO::_EResult_##name[] PROGMEM = #name;
#include "WOCO_failures.h"
#undef X

//--------------------------------------------------------------------
#define X(name) _EResult_##name,
const char* const WOCO::c_EnumNames_ClassFailures[] PROGMEM =
{
  #include "WOCO_failures.h"
};
#undef X

//--------------------------------------------------------------------
::EResult WOCO::Create (ECommand i_CommandId,
                        bool     i_TypeIsReply,
                        bool     i_ActionIsWrite,
                        WOCO*&   o_pWOCO)
{
  if (o_pWOCO != nullptr)
    return (::EResult)EResult::FAIL_WOCO_Command_Exists;

  switch (i_CommandId)
  {
  case ECommand::AliveCheck:      o_pWOCO = new WOCO_AliveCheck     (i_TypeIsReply, i_ActionIsWrite); break;
  case ECommand::DigitalIOMode:   o_pWOCO = new WOCO_DigitalIOMode  (i_TypeIsReply, i_ActionIsWrite); break;
  case ECommand::DigitalIOState:  o_pWOCO = new WOCO_DigitalIOState (i_TypeIsReply, i_ActionIsWrite); break;
  case ECommand::DeviceName:      o_pWOCO = new WOCO_DeviceName     (i_TypeIsReply, i_ActionIsWrite); break;
  case ECommand::DeviceType:      o_pWOCO = new WOCO_DeviceType     (i_TypeIsReply, i_ActionIsWrite); break;
  default: return (::EResult)EResult::FAIL_WOCO_Command_IdInvalid;
  }

  return ::EResult::SUCCESS;
}

//--------------------------------------------------------------------
WOCO::WOCO (bool i_TypeIsReply,
            bool i_ActionIsWrite)
{
  m_TypeIsReply   = i_TypeIsReply;
  m_ActionIsWrite = i_ActionIsWrite;
}

//--------------------------------------------------------------------
bool WOCO::get_ActionIsRead ()
{
  return !m_ActionIsWrite;
}

//--------------------------------------------------------------------
bool WOCO::get_ActionIsWrite ()
{
  return m_ActionIsWrite;
}

//--------------------------------------------------------------------
bool WOCO::get_TypeIsRequest ()
{
  return !m_TypeIsReply;
}

//--------------------------------------------------------------------
bool WOCO::get_TypeIsReply ()
{
  return m_TypeIsReply;
}

//--------------------------------------------------------------------
uint8_t WOCO::get_CommandData_ExpectedLength ()
{
  return m_TypeIsReply
         ? m_ActionIsWrite
           ? get_CommandDataLength_WriteReply ()
           : get_CommandDataLength_ReadReply ()
         : m_ActionIsWrite
           ? get_CommandDataLength_WriteRequest ()
           : get_CommandDataLength_ReadRequest ();
}

//--------------------------------------------------------------------
bool WOCO::get_CommandData_IsLengthVariable ()
{
  return false;
}

//--------------------------------------------------------------------
uint16_t WOCO::get_CommandDataLength_WriteRequest ()
{
  return get_CommandDataLength_ReadReply ();
}

//--------------------------------------------------------------------
uint16_t WOCO::get_CommandDataLength_WriteReply ()
{
  return 0;
}

//--------------------------------------------------------------------
const __FlashStringHelper* WOCO::GetResultText (::EResult i_Result)
{
  if ((uint16_t)i_Result < (uint16_t)EResult::Dummy_FirstClassFailure)
    return Result::GetText (i_Result);
  return (const __FlashStringHelper*)pgm_read_ptr(&c_EnumNames_ClassFailures[(uint16_t)i_Result - (uint16_t)EResult::Dummy_FirstClassFailure - 1]);
}

//--------------------------------------------------------------------
::EResult WOCO::AnalyzeCommandData (ByteBuffer* i_pCommandDataBuffer,
                                    uint16_t    i_CommandDataLength)
{
  if (i_pCommandDataBuffer == nullptr)
    return ::EResult::FAIL_Pointer_IsZero;
  if (i_CommandDataLength > i_pCommandDataBuffer->get_Length ())
    return ::EResult::FAIL_Buffer_TooSmall;

  uint8_t expectedLength = get_CommandData_ExpectedLength ();
  if (get_CommandData_IsLengthVariable ())
  {
    if (i_CommandDataLength < expectedLength)
      return (::EResult)EResult::FAIL_WOCO_CommandData_LengthWrong;
  }
  else
  {
    if (i_CommandDataLength != expectedLength)
      return (::EResult)EResult::FAIL_WOCO_CommandData_LengthWrong;
  }

  return ::EResult::SUCCESS;
}

//--------------------------------------------------------------------
::EResult WOCO::ComposeCommandData (ByteBuffer* i_pCommandDataBuffer,
                                    uint16_t&   o_CommandDataLength)
{
  if (i_pCommandDataBuffer == nullptr)
    return ::EResult::FAIL_Pointer_IsZero;

  uint8_t expectedLength = get_CommandData_ExpectedLength ();
  if (i_pCommandDataBuffer->get_Length () < expectedLength)
    return ::EResult::FAIL_Buffer_TooSmall;

  o_CommandDataLength = 0;
  i_pCommandDataBuffer->SetWritePointer (0);

  return ::EResult::SUCCESS;
}
