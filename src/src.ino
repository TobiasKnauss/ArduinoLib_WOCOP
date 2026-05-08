#include "WOCO.h"
#include "WOCO_AliveCheck.h"
#include "WOCO_DigitalPinState.h"
#include "WOCO_DigitalPinMode.h"

WOCO* m_WocoReadAliveCheck        = WOCO_AliveCheck     ::CreateReadRequest  ();
WOCO* m_WocoReadDigitalPinState   = WOCO_DigitalPinState::CreateReadRequest  (1);
WOCO* m_WocoWriteDigitalPinState  = WOCO_DigitalPinState::CreateWriteRequest (1, HIGH);
WOCO* m_WocoReadDigitalPinMode    = WOCO_DigitalPinMode ::CreateReadRequest  (1);
WOCO* m_WocoWriteDigitalPinMode   = WOCO_DigitalPinMode ::CreateWriteRequest (1, OUTPUT);

uint8_t m_PayloadBuffer[40];

void setup ()
{
  uint8_t payloadLength = 0;

  m_WocoReadAliveCheck        ->ComposePayload (m_PayloadBuffer, sizeof (m_PayloadBuffer), payloadLength);
  m_WocoReadDigitalPinState   ->ComposePayload (m_PayloadBuffer, sizeof (m_PayloadBuffer), payloadLength);
  m_WocoWriteDigitalPinState  ->ComposePayload (m_PayloadBuffer, sizeof (m_PayloadBuffer), payloadLength);
  m_WocoReadDigitalPinMode    ->ComposePayload (m_PayloadBuffer, sizeof (m_PayloadBuffer), payloadLength);
  m_WocoWriteDigitalPinMode   ->ComposePayload (m_PayloadBuffer, sizeof (m_PayloadBuffer), payloadLength);
}

void loop ()
{
}
