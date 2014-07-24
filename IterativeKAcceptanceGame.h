//
//  IterativeKAcceptanceGame.h
//  RangeEquilibria
//
//  Created by Omer Lev on 30/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef RangeEquilibria_IterativeKAcceptanceGame_h
#define RangeEquilibria_IterativeKAcceptanceGame_h

#include "IterativeGame.h"

class IterativeKAcceptanceGame: public IterativeGame {
public:
    IterativeKAcceptanceGame (int voterNum, IterativeVoter** gameVoters,int newK): IterativeGame(voterNum, gameVoters), k(newK) {
        if (k>candidateNumber) {
            k=candidateNumber;
        }
        }
    virtual int breakTies(vector<int> winners) const;

    
protected:
    virtual int getWinnerFromVotes(vector<PrefList> prefs) const;
    int k;
};


#endif
