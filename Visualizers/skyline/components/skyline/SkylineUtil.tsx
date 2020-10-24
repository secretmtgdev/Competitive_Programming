import React from "react";
import { Point, SkylinePoint, SkylineQueuePoint } from "./Types";

export const solveSkyline = (skylines: SkylinePoint[]): Array<Point> => {
  let points: Array<Point> = new Array<Point>();
  let SkylineQueuePoints = convertToSkylineQueuePoints(skylines);
  let currMax
  let mockQueue: Array<number>
  return points;
};

// convert SkylinePoint array to SkylineQueuePoint array
const convertToSkylineQueuePoints = (
  points: SkylinePoint[]
): Array<SkylineQueuePoint> => {
  let skylineQueuePoints: Array<SkylineQueuePoint> = new Array<
    SkylineQueuePoint
  >();
  let point: SkylinePoint;
  for (point of points) {
    skylineQueuePoints.push({
      x: point.x1,
      y: point.y,
      type: "start",
    });
    skylineQueuePoints.push({
      x: point.x2,
      y: point.y,
      type: "end",
    });
  }
  return skylineQueuePoints;
};
