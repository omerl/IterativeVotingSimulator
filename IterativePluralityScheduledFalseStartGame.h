//
//  IterativePluralityScheduledFalseStartGame.h
//  RangeEquilibria
//
//  Created by Omer Lev on 23/2/14.
//
//

#ifndef __RangeEquilibria__IterativePluralityScheduledFalseStartGame__
#define __RangeEquilibria__IterativePluralityScheduledFalseStartGame__

#include <iostream>
#include "IterativePluralityScheduledGame.h"

class IterativePluralityScheduledFalseStartGame: public IterativePluralityScheduledGame {
public:
    IterativePluralityScheduledFalseStartGame (int voterNum,IterativeVoter** gameVoters): IterativePluralityScheduledGame(voterNum,gameVoters) {}
    
    virtual void resetGame();
};
#endif /* defined(__RangeEquilibria__IterativePluralityScheduledFalseStartGame__) */
