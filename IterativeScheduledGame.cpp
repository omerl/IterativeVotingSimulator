//
//  IterativeScheduledGame.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 9/2/14.
//
//

#include "IterativeScheduledGame.h"

int IterativeScheduledGame::getWinner() const {
    return getWinnerFromVotes(votes);
}

int IterativeScheduledGame::getWinnerSwitch(IterativeVoter * player, PrefList list) const {
    int playerNum=-1;
    for (int i=0; (playerNum<0) && (i<voterNumber); i++) {
        if (voters[i]==player) {
            playerNum=i;
        }
    }
    
    vector<PrefList> vec=votes;
    vec[playerNum]=list;
    int winner=getWinnerFromVotes(vec);
    return winner;
}


bool IterativeScheduledGame::playStage() {
    bool played[voterNumber];
    
    int chosen=0;
    bool someoneDid=false;
    
    for (int i=0; i<voterNumber; i++) {
        if (voters[i]->isAbstained()==true) {
            played[i]=true;
            chosen++;
        } else {
            played[i]=false;
        }
    }
    
    int playingPlayers=rand()%(((voterNumber-chosen)/2)-1);
    playingPlayers+=1;
    vector<int>whoPlayed;
    
    for (int i=0; i<playingPlayers; i++) {
    while (chosen<voterNumber) {
        int playerLocation=rand() % (voterNumber-chosen);
        int player=playerLocation;
        for (int i=0; (i<voterNumber) && (playerLocation>=0); i++) {
            if (played[i]==false) {
                playerLocation--;
            } else {
                player++;
            }
        }
        chosen++;
        if ((voters[player]->makeMove())==true) {
            someoneDid=true;
            played[player]=true;
            whoPlayed.push_back(player);
            break;
        } else {
            played[player]=true;
        }
    }
    }
    
    for (vector<int>::iterator iter=whoPlayed.begin();iter!=whoPlayed.end();++iter) {
    
        votes[*iter]=*(voters[*iter]->getVote());
    }
        history.push_back(votes);
        return someoneDid;
}

