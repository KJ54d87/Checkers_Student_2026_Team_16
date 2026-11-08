#ifndef STUDENTAI_H
#define STUDENTAI_H
#include "AI.h"
#include "Board.h"
#include <memory>
#include <random>
#include <vector>
#pragma once

//The following part should be completed by students.
//Students can modify anything except the class name and exisiting functions and varibles.
constexpr double DRAW_REWARD{0.5};
constexpr double KING_MULTIPLIER{3};
constexpr double WIN_REWARD{1.0};
constexpr double LOSS_REWARD{0.0};
constexpr int BLACK_PLAYER{1};
constexpr int WHITE_PLAYER{2};
constexpr int DRAW{-1};

class StudentAI : public AI {
  public:
    Board board;
    StudentAI(int col, int row, int p);
    virtual Move GetMove(Move board);
};

class MCTree {
    class MCTSNode {
        Board board;
        Move move;

        // Children don't own their parent, but own their own children
        MCTSNode* parent;
        vector<unique_ptr<MCTSNode>> children;

        vector<Move> unexpandedMoves;
        int result; // 0: ongoing, -1: draw, 1/2: winning player.

        int movingPlayer;

      public:
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

        bool isTerminal() const;
        bool isFullyExpanded() const;
        int getResult() const;
        int getMovingPlayer() const;
        double averageReward() const;
        void recordReward(double reward);

        const Board& getBoard() const;
        const Move& getMove() const;
        MCTSNode* getParent() const;
        const vector<unique_ptr<MCTSNode>>& getChildren() const;
        size_t unexpandedMoveCount() const;
    };

    double explorationRate;
    MCTSNode root;
    int player;
    std::mt19937 rng{std::random_device{}()};
    MCTSNode& selectChild(MCTSNode& node, int s);
    int rollout(const MCTSNode& node);
    static int oppositePlayer(int player);
    void backpropagate(MCTSNode& node, int result);

  public:
    MCTree(const Board& position, int aiPlayer, double explorationRate);
};

#endif //STUDENTAI_H
