#ifndef WOCO_h
#define WOCO_h

#include <MemoryTools.h>
#include <ByteBuffer.h>
#include <Result.h>

//--------------------------------------------------------------------
// WOCO: WOrker COmmand
//--------------------------------------------------------------------
class WOCO
{
//==================== Enums ====================
public:
  #define X(name) name,
  enum class EResult : uint16_t
  {
    Dummy_FirstClassFailure = (uint16_t)::EResult::Dummy_FirstClassFailure,
    #include "WOCO_failures.h"
    Dummy_LastClassFailure
  };
  #undef X

  enum class ECommand : uint16_t
  {
    None            = 0x0,
    DeviceType      = 0x0001,
    DeviceName      = 0x0002,
    AliveCheck      = 0x0100,
    DigitalIOMode   = 0x0101,
    DigitalIOState  = 0x0102,
  };

//==================== Fields ====================
public:
  //-------------------- static --------------------

  static const bool ACTION_Read  = false;
  static const bool ACTION_Write = true;
  static const bool TYPE_Reply   = true;
  static const bool TYPE_Request = false;

protected:
  //-------------------- static --------------------

  static const bool c_InvertByteOrder = true;

private:
  //-------------------- static --------------------

  static const char* const c_EnumNames_ClassFailures[] PROGMEM;

  #define X(name) static const char _EResult_##name[] PROGMEM;
  #include "WOCO_failures.h"
  #undef X

  //-------------------- instance --------------------

  bool m_ActionIsWrite = false;
  bool m_TypeIsReply   = false;

//==================== Constructors ====================
public:
  //-------------------- static --------------------

  static ::EResult Create (ECommand i_CommandId,
                           bool     i_TypeIsReply,
                           bool     i_ActionIsWrite,
                           WOCO*&   o_pWOCO);

public:
  //-------------------- instance --------------------

  virtual ~WOCO () = default;

protected:
  //-------------------- instance --------------------

  WOCO (bool i_TypeIsReply,
        bool i_ActionIsWrite);

//==================== Properties ====================
public:
  //-------------------- instance --------------------

  virtual ECommand get_Command () = 0;

  bool get_ActionIsRead ();
  bool get_ActionIsWrite ();
  bool get_TypeIsRequest ();
  bool get_TypeIsReply ();

  uint8_t      get_CommandData_ExpectedLength ();
  virtual bool get_CommandData_IsLengthVariable ();

  virtual uint16_t get_CommandDataLength_ReadRequest () = 0;
  virtual uint16_t get_CommandDataLength_ReadReply () = 0;
  virtual uint16_t get_CommandDataLength_WriteRequest ();
  virtual uint16_t get_CommandDataLength_WriteReply ();

//==================== Public Methods ====================
public:
  //-------------------- static --------------------

  static const __FlashStringHelper* GetResultText (::EResult i_Result);

  //-------------------- instance --------------------

  virtual ::EResult AnalyzeCommandData (ByteBuffer* i_pCommandDataBuffer,
                                        uint16_t    i_CommandDataLength);
  virtual ::EResult ComposeCommandData (ByteBuffer* i_pCommandDataBuffer,
                                        uint16_t&   o_CommandDataLength);
};

#endif
