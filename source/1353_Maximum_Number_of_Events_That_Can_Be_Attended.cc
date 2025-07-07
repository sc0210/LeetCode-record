/* 1353. Maximum Number of Events That Can Be Attended */
// class Solution {
// public:
//     struct greater_than_key{
//         inline bool operator() (const vector<int>& arr1, const vector<int>&
//         arr2)
//         {
//             return (arr1[0] < arr2[0]);
//         }
//     };

//     int maxEvents(vector<vector<int>>& events) {
//         int EVENT_NUM = events.size();
//         vector<bool> attend(10e5, false);

//         // sort the events by the starting data
//         std::sort(events.begin(), events.end(), greater_than_key());

//         // traverse from the first
//         int cnt1 = 0;
//         int cnt2 = 0;

//         for(int i=0 ;i<EVENT_NUM; i++){
//             int st1 = events[i][0];
//             int en1 = events[i][1];
//             int p1 = en1;
//             cout << "[" << st1 << "," << en1 << "]";

//             if(attend[st1]==false){
//                 // when selected is not occupied
//                 attend[st1] = true;
//                 cout << st1 << " ";
//                 cnt1++;
//             }else{
//                 // find the next day for avaliable, until reach the en
//                 while(p1>=st1){
//                     // found a empty space
//                     if(attend[p1]==false){
//                         attend[p1] = true;
//                         cnt1++;
//                         cout << p1 << " ";
//                         break;
//                     }
//                     // keep found, move to next day
//                     p1--;
//                 }
//                 cout << "p1:" << p1;
//             }
//             cout << "\n";
//         }

//         return cnt1;
//     }
// };

// class Solution {
// public:
//     static bool compareByEnd(const vector<int>& a, const vector<int>& b) {
//         return a[1] < b[1];  // sort by end time ascending
//     }

//     int maxEvents(vector<vector<int>>& events) {
//         std::sort(events.begin(), events.end(), compareByEnd);

//         int max_day = 0;
//         for (auto& e : events) {
//             max_day = std::max(max_day, e[1]);
//         }

//         vector<bool> attend(max_day + 1, false);
//         int count = 0;

//         for (auto& event : events) {
//             for (int d = event[0]; d <= event[1]; ++d) {
//                 if (!attend[d]) {
//                     attend[d] = true;
//                     count++;
//                     break;
//                 }
//             }
//         }

//         return count;
//     }
// };


class Solution
{
public:
    int maxEvents(vector<vector<int>> &events)
    {
        // 依照 start day 排序
        sort(events.begin(), events.end());

        // 用 min-heap 儲存可參加的活動（根據 end day）
        priority_queue<int, vector<int>, greater<int>> pq;

        int day = 1;
        int i = 0, n = events.size();
        int attended = 0;

        while (i < n || !pq.empty()) {
            // 若 heap 是空的，將 day 跳到下一個 event
            // 的開始日（避免中間空窗浪費）
            if (pq.empty()) {
                day = events[i][0];
            }

            // 將今天開始的活動加入 heap
            while (i < n && events[i][0] == day) {
                pq.push(events[i][1]);
                ++i;
            }

            // 移除已經過期的活動（end < 今天）
            while (!pq.empty() && pq.top() < day) {
                pq.pop();
            }

            // 參加一天活動（最早結束的）
            if (!pq.empty()) {
                pq.pop();
                attended++;
            }

            day++;  // 移到下一天
        }

        return attended;
    }
};
