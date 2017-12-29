//==============================================================================
// SoundBank Class
//==============================================================================
#ifndef _CSOUNDBANK_H_
	#define _CSOUNDBANK_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
//#include "CApp.h"

//==============================================================================
class CSoundBank {
	public:
		static CSoundBank           SoundControl;

		std::vector<Mix_Chunk*>     SoundList;

		int Volume;

	public:
		CSoundBank();

		int OnLoad(char* File);

		void OnCleanup();

	public:
		void Play(int ID);
};

//==============================================================================

#endif
