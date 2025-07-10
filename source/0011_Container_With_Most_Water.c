/* 11 Container with most water */

int maxArea(int *height, int heightSize)
{
    int L = 0;
    int R = heightSize - 1;
    int width = (height[L] < height[R]) ? height[L] : height[R];

    int area = (R - L) * width;
    int maxarea = area;

    if (heightSize == 2)
        return maxarea;

    while (L < R) {
        if (height[L] < height[R])
            L++;
        else
            R--;

        width = (height[L] < height[R]) ? height[L] : height[R];

        area = (R - L) * width;
        maxarea = (maxarea > area) ? maxarea : area;
    }
    return maxarea;
}