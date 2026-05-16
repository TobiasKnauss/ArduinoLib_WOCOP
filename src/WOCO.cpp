#include "WOCO.h"
#include "WOCO_AliveCheck.h"
#include "WOCO_DigitalPinMode.h"
#include "WOCO_DigitalPinState.h"

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
WOCO::WOCO (bool i_TypeIsReply,
            bool i_ActionIsWrite)
{
  m_TypeIsReply   = i_TypeIsReply;
  m_ActionIsWrite = i_ActionIsWrite;
}

//--------------------------------------------------------------------
::EResult WOCO::Create (ECommand i_CommandId,
                        bool     i_TypeIsReply,
                        bool     i_ActionIsWrite,
                        WOCO*&   o_pWOCO)
{
  if (o_pWOCO != 0)
    return (::EResult)EResult::FAIL_WOCO_Command_Exists;

  switch (i_CommandId)
  {
  case ECommand::AliveCheck:      o_pWOCO = new WOCO_AliveCheck      (i_TypeIsReply, i_ActionIsWrite); break;
  case ECommand::DigitalPinMode:  o_pWOCO = new WOCO_DigitalPinMode  (i_TypeIsReply, i_ActionIsWrite); break;
  case ECommand::DigitalPinState: o_pWOCO = new WOCO_DigitalPinState (i_TypeIsReply, i_ActionIsWrite); break;
  default: return (::EResult)EResult::FAIL_WOCO_Command_IdInvalid;
  }

  return ::EResult::SUCCESS;
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
uint8_t WOCO::get_CommandDataLength_WriteRequest ()
{
  return get_CommandDataLength_ReadReply ();
}

//--------------------------------------------------------------------
uint8_t WOCO::get_CommandDataLength_WriteReply ()
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
::EResult WOCO::AnalyzeCommandData (uint8_t* i_pCommandDataBuffer,
                                    uint8_t  i_CommandDataBufferLength,
                                    uint8_t  i_CommandDataLength)
{
  if (i_pCommandDataBuffer == 0)
    return ::EResult::FAIL_Pointer_IsZero;

  if (i_CommandDataLength > i_CommandDataBufferLength)
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
::EResult WOCO::ComposeCommandData (uint8_t* i_pCommandDataBuffer,
                                    uint8_t  i_CommandDataBufferLength,
                                    uint8_t& o_CommandDataLength)
{
  if (i_pCommandDataBuffer == 0)
    return ::EResult::FAIL_Pointer_IsZero;

  uint8_t expectedLength = get_CommandData_ExpectedLength ();
  if (i_CommandDataBufferLength < expectedLength)
    return ::EResult::FAIL_Buffer_TooSmall;

  o_CommandDataLength = 0;

  return ::EResult::SUCCESS;
}
