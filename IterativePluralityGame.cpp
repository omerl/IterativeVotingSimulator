//
//  IterativePluralityGame.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 25/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IterativePluralityGame.h"

int IterativePluralityGame::getWinnerFromVotes(vector<PrefList> prefs) const {
    int scores[candidateNumber];
    for (int i=0; i<candidateNumber; i++) {
        scores[i]=0;
    }
    for (long i=0; i<prefs.size(); i++) {
        if (prefs[i].isAbstained()) {
            continue;
        }
            scores[(prefs[i])[0]]+=1;
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

int* IterativePluralityGame::getScores() {
    int* scores=new int[candidateNumber];
    for (int i=0; i<candidateNumber; i++) {
        scores[i]=0;
    }
    printVotes(votes);
    for (long i=0; i<votes.size(); i++) {
        scores[(votes[i])[0]]+=1;
    }
    return scores;
}

int IterativePluralityGame::breakTies(vector<int> winners) const {
    std::sort(winners.begin(),winners.end());
    return winners[0];
}

void IterativePluralityGame::improvedScore() {
    improveScoreMoves+=1;
}

string IterativePluralityGame::printGame(resultFormat* rs) {
    string s=IterativeGame::printGame(rs);
    if (improveScoreMoves>0) {
    int numOfStates=0;
    for (int i=0; i<winners.size(); i++) {
        numOfStates+=winners[i];
    }
    rs->improvedScore=improveScoreMoves/numOfStates;
    }
    return s;
}

void IterativePluralityGame::gameEnd() {
    IterativeGame::gameEnd();
    
}
