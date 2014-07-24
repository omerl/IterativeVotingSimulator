//
//  IterativeLazyBestVoter.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 31/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IterativeLazyBestVoter.h"
#include "IterativeGame.h"

IterativeVoter* IterativeLazyBestVoter::copy() const {
    return new IterativeLazyBestVoter(*this);
}


bool IterativeLazyBestVoter::makeMove() {
    if (getGame()==NULL) {
        return false;
    }
    
    bool hasChanged=false;
    int currentWinner=getGame()->getWinner();
    //const int * realPrefs=truePrefs.getVote();
    //const int * currentVote=publicPrefs.getVote();
    
    int currentBestChange=currentWinner;
    
    for (int i=0; i<candidateNumber; i++) {
        if (truePrefs[i]==currentWinner) {
            break;
        }
        
        if (i==0) {
            continue;
        }
        
        PrefList voteAttempt;
        voteAttempt[0]=truePrefs[i];
        int pushingForNewVote=1;
        for (int j=0; j<candidateNumber; j++) {
            if (publicPrefs[j]==truePrefs[i]) {
                pushingForNewVote=0;
                continue;
            }
            voteAttempt[j+pushingForNewVote]=publicPrefs[j];  
        }
        
        int newWinner=getGame()->getWinnerSwitch(this,voteAttempt);
        
        for (int j=0; j<candidateNumber; j++) {
            if (truePrefs[j]==currentBestChange) {
                break;
            }
            if (truePrefs[j]==newWinner) {
                currentBestChange=newWinner;
            }
        }
    }
    
    if (currentBestChange!=currentWinner) {
        PrefList voteAttempt;
        //int voteAttempt[candidateNumber];
        voteAttempt[0]=currentBestChange;
        int pushingForNewVote=1;
        for (int j=0; j<candidateNumber; j++) {
            if (publicPrefs[j]==currentBestChange) {
                pushingForNewVote=0;
                continue;
            }
            voteAttempt[j+pushingForNewVote]=publicPrefs[j];  
        }
        publicPrefs=voteAttempt;
        hasChanged=true;
    }
    
    return hasChanged;
}