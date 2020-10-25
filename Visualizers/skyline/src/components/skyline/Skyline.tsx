import React from "react";
import { SkylinePoint, Point, SkylineQueuePoint } from "./Types";
import {
  getSkylinePoints,
  WriteSkylinePoints,
  DrawSkyline,
  convertToSkylineQueuePoints,
  getPointsFromSkylineQueuePoints,
  DrawBuildings,
  WriteBuildingPoints,
} from "./SkylineUtil";
import "./Skyline.css";

interface props {
  skylines: Array<SkylinePoint>;
}

const Skyline: React.FC<props> = ({ skylines }) => {
  console.log("SKYLINES");
  console.log(skylines);
  let newPoints = getSkylinePoints(skylines);
  return (
    <div>
      {/* <WriteSkylinePoints points={newPoints} /> */}
      {/* <DrawSkyline points={newPoints} /> */}
      <WriteBuildingPoints skylines={skylines} />
      <DrawBuildings skylines={skylines} />
    </div>
  );
};

export default Skyline;
