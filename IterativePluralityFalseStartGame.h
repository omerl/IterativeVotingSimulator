//
//  IterativePluralityFalseStartGame.h
//  RangeEquilibria
//
//  Created by Omer Lev on 20/2/14.
//
//

#ifndef __RangeEquilibria__IterativePluralityFalseStartGame__
#define __RangeEquilibria__IterativePluralityFalseStartGame__

#include <iostream>
#include "IterativePluralityGame.h"

class IterativePluralityFalseStartGame: public IterativePluralityGame {
public:
    IterativePluralityFalseStartGame (int voterNum,IterativeVoter** gameVoters): IterativePluralityGame(voterNum,gameVoters) {}

    virtual void resetGame();
};


#endif /* defined(__RangeEquilibria__IterativePluralityFalseStartGame__) */
