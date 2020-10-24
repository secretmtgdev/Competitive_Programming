import NQueensBoard from "./components/n_queens_board/NQueensBoard";
import "./App.css";

function App() {
  const squares = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16];
  let size = squares[Math.floor(Math.random() * squares.length)];
  return (
    <div className="App">
      <NQueensBoard size={size} />
    </div>
  );
}

export default App;
