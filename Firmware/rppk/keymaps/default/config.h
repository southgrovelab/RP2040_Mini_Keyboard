// Copyright 2026 Niclas Söderlund
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Hur länge knapp 4 ska hållas innan Ctrl+Alt+Del skickas (ms)
#define TAPPING_TERM 500

// Hur nära i tid knapp 1 och 4 måste tryckas för att räknas som samtidigt (ms)
#define COMBO_TERM 50

// Kombinationen läses alltid från normalläget, oavsett aktivt lager
#define COMBO_ONLY_FROM_LAYER 0

// Lysdiod för pilläget
#define ARROW_LED_PIN GP18
