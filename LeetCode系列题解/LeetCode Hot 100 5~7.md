<font color = black size = 4 face  = "微软雅黑">LeetCode Top 100 题解

---
#### 1. 最长回文子串
<font color = black size = 3 face  = "微软雅黑">给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
><font color = black size = 3 face  = "微软雅黑">示例 1：
输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。

><font color = black size = 3 face  = "微软雅黑">示例 2：
输入: "cbbd"
输出: "bb"

><font color = black size = 3 face  = "微软雅黑">回文串就是正读反读都一样的字符串，最长回文串就是在一个字符串中最长的回文串，想要找到回文串，一眼以每一个字符为中心，向两边扩散来查找回文串，时间复杂度为O（n^2^）,需要注意的就是奇偶回文串，对于奇数形式的，从遍历到的位置为中心向两边扩展；对于偶数形式的，以当前遍历到的元素和下一个元素为回文串的最中间的两个字符，向两边扩展搜索。
```cpp
class Solution {
public:
	void searchPalindrome(string s, int left, int right, int& start, int& max_len)
	{
		//向两边扩散
		while (left >= 0 && right < s.size() && s[left] == s[right])
		{
			left--;
			right++;
		}

		//判断找到的字符串是否是最长字符串
		if (max_len < right - left - 1)
		{
			start = left + 1;
			max_len = right - left - 1;
		}
	}

	string longestPalindrome(string s) {
		if (s.size() < 2)
			return s;

		int l = s.size(), max_len = 0, start = 0;

		for (int i = 0; i < l - 1; ++i)
		{
			searchPalindrome(s, i, i, start, max_len);//奇数形式
			searchPalindrome(s, i, i + 1, start, max_len);//偶数形式
		}

		return s.substr(start,max_len);
	}
};
```
><font color = black size = 3 face  = "微软雅黑">若是不实用子函数，避免函数开销的话，直接在一个函数中搞定。定义start和max_len，分别表示最长回文子串的起点和长度，遍历s中字符时，先判断剩余的字符数是否小于等于max_len的一半，若是则表明从当前到末尾到子串是半个回文串，那么整个回文串长度最多也就是max_len，也就是说当前位置之后的字符没有搜索的意义，直接break即可。否则继续判断，利用两个变量left和right指向当前位置，然后向右遍历跳过重复项，然后更新max_len和start。
```cpp
class Solution {
public:
	string longestPalindrome(string s) {
		if (s.size() < 2)
			return s;

		int l = s.size(), max_len = 0, start = 0;
		
		for (int i = 0; i < l;)
		{
			if (l - i <= max_len / 2)
				break;

			int left = i, right = i;
			while (right < l - 1 && s[right + 1] == s[right])//考虑到偶数位回文串，跳过相同的字符
				++right;

			i = right + 1;
			while (right < l - 1 && left > 0 && s[left - 1] == s[right + 1])
			{
				++right;
				--left;
			}

			if (max_len < right - left + 1)
			{
				max_len = right - left + 1;
				start = left;
			}
		}

		return s.substr(start,max_len);
	}
};
```
><font color = black size = 3 face  = "微软雅黑">利用动态规划也可解决这个问题。维护一个二维数组dp，其中`dp[i][j]`表示字符串区间`[i,j]`是否为回文串，当i = j时，只有一个字符，肯定是回文串，如果i= j + 1,说明是相邻字符，此时需要判断s[i]是否等于s[j]，如果i和j不相邻，即i - j > 2时，除了判断s[i]和s[j]相等之外，dp[i + 1][j - 1]若为真，就是回文串，可得<br>
><font color = black size = 3 face  = "微软雅黑">dp[i,j] = 1&emsp;&emsp;&emsp; &emsp;&emsp;&emsp; &emsp;&emsp;&emsp; &emsp;&emsp;&emsp; &emsp;&emsp;&emsp; if i == j<br>
> &emsp;&emsp;&emsp; = s[i] == s[j]  &emsp;&emsp;&emsp; &emsp;&emsp;&emsp; &emsp;&emsp;&emsp; &emsp;&ensp; if j = i +1<br>
>  &emsp;&emsp;&emsp;= s[i] == s[j] && dp[i+1][j-1]   &emsp;&emsp;&emsp; &emsp;if j > i + 1 <br>
```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        int n = s.size(), dp[n][n] = {0}, left = 0, len = 1;
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
            for (int j = 0; j < i; ++j) {
                dp[j][i] = (s[i] == s[j] && (i - j < 2 || dp[j + 1][i - 1]));
                if (dp[j][i] && len < i - j + 1) {
                    len = i - j + 1;
                    left = j;
                }
            }
        }
        return s.substr(left, len);
    }
};
```
><font color = black size = 3 face  = "微软雅黑">马拉车算法，时间复杂度为O(n)
```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        string t ="$#";
        for (int i = 0; i < s.size(); ++i) {
            t += s[i];
            t += '#';
        }
        int p[t.size()] = {0}, id = 0, mx = 0, resId = 0, resMx = 0;
        for (int i = 1; i < t.size(); ++i) {
            p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
            while (t[i + p[i]] == t[i - p[i]]) ++p[i];
            if (mx < i + p[i]) {
                mx = i + p[i];
                id = i;
            }
            if (resMx < p[i]) {
                resMx = p[i];
                resId = i;
            }
        }
        return s.substr((resId - resMx) / 2, resMx - 1);
    }
};
```
- [最长回文子串](https://leetcode-cn.com/problems/longest-palindromic-substring/submissions/)
#### 2.正则表达式匹配
<font color = black size = 3 face  = "微软雅黑">给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 `.` 和 `*` 的正则表达式匹配。
><font color = black size = 3 face  = "微软雅黑">`.` 匹配任意单个字符
`*` 匹配零个或多个前面的那一个元素

<font color = black size = 3 face  = "微软雅黑">所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。<br>
<font color = black size = 3 face  = "微软雅黑">说明:<br>
- s 可能为空，且只包含从 a-z 的小写字母。
- p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。

><font color = black size = 3 face  = "微软雅黑">示例 1：<br>
输入:<br>
s = "aa"<br>
p = "a"<br>
输出: false<br>
解释: "a" 无法匹配 "aa" 整个字符串。<br>

><font color = black size = 3 face  = "微软雅黑">示例 2:<br>
输入:<br>
s = "aa"<br>
p = "a`*`"<br>
输出: true<br>
解释: 因为 `*` 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 `a`。因此，字符串 "aa" 可被视为 'a' 重复了一次。

><font color = black size = 3 face  = "微软雅黑">示例 3:<br>
输入:<br>
s = "ab"<br>
p = ".`*`"<br>
输出: true<br>
解释: ".*" 表示可匹配零个或多个（`*`）任意字符（`.`）。

><font color = black size = 3 face  = "微软雅黑">示例 4:<br>
输入:<br>
s = "aab"<br>
p = "c`*`a`*`b"<br>
输出: true<br>
解释: 因为 `*` 表示零个或多个，这里 `c` 为 0 个, `a` 被重复一次。因此可以匹配字符串 "aab"。

><font color = black size = 3 face  = "微软雅黑">示例 5:<br>
输入:<br>
s = "mississippi"<br>
p = "mis`*`is`*`p`*`."<br>
输出: false<br>

><font color = black size = 3 face  = "微软雅黑">用递归Recursion解决：若p为空，若s也为空，返回true，反之返回false；若p的长度为1，若s的长度也为1,且相同或是p为`.`则返回true，反之返回false；若p的第二个字符不为`*`，若s为空则返回false，否则判断首字符是否匹配，且从各自的第二个字符开始调用递归函数匹配；若p的第二个字符为`*`，则进行循环：条件为若s不为空且首字符匹配（包括p[0]为点），调用递归函数匹配s和去掉前两个字符的p，若匹配的返回true，否则s去掉字母，继续进行循环。返回调用 递归函数匹配s和去掉前两个字符的p的结果。
```cpp
class Solution {
public:
	bool isMatch(string s, string p) {
		if (p.empty())
		{
			return s.empty();
		}

		if (p.size() == 1)
		{
			return (s.size() == 1 && (s[0] == p[0] || p[0] == '.'));
		}

		if (p[1] != '*')
		{
			if (s.empty())
			{
				return false;
			}
			return (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));
		}

		while (!s.empty() && (s[0] == p[0] || p[0] == '.'))
		{
			if (isMatch(s, p.substr(2)))
				return true;
			s = s.substr(1);
		}

		return isMatch(s, p.substr(2));
	}
};
```
><font color = black size = 3 face  = "微软雅黑">更加简洁的方法：先判断p是否为空，若为空则根据s为空的情况返回结果。当p的第二个字符为`*`号时，由于`*`前面的字符的个数可以任意，可以为0，则先用递归来调用为0的状况。
```cpp
class Solution {
public:
	bool isMatch(string s, string p) 
	{
		if (p.empty()) 
			return s.empty();
		
		if (p.size() > 1 && p[1] == '*') 
		{
			return isMatch(s, p.substr(2)) || (!s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p));
		}
		else 
		{
			return !s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));
		}
	}
};
```
><font color = black size = 3 face  = "微软雅黑">使用DP来解决，定义一个二位的DP数组，dp[i][j]表示s[0,i]和p[0,j]是否match，则有一下三种情况：
1.  P[i][j] = P[i - 1][j - 1], if p[j - 1] != `*`&& (s[i - 1] `==` p[j - 1] || p[j - 1]` ==` `.`);
2.  P[i][j] = P[i][j - 2], if p[j - 1] `==` `*` and the pattern repeats for 0 times;
3.  P[i][j] = P[i - 1][j] && (s[i - 1] `==` p[j - 2] || p[j - 2] `== ` `.`), if p[j - 1] `==` `*` and the pattern repeats for at least 1 times.
```cpp
class Solution {
public:
	bool isMatch(string s, string p)
	{
		int m = s.size(), n = p.size();
		vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

		dp[0][0] = true;
		for (int i = 0; i <= m; ++i) 
		{
			for (int j = 1; j <= n; ++j) 
			{
				if (j > 1 && p[j - 1] == '*') 
				{
					dp[i][j] = dp[i][j - 2] || (i > 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j]);
				}
				else 
				{
					dp[i][j] = i > 0 && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
				}
			}
		}

		return dp[m][n];
	}
};
```
- [正则表达式匹配](https://leetcode-cn.com/problems/regular-expression-matching/)
#### 3.盛最多水的容器
<font color = black size = 3 face  = "微软雅黑">给你 n 个非负整数 a~1~，a~2~，...，a~n~，每个数代表坐标中的一个点 (i, a~i~) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, a~i~) 和 (i, 0)。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
说明：你不能倾斜容器，且 n 的值至少为 2。![在这里插入图片描述](https://img-blog.csdnimg.cn/20200325180916278.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2t1aXNpOTU=,size_16,color_FFFFFF,t_70)
图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
><font color = black size = 3 face  = "微软雅黑">定义两个指针分别指向数组的左右两边，然后两个指针向中间搜索，每移动一次计算值并和结果比较去较大值。
```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int res = 0, i = 0, j = height.size() - 1;
        
        while (i < j) 
        {
            res = max(res, min(height[i], height[j]) * (j - i));
            height[i] < height[j] ? ++i : --j;
        }
        return res;
    }
};
```
><font color = black size = 3 face  = "微软雅黑">对上述代码进行优化，若高度相同则直接移动，不用计算容量。
```cpp
class Solution {
public:
    int maxArea(vector<int>& height) 
    {
        int res = 0, i = 0, j = height.size() - 1;
        
        while (i < j) 
        {
            int h = min(height[i], height[j]);
            res = max(res, h * (j - i));
            while (i < j && h == height[i]) ++i;
            while (i < j && h == height[j]) --j;
        }
        return res;
    }
};
```
- [盛最多水的容器](https://leetcode-cn.com/problems/container-with-most-water/)