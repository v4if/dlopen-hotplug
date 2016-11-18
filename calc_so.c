/*
* @Author: v4if
* @Date:   2016-11-15 21:38:49
* @Last Modified by:   root
* @Last Modified time: 2016-11-15 21:42:14
*/

float
add(float v1, float v2) {
	return v1 + v2;
}

float
sub(float v1, float v2) {
	return v1 - v2;
}

float
mul(float v1, float v2) {
	return v1 * v2;
}

float
div(float v1, float v2) {
	if (v2 == 0)
	{
		return -1;
	}
	return v1 / v2;
}
