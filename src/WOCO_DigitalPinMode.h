#ifndef WOCO_DigitalPinMode_h
#define WOCO_DigitalPinMode_h

#include "WOCO.h"

//--------------------------------------------------------------------
// Worker Command: Read/Write Digital Pin Mode
//--------------------------------------------------------------------
//  Offset  Length  Data
//     0.0     1.0  Pin Number
//     1.0     1.0  Pin Mode    (used in Read Reply, Write Request)
//--------------------------------------------------------------------
class WOCO_DigitalPinMode
: public WOCO
{
//==================== Fields ====================
  uint8_t m_PinNumber = 0;
  uint8_t m_PinMode   = 0;

//==================== Constructors ====================
public:
  WOCO_DigitalPinMode (bool    i_MessageTypeIsReply,
                       bool    i_ActionIsWrite);

  WOCO_DigitalPinMode (uint8_t i_PinNumber,
                       uint8_t i_PinMode,
                       bool    i_MessageTypeIsReply,
                       bool    i_ActionIsWrite);

//==================== Public Methods ====================
public:
  static WOCO_DigitalPinMode* CreateReadRequest  (uint8_t i_PinNumber);
  static WOCO_DigitalPinMode* CreateReadReply    (uint8_t i_PinNumber,
                                                  uint8_t i_PinMode);
  static WOCO_DigitalPinMode* CreateWriteRequest (uint8_t i_PinNumber,
                                                  uint8_t i_PinMode);
  static WOCO_DigitalPinMode* CreateWriteReply   ();

  ECommand GetCommand () override;

  uint8_t GetPinNumber ();
  uint8_t GetPinMode ();

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
