//
//  IterativeBordaGame.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 31/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IterativeBordaGame.h"

int IterativeBordaGame::getWinnerFromVotes(vector<PrefList> prefs) const {
    int scores[candidateNumber];
    for (int i=0; i<candidateNumber; i++) {
        scores[i]=0;
    }
    for (long i=0; i<prefs.size(); i++) {
        for (int j=0; j<candidateNumber; j++) {
            scores[(prefs[i])[j]]+=candidateNumber-j;
        }
    }
    int maxScore=-1;
    for (int i=0; i<candidateNumber; i++) {
        if (scores[i]>maxScore) {
            maxScore=scores[i];
        }
    }
    vector<int> winners;
    for (int i=0; i<candidateNumber; i++) {
        if (scores[i]==maxScore) {
            winners.push_back(i);
        }
    }
    
    if (winners.size()==1) {
        return winners[0];
    }
    
    return breakTies(winners);
}

int IterativeBordaGame::breakTies(vector<int> winners) const {
    int num=rand() % ((int)(winners.size()));
    return winners[num];
    //    return winners[0];
}
