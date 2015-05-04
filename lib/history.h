
#pragma once

#include <vector>

#include "move.h"
#include "string.h"


namespace Morat {

template<class Board>
class History {
	std::vector<MovePlayer> hist;
	Board board;

public:

	History() { }
	History(const Board & b) : board(b) { }

	const Move & operator [] (int i) const {
		return hist[i];
	}

	MovePlayer last() const {
		if(hist.size() == 0)
			return M_NONE;

		return hist.back();
	}

	const Board & operator * ()  const { return board; }
	const Board * operator -> () const { return & board; }

	std::vector<MovePlayer>::const_iterator begin() const { return hist.begin(); }
	std::vector<MovePlayer>::const_iterator end()   const { return hist.end(); }

	const Board get_board() const {
		Board b(board.get_size());
		for(auto m : hist)
			b.move(m);
		return b;
	}

	int len() const {
		return hist.size();
	}

	void clear() {
		hist.clear();
		board = get_board();
	}

	bool undo() {
		if(hist.size() <= 0)
			return false;

		hist.pop_back();
		board = get_board();
		return true;
	}

	void setturn(Side turn){
		board.setturn(turn);
	}

	bool move(const Move & m){
		return move(MovePlayer(m,board.toplay()));
	}

	bool move(const MovePlayer & m) {
		if(board.valid_move(m)){
			board.move(m);
			hist.push_back(m);
			return true;
		}
		return false;
	}
};

}; // namespace Morat
