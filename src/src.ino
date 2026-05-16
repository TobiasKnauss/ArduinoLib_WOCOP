#include <MemoryTools.h>
#include "WOCO.h"
#include "WOCO_AliveCheck.h"
#include "WOCO_DigitalPinState.h"
#include "WOCO_DigitalPinMode.h"

WOCO* m_pWocoReadDigitalPinState   = WOCO_DigitalPinState::CreateReadRequest  (1);
WOCO* m_pWocoWriteDigitalPinState  = WOCO_DigitalPinState::CreateWriteRequest (1, HIGH);
WOCO* m_pWocoReadDigitalPinMode    = WOCO_DigitalPinMode ::CreateReadRequest  (1);
WOCO* m_pWocoWriteDigitalPinMode   = WOCO_DigitalPinMode ::CreateWriteRequest (1, OUTPUT);

uint8_t m_CommandDataBuffer[40];

void setup ()
{
  WOCO* pWocoReadAliveCheck = nullptr;
  ::EResult result = WOCO::Create (WOCO::ECommand::AliveCheck, WOCO::TYPE_Request, WOCO::ACTION_Read, pWocoReadAliveCheck);

  uint8_t commandDataLength = 0;
  pWocoReadAliveCheck          ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);
  m_pWocoReadDigitalPinState   ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);
  m_pWocoWriteDigitalPinState  ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);
  m_pWocoReadDigitalPinMode    ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);
  m_pWocoWriteDigitalPinMode   ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);

  delete (pWocoReadAliveCheck);
  delete (m_pWocoReadDigitalPinState);
  delete (m_pWocoWriteDigitalPinState);
  DeleteObject (m_pWocoReadDigitalPinMode);
  DeleteObject (m_pWocoWriteDigitalPinMode);
}

void loop ()
{
}
