//
//  main.cpp
//  LearningCPP
//
//  Created by lioneldy on 2016/12/19.
//  Copyright © 2016年 lioneldy. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
         int val;
         ListNode *next;
         ListNode(int x) : val(x), next(NULL) {}
};

//2. Add Two Numbers
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode *sumList = new ListNode(0);
    ListNode *ans = sumList;
    int c = 0;
    while (l1 || l2 || c) {
        int sum = (l1 ? l1 -> val : 0) + (l2 ? l2 -> val : 0) + c;
        c = sum/10;
        sumList->next = new ListNode(sum % 10);
        sumList = sumList->next;
        if(l1) l1 = l1->next;
        if(l2) l2 = l2->next;
    }
    return ans -> next;
}

//3. Longest Substring Without Repeating Characters
int lengthOfLongestSubstring(string s) {
    int maxLenth = 0;
    vector<int> dictMap(256,-1);
    int m = -1;
    for (int i = 0; i < s.length(); i++) {
            m = max(dictMap[s[i]],m);
            dictMap[s[i]] = i;
            maxLenth = max(i - m, maxLenth);
    }
    return maxLenth;
}

//6. ZigZag Conversion
string convert(string s, int numRows) {
    if (numRows <= 1) return s;
    string ans = "";
    long lens = s.length();
    int k = 2 * numRows - 2;
    for (int i = 0; i < numRows; i++) {
        for (int j = i; j < lens; j += k) {
            ans = ans + s[j];
            int secondj = j + k - 2*i;
            if (i != 0 && i != numRows - 1 && secondj < lens)
                ans = ans + s[secondj];
        }
    }
    return ans;
}

//7. Reverse Integer
int reverseInt(int x) {
    long long ans = 0;
    for (; x; x /= 10) {
        ans = ans*10 + x%10;
    }
    if (ans > INT_MAX || ans < INT_MIN) {
        return 0;
    }
    return (int)ans;
}

//9. Palindrome Number
bool isPalindrome(int x) {
    if(x<0|| (x!=0 &&x%10==0)) return false;
    int sum=0;
    while(x>sum)
    {
        sum = sum*10+x%10;
        x = x/10;
    }
    return (x==sum)||(x==sum/10);
}

//10. Regular Expression Matching
bool isMatch(string s, string p) {
    if (p.empty()) return s.empty();
    if (p[1] == '*') {
        return isMatch(s, p.substr(2)) || (!s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p));
    }else
    return !s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));
}

//11. Container With Most Water
/*int maxArea(vector<int>& height) {
    long size = height.size();
    int maxArea = (height[0] < height[1]) ? height[0]:height[1];
    for (int i = 1; i < size; i ++) {
        for (int j = 0; j < i; j ++) {
            int area;
            if (height[i] < height[j])
                area = height[i] * (i - j);
            else area = height[j] * (i - j);
            if (area > maxArea)
                maxArea = area;
        }
    }
    return maxArea;
}*/
//超时
int maxArea(vector<int>& height) {
    int size = (int)height.size();
    int maxArea = (size - 1) * min(height[0], height[size - 1]);
    for (int i = 0, j = size - 1; j > i; ) {
        int area;
        if (height[i] < height[j])
            i++;
        else j--;
        area = min(height[i], height[j]) * (j - i);
        if (area > maxArea) {
            maxArea = area;
        }
    }
    return maxArea;
}

//12. Integer to Roman
string intToRoman(int num) {
    string geweiArray[10] = {"","I","II","III","IV","V","VI","VII","VIII","IX"};
    string shiweiArray[10] = {"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
    string baiweiArray[10] = {"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
    string qianweiArray[4] = {"","M","MM","MMM"};
    string roman = "";
    roman = qianweiArray[num / 1000] + baiweiArray[(num / 100) % 10] + shiweiArray[(num / 10) % 10] + geweiArray[num % 10];
    return roman;
}

//13. Roman to Integer
int romanToInt(string s) {
    int ans = 0;
    int size = (int)s.length();
    for (int i = size - 1; i >= 0; i--) {
        switch (s[i]) {
            case 'I':
                ans += ans >= 5 ? -1 : 1;
                break;
            case 'V':
                ans += 5;
                break;
            case 'X':
                ans += ans >= 50 ? -10 : 10;
                break;
            case 'L':
                ans += 50;
                break;
            case 'C':
                ans += ans >= 500 ? -100 : 100;
                break;
            case 'D':
                ans += 500;
                break;
            case 'M':
                ans += 1000;
                break;
            default:
                break;
        }
    }
    return ans;
}

//14. Longest Common Prefix
string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) return "";
    int maxPrefix = (int)strs[0].length();
    int size = (int)strs.size();
    for (int i = 1; i < size; i++) {
        int j = 0;
        int length = (int)strs[i].length();
        for (; j < maxPrefix && j < length; j++) {
            if (strs[0][j] != strs[i][j]) break;
        }
        if (j < maxPrefix) maxPrefix = j;
    }
    return strs[0].substr(0,maxPrefix);
}

