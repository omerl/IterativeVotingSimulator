//
//  IterativePluralityFalseStartGame.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 20/2/14.
//
//

#include "IterativePluralityFalseStartGame.h"

void IterativePluralityFalseStartGame::resetGame () {
    IterativePluralityGame::resetGame();
    
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