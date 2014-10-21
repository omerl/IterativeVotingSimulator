//
//  main.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 26/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <sys/stat.h>
#include "defs.h"
#include "distributions.h"
#include "IterativeBordaGame.h"
#include "IterativeLazyBestVoter.h"
#include "IterativeBestResponseVoter.h"
#include "IterativePluralityGame.h"
#include "IterativePluralityFalseStartGame.h"
#include "IterativeKAcceptanceGame.h"
#include "IterativePluralityRangeVoter.h"
#include "IterativePluralityRangeMultVoter.h"
#include "IterativePluralityScheduledGame.h"

#include "TestScenario.h"
#include "VoteFileHandle.h"

using namespace std;

string saveDirectoy;
string dadOutput="./";

void runFamily(int voterNumber, int candidateNumber, int gameNumber);
void runDistribution(distributionTypes disType,string s, vector<vector<PrefList> > prefs,int voterNumber, ofstream *output);

void readVoters (IterativeVoter ** voters);

int main (int argc, const char * argv[])
{
    std::cout << "Hello, World!\n";
    srand ((unsigned int)time(NULL));
    
    for (int i=1; i<argc; i++) {
        struct stat buffer;
        if (stat (argv[i], &buffer) == 0) {
            if (i==1) {
                if (S_ISDIR(buffer.st_mode)) {
                    saveDirectoy=argv[i];
                    continue;
                } else {
                    saveDirectoy="/Users/omer/Desktop/Runs/";
                }
            }
            ostringstream fileName(ostringstream::out);
            fileName<<argv[i]<<"for";
            ofstream dataFile;
            dataFile.open (fileName.str().c_str());
            
            VoteFileHandle vfh=VoteFileHandle(argv[i]);
            string s=vfh.runIt(saveDirectoy);
            dataFile<<s;
            cout<<s;
            dataFile.close();
        }
        else {
            saveDirectoy="/Users/omer/Desktop/Runs/";
        }
    }
    
    
    if (argc<=1) {
        saveDirectoy="/Users/omer/Desktop/Runs/";
    }
    /*
     for (int i=3; i<9; i++) {
     runFamily(10,i,200);
     runFamily(20,i,200);
     runFamily(50,i,200);
     }
     */
    cout << "Goodbye, World!\n";
    return 0;
}

void runFamily(int voterNumber,int candidateNumber, int gameNumber) {
    ostringstream fileName(ostringstream::out);
    fileName<<dadOutput<<voterNumber<<candidateNumber;
    ofstream dataFile;
    dataFile.open (fileName.str().c_str());
    
    map<distributionTypes,vector<vector<PrefList> > > m;
    for (distributionTypes i=distFirst; i<=distLast; i++) {
        for (int j=0; j<gameNumber; j++) {
            m[i].push_back(*buildPrefs(i, voterNumber, candidateNumber));
        }
    }
    for (distributionTypes i=distFirst; i<=distLast; i++) {
        runDistribution(i,printDistributionType(i),m[i],voterNumber,&dataFile);
    }
    
    dataFile.close();
}

void runDistribution(distributionTypes disType,string s,vector<vector<PrefList> > prefs,int voterNumber,ofstream *output) {
    TestScenario ts= TestScenario(100, 1000, regular);
    ts.setFilePath(saveDirectoy);
    ts.setDistributionType(disType);
    ts.setTruePrefs(prefs, additive, basic);
    vector<pair<double, double> > Rs;
    for (int i=0; (i<16) && (i<voterNumber); i++) {
        // Rs.push_back(make_pair(((double)i)/((double) voterNumber), 1));
    }
    
    Rs.push_back(make_pair(1, 1));
    
    ts.setRK(Rs);
    ts.setFalseStart(true);
    
    string answer=ts.go();
    
    cout<<answer;
    (*output)<<answer;
    
}

void readVoters(IterativeVoter ** voters) {
    std::ifstream myReadFile;
    myReadFile.open("voters.txt");
    char output[100];
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            
            
            myReadFile >> output;
            cout<<output;
        }
    }
}