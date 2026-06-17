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
uint16_t WOCO_AliveCheck::get_CommandDataLength_ReadRequest ()
{
  return 0;
}

//--------------------------------------------------------------------
uint16_t WOCO_AliveCheck::get_CommandDataLength_ReadReply ()
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
::EResult WOCO_AliveCheck::AnalyzeCommandData ( ByteBuffer* i_pCommandDataBuffer,
                                                uint16_t    i_CommandDataLength)
{
  return WOCO::AnalyzeCommandData (i_pCommandDataBuffer, i_CommandDataLength);
}

//--------------------------------------------------------------------
::EResult WOCO_AliveCheck::ComposeCommandData ( ByteBuffer* i_pCommandDataBuffer,
                                                uint16_t&   o_CommandDataLength)
{
  return WOCO::ComposeCommandData (i_pCommandDataBuffer, o_CommandDataLength);
}
