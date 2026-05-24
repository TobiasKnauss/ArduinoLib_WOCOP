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
// command data size combinations
//         read  write
// request   1     2
// reply     2     0
//--------------------------------------------------------------------
class WOCO_DigitalPinMode
: public WOCO
{
//==================== Fields ====================
private:
  //-------------------- instance --------------------

  uint8_t m_PinNumber = 0;
  uint8_t m_PinMode   = 0;

//==================== Constructors ====================
public:
  //-------------------- instance --------------------

  WOCO_DigitalPinMode (bool    i_TypeIsReply,
                       bool    i_ActionIsWrite);

  WOCO_DigitalPinMode (bool    i_TypeIsReply,
                       bool    i_ActionIsWrite,
                       uint8_t i_PinNumber,
                       uint8_t i_PinMode);

//==================== Properties ====================
public:
  //-------------------- instance --------------------

  ECommand get_Command () override;

  uint16_t get_CommandDataLength_ReadRequest () override;
  uint16_t get_CommandDataLength_ReadReply () override;

  uint8_t get_PinNumber ();
  uint8_t get_PinMode ();

//==================== Public Methods ====================
public:
  //-------------------- static --------------------

  static WOCO_DigitalPinMode* CreateReadRequest  (uint8_t i_PinNumber);
  static WOCO_DigitalPinMode* CreateReadReply    (uint8_t i_PinNumber,
                                                  uint8_t i_PinMode);
  static WOCO_DigitalPinMode* CreateWriteRequest (uint8_t i_PinNumber,
                                                  uint8_t i_PinMode);
  static WOCO_DigitalPinMode* CreateWriteReply   ();

  //-------------------- instance --------------------

  ::EResult AnalyzeCommandData (uint8_t*  i_pCommandDataBuffer,
                                uint16_t  i_CommandDataBufferLength,
                                uint16_t  i_CommandDataLength) override;
  ::EResult ComposeCommandData (uint8_t*  i_pCommandDataBuffer,
                                uint16_t  i_CommandDataBufferLength,
                                uint16_t& o_CommandDataLength) override;
};

#endif
