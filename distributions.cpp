//
//  distributions.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 6/2/14.
//
//

#include "distributions.h"


PrefList createRandomPrefList(int candidates);
PrefList createPolyaPrefList(vector<PrefList> urns, int candidates);
PrefList createPeakedPrefList(vector<double> utils, int candidates);
PrefList createCurvedPrefList(vector<double> utils, int candidates);
PrefList createRiffedPrefList(int a[],int b[],int p, int candidates);
PrefList createLucePrefList(vector<double> ground,int candidates);
PrefList createCurvedPrefListAtPoint(vector<double> utils, int candidates,double point);

int getCondorcetWinnerFromVotes(vector<PrefList> prefs);


vector<PrefList> * buildPrefs(distributionTypes dist,int voters,int candidates, int urnNumber) {
    switch (dist) {
        case uniform:
            return buildUniformPrefs(voters, candidates);
            break;
        case peaked:
            return buildPeakedPrefs(voters, candidates);
            break;
        case curved:
            return buildCurvedPrefs(voters, candidates);
            break;
        case urn2:
            return buildUrnPrefs(voters, candidates, 2);
            break;
        case urn3:
            return buildUrnPrefs(voters, candidates, 3);
        case riffle:
            return buildRifflePrefs(voters, candidates);
            break;
        case luce:
            return buildLucePrefs(voters, candidates);
            break;
        default:
            break;
    }
    return NULL;
}

vector<PrefList> * buildUniformPrefs(int voters,int candidates) {
    vector<PrefList> * prefs=new vector<PrefList>();
    for (int i=0; i<voters; i++) {
        PrefList pref=createRandomPrefList(candidates);
        prefs->push_back(pref);
    }
    return prefs;
}

vector<PrefList> * buildPeakedPrefs(int voters,int candidates) {
    vector<PrefList> * prefs=new vector<PrefList>();
    vector<double> peakUtils;
    
    for (int i=0;i<candidates;i++) {
        peakUtils.push_back(((double)rand())/RAND_MAX);
    }
    
    double groundArrayBase [candidates];
    int groundArray [candidates];
    for (int i=0; i<candidates; i++) {
        groundArrayBase[i]=peakUtils[i];
    }
    
    for (int i=0; i<candidates; i++) {
        double max=-1;
        int maxIndex=-1;
        for (int j=0;j<candidates;j++) {
            if (max<groundArrayBase[j]) {
                max=groundArrayBase[j];
                maxIndex=j;
            }
        }
        groundArray[i]=maxIndex;
        groundArrayBase[maxIndex]=-2;
    }

        prefs->push_back(PrefList(candidates,groundArray));
    for (int i=1; i<voters; i++) {
        PrefList pref=createPeakedPrefList(peakUtils,candidates);
        prefs->push_back(pref);
    }

    return prefs;
}


vector<PrefList> * buildCurvedPrefs(int voters,int candidates) {
    vector<PrefList> * prefs=new vector<PrefList>();
    vector<double> peakUtils;
    for (int i=0;i<candidates;i++) {
        peakUtils.push_back(((double)rand())/RAND_MAX);
    }
    
    
    prefs->push_back(createCurvedPrefListAtPoint(peakUtils, candidates, 0.5));

    
    for (int i=1; i<voters; i++) {
        PrefList pref=createCurvedPrefList(peakUtils,candidates);
        prefs->push_back(pref);
    }
    return prefs;
}

vector<PrefList> * buildUrnPrefs(int voters,int candidates,int urnNumber) {
    vector<PrefList> * prefs=new vector<PrefList>();
    vector<PrefList> urns;
    for (int i=0;i<urnNumber;i++) {
        urns.push_back(createRandomPrefList(candidates));
    }
    for (int i=0; i<voters; i++) {
        PrefList pref=createPolyaPrefList(urns,candidates);
        prefs->push_back(pref);
    }
    return prefs;
}

vector<PrefList> * buildRifflePrefs(int voters,int candidates) {
    vector<PrefList> * prefs=new vector<PrefList>();
    int pSize=rand()%(candidates-2);
    pSize=pSize+1;
    int groupA [pSize];
    
    PrefList pl=createRandomPrefList(candidates);
    for (int i=0; i<pSize; i++) {
        groupA[i]=pl[i];
    }
    
        int groupB [candidates-pSize];
    
    for (int i=0; i<(candidates-pSize); i++) {
             groupB[i]=pl[i+pSize];
    }
    
    for (int i=0; i<voters; i++) {
        PrefList pref=createRiffedPrefList(groupA, groupB, pSize,candidates);
        prefs->push_back(pref);
    }
    return prefs;
    
}
vector<PrefList> * buildLucePrefs(int voters,int candidates) {
    vector<PrefList> * prefs=new vector<PrefList>();
    vector<double> groundVec;
    for (int i=0;i<candidates;i++) {
        groundVec.push_back(((double)rand())/RAND_MAX);
    }
    double groundArrayBase [candidates];
    int groundArray [candidates];
    for (int i=0; i<candidates; i++) {
        groundArrayBase[i]=groundVec[i];
    }
    
    for (int i=0; i<candidates; i++) {
        double max=-1;
        int maxIndex=-1;
        for (int j=0;j<candidates;j++) {
            if (max<groundArrayBase[j]) {
                max=groundArrayBase[j];
                maxIndex=j;
            }
        }
        groundArray[i]=maxIndex;
        groundArrayBase[maxIndex]=-2;
    }
    
    prefs->push_back(PrefList(candidates,groundArray));
    for (int i=1; i<voters; i++) {
        PrefList pref=createLucePrefList(groundVec,candidates);
        prefs->push_back(pref);
    }
    return prefs;
    
}


