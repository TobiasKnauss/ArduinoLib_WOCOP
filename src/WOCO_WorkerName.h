#ifndef WOCO_WorkerName_h
#define WOCO_WorkerName_h

#include "WOCO.h"

//--------------------------------------------------------------------
// Worker Command: Read Worker Name
//--------------------------------------------------------------------
//  Offset  Length  Data
//     0.0    32.0  Worker Name
//--------------------------------------------------------------------
// command data size combinations
//         read  write
// request   0    --
// reply    32    --
//--------------------------------------------------------------------
class WOCO_WorkerName
: public WOCO
{
//==================== Fields ====================
private:
  //-------------------- instance --------------------

  char m_WorkerName[32];

//==================== Constructors ====================
public:
  //-------------------- instance --------------------

  WOCO_WorkerName (bool i_TypeIsReply,
                   bool i_ActionIsWrite);

  WOCO_WorkerName (bool    i_TypeIsReply,
                   bool    i_ActionIsWrite,
                   char*   i_pWorkerName,
                   uint8_t i_WorkerNameLength);

//==================== Properties ====================
public:
  //-------------------- instance --------------------

  ECommand get_Command () override;

  virtual bool get_CommandData_IsLengthVariable () override;

  uint16_t get_CommandDataLength_ReadRequest () override;
  uint16_t get_CommandDataLength_ReadReply () override;

  char*   get_WorkerName ();
  uint8_t get_WorkerNameLength ();

//==================== Public Methods ====================
public:
  //-------------------- static --------------------

  static WOCO_WorkerName* CreateReadRequest ();
  static WOCO_WorkerName* CreateReadReply   (char*   i_pWorkerName,
                                             uint8_t i_WorkerNameLength);

  //-------------------- instance --------------------

  ::EResult AnalyzeCommandData (uint8_t*  i_pCommandDataBuffer,
                                uint16_t  i_CommandDataBufferLength,
                                uint16_t  i_CommandDataLength) override;
  ::EResult ComposeCommandData (uint8_t*  i_pCommandDataBuffer,
                                uint16_t  i_CommandDataBufferLength,
                                uint16_t& o_CommandDataLength) override;
};

#endif
