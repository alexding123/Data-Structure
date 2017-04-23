#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;

struct Processor {
  Processor(int index, long long available_time): 
    index(index), available_time(available_time)
  {}
  long long available_time;
  int index;
};
struct GreaterThanByTime {
  bool operator()(const Processor& lhs, const Processor& rhs) const {
    if (lhs.available_time == rhs.available_time) {
      return lhs.index > rhs.index;
    } else {
      return lhs.available_time > rhs.available_time;
    }
  }
};
class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());

    std::priority_queue<Processor, std::vector<Processor>, GreaterThanByTime> p; // processors
    for (int i = 0; i < num_workers_; i++) { 
      p.push(Processor(i, 0));
    }

    for (int i = 0; i < jobs_.size(); i++) {
      Processor c = p.top();
      p.pop();
      assigned_workers_[i] = c.index;
      start_times_[i] = c.available_time;
      p.push(Processor(c.index, c.available_time+jobs_[i]));
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
