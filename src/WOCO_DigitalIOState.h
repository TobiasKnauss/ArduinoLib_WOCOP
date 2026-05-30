#ifndef WOCO_DigitalIOState_h
#define WOCO_DigitalIOState_h

#include "WOCO.h"

//--------------------------------------------------------------------
// Worker Command: Read/Write Digital Pin State
//--------------------------------------------------------------------
//  Offset  Length  Data
//     0.0     1.0  Pin Number
//     1.0     1.0  Pin State    (used in Read Reply, Write Request)
//--------------------------------------------------------------------
// command data size combinations
//         read  write
// request   1     2
// reply     2     0
//--------------------------------------------------------------------
class WOCO_DigitalIOState
: public WOCO
{
//==================== Fields ====================
private:
  //-------------------- instance --------------------

  uint8_t m_IONumber = 0;
  bool    m_IOState  = false;

//==================== Constructors ====================
public:
  //-------------------- instance --------------------

  WOCO_DigitalIOState ( bool    i_TypeIsReply,
                        bool    i_ActionIsWrite);

  WOCO_DigitalIOState ( bool    i_TypeIsReply,
                        bool    i_ActionIsWrite,
                        uint8_t i_IONumber,
                        bool    i_IOState);

//==================== Properties ====================
public:
  //-------------------- instance --------------------

  ECommand get_Command () override;

  uint16_t get_CommandDataLength_ReadRequest () override;
  uint16_t get_CommandDataLength_ReadReply () override;

  uint8_t get_IONumber ();
  bool    get_IOState ();

//==================== Public Methods ====================
public:
  //-------------------- static --------------------

  static WOCO_DigitalIOState* CreateReadRequest  (uint8_t i_IONumber);
  static WOCO_DigitalIOState* CreateReadReply    (uint8_t i_IONumber,
                                                  bool    i_IOState);
  static WOCO_DigitalIOState* CreateWriteRequest (uint8_t i_IONumber,
                                                  bool    i_IOState);
  static WOCO_DigitalIOState* CreateWriteReply   ();

  //-------------------- instance --------------------

  ::EResult AnalyzeCommandData (uint8_t*  i_pCommandDataBuffer,
                                uint16_t  i_CommandDataBufferLength,
                                uint16_t  i_CommandDataLength) override;
  ::EResult ComposeCommandData (uint8_t*  i_pCommandDataBuffer,
                                uint16_t  i_CommandDataBufferLength,
                                uint16_t& o_CommandDataLength) override;
};

#endif
