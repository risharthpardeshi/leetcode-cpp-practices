//Runtime: 516 ms, faster than 5.03% of C++ online submissions for Range Sum Query - Mutable.
//Memory Usage: 16.5 MB, less than 100.00% of C++ online submissions for Range Sum Query - Mutable.
class NumArray {
public:
    vector<int> nums;
    vector<int> sum;
    
    NumArray(vector<int>& nums) {
        this->nums = nums;
        this->sum = vector<int>(nums.size(), 0);
        for(int i = 0; i < nums.size(); i++){
            sum[i] = ((i-1>=0)?sum[i-1]:0) + nums[i];
        }
    }
    
    void update(int i, int val) {
        for(int cur = i; cur < sum.size(); cur++){
            sum[cur] += (val - nums[i]);
        }
        nums[i] = val;
    }
    
    int sumRange(int i, int j) {
        return sum[j] - ((i-1>=0)?sum[i-1]:0);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */
 
//Approach 2: Sqrt Decomposition
//Runtime: 52 ms, faster than 38.63% of C++ online submissions for Range Sum Query - Mutable.
//Memory Usage: 16.6 MB, less than 100.00% of C++ online submissions for Range Sum Query - Mutable.
//time: preprocessing - O(n), range sum query - O(sqrt(n)), update query - O(1)
//space: O(sqrt(n))
class NumArray {
public:
    vector<int> blocks;
    vector<int> nums;
    int len;
    
    NumArray(vector<int>& nums) {
        this->nums = nums;
        /*
        9 -> 3
        10 -> 4
        */
        if(nums.size() == 0){
            this->len = 0;
        }else{
            this->len = ceil(nums.size()/sqrt(nums.size()));
        }
        this->blocks = vector<int>(len, 0);
        for(int i = 0; i < nums.size(); i++){
            blocks[i/len] += nums[i];
        }
    }
    
    void update(int i, int val) {
        int blockId = i/len;
        blocks[blockId] += (val - nums[i]);
        nums[i] = val;
    }
    
    int sumRange(int i, int j) {
        int sum = 0;
        
        int startBlock = i/len, endBlock = j/len;
        
        if(startBlock == endBlock){
            for(int k = i; k <= j; k++){
                sum += nums[k];
            }
        }else{
            /*
            startBlock+1: the next block's id
            (startBlock+1)*len: the next block's start position
            (startBlock+1)*len-1: the current block's end position
            */
            for(int k = i; k <= (startBlock+1)*len -1; k++){
                sum += nums[k];
            }
            for(int k = startBlock+1; k <= endBlock-1; k++){
                sum += blocks[k];
            }
            for(int k = endBlock*len; k <= j; k++){
                sum += nums[k];
            }
        }
        
        return sum;
    }
};

//Approach 3: Segment Tree
//Runtime: 44 ms, faster than 50.75% of C++ online submissions for Range Sum Query - Mutable.
//Memory Usage: 16.7 MB, less than 100.00% of C++ online submissions for Range Sum Query - Mutable.
//Build segment tree - time O(n), space O(n)
//Update segment tree - time O(logn), space O(1)
//Range Sum Query - time O(logn), space O(1)
class NumArray {
public:
    vector<int> tree;
    int n;
    
    NumArray(vector<int>& nums) {
        if(nums.size() > 0){
            n = nums.size();
            buildTree(nums);
        }
    }
    
    void buildTree(vector<int>& nums){
        tree = vector<int>(n*2);
        //tree[n ... 2n-1] = nums[0 ... n-1]
        for(int i = n, j = 0; i < n*2; i++, j++){
            tree[i] = nums[j];
        }
        /*
        tree[n-1] = tree[2n-2] + tree[2n-1]
        if n = 8
        tree[7] = tree[14] + tree[15]
        tree[6] = tree[12] + tree[13]
        tree[5] = tree[10] + tree[11]
        tree[4] = tree[8] + tree[9]
        
        tree[3] = tree[6] + tree[7]
        tree[2] = tree[4] + tree[5]
        
        tree[1] = tree[2] + tree[3]
        
        if n = 3
        tree[2] = tree[4] + tree[5]
        tree[1] = tree[2] + tree[3] //total sum of leaves
        */
        for(int i = n-1; i > 0; i--){
            tree[i] = tree[i*2] + tree[i*2+1];
        }
    };
    
    void update(int i, int val) {
        //recall that the leaf node takes tree[n ... 2n-1]
        i += n;
        tree[i] = val;
        while(i > 0){
            int left = i;
            int right = i;
            if(i % 2 == 0){
                //it's left ndoe
                right = i+1;
            }else{
                //it's right node
                left = i-1;
            }
            tree[i/2] = tree[left] + tree[right];
            i /= 2;
        }
    }
    
    int sumRange(int i, int j){
        //recall that the leaf node takes tree[n ... 2n-1]
        i += n;
        j += n;
        
        int sum = 0;
        
        while(i <= j){
            // cout << "[" << i << ", " << j << "]" << endl;
            if(i % 2 == 1){
                /*
                if i is right child of its parent,
                then we cannot use its parent's value
                */
                // cout << "l: " << i << endl;
                sum += tree[i];
                i++;
            }
            if(j % 2 == 0){
                /*
                if r is left child of its parent,
                then we cannot use its parent's value
                */
                // cout << "r: " << j << endl;
                sum += tree[j];
                j--;
            }
            i /= 2;
            j /= 2;
        }
        
        return sum;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */