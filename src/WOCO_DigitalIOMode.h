#ifndef WOCO_DigitalIOMode_h
#define WOCO_DigitalIOMode_h

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
class WOCO_DigitalIOMode
: public WOCO
{
//==================== Fields ====================
private:
  //-------------------- instance --------------------

  uint8_t m_IONumber = 0;
  uint8_t m_IOMode   = 0;

//==================== Constructors ====================
public:
  //-------------------- instance --------------------

  WOCO_DigitalIOMode (bool    i_TypeIsReply,
                      bool    i_ActionIsWrite);

  WOCO_DigitalIOMode (bool    i_TypeIsReply,
                      bool    i_ActionIsWrite,
                      uint8_t i_IONumber,
                      uint8_t i_IOMode);

//==================== Properties ====================
public:
  //-------------------- instance --------------------

  ECommand get_Command () override;

  uint16_t get_CommandDataLength_ReadRequest () override;
  uint16_t get_CommandDataLength_ReadReply () override;

  uint8_t get_IONumber ();
  uint8_t get_IOMode ();

//==================== Public Methods ====================
public:
  //-------------------- static --------------------

  static WOCO_DigitalIOMode* CreateReadRequest  ( uint8_t i_IONumber);
  static WOCO_DigitalIOMode* CreateReadReply    ( uint8_t i_IONumber,
                                                  uint8_t i_IOMode);
  static WOCO_DigitalIOMode* CreateWriteRequest ( uint8_t i_IONumber,
                                                  uint8_t i_IOMode);
  static WOCO_DigitalIOMode* CreateWriteReply   ();

  //-------------------- instance --------------------

  ::EResult AnalyzeCommandData (ByteBuffer* i_pCommandDataBuffer,
                                uint16_t    i_CommandDataLength) override;
  ::EResult ComposeCommandData (ByteBuffer* i_pCommandDataBuffer,
                                uint16_t&   o_CommandDataLength) override;
};

#endif
