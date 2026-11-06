#include "Board.h"
#include "StudentAI.h"
#include <gtest/gtest.h>

TEST(MCTSNodeTest, BasicConstruction) {
     Board basic_board = Board(5, 5, 2);     
     Move empty_move = Move();
     MCTree::MCTSNode node = MCTree::MCTSNode(basic_board, empty_move, BLACK_PLAYER);
     
     EXPECT_EQ(basic_board.row, node.getBoard().row);
}
