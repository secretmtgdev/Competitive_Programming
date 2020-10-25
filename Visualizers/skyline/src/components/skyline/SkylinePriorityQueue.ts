import { SkylineQueuePoint } from "./Types";

/** TODO:
 * Investigate the cause of the insertion failure. This class cannot be used
 * until the cause of failure is resolved.
 */

class SkylinePriorityQueue {
  heap: Array<number>;
  currentSize: number;

  // we are going to always know the size of the queue
  // as we will pass in a structure with the defined max
  // length. This allows us to avoid having to resize the
  // array. We will not build the heap by default, that is
  // up to the user to do so when the time is right.
  constructor(initSize: number) {
    this.currentSize = 0;

    // the skyline algorithm will input a default value of
    // 0 to start the solution
    this.heap = new Array<number>(initSize + 1);

    // set the default values to -1.
    this.heap.fill(-1);
  }

  // Each parent should have a larger value than its children
  // h[i] >= h[2i] && h[i] >= h[2i+1] && h[floor(i/2)] >= h[i]

  insert(x: number): void {
    // create a new bubble
    this.currentSize++;
    let bubble: number = this.currentSize;

    // set the initial hole to the value x
    // percolate upward
    for (
      this.heap[this.currentSize] = x;
      bubble > 0 && x > this.heap[Math.floor(bubble / 2)];

    ) {
      let newBubble = Math.floor(bubble / 2);
      this.heap[bubble] = this.heap[newBubble];
      bubble = newBubble;
    }
    this.heap[bubble] = x;
  }

  findMax(): number {
    return this.heap[0];
  }

  deleteMax(): void {
    if (this.isEmpty()) {
      throw new Error("Can't delete from an empty heap");
    }

    let bubble: number = 1;
    this.startPercolateDown(bubble);
  }

  deleteValue(x: number): void {
    if (this.isEmpty()) {
      throw new Error("Can't delete from an empty heap");
    }

    let index = this.find(x);
    console.log(`Index of value to delete: ${index}`);
    if (index >= 0) {
      this.startPercolateDown(index + 1);
    }
  }

  find(x: number): number {
    for (let index = 0; index < this.currentSize; index++) {
      if (this.heap[index] === x) return index;
    }
    return -1;
  }

  isEmpty(): boolean {
    return this.currentSize === 0;
  }

  toString(): string {
    let str: string = `[${this.heap[0]}`;
    for (let i = 1; i < this.currentSize; i++) {
      str += `, ${this.heap[i]}`;
    }
    return str + "]";
  }

  //////////////////////
  // Helper functions //
  //////////////////////
  private startPercolateDown(bubble: number): void {
    this.heap[bubble] = this.heap[this.currentSize--];
    this.percolateDown(bubble);
  }

  private percolateDown(bubble: number): void {
    let child: number;
    let tmp = this.heap[bubble];

    // ensure that we are percloating downward
    // set the bubble to the appropriate child when available
    for (; bubble * 2 <= this.currentSize; bubble = child) {
      child = bubble * 2;

      // ensure that we are still in the boundaries &
      // select the appropriate child to set the next bubble
      if (
        child != this.currentSize &&
        this.heap[child] < this.heap[child + 1]
      ) {
        child++;
      }

      // update the bubble value if we are still looking
      if (this.heap[child] > tmp) {
        this.heap[bubble] = this.heap[child];
      } else {
        break;
      }
    }
    // Set the bottom value with the value that
    // has been percolated downward
    this.heap[bubble] = tmp;
  }

  ///////////////////////
  // Traversal helpers //
  ///////////////////////
  // For a given heap-node i, left-child: 2i, right-child: 2i + 1, parent floor(i/2)
  private getLeftChildIndex(i: number): number {
    return 2 * i;
  }

  private getRightChildIndex(i: number): number {
    return 2 * i + 1;
  }

  private getParentIndex(i: number): number {
    return Math.floor(i / 2);
  }
}

export default SkylinePriorityQueue;
