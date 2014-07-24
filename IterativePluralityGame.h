//
//  IterativePluralityGame.h
//  RangeEquilibria
//
//  Created by Omer Lev on 25/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef RangeEquilibria_IterativePluralityGame_h
#define RangeEquilibria_IterativePluralityGame_h

#include "IterativeGame.h"

class IterativePluralityGame: public IterativeGame {
public:
    IterativePluralityGame (int voterNum,IterativeVoter** gameVoters): IterativeGame(voterNum,gameVoters) {}
    int* getScores();
    void improvedScore();
    virtual string printGame(resultFormat* rs);
    virtual void gameEnd();
    
protected:
    virtual int getWinnerFromVotes(vector<PrefList> prefs) const;
    virtual int breakTies(vector<int> winners) const;
    int improveScoreMoves=0;
};



#endif
