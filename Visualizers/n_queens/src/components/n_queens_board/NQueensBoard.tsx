import React from "react";
import "./NQueensBoard.css";
import { solveQueens } from "./NQueensUtils";

interface props {
  size: number;
}

const NQueensBoard: React.FC<props> = ({ size }) => {
  var containerStyle = {
    display: "grid",
    gridTemplateColumns: `repeat(${size}, 1fr)`,
  };
  return <div style={containerStyle}>{solveQueens(size)}</div>;
};

export default NQueensBoard;
