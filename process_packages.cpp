#include <iostream>
#include <queue>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time):
            arrival_time(arrival_time),
            process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
            dropped(dropped),
            start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
            size_(size),
            finish_time_()
    {}

    Response Process(const Request &request) {
        // Fallback in case of Empty Queue
        // to avoid not by me defined behavior
        int back = 0;
        int front = 0;
        if(!finish_time_.empty()) {
            front = finish_time_.front();
            back = finish_time_.back();
        }

        if(request.arrival_time >= front && !finish_time_.empty())
            finish_time_.pop();

        // Buffer is Full
        if(finish_time_.size() >= size_)
            return Response(true, -1);
        // Add to Buffer
        finish_time_.push(back + request.process_time);
        // Starts either at the end of last's Process
        // or at time of arrival (when bigger)
        return Response(false, std::max(back, request.arrival_time));
    }
private:
    int size_;
    std::queue <int> finish_time_;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
