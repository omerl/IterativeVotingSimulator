//
//  distributions.h
//  RangeEquilibria
//
//  Created by Omer Lev on 6/2/14.
//
//

#ifndef __RangeEquilibria__distributions__
#define __RangeEquilibria__distributions__

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include "defs.h"
#include "PrefList.h"

using namespace std;

vector<PrefList> * buildPrefs(distributionTypes dist,int voters,int candidates, int urnNumber=0);
vector<PrefList> * buildUniformPrefs(int voters,int candidates);
vector<PrefList> * buildPeakedPrefs(int voters,int candidates);
vector<PrefList> * buildCurvedPrefs(int voters,int candidates);
vector<PrefList> * buildUrnPrefs(int voters,int candidates,int urnNumber);
vector<PrefList> * buildRifflePrefs(int voters,int candidates);
vector<PrefList> * buildLucePrefs(int voters,int candidates);

PrefList createRandomPrefList(int candidates);




#endif /* defined(__RangeEquilibria__distributions__) */
