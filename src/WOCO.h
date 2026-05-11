#ifndef WOCO_h
#define WOCO_h

#include <Result.h>
#include <MemoryTools.h>

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
    WorkerType      = 0x0001,
    WorkerName      = 0x0002,
    AliveCheck      = 0x0100,
    DigitalPinMode  = 0x0101,
    DigitalPinState = 0x0102,
  };

//==================== Fields ====================
private:
  static const char* const c_EnumNames_ClassFailures[] PROGMEM;

  #define X(name) static const char _EResult_##name[] PROGMEM;
  #include "WOCO_failures.h"
  #undef X

  bool m_ActionIsWrite      = false;
  bool m_MessageTypeIsReply = false;

//==================== Constructors ====================
protected:
  WOCO (bool i_MessageTypeIsReply,
        bool i_ActionIsWrite);

public:
  static ::EResult Create (ECommand i_CommandId,
                           bool     i_MessageTypeIsReply,
                           bool     i_ActionIsWrite,
                           WOCO*&   o_WOCO);

//==================== Public Methods ====================
public:
  static const __FlashStringHelper* GetResultText (::EResult i_Result);

  bool GetActionIsRead ();
  bool GetActionIsWrite ();
  bool GetMessageTypeIsRequest ();
  bool GetMessageTypeIsReply ();

  virtual ECommand GetCommand () = 0;
  uint8_t          GetPayloadLengthExpected ();
  virtual bool     GetPayloadLengthIsVariable ();

  virtual uint8_t GetPayloadLength_ReadRequest () = 0;
  virtual uint8_t GetPayloadLength_ReadReply () = 0;
  virtual uint8_t GetPayloadLength_WriteRequest ();
  virtual uint8_t GetPayloadLength_WriteReply ();

  virtual ::EResult AnalyzePayload (uint8_t* i_pPayloadBuffer,
                                    uint8_t  i_PayloadBufferLength,
                                    uint8_t  i_PayloadLength);
  virtual ::EResult ComposePayload (uint8_t* i_pPayloadBuffer,
                                    uint8_t  i_PayloadBufferLength,
                                    uint8_t& o_PayloadLength);
};

#endif
