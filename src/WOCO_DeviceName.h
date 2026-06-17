#ifndef WOCO_DeviceName_h
#define WOCO_DeviceName_h

#include "WOCO.h"

//--------------------------------------------------------------------
// Worker Command: Read Device Name
//--------------------------------------------------------------------
//  Offset  Length  Data
//     0.0    32.0  Device Name
//--------------------------------------------------------------------
// command data size combinations
//         read  write
// request   0    --
// reply    32    --
//--------------------------------------------------------------------
class WOCO_DeviceName
: public WOCO
{
//==================== Fields ====================
private:
  //-------------------- instance --------------------

  char m_DeviceName[32];

//==================== Constructors ====================
public:
  //-------------------- instance --------------------

  WOCO_DeviceName (bool i_TypeIsReply,
                   bool i_ActionIsWrite);

  WOCO_DeviceName (bool    i_TypeIsReply,
                   bool    i_ActionIsWrite,
                   char*   i_pDeviceName,
                   uint8_t i_DeviceNameLength);

//==================== Properties ====================
public:
  //-------------------- instance --------------------

  ECommand get_Command () override;

  virtual bool get_CommandData_IsLengthVariable () override;

  uint16_t get_CommandDataLength_ReadRequest () override;
  uint16_t get_CommandDataLength_ReadReply () override;

  char*   get_DeviceName ();
  uint8_t get_DeviceNameLength ();

//==================== Public Methods ====================
public:
  //-------------------- static --------------------

  static WOCO_DeviceName* CreateReadRequest ();
  static WOCO_DeviceName* CreateReadReply   (char*   i_pDeviceName,
                                             uint8_t i_DeviceNameLength);

  //-------------------- instance --------------------

  ::EResult AnalyzeCommandData (ByteBuffer* i_pCommandDataBuffer,
                                uint16_t    i_CommandDataLength) override;
  ::EResult ComposeCommandData (ByteBuffer* i_pCommandDataBuffer,
                                uint16_t&   o_CommandDataLength) override;
};

#endif
