#ifndef WOCO_AliveCheck_h
#define WOCO_AliveCheck_h

#include "WOCO.h"

//--------------------------------------------------------------------
// Worker Command: Read Alive Check
//--------------------------------------------------------------------
//  Offset  Length  Data
//  --- no command data ---
//--------------------------------------------------------------------
// command data size combinations
//         read  write
// request  --    --
// reply    --    --
//--------------------------------------------------------------------
class WOCO_AliveCheck
: public WOCO
{
//==================== Constructors ====================
public:
  //-------------------- instance --------------------

  WOCO_AliveCheck (bool i_TypeIsReply,
                   bool i_ActionIsWrite);

//==================== Properties ====================
public:
  //-------------------- instance --------------------

  ECommand get_Command () override;

  uint16_t get_CommandDataLength_ReadRequest () override;
  uint16_t get_CommandDataLength_ReadReply () override;

//==================== Public Methods ====================
public:
  //-------------------- static --------------------

  static WOCO_AliveCheck* CreateReadRequest ();
  static WOCO_AliveCheck* CreateReadReply   ();

  //-------------------- instance --------------------

  ::EResult AnalyzeCommandData (uint8_t*  i_pCommandDataBuffer,
                                uint16_t  i_CommandDataBufferLength,
                                uint16_t  i_CommandDataLength) override;
  ::EResult ComposeCommandData (uint8_t*  i_pCommandDataBuffer,
                                uint16_t  i_CommandDataBufferLength,
                                uint16_t& o_CommandDataLength) override;
};

#endif
