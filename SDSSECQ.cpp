#include <chrono>

#include "Core/SDSSECQClient.h"

using namespace chrono;

int main() {
    SDSSECQClient client;

    cout << duration_cast<microseconds>(system_clock::now().time_since_epoch()).count() << endl;
    for (int i = 0; i < 1000; ++i) {
        client.update(INS, "alice", i);
        client.update(INS, "bob", i);
    }
    cout << duration_cast<microseconds>(system_clock::now().time_since_epoch()).count() << endl;
    for (int i = 0; i < 100; ++i) {
        client.update(DEL, "alice", i);
        client.update(DEL, "bob", i);
    }
    cout << duration_cast<microseconds>(system_clock::now().time_since_epoch()).count() << endl;
    vector<int> results = client.search(2, "alice", "bob");
//    for (int res : results) {
//        cout << res << endl;
//    }
    cout << duration_cast<microseconds>(system_clock::now().time_since_epoch()).count() << endl;
    return 0;
}
