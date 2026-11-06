#ifndef STUDENTAI_H
#define STUDENTAI_H
#include "AI.h"
#include "Board.h"
#include <memory>
#include <vector>
#pragma once

//The following part should be completed by students.
//Students can modify anything except the class name and exisiting functions and varibles.
class StudentAI : public AI {
  public:
    Board board;
    StudentAI(int col, int row, int p);
    virtual Move GetMove(Move board);
};

class MCTree {
  public:
    class MCTSNode {
        Board board;
        Move move;

        // Children don't own their parent, but own their own children
        MCTSNode* parent;
        vector<unique_ptr<MCTSNode>> children;

        vector<Move> unexpandedMoves;
        int result; // 0: ongoing, -1: draw, 1/2: winning player.

      public:
        int moving_player;
        double w_i;
        unsigned int s_i;

        MCTSNode(const Board& position, const Move& incomingMove,
                 int playerToMove, MCTSNode* parentNode = nullptr);

        // Remove copy & move to prevent dangling pointers
        MCTSNode(const MCTSNode&) = delete;
        MCTSNode& operator=(const MCTSNode&) = delete;
        MCTSNode(MCTSNode&&) = delete;
        MCTSNode& operator=(MCTSNode&&) = delete;

        MCTSNode* expandOne();

        void generateChildren();

        bool isTerminal() const;
        bool isFullyExpanded() const;
        int getResult() const;
        double averageReward() const;
        void recordReward(double reward);

        const Board& getBoard() const;
        const Move& getMove() const;
        MCTSNode* getParent() const;
        const vector<unique_ptr<MCTSNode>>& getChildren() const;
        size_t unexpandedMoveCount() const;
    };

    int player;
    MCTSNode root;

    MCTree(const Board& position, int aiPlayer);
};

#endif //STUDENTAI_H
