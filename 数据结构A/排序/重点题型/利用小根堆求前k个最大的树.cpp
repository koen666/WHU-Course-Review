#include <iostream>
#include <vector>

using namespace std;

// 交换两个数
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

/**
 * 堆调整函数 (Sift Down / Heapify)
 * 功能：维护小顶堆性质，将 break 规则的节点向下沉
 * @param arr 堆数组
 * @param n   堆的大小
 * @param i   当前要调整的节点下标
 */
void minHeapify(vector<int>& arr, int n, int i) {
    int smallest = i;       // 假设当前节点是最小的
    int left = 2 * i + 1;   // 左孩子下标
    int right = 2 * i + 2;  // 右孩子下标

    // 如果左孩子存在，且左孩子比当前最小的小
    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }

    // 如果右孩子存在，且右孩子比当前最小的小
    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }

    // 如果最小值不是当前节点，说明需要交换，继续向下调整
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        // 递归调整受影响的子树
        minHeapify(arr, n, smallest);
    }
}

int main() {
    // 1. 输入处理
    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> R(n);
    for (int i = 0; i < n; i++) {
        cin >> R[i];
    }

    // 2. 建立大小为 k 的小顶堆
    // 先把前 k 个元素放入一个临时容器（其实可以直接在原数组操作，但为了清晰我们用 heap 数组）
    vector<int> heap(k);
    for (int i = 0; i < k; i++) {
        heap[i] = R[i];
    }

    // 建堆：从最后一个非叶子节点开始，向上进行 Heapify
    // 最后一个非叶子节点下标是 (k/2 - 1)
    for (int i = k / 2 - 1; i >= 0; i--) {
        minHeapify(heap, k, i);
    }

    // 3. 遍历剩余元素 (从第 k 个到第 n-1 个)
    for (int i = k; i < n; i++) {
        // 如果当前元素比堆顶（堆中最小值）大
        if (R[i] > heap[0]) {
            heap[0] = R[i]; // 替换堆顶
            minHeapify(heap, k, 0); // 重新调整堆，让最小值浮上来
        }
    }

    // 4. 输出
    // 此时 heap 中存放的就是最大的 k 个数。
    // 题目要求“从小到大”输出。
    // 方法：小顶堆的根是最小的，我们可以每次取出根，打印，
    // 然后把堆的最后一个元素放到根的位置，堆大小减1，再调整。
    
    // 为了不破坏原 heap 用于调试（虽然这里不需要），我们直接在这个 heap 上操作输出
    // 实际上更简单的做法是：因为 k 很小，对 heap 数组做一次简单的排序也可以
    // 但为了纯粹展示堆的用法，我们用“堆排序”的逻辑输出：
    
    // 这里的逻辑稍微绕一点：
    // 我们想要从小到大输出。现在的 heap[0] 就是最小的。
    // 我们直接打印 heap[0]，然后 ExtractMin。
    
    vector<int> result; 
    int currentSize = k;
    
    for(int i = 0; i < k; i++) {
        result.push_back(heap[0]); // 把最小的存下来
        
        // 移除堆顶：把最后一个元素挪到堆顶，长度减1，向下调整
        heap[0] = heap[currentSize - 1];
        currentSize--;
        minHeapify(heap, currentSize, 0);
    }

    // 打印结果
    for (int i = 0; i < k; i++) {
        cout << result[i] << (i == k - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}