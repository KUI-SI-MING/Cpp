<font color = black size = 4 face  = "微软雅黑">LeetCode Top 100 题解

---
#### 1. 两数之和
<font color = black size = 3 face  = "微软雅黑">给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

<font color = black size = 3 face  = "微软雅黑">你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。

><font color = black size = 3 face  = "微软雅黑">来源：力扣（LeetCode）
链接：[https://leetcode-cn.com/problems/two-sum/](https://leetcode-cn.com/problems/two-sum/)

><font color = black size = 3 face  = "微软雅黑">考虑到不能重复利用数组中的同样的元素就不能利用前后元素相加的方法判断是否存在目标，所以从相反面考虑先利用`target`减去`nums`里的某个元素，再在剩下的元素中寻找与差值相同的元素返回下标，若都不同则返回空的`vector`，这样的时间复杂度为O( n^2) ,看了下资料我这应该是取巧的暴力法，虽然没有超时，但是不高效

```cpp
class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int> res;
		if (nums.size() == 0)
			return res;

		int oth = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			oth = target - nums[i];
			res.push_back(i);
			for (int j = i + 1; j < nums.size(); j++)
			{
				if (oth == nums[j])
				{
					res.push_back(j);
					return res;
				}
			}
			res.clear();
		}
        return res;
	}
};
```
><font color = black size = 3 face  = "微软雅黑">要想用线性的时间复杂度解决问题需要我们考虑用空间换取时间，用HashMap构建元素和坐标的映射关系，HashMap是常数级的查找效率，这样我们遍历数组，然后用target减去遍历到的元素得到另外一个数字，再在HashMap中查找该数字，但是需注意判断找到的数字是不是第一个数字，这样也就是省去了我上边代码的里层循环
```cpp
class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> np;
		vector<int> res;

		for (int i = 0; i < nums.size(); i++)
		{
			np[nums[i]] = i;
		}

		for (int i = 0; i < nums.size(); i++)
		{
			int tmp = target - nums[i];
			if (np.count(tmp) && np[tmp] != i)
			{
				res.push_back(i);
				res.push_back(np[tmp]);
                break;
			}
		}

		return res;

	}
};
```
><font color = black size = 3 face  = "微软雅黑">看了下还有大佬将两个for循环合并成一个，贴上代码
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m;
        for (int i = 0; i < nums.size(); ++i) {
            if (m.count(target - nums[i])) {
                return {i, m[target - nums[i]]};
            }
            m[nums[i]] = i;
            
        }
        return {};
    }
};
```
#### 2. 两数相加
<font color = black size = 3 face  = "微软雅黑">给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

<font color = black size = 3 face  = "微软雅黑">如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

<font color = black size = 3 face  = "微软雅黑">您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

><font color = black size = 3 face  = "微软雅黑">示例：
输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807

> <font color = black size = 3 face  = "微软雅黑">来源：力扣（LeetCode）
链接：[https://leetcode-cn.com/problems/add-two-numbers](https://leetcode-cn.com/problems/add-two-numbers/)

><font color = black size = 3 face  = "微软雅黑">建立一个新链表，然后从输入的两个链表处获取相加元素，设置carry记录进位信息，由于最低位在链表的开头，则可以直接在遍历链表的同时进行加法，由于链表可能为空，所以在取当前结点值的时候，先判断一下，若为空则取0，否则取结点值。然后把两个结点值相加，同时还要加上进位 carry。然后更新 carry，直接 sum/10 即可，然后以 sum%10 为值建立一个新结点，连到 prev后面，然后 prev移动到下一个结点。之后再更新两个结点，若存在，则指向下一个位置。循环退出之后，最高位的进位问题要最后特殊处理一下，若 carry 为1，则再建一个值为1的结点
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode dum(-1);
		int carry = 0;
		ListNode *prev = &dum;
		for (ListNode* pa = l1, *pb = l2; pa != nullptr || pb != nullptr;
			pa = pa == nullptr ? nullptr : pa->next,
			pb = pb == nullptr ? nullptr : pb->next,
			prev = prev->next)
		{
			const int ai = pa == nullptr ? 0 : pa->val;
			const int bi = pb == nullptr ? 0 : pb->val;
			const int value = (ai + bi + carry) % 10;
			carry = (ai + bi + carry) / 10;
			prev->next = new ListNode(value);
		}
		if (carry > 0)
			prev->next = new ListNode(carry);

		return dum.next;
	}
};
```
#### 3. 无重复字符的最长子串
<font color = black size = 3 face  = "微软雅黑">给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

