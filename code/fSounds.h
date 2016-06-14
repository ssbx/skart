#ifndef FSOUNDS_H
#define FSOUNDS_H

#include <shake.h>

int FED_SOUND_Intro;
int FED_SOUND_GunShot;

void FSounds_Init() {
    shakeInit(0.05);
    FED_SOUND_GunShot = shakeLoad("shot.wav");
}

void FSounds_Cleanup() {
    shakeTerminate();
}

void FSounds_Play(int soundId) {
    shakePlay(soundId);
}

#endif // FSOUNDS_H
