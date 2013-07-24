/**
 * @author: Huxley
 **/

#ifndef DEFINES_H
#define DEFINES_H

const int kMaxSize = 10;
const int kBoardSize = 8;

// Using in ai_mobility.cc
const int kTotal = kBoardSize * kBoardSize;
const int kOpening = 8;
const int kEnd = 40;

// Using in ai_player.cc
const int kInf = 1e6;
const int kDepth = 5;

// Using in board_layout.cc
const int kScoreColumn = kMaxSize + 2;
const int kScoreLine = kBoardSize - 1;
const int kShowItemColumn = kMaxSize + 2;
const int kStartButtonLine = 1;
const int kBlackCountTextLine = 2;
const int kBlackCountLcdLine = 3;
const int kWhiteCountTextLine = 4;
const int kWhiteCountLcdLine = 5;

// Using in othello_board.cc
const int kDiag1 = 0x80;
const int kDiag2 = 0x20;
const int kDiag3 = 0x8;
const int kDiag4 = 0x2;
const int kLine1 = 0x40;
const int kLine2 = 0x10;
const int kLine3 = 0x4;
const int kLine4 = 0x1;

enum CellType {WHITE, BLACK, EMPTY};

#endif // DEFINES_H
