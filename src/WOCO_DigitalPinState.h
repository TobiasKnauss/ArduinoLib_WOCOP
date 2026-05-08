#ifndef WOCO_DigitalPinState_h
#define WOCO_DigitalPinState_h

#include "WOCO.h"

//--------------------------------------------------------------------
// Worker Command: Read/Write Digital Pin State
//--------------------------------------------------------------------
//  Offset  Length  Data
//     0.0     1.0  Pin Number
//     1.0     1.0  Pin State    (used in Read Reply, Write Request)
//--------------------------------------------------------------------
class WOCO_DigitalPinState
: public WOCO
{
//==================== Fields ====================
  uint8_t m_PinNumber = 0;
  bool    m_PinState  = false;

//==================== Constructors ====================
  WOCO_DigitalPinState (uint8_t i_PinNumber,
                        bool    i_PinState,
                        bool    i_MessageTypeIsReply,
                        bool    i_ActionIsWrite);

//==================== Public Methods ====================
public:
  static WOCO_DigitalPinState* CreateReadRequest  (uint8_t i_PinNumber);
  static WOCO_DigitalPinState* CreateReadReply    (uint8_t i_PinNumber,
                                                   bool    i_PinState);
  static WOCO_DigitalPinState* CreateWriteRequest (uint8_t i_PinNumber,
                                                   bool    i_PinState);
  static WOCO_DigitalPinState* CreateWriteReply   ();

  uint16_t GetCommand () override;

  uint8_t GetPinNumber ();
  bool    GetPinState ();

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
