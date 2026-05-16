#include "WOCO.h"
#include "WOCO_AliveCheck.h"
#include "WOCO_DigitalPinState.h"
#include "WOCO_DigitalPinMode.h"

WOCO* m_WocoReadAliveCheck        = WOCO_AliveCheck     ::CreateReadRequest  ();
WOCO* m_WocoReadDigitalPinState   = WOCO_DigitalPinState::CreateReadRequest  (1);
WOCO* m_WocoWriteDigitalPinState  = WOCO_DigitalPinState::CreateWriteRequest (1, HIGH);
WOCO* m_WocoReadDigitalPinMode    = WOCO_DigitalPinMode ::CreateReadRequest  (1);
WOCO* m_WocoWriteDigitalPinMode   = WOCO_DigitalPinMode ::CreateWriteRequest (1, OUTPUT);

uint8_t m_CommandDataBuffer[40];

void setup ()
{
  uint8_t commandDataLength = 0;

  m_WocoReadAliveCheck        ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);
  m_WocoReadDigitalPinState   ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);
  m_WocoWriteDigitalPinState  ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);
  m_WocoReadDigitalPinMode    ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);
  m_WocoWriteDigitalPinMode   ->ComposeCommandData (m_CommandDataBuffer, sizeof (m_CommandDataBuffer), commandDataLength);
}

void loop ()
{
}
