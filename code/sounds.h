#ifndef FSOUNDS_H
#define FSOUNDS_H

#include <shake.h>

int FED_SOUND_Intro;
int FED_SOUND_GunShot;

void
init_sounds()
{
    shakeInit(0.20);
    FED_SOUND_GunShot = shakeLoad("sounds/shot.wav");
}

void
cleanup_sounds()
{
    shakeTerminate();
}

void
play_sound(int soundId)
{
    shakePlay(soundId);
}

#endif // FSOUNDS_H
