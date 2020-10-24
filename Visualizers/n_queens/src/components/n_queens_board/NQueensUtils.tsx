import React from "react";

interface Queen {
  row: number;
  col: number;
}

var DEFAULT_QUEEN: Queen = { row: -1, col: -1 };

export const solveQueens = (size: number) => {
  let queens: Array<Queen> = new Array<Queen>();
  queens.fill(DEFAULT_QUEEN);
  solveQueensUtil(0, size, queens);
  return drawQueens(size, queens);
};

const drawQueens = (size: number, queens: Array<Queen>) => {
  var tableCells = [];
  for (let i = 0; i < size * size; i++) {
    // check to see if i matches a queen
    let matchQueen: boolean = false;
    for (let j = 0; j < queens.length; j++) {
      let queen: Queen = queens[j];
      if (i === queen.row * size + queen.col) {
        matchQueen = true;
        break;
      }
    }
    if (matchQueen) {
      tableCells.push(<div className="grid-item">Q</div>);
    } else {
      tableCells.push(<div className="grid-item"></div>);
    }
  }
  return tableCells;
};

const solveQueensUtil = (
  row: number,
  size: number,
  queensPlace: Array<Queen>
): boolean => {
  if (row === size) {
    return true;
  }

  // while we are still solving the queens problem
  for (let col: number = 0; col < size; col++) {
    // check to see if the current position is under attack from the
    // first column up to the current column
    let safe: boolean = true;
    for (let queenIdx: number = 0; queenIdx < row; queenIdx++) {
      if (queenUnderAttack(queenIdx, queensPlace, row, col)) {
        safe = false;
        break;
      }
    }
    if (safe) {
      // choose
      queensPlace[row] = {
        row,
        col,
      };

      // explore
      if (solveQueensUtil(row + 1, size, queensPlace)) {
        return true;
      }

      // unchoose
      queensPlace[row] = DEFAULT_QUEEN;
    }
  }
  return false;
};

// Check to see if M[row, col] is under attack by a ith queen
const queenUnderAttack = (
  queenIdx: number,
  queens: Array<Queen>,
  row: number,
  col: number
) => {
  let queen = queens[queenIdx];
  let qRow = queen.row;
  let qCol = queen.col;
  // case Bottom left to top right diagonal: qRow + qCol == row + col
  // case Top left to bottom right diagonal: qRow - qCol == row - col
  // case same colum: qCol == col
  // no need for the row case since we are placing queens row by row
  return qRow + qCol === row + col || qRow - qCol === row - col || qCol === col;
};
