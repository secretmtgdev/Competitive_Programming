import React from "react";
import { Point, SkylinePoint, SkylineQueuePoint, SkylineType } from "./Types";
// import SkylinePriorityQueue from "./SkylinePriorityQueue";
import SkylineQueue from "./SkylineQueue";

var DEFAULT_WIDTH = 25;

interface skylineProps {
  points: Array<Point>;
}

interface buildingProps {
  skylines: Array<SkylinePoint>;
}

export const WriteSkylinePoints: React.FC<skylineProps> = ({ points }) => {
  let renderedPoints = points.map((point, idx) => (
    <div key={idx}>
      x: {point.x}, y: {point.y}
    </div>
  ));
  return <>{renderedPoints}</>;
};

export const DrawSkyline: React.FC<skylineProps> = ({ points }) => {
  let renderedPoints = [];
  let prev_height = 0,
    curr_height = 0;
  let prev_x = 0,
    curr_x = 0;
  let xDrawPoint = 0;
  for (let i = 0; i < points.length; i++) {
    curr_height = points[i].y;
    curr_x = points[i].x;
    if (prev_height !== curr_height) {
      // denote the end of a block, 'draw'
      let width = DEFAULT_WIDTH * (curr_x - prev_x);
      let style = {
        height: `${DEFAULT_WIDTH * prev_height}px`,
        width: `${width}px`,
        left: xDrawPoint,
        bottom: 0,
        //backgroundColor: getRandomColor(),
      };
      xDrawPoint += width;

      renderedPoints.push(<div className="skyline-block" style={style}></div>);
    }
    prev_height = curr_height;
  }
  return <div className="skyline-container">{renderedPoints}</div>;
};

export const WriteBuildingPoints: React.FC<buildingProps> = ({ skylines }) => {
  let renderedPoints = skylines.map((point, idx) => (
    <div key={idx}>
      x1: {point.x1}, x2: {point.x2}, y: {point.y}
    </div>
  ));
  return <>{renderedPoints}</>;
};
export const DrawBuildings: React.FC<buildingProps> = ({ skylines }) => {
  let renderedPoints = [];
  let xDrawPoint = 0;
  for (let i = 0; i < skylines.length; i++) {
    let skyline = skylines[i];
    let width = DEFAULT_WIDTH * (skyline.x2 - skyline.x1);
    let style = {
      height: `${DEFAULT_WIDTH * skyline.y}px`,
      width: `${width}px`,
      left: xDrawPoint,
      bottom: 0,
      // backgroundColor: getRandomColor(),
    };
    xDrawPoint += width;

    renderedPoints.push(
      <div key={i} className="skyline-block" style={style}></div>
    );
  }
  return <div className="skyline-container">{renderedPoints}</div>;
};

export const getSkylinePoints = (
  skylines: Array<SkylinePoint>
): Array<Point> => {
  let points: Array<Point> = new Array<Point>();
  let skylineQueuePoints = convertToSkylineQueuePoints(skylines);
  skylineQueuePoints.sort(sortSkylinePoints);

  // let priorityQueue = new SkylinePriorityQueue(skylineQueuePoints.length);
  let priorityQueue = new SkylineQueue(skylineQueuePoints.length);
  priorityQueue.insert(0);

  let prev_max = 0;
  let curr_max: number;
  let skylineQueuePoint: SkylineQueuePoint;
  for (let i = 0; i < skylineQueuePoints.length; i++) {
    skylineQueuePoint = skylineQueuePoints[i];
    if (skylineQueuePoint.type === SkylineType.END) {
      priorityQueue.deleteValue(skylineQueuePoint.y);
    } else {
      priorityQueue.insert(skylineQueuePoint.y);
    }
    curr_max = priorityQueue.findMax();
    if (prev_max !== curr_max) {
      points.push({
        x: skylineQueuePoint.x,
        y:
          skylineQueuePoint.type === SkylineType.START
            ? skylineQueuePoint.y
            : curr_max,
      });
    }
    prev_max = curr_max;
  }
  return points;
};

// apply a customized sort on the skyline points
const sortSkylinePoints = (
  a: SkylineQueuePoint,
  b: SkylineQueuePoint
): number => {
  let sameType = a.type === b.type;
  let sameStart: boolean = sameType && b.type === SkylineType.START;
  let sameEnd: boolean = sameType && b.type === SkylineType.END;
  let sameX: boolean = a.x === b.x;
  // Edge case 1: Higher height should be looked at first
  // 1) Both have the same x value
  // 2) Both are starting values
  if (sameStart && sameX) {
    return b.y - a.y;
  }
  // Edge case 2: lower height should be looked at first
  // 1) Both have the same x values
  // 2) Both are ending values
  else if (sameEnd && sameX) {
    return a.y - b.y;
  }
  // Edge case 3: Start should show up prior to end
  // 1) Start and End point land on the same x
  else if (!sameType && sameX) {
    return -1;
  } else {
    // default sorting in the event that the other three edge cases
    // are not present
    return a.x - b.x;
  }
};

// convert SkylinePoint array to SkylineQueuePoint array
export const convertToSkylineQueuePoints = (
  points: Array<SkylinePoint>
): Array<SkylineQueuePoint> => {
  let skylineQueuePoints: Array<SkylineQueuePoint> = new Array<
    SkylineQueuePoint
  >();
  let point: SkylinePoint;
  for (let i = 0; i < points.length; i++) {
    point = points[i];
    skylineQueuePoints.push({
      x: point.x1,
      y: point.y,
      type: SkylineType.START,
    });
    skylineQueuePoints.push({
      x: point.x2,
      y: point.y,
      type: SkylineType.END,
    });
  }
  return skylineQueuePoints;
};

export const getPointsFromSkylineQueuePoints = (
  points: Array<SkylineQueuePoint>
) => {
  let convertedPoints = new Array<Point>(points.length);
  convertedPoints = points.map(({ x, y }) => ({ x, y }));
  return convertedPoints;
};

export const getRandomColor = (): string => {
  let red = Math.floor(Math.random() * 255);
  let green = Math.floor(Math.random() * 255);
  let blue = Math.floor(Math.random() * 255);
  return `rgb(${red}, ${green}, ${blue})`;
};
