#include "Puzzle8Solver.h"

#include "Puzzle8StateManager.h"
#include "Puzzle8PQ.h"
#include <map>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

void WeightedAStar(std::string puzzle, double w, int & cost, int & expansions) {
	cost = 0;
	expansions = 0;

	// TODO

	//initializing important components
	Puzzle8StateManager sm;	// Initialize the state manager.
	Puzzle8State s(puzzle);
	sm.GenerateState(s);

	//make a map to keep track of the ids and their corresponding states
	map<int , Puzzle8State> states;
	states[sm.GetStateId(s)] = s;
	

	Puzzle8PQ pq; // Initialize the priority queue.
	double f = w * (double)s.calculateHeuristic() + cost;
	pq.push(PQElement(sm.GetStateId(s), f)); // Create a PQElement and add it to the queue.


	//keep track of the cost
	map<int, int> costTracker;
	costTracker[sm.GetStateId(s)] = 0;

	//maintain a closed list
	std::unordered_map<int, int> closedList;
	//start expanding
	bool found = false;
	while(!pq.empty() && !found){

		PQElement next = pq.top(); // The element with the minimum f-val.
		pq.pop();

		// check if the current state is equal to the goal state
		if(states[next.id].GetLinearizedForm() == "012345678"){
			found = true;
			cost = costTracker[next.id];
		}else{
			//check if the current node is in the closed list
			if(closedList.find(next.id) == closedList.end()){
				std::vector<Puzzle8State> temp = states[next.id].getSuccessors();

				for(int i = 0; i < temp.size(); i++){
		
					sm.GenerateState(temp[i]);
					//check if the children are in the closed list
					if(closedList.find(sm.GetStateId(temp[i])) == closedList.end()){
						//check if it's already in the open list. Add it if its cost is strictly less.
						if(states.find(sm.GetStateId(temp[i])) != states.end()){
							if(costTracker[next.id] + 1 < costTracker[sm.GetStateId(temp[i])]){
								costTracker[sm.GetStateId(temp[i])] = costTracker[next.id] + 1;
								double f =  (double)costTracker[sm.GetStateId(temp[i])] + w*(double)temp[i].calculateHeuristic();
								pq.push(PQElement(sm.GetStateId(temp[i]), f));
							}
						}else{
							costTracker[sm.GetStateId(temp[i])] = costTracker[next.id] + 1;
							double f =  (double)costTracker[sm.GetStateId(temp[i])] + w*(double)temp[i].calculateHeuristic();
							pq.push(PQElement(sm.GetStateId(temp[i]), f));

							states[sm.GetStateId(temp[i])] = temp[i];
						}
						
					}
				}
				expansions ++;
				closedList[next.id] = 1;
			}
		}
	}
}