><font color = black size = 3 face  = "微软雅黑">示例 1:
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:

><font color = black size = 3 face  = "微软雅黑">输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:

><font color = black size = 3 face  = "微软雅黑">输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

><font color = black size = 3 face  = "微软雅黑">来源：力扣（LeetCode）
链接：[https://leetcode-cn.com/problems/longest-substring-without-repeating-characters](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters)

><font color = black size = 3 face  = "微软雅黑">
```cpp
class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		const int ASC = 256;
		int last[ASC];//记录字符上次出现的位置
		int start = 0;//记录当前字串的起始位置

		fill(last, last+ASC, -1);
		int maxlen = 0;
		for (int i = 0; i < s.size(); i++)
		{
				if (last[s[i]] >= start)
				{
                    //s[i]又出现
					maxlen = max(i - start, maxlen);
					start = last[s[i]] + 1;
				}
				last[s[i]] = i;
		}

		return max((int)s.size() - start, maxlen);//最后一次
	}
};
```
#### 4.寻找两个有序数组的中位数
<font color = black size = 3 face  = "微软雅黑">给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。
<font color = black size = 3 face  = "微软雅黑">请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
<font color = black size = 3 face  = "微软雅黑">你可以假设 nums1 和 nums2 不会同时为空。
><font color = black size = 3 face  = "微软雅黑">来源：力扣（LeetCode）
链接：[https://leetcode-cn.com/problems/median-of-two-sorted-arrays](https://leetcode-cn.com/problems/median-of-two-sorted-arrays)

><font color = black size = 3 face  = "微软雅黑">示例 1:
nums1 = [1, 3]
nums2 = [2]
则中位数是 2.0

><font color = black size = 3 face  = "微软雅黑">示例 2:
nums1 = [1, 2]
nums2 = [3, 4]
则中位数是 (2 + 3)/2 = 2.5

><font color = black size = 3 face  = "微软雅黑">&emsp;&emsp;本题的目的是查找出两个有序数组中的中位数，同时限制时间复杂度为O(log(m + n))，首先明确中位数的概念：如果某个有序数组长度是奇数，则中位数就是最中间的那个数，如果数组长度是偶数，中位数就是最中间的两个数的平均值。对于两个有序数组同样适用，例如设两个有序数组的长度分别为m和n,`m+n`的奇偶不确定，我们分别找第`(m+n+1) / 2`个和`(m+n+2)/2`个，然后求其平均值即可得到中位数，若`m+n`为奇数，则`(m+n+1) / 2`和`(m+n+2)/2`的值相等，其平均值是其本身；其次需要考虑的是时间复杂为 O(log (m+n))，因此需要避免一切超过这个时间复杂度的操作，如：将两个数组合并操作；拷贝数组等；股从这个时间复杂度的就是二分法了，所以需要考虑到的就是如何在两个数组间使用二分查找法。
><font color = black size = 3 face  = "微软雅黑">&emsp;&emsp;定义一个函数在两个有序数组中查找第k个元素，使用i和j标记数组nums1和nums2的起始位置。首先考虑两个数组中的特殊情况：当某一个数组的起始位置大于等于数组长度时，说明其所有的数字已经被淘汰，然后在另一个数组中查找；如果K=1，需要比较nums1和nums2的起始位置i和j上的数字即可。然后考虑一般情况：采用二分法，对K进行二分，即分别在nums1和nums2里查找第K/2个元素。由于数组长度不定，需要考虑到数组是否存在第K/2个数字，若存在就取出，若不存在就赋值整形最大值（以在nums1或nums2中先排除K/2个较小的数字，判断的依据就是看midVal1和midVal2谁更小，若某个数组长度不到K/2则无法淘汰，因此将其对应的idVal值设为整形最大值，以保证其不会被排除）。
><font color = black size = 3 face  = "微软雅黑">&emsp;&emsp;还需要考虑到若两个数组都不存在第K/2个元素，这种情况在此题中不可能，因为K不是任意给的，而是m+n的中间值，所以必定会有一个数组是存在第K/2个数字。至此，比较两个数组的第K/2小的数字midVal1和midVal2的大小，若nums1的第K/2个数字小，那么排除nums1中的前K/2个元素，将nums1的起始位置i后移K/2个同时K自减K/2，调用递归。
```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size(), left = (m + n + 1) / 2, right = (m + n + 2) / 2;
        return (findKth(nums1, 0, nums2, 0, left) + findKth(nums1, 0, nums2, 0, right)) / 2.0;
    } 
      int findKth(vector<int>& nums1, int i, vector<int>& nums2, int j, int k)     			   {
        if (i >= nums1.size()) return nums2[j + k - 1];
        if (j >= nums2.size()) return nums1[i + k - 1];
        if (k == 1) return min(nums1[i], nums2[j]);
        int midVal1 = (i + k / 2 - 1 < nums1.size()) ? nums1[i + k / 2 - 1] : INT_MAX;
        int midVal2 = (j + k / 2 - 1 < nums2.size()) ? nums2[j + k / 2 - 1] : INT_MAX;
        if (midVal1 < midVal2) {
            return findKth(nums1, i + k / 2, nums2, j, k - k / 2);
        } else {
            return findKth(nums1, i, nums2, j + k / 2, k - k / 2);
        }
    }
};
```
><font color = black size = 3 face  = "微软雅黑">&emsp;&emsp;跨过题目要求的时间复杂度的要求，考虑使用新的数组来进行处理,这样就不要用起始位置变量了，不过拷贝数组的操作可能会增加时间复杂度，也许会超出限制。同一样的先考虑特殊情况：数组是否为空；当K=1时的查找。取出两个数组的第K/2个坐标i和j，为了避免没有第K/2个元素，每次都和数组长度进行比较，取出较小值。
```cpp
class Solution {
public:
	int findKth(vector<int> nums1, vector<int> nums2, int k)
	{
		if (nums1.empty())
			return nums2[k - 1];

		if (nums2.empty())
			return nums1[k - 1];

		if (k == 1)
		{
			return min(nums1[0], nums2[0]);
		}

		int i = min((int)nums1.size(), k / 2);
		int j = min((int)nums2.size(), k / 2);

		if (nums1[i - 1] > nums2[j - 1])
		{
			return findKth(nums1, vector<int>(nums2.begin() + j, nums2.end()), k - j);
		}
		else
		{
			return findKth(vector<int>(nums1.begin() + i, nums1.end()),nums2, k - i);
		}
		return 0;
	}

	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int m = nums1.size(), n = nums2.size();

		return (findKth(nums1, nums2, (m + n + 1) / 2) + findKth(nums1, nums2, (m + n + 2) / 2)) / 2.0;
	}
};
```
><font color = black size = 3 face  = "微软雅黑">&emsp;&emsp;这个题还可以用迭代形式的二分搜索法。
```cpp

class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int m = nums1.size(), n = nums2.size();

		if (m < n) 
			return findMedianSortedArrays(nums2, nums1);
		if (n == 0) 
			return ((double)nums1[(m - 1) / 2] + (double)nums1[m / 2]) / 2.0;
		int left = 0, right = n * 2;
		
		while (left <= right) 
		{
			int mid2 = (left + right) / 2;
			int mid1 = m + n - mid2;

			double L1 = mid1 == 0 ? INT_MIN : nums1[(mid1 - 1) / 2];
			double L2 = mid2 == 0 ? INT_MIN : nums2[(mid2 - 1) / 2];
			double R1 = mid1 == m * 2 ? INT_MAX : nums1[mid1 / 2];
			double R2 = mid2 == n * 2 ? INT_MAX : nums2[mid2 / 2];

			if (L1 > R2) 
				left = mid2 + 1;
			else if 
				(L2 > R1) right = mid2 - 1;
			else 
				return (max(L1, L2) + min(R1, R2)) / 2;
		}
		return -1;
	}
};
```