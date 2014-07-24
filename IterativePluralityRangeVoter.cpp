//
//  IterativePluralityRangeVoter.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 17/12/13.
//
//

#include "IterativePluralityRangeVoter.h"

IterativeVoter* IterativePluralityRangeVoter::copy() const {
    return new IterativePluralityRangeVoter(*this);
}

void IterativePluralityRangeVoter::setR (int ra) {
    r=ra;
}

void IterativePluralityRangeVoter::setK (int ka) {
    k=ka;
}

void IterativePluralityRangeVoter::setR (double ra) {
    r=ra;
}

void IterativePluralityRangeVoter::setK (double ka) {
    k=ka;
}

void IterativePluralityRangeVoter::setRangeType(rangeTypes typeRa) {
    typeR=typeRa;
}

double IterativePluralityRangeVoter::getR() {
    return r;
}

double IterativePluralityRangeVoter::getK() {
    return k;
}


bool IterativePluralityRangeVoter::makeMove() {
    int winner=game->getWinner();
    if (winner==truePrefs[0]) {
        return false;
    }
    int* scores=((IterativePluralityGame *)game)->getScores();
    
    
    bool foundWinner=false;
    bool foundPublicVote=false;
    
    int realPublicRank=truePrefs.getRankForCandidate(publicPrefs[0]);
    
    if (scores[publicPrefs[0]]+r>=scores[winner]) {
        for (int i=realPublicRank+1; i<candidateNumber; i++) {
            if ((scores[winner]-scores[truePrefs[i]]+scores[winner]-scores[publicPrefs[0]])<r) {
                delete (scores);
                return false;
            }
            if ((scores[winner]-scores[truePrefs[i]]+scores[winner]-scores[publicPrefs[0]])>r) {
                break;
            }
            
            bool publicWinsTie=false;
            vector<int> ties;
            ties.push_back(truePrefs[i]);
            ties.push_back(publicPrefs[0]);
            ties.push_back(winner);
            int tieWinner=game->breakTies(ties);
            if (tieWinner==publicPrefs[0]) {
                publicWinsTie=true;
            }
            
            
            if (((scores[winner]-scores[truePrefs[i]]+scores[winner]-scores[publicPrefs[0]])==r) && (publicWinsTie==true)) {
                delete (scores);
                return false;
            }
        }
    }
    
    for (int i=0;(i<candidateNumber) && (foundWinner==false);i++) {
        
        if (truePrefs[i]==publicPrefs[0]) {
            foundPublicVote=true;
        }
        
        if (truePrefs[i]==winner) {
            foundWinner=true;
            continue;
        }
        int diff=scores[winner]-scores[truePrefs[i]];
        bool winnerWinsTie=false;
        if (diff==(r+1)) {
            vector<int> ties;
            ties.push_back(truePrefs[i]);
            ties.push_back(winner);
            int tieWinner=game->breakTies(ties);
            if (tieWinner==winner) {
                winnerWinsTie=false;
            }
        }
        
        if ((diff<(r+1)) || ((diff==(r+1)) && (winnerWinsTie==false))) {
            if (publicPrefs[0]==truePrefs[i]) {
                if ((diff<r) || ((diff==r) && (winnerWinsTie==false))) {
                    delete (scores);
                    return false;
                }
                else {
                    continue;
                }
            }
            for (int j=0; j<candidateNumber; j++) {
                if (publicPrefs[j]==truePrefs[i]) {
                    if (foundPublicVote==false) {
                        ((IterativePluralityGame*)game)->improvedScore();
                    }
                    publicPrefs[j]=publicPrefs[0];
                    publicPrefs[0]=truePrefs[i];
                    
                    break;
                }
            }
            delete (scores);
            return true;
        }
    }
    
    if (foundWinner==true) {
        int secondScore=-1;
        int secondScoreCand=-1;
        for (int i=0; i<candidateNumber; i++) {
            if (i==winner) {
                continue;
            }
            if (scores[i]>secondScore) {
                secondScore=scores[i];
                secondScoreCand=i;
            }
        }
        
        int diff=scores[winner]-secondScore;
        bool winTie=true;
        if (diff==r) {
            vector<int> ties;
            ties.push_back(secondScoreCand);
            ties.push_back(winner);
            int tieWinner=game->breakTies(ties);
            if (tieWinner==secondScoreCand) {
                winTie=false;
            }
        }
        if ((diff<r) || ((diff==r) && (winTie=false))) {
            if (publicPrefs[0]==winner) {
                delete (scores);
                return false;
            }
            for (int j=0; j<candidateNumber; j++) {
                if (publicPrefs[j]==winner) {
                    if (foundPublicVote==false) {
                        ((IterativePluralityGame*)game)->improvedScore();
                    }
                    publicPrefs[j]=publicPrefs[0];
                    publicPrefs[0]=winner;
                    break;
                }
            }
            delete (scores);
            return true;
        }
        
        if (typeR!=basic) {
            vector<int> ties;
            ties.push_back(publicPrefs[0]);
            ties.push_back(winner);
            int tieWinner=game->breakTies(ties);
            if ((scores[winner]-k<scores[publicPrefs[0]]) || ((scores[winner]-k==scores[publicPrefs[0]]) && (tieWinner==publicPrefs[0]))) {
                delete (scores);
                return false;
            }
        }
        
        if (typeR==truthful) {
            if (publicPrefs[0]==truePrefs[0]) {
                delete (scores);
                return false;
            }
            resetVoter();
            delete (scores);
            return true;
        }
        
        if (typeR==lazy) {
            abstainVoter();
            delete (scores);
            return true;
        }
        
    }
    
    
    delete(scores);
    return false;
}

