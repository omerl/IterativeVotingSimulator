//
//  IterativeScheduledGame.h
//  RangeEquilibria
//
//  Created by Omer Lev on 9/2/14.
//
//

#ifndef __RangeEquilibria__IterativeScheduledGame__
#define __RangeEquilibria__IterativeScheduledGame__

#include <iostream>
#include "IterativeGame.h"

class IterativeScheduledGame: public IterativeGame {
public:
    IterativeScheduledGame (int voterNum,IterativeVoter** gameVoters): IterativeGame(voterNum,gameVoters) {}
    virtual int getWinner() const;
    virtual int getWinnerSwitch(IterativeVoter * player, PrefList list) const;
    virtual bool playStage();

private:
    bool stepStart;
    
};

#endif /* defined(__RangeEquilibria__IterativeScheduledGame__) */
