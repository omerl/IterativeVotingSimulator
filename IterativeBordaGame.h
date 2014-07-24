//
//  IterativeBordaGame.h
//  RangeEquilibria
//
//  Created by Omer Lev on 31/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef RangeEquilibria_IterativeBordaGame_h
#define RangeEquilibria_IterativeBordaGame_h

#include "IterativeGame.h"

class IterativeBordaGame: public IterativeGame {
public:
    IterativeBordaGame (int voterNum,IterativeVoter** gameVoters): IterativeGame(voterNum, gameVoters) {}
    
protected:
    virtual int getWinnerFromVotes(vector<PrefList> prefs) const;
    virtual int breakTies(vector<int> winners) const;
};

#endif
