//
//  IterativePluralityScheduledGame.h
//  RangeEquilibria
//
//  Created by Omer Lev on 9/2/14.
//
//

#ifndef __RangeEquilibria__IterativePluralityScheduledGame__
#define __RangeEquilibria__IterativePluralityScheduledGame__

#include <iostream>
#include "IterativeScheduledGame.h"

class IterativePluralityScheduledGame: public IterativeScheduledGame {
public:
    IterativePluralityScheduledGame (int voterNum, IterativeVoter** gameVoters): IterativeScheduledGame(voterNum,gameVoters) {}
    int* getScores();
    
    virtual int breakTies(vector<int> winners) const;

protected:
    virtual int getWinnerFromVotes(vector<PrefList> prefs) const;
};


#endif /* defined(__RangeEquilibria__IterativePluralityScheduledGame__) */
