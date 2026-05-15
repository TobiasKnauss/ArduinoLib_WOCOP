#include "WOCO_AliveCheck.h"

//--------------------------------------------------------------------
WOCO_AliveCheck::WOCO_AliveCheck (bool i_MessageTypeIsReply,
                                  bool i_ActionIsWrite)
: WOCO (i_MessageTypeIsReply,
        i_ActionIsWrite)
{
}

//--------------------------------------------------------------------
WOCO::ECommand WOCO_AliveCheck::get_Command ()
{
  return ECommand::AliveCheck;
}

//--------------------------------------------------------------------
uint8_t WOCO_AliveCheck::get_PayloadLength_ReadRequest ()
{
  return 0;
}

//--------------------------------------------------------------------
uint8_t WOCO_AliveCheck::get_PayloadLength_ReadReply ()
{
  return 0;
}

//--------------------------------------------------------------------
WOCO_AliveCheck* WOCO_AliveCheck::CreateReadRequest ()
{
  return new WOCO_AliveCheck (false, false);
}

//--------------------------------------------------------------------
WOCO_AliveCheck* WOCO_AliveCheck::CreateReadReply ()
{
  return new WOCO_AliveCheck (false, false);
}

//--------------------------------------------------------------------
::EResult WOCO_AliveCheck::AnalyzePayload (uint8_t* i_pPayloadBuffer,
                                           uint8_t  i_PayloadBufferLength,
                                           uint8_t  i_PayloadLength)
{
  ::EResult result = WOCO::AnalyzePayload(i_pPayloadBuffer, i_PayloadBufferLength, i_PayloadLength);
  if (result != ::EResult::SUCCESS)
    return result;

  return ::EResult::SUCCESS;
}

//--------------------------------------------------------------------
::EResult WOCO_AliveCheck::ComposePayload (uint8_t* i_pPayloadBuffer,
                                           uint8_t  i_PayloadBufferLength,
                                           uint8_t& o_PayloadLength)
{
  ::EResult result = WOCO::ComposePayload (i_pPayloadBuffer, i_PayloadBufferLength, o_PayloadLength);
  if (result != ::EResult::SUCCESS)
    return result;

  return ::EResult::SUCCESS;
}