//15. 3Sum
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());
    int size = (int)nums.size();
    for (int i = 0; i < size; i ++) {
        int begin = i + 1;
        int end = size - 1;
        while (begin < end){
            int sum = nums[i] + nums[begin] +nums[end];
            if (sum > 0) end--;
            else if (sum < 0) begin++;
            else {
                vector<int> tri(3,0);
                tri[0] = nums[i];
                tri[1] = nums[begin];
                tri[2] = nums[end];
                ans.push_back(tri);
                while (begin < end && nums[begin] == tri[1]) begin++;
                while (begin < end && nums[end] == tri[2]) end--;
            }
        }
        while (i + 1 < size && nums[i] == nums [i+1]) i++;
    }
    return ans;
}

//16. 3Sum Closest
int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int size = (int)nums.size();
    int closest = INT_MAX;
    int ans = closest;
    for (int i = 0; i < size; i ++) {
        int begin = i + 1;
        int end = size - 1;
        while (begin < end){
            int sum = nums[i] + nums[begin] +nums[end];
            if (sum > target) {
                if (sum - target < closest) {
                    closest = sum - target;
                    ans = sum;
                }
                end--;
            }
            else if (sum < target) {
                if (target - sum < closest) {
                    closest = target - sum;
                    ans = sum;
                }
                begin++;
            }
            else {
                return target;
            }
        }
        while (i + 1 < size && nums[i] == nums [i+1]) i++;
    }
    return ans;
}

//最大公约数
int gcd(int a, int b) {
    return (a%b==0) ? b : gcd(b,a%b);
}

//全排列算法
void Swap(char *a, char *b) {
    char t = *a;
    *a = *b;
    *b = t;
}
//在pszStr数组中，[nBegin,nEnd)中是否有数字与下标为nEnd的数字相等
bool IsSwap(char *pszStr, int nBegin, int nEnd) {
    for (int i = nBegin; i < nEnd; i++)
        if (pszStr[i] == pszStr[nEnd])
            return false;
    return true;
}
//k表示当前选取到第几个数,m表示共有多少数.
void AllRange(char *pszStr, int k, int m) {
    if (k == m) {
        static int s_i = 1;
        printf("  第%3d个排列\t%s\n", s_i++, pszStr);
    }
    else {
        for (int i = k; i <= m; i++) {//第i个数分别与它后面的数字交换就能得到新的排列
            if (IsSwap(pszStr, k, i)) {
                Swap(pszStr + k, pszStr + i);
                AllRange(pszStr, k + 1, m);
                Swap(pszStr + k, pszStr + i);
            }
        }
    }
}

//17. Letter Combinations of a Phone Number
vector<string> letterCombinations(string digits) {
    string nums[]={"0","1","abc","def","ghi","jkl","mno","pqrs","uvw","xyz"};
    vector<string> ans;
    long length = digits.length();
    for (int i = 0; i < length; i++) {
        if (!ans.size()) {
            ans.push_back("");
        }
        vector<string> temp;
        for (int j = 0; j < ans.size(); j++) {
            string str = nums[digits[i] - '0'];
            for (int k = 0; k < str.length(); k++) {
                temp.push_back(ans[j] + str[k]);
            }
        }
        ans = temp;
    }
    return ans;
}

