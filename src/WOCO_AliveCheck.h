#ifndef WOCO_AliveCheck_h
#define WOCO_AliveCheck_h

#include "WOCO.h"

//--------------------------------------------------------------------
// Worker Command: Read Alive Check
//--------------------------------------------------------------------
//  Offset  Length  Data
//  --- no payload ---
//--------------------------------------------------------------------
class WOCO_AliveCheck
: public WOCO
{
//==================== Constructors ====================
  WOCO_AliveCheck (bool i_MessageTypeIsReply,
                   bool i_ActionIsWrite);

//==================== Public Methods ====================
public:
  static WOCO_AliveCheck* CreateReadRequest ();
  static WOCO_AliveCheck* CreateReadReply   ();

  uint16_t GetCommand () override;

  uint8_t GetPayloadLength_ReadRequest () override;
  uint8_t GetPayloadLength_ReadReply () override;

  ::EResult AnalyzePayload (uint8_t* i_pPayloadBuffer,
                            uint8_t  i_PayloadBufferLength,
                            uint8_t  i_PayloadLength) override;
  ::EResult ComposePayload (uint8_t* i_pPayloadBuffer,
                            uint8_t  i_PayloadBufferLength,
                            uint8_t& o_PayloadLength) override;
};

#endif
