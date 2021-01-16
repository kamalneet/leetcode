// 1642. Furthest Building You Can Reach
// https://leetcode.com/problems/furthest-building-you-can-reach/

#include <set>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        multiset<int> ladderJumps;
        long long sumOfBrickJumps = 0;
        int i = 1;
	int numJumps = 0;
        for (; i < heights.size(); ++i) {
            const int jump = heights[i] - heights[i-1];
            if (jump <= 0) {
                continue;
            }
	    ++numJumps;
            if (ladderJumps.size() < ladders) {
                ladderJumps.emplace(jump);
                continue;
            }
            if (ladders > 0) {
                // There is contention for ladders. If the ladder is being currently used for a smaller jump,
                // replace that use with bricks, and use the freed ladder for the current jump.
                const int curMinLadderUse = *ladderJumps.begin();
                if (curMinLadderUse < jump) {
                    ladderJumps.erase(ladderJumps.begin());
                    ladderJumps.emplace(jump);
                    sumOfBrickJumps += curMinLadderUse;
                } else {
                    sumOfBrickJumps += jump;
                }
            } else {
                sumOfBrickJumps += jump;
            }
            if (sumOfBrickJumps > bricks) {
                break;
            }
        }
        return i-1;
    }
};

int main() {
	ifstream f("testcase");
	string hLine;
	getline(f, hLine);
	hLine=hLine.substr(1, hLine.size() - 2);
	std::stringstream ss(hLine);
	vector<int> h;
	for (int i; ss >> i;) {
		h.push_back(i);
		if (ss.peek() == ',') {
			ss.ignore();
		}
	}

	string bricksStr, laddersStr;
	getline(f, bricksStr);
	getline(f, laddersStr);
	int ladders = stoi(laddersStr);
	int bricks = stoi(bricksStr);
	Solution s;
	cout << "ans: " << s.furthestBuilding(h, bricks, ladders) << endl;
}
