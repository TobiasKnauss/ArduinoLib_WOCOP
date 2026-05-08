#include "WOCO.h"

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
WOCO::WOCO (bool i_MessageTypeIsReply,
            bool i_ActionIsWrite)
{
  m_MessageTypeIsReply = i_MessageTypeIsReply;
  m_ActionIsWrite      = i_ActionIsWrite;
}

//--------------------------------------------------------------------
bool WOCO::GetActionIsRead ()
{
  return !m_ActionIsWrite;
}

//--------------------------------------------------------------------
bool WOCO::GetActionIsWrite ()
{
  return m_ActionIsWrite;
}

//--------------------------------------------------------------------
bool WOCO::GetMessageTypeIsRequest ()
{
  return !m_MessageTypeIsReply;
}

//--------------------------------------------------------------------
bool WOCO::GetMessageTypeIsReply ()
{
  return m_MessageTypeIsReply;
}

//--------------------------------------------------------------------
uint8_t WOCO::GetPayloadLengthExpected ()
{
  return m_MessageTypeIsReply
         ? m_ActionIsWrite
           ? GetPayloadLength_WriteReply ()
           : GetPayloadLength_ReadReply ()
         : m_ActionIsWrite
           ? GetPayloadLength_WriteRequest ()
           : GetPayloadLength_ReadRequest ();
}

//--------------------------------------------------------------------
bool WOCO::GetPayloadLengthIsVariable ()
{
  return false;
}

//--------------------------------------------------------------------
uint8_t WOCO::GetPayloadLength_WriteRequest ()
{
  return GetPayloadLength_ReadReply ();
}

//--------------------------------------------------------------------
uint8_t WOCO::GetPayloadLength_WriteReply ()
{
  return 0;
}

//--------------------------------------------------------------------
::EResult WOCO::AnalyzePayload (uint8_t* i_pPayloadBuffer,
                                uint8_t  i_PayloadBufferLength,
                                uint8_t  i_PayloadLength)
{
  if (i_pPayloadBuffer == 0)
    return ::EResult::FAIL_Pointer_IsZero;

  if (i_PayloadLength > i_PayloadBufferLength)
    return ::EResult::FAIL_Buffer_TooSmall;

  uint8_t expectedLength = GetPayloadLengthExpected ();
  if (GetPayloadLengthIsVariable ())
    if (i_PayloadLength < expectedLength)
      return (::EResult)EResult::FAIL_WOCO_Payload_LengthWrong;
  else
    if (i_PayloadLength != expectedLength)
      return (::EResult)EResult::FAIL_WOCO_Payload_LengthWrong;

  return ::EResult::SUCCESS;
}

//--------------------------------------------------------------------
::EResult WOCO::ComposePayload (uint8_t* i_pPayloadBuffer,
                                uint8_t  i_PayloadBufferLength,
                                uint8_t& o_PayloadLength)
{
  if (i_pPayloadBuffer == 0)
    return ::EResult::FAIL_Pointer_IsZero;

  uint8_t expectedLength = GetPayloadLengthExpected ();
  if (i_PayloadBufferLength < expectedLength)
    return ::EResult::FAIL_Buffer_TooSmall;

  o_PayloadLength = 0;

  return ::EResult::SUCCESS;
}
