//==============================================================================
#include "CMusicBank.h"

//==============================================================================
CMusicBank CMusicBank::MusicControl;

//==============================================================================
CMusicBank::CMusicBank() {
	Volume = 0;
}

//------------------------------------------------------------------------------
int CMusicBank::OnLoad(char* File) {
    Mix_Music* TempMusic = NULL;

    TempMusic = Mix_LoadMUS(File);
	 char* a = Mix_GetError();
    if((TempMusic) == NULL) {
        return -1;
    }

    MusicList.push_back(TempMusic);

    return (MusicList.size() - 1);
}

//------------------------------------------------------------------------------
void CMusicBank::OnCleanup() {
    for(unsigned int i = 0;i < MusicList.size();i++) {
        Mix_HaltMusic();

        Mix_FreeMusic(MusicList[i]);
    }

    MusicList.clear();
}

//==============================================================================
void CMusicBank::Play(int ID) {
    if(ID < 0 || ID >= MusicList.size()) return;
    if(MusicList[ID] == NULL) return;
	Mix_VolumeMusic(MusicControl.Volume);
    //Mix_PlayMusic(MusicList[ID], 0);
	Mix_PlayMusic(MusicList[ID], -1); // second parameter = -1 -> ininite music
	
}

//==============================================================================
