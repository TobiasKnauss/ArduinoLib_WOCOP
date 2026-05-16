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
// command data size combinations
//         read  write
// request   1     2
// reply     2     0
//--------------------------------------------------------------------
class WOCO_DigitalPinState
: public WOCO
{
//==================== Fields ====================
private:
  //-------------------- instance --------------------

  uint8_t m_PinNumber = 0;
  bool    m_PinState  = false;

//==================== Constructors ====================
public:
  //-------------------- instance --------------------

  WOCO_DigitalPinState (bool    i_TypeIsReply,
                        bool    i_ActionIsWrite);

  WOCO_DigitalPinState (bool    i_TypeIsReply,
                        bool    i_ActionIsWrite,
                        uint8_t i_PinNumber,
                        bool    i_PinState);

//==================== Properties ====================
public:
  //-------------------- instance --------------------

  ECommand get_Command () override;

  uint8_t get_CommandDataLength_ReadRequest () override;
  uint8_t get_CommandDataLength_ReadReply () override;

  uint8_t get_PinNumber ();
  bool    get_PinState ();

//==================== Public Methods ====================
public:
  //-------------------- static --------------------

  static WOCO_DigitalPinState* CreateReadRequest  (uint8_t i_PinNumber);
  static WOCO_DigitalPinState* CreateReadReply    (uint8_t i_PinNumber,
                                                   bool    i_PinState);
  static WOCO_DigitalPinState* CreateWriteRequest (uint8_t i_PinNumber,
                                                   bool    i_PinState);
  static WOCO_DigitalPinState* CreateWriteReply   ();

  //-------------------- instance --------------------

  ::EResult AnalyzeCommandData (uint8_t* i_pCommandDataBuffer,
                                uint8_t  i_CommandDataBufferLength,
                                uint8_t  i_CommandDataLength) override;
  ::EResult ComposeCommandData (uint8_t* i_pCommandDataBuffer,
                                uint8_t  i_CommandDataBufferLength,
                                uint8_t& o_CommandDataLength) override;
};

#endif
