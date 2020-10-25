class SkylineQueue {
  size: number;
  queue: Array<number>;
  constructor(capacity: number) {
    this.size = 0;
    this.queue = new Array<number>(capacity);
    this.queue.fill(-1);
  }

  insert(x: number): void {
    this.queue[this.size++] = x;
    this.queue.sort((a, b) => b - a);
  }

  deleteValue(x: number): void {
    for (let i = 0; i < this.size; i++) {
      if (this.queue[i] === x) {
        this.queue[i] = -1;
        this.size--;
      }
    }
    this.queue.sort((a, b) => b - a);
  }

  findMax(): number {
    return this.queue[0];
  }
}

export default SkylineQueue;
