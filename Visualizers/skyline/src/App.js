import "./App.css";
import Skyline from "./components/skyline/Skyline";

function App() {
  const skylinePoints = [
    { x1: 1, x2: 3, y: 3 },
    { x1: 2, x2: 4, y: 4 },
    { x1: 5, x2: 8, y: 2 },
    { x1: 6, x2: 7, y: 4 },
    { x1: 8, x2: 9, y: 4 },
  ];
  return (
    <div className="App">
      <Skyline skylines={skylinePoints} />
    </div>
  );
}

export default App;