PrefList createRandomPrefList(int candidates) {
    int prefs[candidates];
    
    for (int i=0; i<candidates; i++) {
        prefs[i]=-1;
    }
    
    for (int i=0; i<candidates; i++) {
        bool foundUnused=false;
        while (foundUnused==false) {
            bool found=false;
            int cand=rand() % candidates;
            for (int j=0; (j<i) && (found==false); j++) {
                if (prefs[j]==cand) {
                    found=true;
                }
            }
            if (found==false) {
                prefs[i]=cand;
                foundUnused=true;
            }
        }
    }
    return PrefList(candidates,prefs);
}


PrefList createPolyaPrefList(vector<PrefList> urns, int candidates) {
    int prefs[candidates];
    
    for (int i=0; i<candidates; i++) {
        prefs[i]=-1;
    }
    
    int urn=rand()%(urns.size()+1);
    if (urn<urns.size()) {
        for (int i=0; i<candidates; i++) {
            prefs[i]=urns[urn][i];
        }
    }
    else {
        return createRandomPrefList(candidates);
    }
    return PrefList(candidates,prefs);
}


PrefList createPeakedPrefList(vector<double> utils, int candidates) {
    int prefs[candidates];
    double location=((double)rand())/RAND_MAX;
    double distance [candidates];
    
    for (int i=0; i<candidates; i++) {
        prefs[i]=-1;
        //distance[i]=fabs(utils[i]-location);
        if (location>utils[i]) {
            distance[i]=location-utils[i];
        } else {
            distance[i]=utils[i]-location;
        }
    }
    
    for (int i=0; i<candidates; i++) {
        double min=2;
        int minIndex=-1;
        for (int j=0;j<candidates;j++) {
            if (min>distance[j]) {
                min=distance[j];
                minIndex=j;
            }
        }
        prefs[i]=minIndex;
        distance[minIndex]=2;
    }
    
    return PrefList(candidates,prefs);
}

PrefList createCurvedPrefList(vector<double> utils, int candidates) {
    int prefs[candidates];
    double location=((double)rand())/RAND_MAX;
    double distance [candidates];
    
    for (int i=0; i<candidates; i++) {
        prefs[i]=-1;
        if (location>utils[i]) {
            distance[i]=location-utils[i];
        } else {
            distance[i]=utils[i]-location;
        }
    }
    
    for (int i=0; i<candidates; i++) {
        double max=-1;
        int maxIndex=-1;
        for (int j=0;j<candidates;j++) {
            if (max<distance[j]) {
                max=distance[j];
                maxIndex=j;
            }
        }
        prefs[i]=maxIndex;
        distance[maxIndex]=-2;
    }
    
    return PrefList(candidates,prefs);
}

PrefList createCurvedPrefListAtPoint(vector<double> utils, int candidates,double point) {
    int prefs[candidates];
    double location=point;
    double distance [candidates];
    
    for (int i=0; i<candidates; i++) {
        prefs[i]=-1;
        if (location>utils[i]) {
            distance[i]=location-utils[i];
        } else {
            distance[i]=utils[i]-location;
        }
    }
    
    for (int i=0; i<candidates; i++) {
        double max=-1;
        int maxIndex=-1;
        for (int j=0;j<candidates;j++) {
            if (max<distance[j]) {
                max=distance[j];
                maxIndex=j;
            }
        }
        prefs[i]=maxIndex;
        distance[maxIndex]=-2;
    }
    
    return PrefList(candidates,prefs);
}


PrefList createRiffedPrefList(int a[],int b[],int p, int candidates) {
    int prefs[candidates];
    
    for (int i=0; i<candidates; i++) {
        prefs[i]=-1;
    }
    PrefList pl=createRandomPrefList(candidates);
    vector<int> y;
    for (int i=0; i<candidates; i++) {
        y.push_back(pl[i]);
    }
    
    std::sort(y.begin(),y.begin()+p);
    std::sort(y.begin()+p,y.end());
    
    for (int i=0; i<candidates; i++) {
        int firstPermutation=-1;
        for (int j=0; j<p; j++) {
            if (a[j]==i) {
                if (j==(p-1)) {
                    firstPermutation=a[0];
                }
                else {
                    firstPermutation=a[j+1];
                }
                break;
            }
        }
        if (firstPermutation==-1) {
            for (int j=0; j<(candidates-p); j++) {
                if (b[j]==i) {
                    if (j==((candidates-p)-1)) {
                        firstPermutation=b[0];
                    }
                    else {
                        firstPermutation=b[j+1];
                    }
                    break;
                }
            }
        }
        if (firstPermutation==-1) {
            cout<<"ERROR IN RIFFED MODEL CREATION";
        }
        vector<int>::iterator it=find(y.begin(), y.end(), firstPermutation);
        ++it;
        if (it==y.end()) {
            prefs[i]=y[0];
        } else {
            prefs[i]=*it;
        }
    }
    
    return PrefList(candidates,prefs);
}

PrefList createLucePrefList(vector<double> ground,int candidates) {
    double vals[candidates];
    int prefs[candidates];
    
    for (int i=0; i<candidates; i++) {
        double location=((double)rand())/RAND_MAX;
        location=log(location)*-1;
        location=log(location)*-1;
        location+=ground[i];
        if (location>1) {
            location=1;
        }
        if (location<0) {
            location=0;
        }
        vals[i]=location;
    }
    
    for (int i=0; i<candidates; i++) {
        prefs[i]=-1;
    }
    
    for (int i=0; i<candidates; i++) {
        double max=-1;
        int maxIndex=-1;
        for (int j=0;j<candidates;j++) {
            if (max<vals[j]) {
                max=vals[j];
                maxIndex=j;
            }
        }
        prefs[i]=maxIndex;
        vals[maxIndex]=-2;
    }
    
    return PrefList(candidates,prefs);
    
}

