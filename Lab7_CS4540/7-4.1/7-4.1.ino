#include <Adafruit_NeoPixel.h>

#define PIN 6            // NeoPixel data pin
#define NUMPIXELS 24     // Change to match your strip/ring count

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// -------------------------------
// GLOBAL ANIMATION VARIABLES
// -------------------------------
int waveOffset = 0;       // Moves the rainbow pattern
int sparkleTimer = 0;     // Controls sparkle frequency

// Breathing brightness
int breath = 0;
bool breathUp = true;

// Shooting star variables
bool starActive = false;
int starPos = 0;
int starSpeed = 2;        // pixels per frame
int starDirection = 1;    // 1 = left→right, -1 = right→left

// -------------------------------
// SHOOTING STAR FUNCTION
// -------------------------------
void drawShootingStar() {
  if (!starActive) return;

  // Draw tail (fade behind the star)
  for (int t = 0; t < 5; t++) {
    int tailPos = starPos - t * starDirection;

    if (tailPos >= 0 && tailPos < NUMPIXELS) {
      int fade = 255 - t * 50;  // fade each tail segment
      pixels.setPixelColor(tailPos, pixels.Color(fade, fade, fade));
    }
  }

  // Move star
  starPos += starSpeed * starDirection;

  // If star leaves the strip, deactivate
  if (starPos < 0 || starPos >= NUMPIXELS) {
    starActive = false;
  }
}

void setup() {
  pixels.begin();
  pixels.setBrightness(50);  // Start at medium brightness
}

void loop() {

  // -------------------------------
  // 1. BREATHING BRIGHTNESS EFFECT
  // -------------------------------
  if (breathUp) {
    breath++;
    if (breath >= 150) breathUp = false;
  } else {
    breath--;
    if (breath <= 30) breathUp = true;
  }
  pixels.setBrightness(breath);

  // -------------------------------
  // 2. RAINBOW WAVE ANIMATION
  // -------------------------------
  for (int i = 0; i < NUMPIXELS; i++) {
    int colorIndex = (i * 10 + waveOffset) & 255;
    pixels.setPixelColor(i, pixels.ColorHSV(colorIndex * 256));
  }

  waveOffset++;  // Move the rainbow forward

  // -------------------------------
  // 3. RANDOM SPARKLES
  // -------------------------------
  sparkleTimer++;
  if (sparkleTimer > 5) {   // Sparkle every few frames
    sparkleTimer = 0;

    int s = random(NUMPIXELS);
    pixels.setPixelColor(s, pixels.Color(255, 255, 255)); // White sparkle
  }

  // -------------------------------
  // 4. SHOOTING STAR TRIGGER
  // -------------------------------
  if (!starActive && random(0, 100) < 3) {  // ~3% chance per frame
    starActive = true;
    starDirection = random(0, 2) == 0 ? 1 : -1;
    starPos = (starDirection == 1) ? 0 : NUMPIXELS - 1;
  }

  // Draw the shooting star if active
  drawShootingStar();

  // -------------------------------
  // 5. SHOW EVERYTHING
  // -------------------------------
  pixels.show();
  delay(20);
}
