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
public:
  WOCO_AliveCheck (bool i_MessageTypeIsReply,
                   bool i_ActionIsWrite);

//==================== Properties ====================
public:
  //-------------------- instance --------------------

  ECommand get_Command () override;

  uint8_t get_PayloadLength_ReadRequest () override;
  uint8_t get_PayloadLength_ReadReply () override;

//==================== Public Methods ====================
public:
  //-------------------- static --------------------

  static WOCO_AliveCheck* CreateReadRequest ();
  static WOCO_AliveCheck* CreateReadReply   ();

  //-------------------- instance --------------------

  ::EResult AnalyzePayload (uint8_t* i_pPayloadBuffer,
                            uint8_t  i_PayloadBufferLength,
                            uint8_t  i_PayloadLength) override;
  ::EResult ComposePayload (uint8_t* i_pPayloadBuffer,
                            uint8_t  i_PayloadBufferLength,
                            uint8_t& o_PayloadLength) override;
};

#endif
