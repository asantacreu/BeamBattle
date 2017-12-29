#include "sdl.h"


class CControl{

	public:

		static CControl Keys;

		CControl();



		bool                PressUp;
        bool                PressDown;
        bool                PressLeft;
        bool			    PressRight;
		bool				PressW;
        bool				PressS;
		bool				PressB;
        bool				PressA;
        bool				PressD;
        bool			    PressSpace;
       // bool			    PressPause;
        bool			    PressEsc;
        bool			    SpaceDown;
		bool				PressMouseL;
		bool				PressMouseR;
		bool				ShowStart1P;
		bool				ShowStart2P;
		bool				ShowPAgain;
		bool				ShowOptions;
		bool				ShowLArrowP1;
		bool				ShowRArrowP1;
		bool				ShowLArrowP2;
		bool				ShowRArrowP2;
		bool				ShowLArrowVolume;
		bool				ShowRArrowVolume;
		bool				ShowBack;
		bool				ShowQuit;
};
