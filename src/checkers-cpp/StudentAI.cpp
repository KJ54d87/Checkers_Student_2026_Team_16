#include "StudentAI.h"
#include <algorithm>
#include <cmath>
#include <random>
#include <stdexcept>
#include <utility>

//The following part should be completed by students.
//The students can modify anything except the class name and exisiting functions and varibles.
StudentAI::StudentAI(int col, int row, int p) : AI(col, row, p) {
    board = Board(col, row, p);
    board.initializeGame();
    player = 2;
}

Move StudentAI::GetMove(Move move) {
    if (move.seq.empty()) {
        player = 1;
    } else {
        board.makeMove(move, player == 1 ? 2 : 1);
    }
    vector<vector<Move>> moves = board.getAllPossibleMoves(player);
    int i = rand() % (moves.size());
    vector<Move> checker_moves = moves[i];
    int j = rand() % (checker_moves.size());
    Move res = checker_moves[j];
    board.makeMove(res, player);
    return res;
}

MCTree::MCTSNode::MCTSNode(const Board& position, const Move& incomingMove,
                           int playerToMove, MCTSNode* parentNode)
    : board(position), move(incomingMove), parent(parentNode), children(),
      unexpandedMoves(), result(0), movingPlayer(playerToMove), w_i(0.0),
      s_i(0) {
    if (movingPlayer != 1 && movingPlayer != 2) {
        throw invalid_argument("MCTSNode player must be 1 or 2");
    }

    // Catch ties and return sentinel
    if (board.tieCount >= board.tieMax) {
        result = -1;
        return;
    }

    const auto movesByChecker = board.getAllPossibleMoves(movingPlayer);
    for (const auto& checkerMoves : movesByChecker) {
        unexpandedMoves.insert(unexpandedMoves.end(), checkerMoves.begin(),
                               checkerMoves.end());
    }
    if (unexpandedMoves.empty()) {
        result = 3 - movingPlayer;
    }
}

MCTree::MCTSNode* MCTree::MCTSNode::expandOne() {
    if (isTerminal() || isFullyExpanded()) {
        return nullptr;
    }

    const Move nextMove = unexpandedMoves.back();
    Board nextBoard = board;
    nextBoard.makeMove(nextMove, movingPlayer);

    unique_ptr<MCTSNode> child(
        new MCTSNode(nextBoard, nextMove, 3 - movingPlayer, this));
    children.push_back(std::move(child));
    unexpandedMoves.pop_back();
    return children.back().get();
}

bool MCTree::MCTSNode::isTerminal() const { return result != 0; }

bool MCTree::MCTSNode::isFullyExpanded() const {
    return unexpandedMoves.empty();
}

int MCTree::MCTSNode::getResult() const { return result; }

int MCTree::MCTSNode::getMovingPlayer() const { return movingPlayer; }

double MCTree::MCTSNode::averageReward() const {
    return s_i == 0 ? 0.0 : w_i / s_i;
}

void MCTree::MCTSNode::recordReward(double reward) {
    if (!isfinite(reward) || reward < 0.0 || reward > 1.0) {
        throw invalid_argument("MCTS reward must be between 0 and 1");
    }
    w_i += reward;
    ++s_i;
}

const Board& MCTree::MCTSNode::getBoard() const { return board; }

const Move& MCTree::MCTSNode::getMove() const { return move; }

MCTree::MCTSNode* MCTree::MCTSNode::getParent() const { return parent; }

const vector<unique_ptr<MCTree::MCTSNode>>&
MCTree::MCTSNode::getChildren() const {
    return children;
}

size_t MCTree::MCTSNode::unexpandedMoveCount() const {
    return unexpandedMoves.size();
}

MCTree::MCTree(const Board& position, int aiPlayer, double explorationRate)
    : explorationRate(explorationRate), root(position, Move(), aiPlayer),
      player(aiPlayer) {}

MCTree::MCTSNode& MCTree::selectChild(MCTSNode& node, int s) {
    const auto& children = node.getChildren();
    if (children.empty()) {
        throw std::logic_error(
            "Cannot select a child from a childless node");
    }

    vector<std::pair<double, MCTSNode*>> scores;
    scores.reserve(children.size());

    for (const auto& child : children) {
        if (child->s_i == 0) {
            return *child;
        }

        const double score =
            child->averageReward() +
            explorationRate * std::sqrt(std::log1p(s) / child->s_i);
        scores.emplace_back(score, child.get());
    }

    const auto best =
        std::max_element(scores.begin(), scores.end(),
                         [](const std::pair<double, MCTSNode*>& a,
                            const std::pair<double, MCTSNode*>& b) {
                             return a.first < b.first;
                         });

    return *best->second;
}
