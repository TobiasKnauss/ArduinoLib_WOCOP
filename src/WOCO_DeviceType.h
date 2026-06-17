#ifndef WOCO_DeviceType_h
#define WOCO_DeviceType_h

#include "WOCO.h"

//--------------------------------------------------------------------
// Worker Command: Read Device Type
//--------------------------------------------------------------------
//  Offset  Length  Data
//     0.0     4.0  Device Type
//--------------------------------------------------------------------
// command data size combinations
//         read  write
// request   0    --
// reply     4    --
//--------------------------------------------------------------------
class WOCO_DeviceType
: public WOCO
{
//==================== Fields ====================
private:
  //-------------------- instance --------------------

  uint32_t m_DeviceType = 0;

//==================== Constructors ====================
public:
  //-------------------- instance --------------------

  WOCO_DeviceType (bool i_TypeIsReply,
                   bool i_ActionIsWrite);

  WOCO_DeviceType (bool     i_TypeIsReply,
                   bool     i_ActionIsWrite,
                   uint32_t i_DeviceType);

//==================== Properties ====================
public:
  //-------------------- instance --------------------

  ECommand get_Command () override;

  uint16_t get_CommandDataLength_ReadRequest () override;
  uint16_t get_CommandDataLength_ReadReply () override;

  uint32_t get_DeviceType ();

//==================== Public Methods ====================
public:
  //-------------------- static --------------------

  static WOCO_DeviceType* CreateReadRequest ();
  static WOCO_DeviceType* CreateReadReply   (uint32_t i_DeviceType);

  //-------------------- instance --------------------

  ::EResult AnalyzeCommandData (ByteBuffer* i_pCommandDataBuffer,
                                uint16_t    i_CommandDataLength) override;
  ::EResult ComposeCommandData (ByteBuffer* i_pCommandDataBuffer,
                                uint16_t&   o_CommandDataLength) override;
};

#endif
