//
//  IterativeBestResponseVoter.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 4/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IterativeBestResponseVoter.h"
#include "IterativeGame.h"

IterativeVoter* IterativeBestResponseVoter::copy() const{
    return new IterativeBestResponseVoter(*this);
}

bool IterativeBestResponseVoter::makeMove() {
    if (getGame()==NULL) {
        return false;
    }

    currentBestWinner=getGame()->getWinner();
    bestPrefs.clear();
    
    PrefList tempPref;
    makeEveryOptionMove(candidateNumber, tempPref);
    int minDistance=candidateNumber*candidateNumber;
    vector<PrefList> winners;
    winners.clear();
    if (bestPrefs.size()>1) {
        for (long i=bestPrefs.size()-1; i>=0; i--) {
            if (truePrefs.distanceFromPref(bestPrefs[i])<minDistance) {
                minDistance=truePrefs.distanceFromPref(bestPrefs[i]);
            }
        }
        for (long i=bestPrefs.size()-1; i>=0; i--) {
            if (truePrefs.distanceFromPref(bestPrefs[i])==minDistance) {
                winners.push_back(bestPrefs[i]);
            }
        }
    } else {
        winners.push_back(bestPrefs[0]);
    }
    
    if (getGame()->getWinner()!=currentBestWinner) {
        publicPrefs=winners[0];
        return true;
    }
    return false;
}

void IterativeBestResponseVoter::makeEveryOptionMove(int placesLeft, PrefList& tempPref) {
    if (placesLeft==0) {
        bool changingBest=false;
        int newWinner=getGame()->getWinnerSwitch(this,tempPref);
        
        if (newWinner==currentBestWinner) {
            bestPrefs.push_back(PrefList(tempPref));
            return;
        }
        
        for (int j=0; j<candidateNumber; j++) {
            if (truePrefs[j]==newWinner) {
                changingBest=true;
                break;
            }
            if (truePrefs[j]==currentBestWinner) {
                break;
            }
        }
        
        if (changingBest==true) {
            bestPrefs.clear();
            currentBestWinner=newWinner;
            bestPrefs.push_back(PrefList(tempPref));
        }
        return;
    }
    
    for (int i=0; i<candidateNumber; i++) {
        bool usedThisCandidate=false;
        for (int j=0; j<candidateNumber-placesLeft; j++) {
            if (tempPref[j]==i) {
                usedThisCandidate=true;
                break;
            }
        }
        if (usedThisCandidate==true) {
            continue;
        }
        tempPref[candidateNumber-placesLeft]=i;
        makeEveryOptionMove(placesLeft-1, tempPref);
    }
    
}