#pragma once

class FilterTIG
{
public:
	void update(CMat &w);	

	// For a W by H gradient magnitude map, find a W-7 by H-7 CV_32F matching score map
	Mat matchTemplate(const Mat &mag1u); 
	
	inline float dot(const INT64 tig1, const INT64 tig2, const INT64 tig4, const INT64 tig8);

public:
	void reconstruct(Mat &w); // For illustration purpose

private:
	static const int NUM_COMP = 2; // Number of components
	static const int D = 64; // Dimension of TIG
	INT64 _bTIGs[NUM_COMP]; // Binary TIG features
    
    // _coeffs1 里面存储的是 w 二值化后的系数 βi。对应论文中的公式4.因为论文设置 Nw = 2；
    // 所以，NUM_COMP 就等于 2；
	float _coeffs1[NUM_COMP]; // Coefficients of binary TIG features

	// For efficiently deals with different bits in CV_8U gradient map
	float _coeffs2[NUM_COMP], _coeffs4[NUM_COMP], _coeffs8[NUM_COMP]; 
};


inline float FilterTIG::dot(const INT64 tig1, const INT64 tig2, const INT64 tig4, const INT64 tig8)
{
    // __popcnt64 Counts the number of one bits (population count) in a 16-, 32-, or 64-byte unsigned integer.
	INT64 bcT1 = __popcnt64(tig1);
	INT64 bcT2 = __popcnt64(tig2);
	INT64 bcT4 = __popcnt64(tig4);
	INT64 bcT8 = __popcnt64(tig8);
    
	// 根据论文，作者设置 Nw =2 ; Ng = 4。再根据公式5，这里分别用 << 1,2,3,4 代表四种 2^1,2^2,2^3,2^4.
    // __popcnt64(_bTIGs[0] & tig1) 是二进制内积的计算方法。显然，根据二进制的特点，二进制向量对应元素相乘
    // 就等价于 “ & ” 操作。然后把所有的 “ 1 ” 加起来，就对应 __popcnt64 操作。
	INT64 bc01 = (__popcnt64(_bTIGs[0] & tig1) << 1) - bcT1; // 这里的 << 1，对应公式 6 或 4 中的内积乘以 2.
	INT64 bc02 = ((__popcnt64(_bTIGs[0] & tig2) << 1) - bcT2) << 1;
	INT64 bc04 = ((__popcnt64(_bTIGs[0] & tig4) << 1) - bcT4) << 2;
	INT64 bc08 = ((__popcnt64(_bTIGs[0] & tig8) << 1) - bcT8) << 3;

	INT64 bc11 = (__popcnt64(_bTIGs[1] & tig1) << 1) - bcT1;
	INT64 bc12 = ((__popcnt64(_bTIGs[1] & tig2) << 1) - bcT2) << 1;
	INT64 bc14 = ((__popcnt64(_bTIGs[1] & tig4) << 1) - bcT4) << 2;
	INT64 bc18 = ((__popcnt64(_bTIGs[1] & tig8) << 1) - bcT8) << 3;
    
    // 这里的 _coeffs1[0] 和 _coeffs1[1] 就是公式 6 中的 βi。因为论文设置 Nw = 2。
    // 所以，_coeffs1 中就只存有两个系数。
	return _coeffs1[0] * (bc01 + bc02 + bc04 + bc08) + _coeffs1[1] * (bc11 + bc12 + bc14 + bc18);
}
