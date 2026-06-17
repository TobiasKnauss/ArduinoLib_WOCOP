#include <MemoryTools.h>
#include "WOCO.h"
#include "WOCO_AliveCheck.h"
#include "WOCO_DigitalIOState.h"
#include "WOCO_DigitalIOMode.h"
#include "WOCO_DeviceName.h"
#include "WOCO_DeviceType.h"

using namespace MemoryTools;

WOCO* m_pWocoReadDigitalIOState   = WOCO_DigitalIOState ::CreateReadRequest  (1);
WOCO* m_pWocoWriteDigitalIOState  = WOCO_DigitalIOState ::CreateWriteRequest (1, HIGH);
WOCO* m_pWocoReadDigitalIOMode    = WOCO_DigitalIOMode  ::CreateReadRequest  (1);
WOCO* m_pWocoWriteDigitalIOMode   = WOCO_DigitalIOMode  ::CreateWriteRequest (1, OUTPUT);
WOCO* m_pWocoReadDeviceName       = WOCO_DeviceName     ::CreateReadRequest  ();
WOCO* m_pWocoReadDeviceType       = WOCO_DeviceType     ::CreateReadRequest  ();

ByteBuffer* m_pCommandDataBuffer;

void setup ()
{
  WOCO* pWocoReadAliveCheck = nullptr;
  ::EResult result = WOCO::Create (WOCO::ECommand::AliveCheck, WOCO::TYPE_Request, WOCO::ACTION_Read, pWocoReadAliveCheck);

  uint16_t commandDataLength = 0;
  pWocoReadAliveCheck         ->ComposeCommandData (m_pCommandDataBuffer, commandDataLength);
  m_pWocoReadDigitalIOState   ->ComposeCommandData (m_pCommandDataBuffer, commandDataLength);
  m_pWocoWriteDigitalIOState  ->ComposeCommandData (m_pCommandDataBuffer, commandDataLength);
  m_pWocoReadDigitalIOMode    ->ComposeCommandData (m_pCommandDataBuffer, commandDataLength);
  m_pWocoWriteDigitalIOMode   ->ComposeCommandData (m_pCommandDataBuffer, commandDataLength);
  m_pWocoReadDeviceName       ->ComposeCommandData (m_pCommandDataBuffer, commandDataLength);
  m_pWocoReadDeviceType       ->ComposeCommandData (m_pCommandDataBuffer, commandDataLength);

  delete (pWocoReadAliveCheck);
  delete (m_pWocoReadDigitalIOState);
  delete (m_pWocoWriteDigitalIOState);
  DeleteObject (m_pWocoReadDigitalIOMode);
  DeleteObject (m_pWocoWriteDigitalIOMode);
}

void loop ()
{
}
