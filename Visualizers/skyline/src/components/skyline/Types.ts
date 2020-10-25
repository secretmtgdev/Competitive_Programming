export interface SkylinePoint {
  x1: number;
  x2: number;
  y: number;
}

export interface SkylineQueuePoint {
  x: number;
  y: number;
  type: SkylineType;
}

export enum SkylineType {
  START = "start",
  END = "end",
}

export interface Point {
  x: number;
  y: number;
}
