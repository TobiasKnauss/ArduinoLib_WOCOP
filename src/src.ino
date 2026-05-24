#include <MemoryTools.h>
#include "WOCO.h"
#include "WOCO_AliveCheck.h"
#include "WOCO_DigitalIOState.h"
#include "WOCO_DigitalIOMode.h"
#include "WOCO_WorkerName.h"
#include "WOCO_WorkerType.h"

WOCO* m_pWocoReadDigitalIOState   = WOCO_DigitalIOState ::CreateReadRequest  (1);
WOCO* m_pWocoWriteDigitalIOState  = WOCO_DigitalIOState ::CreateWriteRequest (1, HIGH);
WOCO* m_pWocoReadDigitalIOMode    = WOCO_DigitalIOMode  ::CreateReadRequest  (1);
WOCO* m_pWocoWriteDigitalIOMode   = WOCO_DigitalIOMode  ::CreateWriteRequest (1, OUTPUT);
WOCO* m_pWocoReadWorkerName       = WOCO_WorkerName     ::CreateReadRequest  ();
WOCO* m_pWocoReadWorkerType       = WOCO_WorkerType     ::CreateReadRequest  ();

uint8_t m_CommandDataBuffer[40];

void setup ()
{
  WOCO* pWocoReadAliveCheck = nullptr;
  ::EResult result = WOCO::Create (WOCO::ECommand::AliveCheck, WOCO::TYPE_Request, WOCO::ACTION_Read, pWocoReadAliveCheck);

  uint16_t commandDataLength = 0;
  pWocoReadAliveCheck         ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);
  m_pWocoReadDigitalIOState   ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);
  m_pWocoWriteDigitalIOState  ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);
  m_pWocoReadDigitalIOMode    ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);
  m_pWocoWriteDigitalIOMode   ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);
  m_pWocoReadWorkerName       ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);
  m_pWocoReadWorkerType       ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);

  delete (pWocoReadAliveCheck);
  delete (m_pWocoReadDigitalIOState);
  delete (m_pWocoWriteDigitalIOState);
  DeleteObject (m_pWocoReadDigitalIOMode);
  DeleteObject (m_pWocoWriteDigitalIOMode);
}

void loop ()
{
}
