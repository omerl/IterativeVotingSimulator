//
//  IterativeKAcceptanceGame.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 30/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IterativeKAcceptanceGame.h"

int IterativeKAcceptanceGame::getWinnerFromVotes(vector<PrefList> prefs) const {
    int scores[candidateNumber];
    for (int i=0; i<candidateNumber; i++) {
        scores[i]=0;
    }
    for (long i=0; i<prefs.size(); i++) {
        for (int j=0; j<k; j++) {
            scores[(prefs[i])[j]]+=1;
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

int IterativeKAcceptanceGame::breakTies(vector<int> winners) const {
    std::sort(winners.begin(),winners.end());
    return winners[0];
}