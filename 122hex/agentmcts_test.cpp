
#include "../lib/catch.hpp"

#include "agentmcts.h"
#include "gtp.h"


using namespace Morat;
using namespace Hex122;

/*void test_playout(AgentMCTS &agent, Outcome outcome, bool fullboard){
	while(!agent.done()){
		agent.search(10, 0, 0);
	}
	while(agent.rootboard.won()==Outcome::UNKNOWN){
		agent.search(10, 0, 0);
		Move move = agent.return_move(0);
		agent.move(move);
	}
	REQUIRE(agent.rootboard.won() == outcome);
	if(fullboard){//check that board is full in the cases where loser should be able to force it
		REQUIRE(agent.rootboard.num_moves() == agent.rootboard.numcells());
	}
	logerr("Completed a test game.\n");
}*/

bool playout_outcome(AgentMCTS &agent, Outcome player){
	while(!agent.done()){
		agent.search(10, 0, 0);
	}
	while(agent.rootboard.won()==Outcome::UNKNOWN){
		agent.search(10, 0, 0);
		Move move = agent.return_move(0);
		agent.move(move);
	}
	logerr("Completed a test game.\n");
	return agent.rootboard.won() == player;
}

void setup_game(AgentMCTS &agent, int size, std::vector<std::string> moves){
	Board b(size);
	agent.set_board(b, true);
	agent.longestloss = true;//loser tries to draw out game
	for(auto m : moves) {
		agent.move(Move(m));
	}
}

vecstr test_openings(int board_size){
	vecstr wins;
	AgentMCTS agent;
	for(int x=0; x<board_size; x++){
		for(int y=0; y<board_size; y++){
			Move move(x,y);
			setup_game(agent, board_size, {move.to_s()});
			if(playout_outcome(agent, Outcome::P1)){
				wins.push_back(move.to_s());
			}
		}
	}
	return wins;
}

TEST_CASE("Hex122::AgentMCTS::Node::to_s/from_s", "[Hex122][agentmcts]") {
	AgentMCTS::Node n(Move("a1"));
	auto s = n.to_s();
	AgentMCTS::Node k;
	REQUIRE(k.from_s(s));
	REQUIRE(n.to_s() == k.to_s());
}

TEST_CASE("Hex122::AgentMCTS 3x3", "[Hex122][agentmcts]"){
	vecstr wins = test_openings(3);
	vecstr expected = {"b2"};
	REQUIRE(wins == expected);
}

TEST_CASE("Hex122::AgentMCTS 4x4", "[Hex122][agentmcts]"){
	vecstr wins = test_openings(4);
	vecstr expected = {"b2","c3"};
	REQUIRE(wins == expected);
}


