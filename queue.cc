#define MAX_QUEUE

template<class T>
struct Queue {
  T arr[MAX_QUEUE];
  int f, b;
  Queue() : f(0), b(0) {}
  void push(const T& val) { arr[b++] = val; }
  bool empty() { return f == b; }
  T& pop() { return arr[f++]; }
};
