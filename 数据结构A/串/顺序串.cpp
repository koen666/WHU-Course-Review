#include<iostream>
using namespace std;

const int MaxSize = 100; // 预定义最大长度

class SqString {
public:
    char data[MaxSize];  // 存放串中元素
    int length;          // 实际串长度

    SqString SubStr(int i, int j) {
        SqString s;
        s.length = 0; // 初始化新串长度为0
        
        // 参数有效性检查：起始序号i合法，长度j大于0，且不超出范围
        if (i < 0 || i >= length || j < 0 || i + j > length) {
            return s; // 参数错误时返回空串
        }
        
        // 将 data[i...i+j-1] 复制到新串s中
        for (int k = i; k < i + j; k++) {
            s.data[k - i] = data[k];
        }
        s.length = j; // 设置新串实际长度
        return s;
    }

    int Strcmp(SqString& s, SqString& t) {
        // 获取两个串中较短的长度作为比较范围
        int minl = (s.length < t.length) ? s.length : t.length;
        
        for (int i = 0; i < minl; i++) {
            if (s.data[i] > t.data[i]) return 1;
            else if (s.data[i] < t.data[i]) return -1;
        }
        
        // 若前minl个字符都相同，比较长度
        if (s.length == t.length) return 0;
        else if (s.length > t.length) return 1;
        else return -1;
    }
};  

