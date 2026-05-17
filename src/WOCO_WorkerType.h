#ifndef WOCO_WorkerType_h
#define WOCO_WorkerType_h

#include "WOCO.h"

//--------------------------------------------------------------------
// Worker Command: Read Worker Type
//--------------------------------------------------------------------
//  Offset  Length  Data
//     0.0     4.0  Worker Type
//--------------------------------------------------------------------
// command data size combinations
//         read  write
// request   0    --
// reply     4    --
//--------------------------------------------------------------------
class WOCO_WorkerType
: public WOCO
{
//==================== Fields ====================
private:
  //-------------------- instance --------------------

  uint32_t m_WorkerType = 0;

//==================== Constructors ====================
public:
  //-------------------- instance --------------------

  WOCO_WorkerType (bool i_TypeIsReply,
                   bool i_ActionIsWrite);

  WOCO_WorkerType (bool     i_TypeIsReply,
                   bool     i_ActionIsWrite,
                   uint32_t i_WorkerType);

//==================== Properties ====================
public:
  //-------------------- instance --------------------

  ECommand get_Command () override;

  uint8_t get_CommandDataLength_ReadRequest () override;
  uint8_t get_CommandDataLength_ReadReply () override;

  uint32_t get_WorkerType ();

//==================== Public Methods ====================
public:
  //-------------------- static --------------------

  static WOCO_WorkerType* CreateReadRequest ();
  static WOCO_WorkerType* CreateReadReply   (uint32_t i_WorkerType);

  //-------------------- instance --------------------

  ::EResult AnalyzeCommandData (uint8_t* i_pCommandDataBuffer,
                                uint8_t  i_CommandDataBufferLength,
                                uint8_t  i_CommandDataLength) override;
  ::EResult ComposeCommandData (uint8_t* i_pCommandDataBuffer,
                                uint8_t  i_CommandDataBufferLength,
                                uint8_t& o_CommandDataLength) override;
};

#endif
