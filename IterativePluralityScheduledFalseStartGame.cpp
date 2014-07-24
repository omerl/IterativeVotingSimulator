//
//  IterativePluralityScheduledFalseStartGame.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 23/2/14.
//
//

#include "IterativePluralityScheduledFalseStartGame.h"

void IterativePluralityScheduledFalseStartGame::resetGame () {
    IterativePluralityScheduledGame::resetGame();
    
    votes.clear();
    history.clear();
    votes.clear();
    for (int i=0;i<voterNumber;i++) {
        PrefList pub=createRandomPrefList(candidateNumber);
        voters[i]->resetVoter();
        voters[i]->setPublicVoter(&pub);
        const PrefList *pf=voters[i]->getVote();
        votes.push_back(*pf);
    }
    history.push_back(votes);
    
    
}