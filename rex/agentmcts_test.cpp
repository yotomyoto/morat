
#include "../lib/catch.hpp"

#include "agentmcts.h"
#include "gtp.h"


using namespace Morat;
using namespace Rex;

void test_playout(AgentMCTS &agent, Outcome outcome){
	while(agent.rootboard.won()==Outcome::UNKNOWN){
		agent.search(10, 0, 0);
		Move move = agent.return_move(0);
		agent.move(move);
	}
	REQUIRE(agent.rootboard.won() == outcome);
}

void setup_game(AgentMCTS &agent, std::string size, std::vector<std::string> moves){
	Board b(4);
	agent.set_board(b, true);
	for(auto m : moves) {
		agent.move(Move(m));
	}
}

TEST_CASE("Rex::AgentMCTS::Node::to_s/from_s", "[rex][agentmcts]") {
	AgentMCTS::Node n(Move("a1"));
	auto s = n.to_s();
	AgentMCTS::Node k;
	REQUIRE(k.from_s(s));
	REQUIRE(n.to_s() == k.to_s());
}

TEST_CASE("Rex::AgentMCTS 3x3", "[rex][agentmcts]"){
	SECTION("Unspecified Opening"){
		AgentMCTS agent;
		setup_game(agent, "3", {});//4x4 board with no specified opening
		test_playout(agent, Outcome::P2);//should be player1 win
	}
}

TEST_CASE("Rex::AgentMCTS 4x4", "[rex][agentmcts]"){

	SECTION("Unspecified Opening"){
		AgentMCTS agent;
		setup_game(agent, "4", {});//4x4 board with no specified opening
		test_playout(agent, Outcome::P1);//should be player1 win
	}

	SECTION("Obtuse Corner Open"){
		AgentMCTS agent;
		setup_game(agent, "4", {"a4"});//4x4 board with obtuse corner opening move
		test_playout(agent, Outcome::P1);//should be player1 win
	}

	SECTION("Acute Corner Open"){
		AgentMCTS agent;
		setup_game(agent, "4", {"a1"});//4x4 board with acute corner opening move
		test_playout(agent, Outcome::P1);//should be player1 win
	}	
}


