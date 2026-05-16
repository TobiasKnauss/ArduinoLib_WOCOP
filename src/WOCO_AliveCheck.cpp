#include "WOCO_AliveCheck.h"

//--------------------------------------------------------------------
WOCO_AliveCheck::WOCO_AliveCheck (bool i_TypeIsReply,
                                  bool i_ActionIsWrite)
: WOCO (i_TypeIsReply,
        i_ActionIsWrite)
{
}

//--------------------------------------------------------------------
WOCO::ECommand WOCO_AliveCheck::get_Command ()
{
  return ECommand::AliveCheck;
}

//--------------------------------------------------------------------
uint8_t WOCO_AliveCheck::get_CommandDataLength_ReadRequest ()
{
  return 0;
}

//--------------------------------------------------------------------
uint8_t WOCO_AliveCheck::get_CommandDataLength_ReadReply ()
{
  return 0;
}

//--------------------------------------------------------------------
WOCO_AliveCheck* WOCO_AliveCheck::CreateReadRequest ()
{
  return new WOCO_AliveCheck (TYPE_Request, ACTION_Read);
}

//--------------------------------------------------------------------
WOCO_AliveCheck* WOCO_AliveCheck::CreateReadReply ()
{
  return new WOCO_AliveCheck (TYPE_Reply, ACTION_Read);
}

//--------------------------------------------------------------------
::EResult WOCO_AliveCheck::AnalyzeCommandData (uint8_t* i_pCommandDataBuffer,
                                               uint8_t  i_CommandDataBufferLength,
                                               uint8_t  i_CommandDataLength)
{
  ::EResult result = WOCO::AnalyzeCommandData(i_pCommandDataBuffer, i_CommandDataBufferLength, i_CommandDataLength);
  if (result != ::EResult::SUCCESS)
    return result;

  return ::EResult::SUCCESS;
}

//--------------------------------------------------------------------
::EResult WOCO_AliveCheck::ComposeCommandData (uint8_t* i_pCommandDataBuffer,
                                               uint8_t  i_CommandDataBufferLength,
                                               uint8_t& o_CommandDataLength)
{
  ::EResult result = WOCO::ComposeCommandData (i_pCommandDataBuffer, i_CommandDataBufferLength, o_CommandDataLength);
  if (result != ::EResult::SUCCESS)
    return result;

  return ::EResult::SUCCESS;
}