//18. 4Sum
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> ans;
    int size = (int)nums.size();
    if (size < 3) {
        return ans;
    }
    sort(nums.begin(), nums.end());
    for (int i = 0; i < size; i++) {
        int target_3 = target - nums[i];
        for (int j = i + 1; j < size; j++) {
            int target_2 = target_3 - nums[j];
            int begin = j + 1;
            int end = size - 1;
            while (begin < end) {
                int twosum = nums[begin] + nums[end];
                if (twosum > target_2) {
                    end--;
                }
                else if (twosum < target_2) {
                    begin++;
                }else {
                    vector<int> temp(4,0);
                    temp[0] = nums[i];
                    temp[1] = nums[j];
                    temp[2] = nums[begin];
                    temp[3] = nums[end];
                    ans.push_back(temp);
                    while (begin < end && nums[begin] == temp[2]) {
                        begin++;
                    }
                    while (begin < end && nums[end] == temp[3] ) {
                        end--;
                    }
                }
            }
            while (j + 1 < size && nums[j] == nums [j+1]) j++;
        }
        while (i + 1 < size && nums[i] == nums [i+1]) i++;
    }
    return ans;
}

//19. Remove Nth Node From End of List
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode realHead(0);
    realHead.next = head;
    head = &realHead;
    ListNode *p = &realHead;
    while (n-- > 0) {
        p = p->next;
    }
    while (p->next != nullptr) {
        p = p->next;
        head = head->next;
    }
    head->next = head->next->next;
    return realHead.next;
}

//20. Valid Parentheses
bool isValid(string s) {
    string stack = "";
    int size = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            stack += s[i];
            size++;
        }
        if (s[i] == ')') {
            if (stack[size - 1] != '(') {
                return false;
            }
            size--;
            if (size < 0) {
                return false;
            }
            stack = stack.substr(0,size);
        }
        if (s[i] == ']') {
            if (stack[size - 1] != '[') {
                return false;
            }
            size--;
            if (size < 0) {
                return false;
            }
            stack = stack.substr(0,size);
        }
        if (s[i] == '}') {
            if (stack[size - 1] != '{') {
                return false;
            }
            size--;
            if (size < 0) {
                return false;
            }
            stack = stack.substr(0,size);
        }
    }
    
    if (size > 0) {
        return false;
    }
    return true;
}

//21. Merge Two Sorted Lists
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode head(0);
    ListNode *p = &head;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            p->next = l1;
            l1 = l1->next;
        }else {
            p->next = l2;
            l2 = l2->next;
        }
        p = p->next;
    }
    if (l1 != nullptr) {
        p->next = l1;
    }
    if (l2 != nullptr) {
        p->next = l2;
    }
    return head.next;
}

//22. Generate Parentheses
void generateParenthesisPart(vector<string> &ans, int rn, int ln, int n, string s) {
    if (rn == n) {
        ans.push_back(s);
        return;
    }
    if (ln < n) {
        generateParenthesisPart(ans, rn, ln + 1, n, s + "(");
    }
    if (rn < ln) {
        generateParenthesisPart(ans, rn + 1, ln, n, s + ")");
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> ans;
    generateParenthesisPart(ans, 0, 0, n, "");
    return ans;
}

//23. Merge k Sorted Lists
ListNode* mergeKLists(vector<ListNode*>& lists) {
    int k = (int)lists.size();
    if (k == 0) {
        return nullptr;
    }
    while (k > 1) {
        for (int i = 0; i < k/2; i++) {
            lists[i] = mergeTwoLists(lists[i], lists[k - 1 - i]);
        }
        k = (k+1)/2;
    }
    return lists.front();
}

//24. Swap Nodes in Pairs
ListNode* swapPairs(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *p = head;
    ListNode *q = head->next;
    head = q;
    ListNode *r = p;
    p->next = q->next;
    q->next = p;
    p = p->next;
    while (p != nullptr) {
        q = p->next;
        if (q == nullptr) {
            break;
        }
        r->next = q;
        r = p;
        p->next = q->next;
        q->next = p;
        p = p->next;
    }
    return head;
}

//25. Reverse Nodes in k-Group 
ListNode* reverseKGroup(ListNode* head, int k) {
    if(k == 1) return head;
    ListNode preHead(-1);
    preHead.next = head;
    ListNode *p, *q, *pre;
    pre = &preHead;
    int n = 0;
    while (head != nullptr) {
        n++;
        head = head->next;
    }
    while (n >= k) {
        p = pre->next;
        q = p->next;
        for (int i = 1; i < k; i++) {
            p->next = q->next;
            q->next = pre->next;
            pre->next = q;
            q = p->next;
        }
        pre = p;
        n -= k;
    }
    return preHead.next;
}

int main(int argc, const char * argv[]) {
    return 0;
}
