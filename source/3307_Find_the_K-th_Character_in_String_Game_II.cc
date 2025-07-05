/* 3307. Find the K-th Character in String Game II */
#include <vector>

char kthCharacter(long long k, std::vector<int> &operations)
{
    //    Brute force (TLE)
    //    int operations_cnt = operations.size();

    //    std::vector<char> mem(static_cast<int>(pow(2,operations_cnt)), '0');
    //    mem[0] = 'a'; //store the initial value

    //    int head,start,upperlimit;
    //    for(int i=0; i<operations_cnt; i++){
    //     if(operations[i]==0){
    //         // i=1, expand mem size to 2^1
    //         // i=2, expand mem size to 2^2
    //         head = 0;
    //         start = pow(2,i);
    //         upperlimit = static_cast<int>(pow(2,i+1));
    //         for(int k=start; k<upperlimit; k++){
    //             mem[k] = mem[head++];
    //         }
    //     }else if(operations[i]==1){
    //         head = 0;
    //         start = pow(2,i);
    //         upperlimit = static_cast<int>(pow(2,i+1));
    //         for(int k=start; k<upperlimit; k++){
    //             mem[k] = mem[head++]+1;
    //         }
    //     }
    //    }
    //    for(char val : mem){
    //     cout << val << " ";
    //    }
    //    return mem[k-1];


    /* Divide by half*/
    char ans = 'a';
    // handel edge case, k==1
    if (k == 1)
        return ans;

    long long half = 1, i = 0;
    int op1 = 0, op2 = 0;
    std::vector<int> steps;

    // when k is larger than 2, k =3,4,5,6, divide in half each time
    while (k > 2) {
        half = 1;  // reset the val of half
        for (i = 1; i <= k; i++) {
            if ((pow(2, i) < k) && (k <= pow(2, i + 1))) {
                half = pow(2, i);
                break;
            }
        }

        k = k % half;  // divide by half
        if (k == 0)
            k = half;  // modify the edge value

        if (operations[i] == 0) {
            steps.push_back(0);
        } else if (operations[i] == 1) {
            steps.push_back(1);
        }
    }

    // handle edge case k==2
    if (k == 2 && operations[0]) {
        steps.push_back(operations[0]);
    }

    reverse(steps.begin(), steps.end());
    for (int val : steps) {
        if (val == 1) {
            // when the addition of character is exceed the range (a~z)
            if (ans + 1 > 'z') {
                ans = 'a';
            } else {
                ans++;
            }
        }
        cout << ans << " ";
    }

    return ans;
}