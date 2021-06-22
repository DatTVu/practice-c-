class Solution
{
public:
    void rotate(vector<int> &nums, int k)
    {
        std::size_t size_ = nums.size();
        k = k % size_;
        int cnt = 0;
        int startIdx;
        int nextIdx;
        for (startIdx = 0; cnt < size_; ++startIdx)
        {
            nextIdx = startIdx;
            int preVal = nums[startIdx];
            int nextVal = 0;
            do
            {
                nextIdx = (nextIdx + k) % size_;
                nextVal = nums[nextIdx];
                nums[nextIdx] = preVal;
                preVal = nextVal;
                cnt++;
            } while (startIdx != nextIdx);
        }
    }
};