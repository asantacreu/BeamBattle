//==============================================================================
// MusicBank Class
//==============================================================================
#ifndef _CMUSICBANK_H_
	#define _CMUSICBANK_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>

//==============================================================================
class CMusicBank {
	public:
		static CMusicBank           MusicControl;

		std::vector<Mix_Music*>     MusicList;

		int Volume;

	public:
		CMusicBank();

		int OnLoad(char* File);

		void OnCleanup();

	public:
		void Play(int ID);
};

//==============================================================================

#endif
